---
layout: post
title: Auto test of APP
categories: Python
description: 笔记
keywords: Python, autotest, APP
---

自动卸载、安装系统app，自动测试

## 链接

* [Python 自动卸载、安装系统app，自动测试](https://tsbxmw.github.io/2016/11/13/Python-modeltest/)

##  内容

  * 获取app
  * 自动卸载对应app
  * 安装app

### 获取app

```python

        #coding=UTF-8
        import datetime, os
        import ftplib
        import shutil
        import sys
        import time, re
        import zipfile
        class FTP(object):
            def __init__(self, address, user, pwd):
                self.host, self.port = self.__parseAddress(address)
                self.user=user
                self.passwd = pwd
            
            def __parseAddress(self, add):
                add = add.lower()
                if add.startswith("ftp://"):
                    add = add[6:]
                addSplit = add.split(":")
                if len(addSplit) == 2:
                    return addSplit[0], int(addSplit[1])
                else:
                    return addSplit[0], 21
                
            def connect(self):
                self.ftp= ftplib.FTP()
                self.ftp.set_debuglevel(0)
                self.ftp.set_pasv(0)
                self.ftp.connect(self.host,self.port)
                self.ftp.login(self.user, self.passwd)
            
            def disconnect(self):
                self.ftp.close()
                
            def getDir(self, remote, local):
                self.walk(remote, local)
            
            '''add by mengwei 10192582 20160726'''
            def getzip(self,versionzip,file_ends,local):
                print(local)
               # self.ftp.cwd(remote)
                file_handler=open(local+"\\VERSION"+file_ends, 'wb')
                self.ftp.retrbinary("RETR %s" %(versionzip), file_handler.write)
                file_handler.close()
                return True
            
            def get_dirs_files(self, remote = None):
                
                if remote:
                    self.ftp.cwd(remote)
                dir_res = []
                self.ftp.dir('.', dir_res.append)
                files = [f.split(None, 4)[-1] for f in dir_res if not '<DIR>' in f]
                dirs = [f.split(None, 4)[-1] for f in dir_res if '<DIR>' in f]
                return (files, dirs)
            def walk(self, next_dir, local_dir):
                self.ftp.cwd(next_dir)
                try:
                    os.mkdir(local_dir)
                except OSError:
                    pass
                
                files, dirs = self.get_dirs_files()
                for f in files:
                    print 'get', next_dir, ':', f
                    localPath = os.path.join(local_dir, f)
                    outf = open(localPath, 'wb')
                    try:
                        self.ftp.retrbinary('RETR %s' % f, outf.write)
                    finally:
                        outf.close()
                for d in dirs:
                    self.walk(next_dir+'/'+d, os.path.join(local_dir, d))
        class DownloadVersion(object):
            ftpAddress = "192.168.1.1"
            ftpUser = 'user_name'
            ftpPwd = 'passwd'
            '''file ends and local version dir '''
            file_ends = '' #or .zip
            version_dir = '..\\testdata\\version'
            def __init__(self, local = None):
                if local:
                    self.local = local
                else:
                    self.local = '.'
                self.readConfig()
                    
            def readConfig(self):
                platform = os.getenv("PRODUCT_PLATFORM")
                if platform.lower() == 'mtk':
                   self.versionFileList.append(os.getenv("MTK_FLASH_SCATTER_FILE"))
                
             
            
            def getendsftp(self):
                #ftp = FTP(self.ftpAddress, self.ftpUser, self.ftpPwd)
                #ftp.connect()
            #    print("successful")
                #files, dirs = ftp.get_dirs_files(self.calcVersionPathInFtp(ftp))
                #ftp.disconnect()
                files = os.getenv('VERSION_PATH_IN_FTP')
                
                if(files.endswith(".7z")):
                    self.file_ends = ".7z"
                if(files.endswith(".zip")):
                    self.file_ends = ".zip"
                
            def download(self):
                localDir = os.path.abspath(self.local)
                if os.path.exists(localDir):
                    shutil.rmtree(localDir)
                os.makedirs(localDir)
                ftp = FTP(self.ftpAddress, self.ftpUser, self.ftpPwd)
                ftp.connect()
                filename = os.getenv('VERSION_PATH_IN_FTP')
                ftp.getzip(filename,self.file_ends,localDir)
                
                localDir = os.path.abspath(self.local)
                ftp.disconnect()
                return localDir
            '''add by mengwei10192582 20160756'''
            def unzipfile(self,localversion):
                filename = localversion + self.file_ends
                filedir = localversion
                
                starttime = time.time()
                print ('UNZIP the VERSION')
                print ('debug info : ' + filename + ' + ' + self.version_dir)
                os.system(".\\HaoZip\\HaoZipC e  "+ filename + " -o"+self.version_dir)
                endtime = time.time()
               
        if __name__ == '__main__':
            default_encoding = 'utf-8'
            if sys.getdefaultencoding() != default_encoding:
                reload(sys)
                sys.setdefaultencoding(default_encoding)
            try:
                if os.path.exists("fail.txt"):
                    os.remove("fail.txt")
            except:
                pass
            
            try:
                
                down = DownloadVersion("..\\testdata\\version")
                down.getendsftp()
                print(down.file_ends)
                #down.checkIfVersionComplete(down.file_ends)
                localDir = down.download()
                print "Download version from FTP successfully!"
                print ("debug : " + localDir)
               # localDir = "D:\\SVN\\project\\P817E52_OEM_VDF\\testdata\\version"
                print ("debug : " + localDir+"\\VERSION")
                
                down.unzipfile(localDir+"\\VERSION" )
                
            except Exception, e:
                open("fail.txt", 'w').write(str(e))
                raise Exception(str(e))

```

### 卸载安装app

```python

    #coding=UTF-8
    '''
    author    : mengwei 
    date      : 20160830
    version   : 1.0
    modify    : 20160901 , add some print to make it easy to use
    modify    : 20160913 , add MAPPING_NAME and get the path install from the system filssystem
    modify    : 20160914 , add exception deal 
    '''
    import os
    import sys,time
    import xml.etree.cElementTree as ET
    class Replace(object):
        
        def __init__(self,packagename,apkname):
            self.packagename = os.getenv(packagename) #get the package from the env
            self.apkname = os.getenv(apkname) #get the apkname from the env
            self.pathinstall = None
            self.pathlocal = None
            '''
            package name  : app package name
            path install  : app in system path 
            path local    : app in local path
            '''
        def getlocalpath(self):
            apk_local_path = "..\\testdata\\version\\" #path_py is the version path (apk path )
            print(apk_local_path)
            filelist = os.listdir(apk_local_path)
            print(filelist)
            for i in filelist :
                if i.endswith(".apk"):
                    if "unsigned" in i : #find the unsigned apk 
                        print i
                        print (i+' is the unsigned apk , we need the signed apk now =_=')
                    else :
                        PATH_LOCAL = apk_local_path + i
                        print PATH_LOCAL + ' is the apk what we need to push in the phone !'
                        self.pathlocal=PATH_LOCAL
                        
                        
        '''get path install by info.xml
           add by mengwei 
           date 20160913
           need the info.xml file to get 
           in the new version , do not need the file info.xml
        '''
        def get_path_install(self):
            
                    
            if (self.pathinstall == None):
                print ("get path install from the info files !")
                try:
                    tree = ET.parse("info.xml")
                    root = tree.getroot()
                    print (root.tag,"---",root.attrib)
                    for package in root.findall("package"):
                        if package.get("name") == self.packagename :
                            self.pathinstall = package.find("path_install").text
                            print ("debug info By mw :" + self.pathinstall)
                    
                except Exception , e:
                    raise Exception(str(e))
            else:
                print ("do not need get the path !")
                
        
        
        def find_apk_path(self):
        
            print ("APK_NAME is : " + self.apkname)
            found_apk_in_app = False  #if found the apk in the /system/app , then found_apk_in_app would be True
            has_apk = False #if the dir (/system/app and /system/priv-app ) do not have the apk file then has_apk would be False , else would be True
            
            os.system("adb shell ls /system/app > app.txt") #get the apk list of the /system/app
            os.system("adb shell ls /system/priv-app > priv-app.txt") #get the apk list of the /system/priv-app
            if os.path.exists("app.txt"): # if the app.txt is exist
                apk_app_list = open("app.txt","r")
                for f in apk_app_list.readlines() :
                    #print f
                    if self.apkname in f:
                        apk_dir_path = "/system/app/"+self.apkname
                        os.system("adb shell ls " + apk_dir_path + " > apk_dir.txt")
                        apk_list = open("apk_dir.txt","r")
                        for apk in apk_list.readlines():
                            if apk.endswith(".apk"):
                                self.pathinstall = apk_dir_path  + "/" + apk 
                                has_apk = True
                        apk_list.close()
                        
                        if has_apk == False: # if not exist the apk files , then the path install is ..+ 
                            self.pathinstall = apk_dir_path  + "/" + self.apkname + ".apk"
                        found_apk_in_app  = True
                        
                        
                apk_app_list.close()
            
                print ("--------------------------")
            else :
                print ("Do not find the app.txt ")
            
            if  found_apk_in_app  == False :
                if os.path.exists("priv-app.txt"):
                    apk_priv_list = open("priv-app.txt","r")
                    for g in apk_priv_list.readlines() :
                        #print g
                        if self.apkname in g: 
                            apk_dir_path = "/system/priv-app/" + self.apkname
                            os.system("adb shell ls " + apk_dir_path + " > apk_dir.txt")
                            apk_list = open("apk_dir.txt","r")
                            for apk in apk_list.readlines():
                                if apk.endswith(".apk"):
                                    self.pathinstall = apk_dir_path  + "/" + apk 
                                    has_apk = True
                            
                            apk_list.close()
                            if has_apk == False:
                                self.pathinstall = apk_dir_path  + "/" + self.apkname + ".apk"
                            
                    apk_priv_list.close()    
                    print ("++++++++++++++++++++++++++")
            print ("the apk path in system is :" + self.pathinstall)
            return has_apk
        
        def startreplace(self,has_apk):
            '''os.system("replace_APP.bat " + self.pathinstall + " " + self.packagename + " " + self.pathlocal)'''
            try:
                os.system("adb remount")
                if has_apk == True :
                    os.system("adb shell rm " + self.pathinstall)
                print("start uninstall the apk")
                os.system("adb uninstall " + self.packagename)
                print("start install the apk")
                os.system("adb push " + self.pathlocal + " " + self.pathinstall)
                os.system("adb shell sync")
                os.system("adb reboot")
                print ("wait for the device reboot ...")
                os.system("ping -n 150 127.0.0.1 > ping.temp")
            except Exception , e:
                raise Exception(str(e))
           
    if __name__=='__main__':
        default_encoding = 'utf-8'
        if sys.getdefaultencoding() != default_encoding:
            reload(sys)
            sys.setdefaultencoding(default_encoding)
            
        try:
            packagename = "PACKAGE_NAME"
            apkname = "MAPPING_NAME"
            replace = Replace( packagename,apkname )
            print('Start replace the apk ...')
            #replace.get_path_install()
            has_apk = replace.find_apk_path()
            
            replace.getlocalpath()
            replace.startreplace(has_apk)
        
        
        except Exception , e:
            raise Exception(str(e))


```

### 文中之前的版本info.xml

```xml

    <?xml version="1.0"?>
    <packages>
        <package name="com.android.contacts">
        <path_install>/system/priv-app/Contacts_MB/Contacts_MB.apk</path_install>
        </package>
        <package name="com.zte.camera">
        <path_install>/system/priv-app/Camera_MF/Camera_MF.apk</path_install>
        </package>
        <package name="com.android.settings">
        <path_install>/system/priv-app/Settings_MB/Settings_MB.apk</path_install>
        </package>
        <package name="com.android.dialer">
        <path_install>/system/priv-app/Dialer_MB/Dialer_MB.apk</path_install>
        </package>
        <package name="com.android.email">
        <path_install>/system/priv-app/Email_MB/Email_MB.apk</path_install>
        </package>
        <package name="com.android.exchange">
        <path_install>/system/priv-app/Exchange_MB/Exchange_MB.apk</path_install>
        </package>
    </packages>

```

### LINK
* github python 未上传