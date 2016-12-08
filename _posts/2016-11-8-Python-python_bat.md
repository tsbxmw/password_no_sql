---
layout: post
title: Python Program
categories: Python
description: 笔记
keywords: Python, Markdown, bat
---

将之前写的bat小程序转化为python

## 链接

* [Python 小程序](https://tsbxmw.github.io/2016/11/08/Pyhton-python_bat/)

##  内容

  整个流程就是查找文件中的信息，并根据是否查找到信息并输出结果到html和xml，如果有错误则输出到fail.txt中

### bat 源程序

  主要作用是利用grep从文件中查找某些信息，并输出结果

```bat
        @echo off
        echo [------------------------------------------------------]
        echo [          getset tool                                 ]
        echo [          version 1.0                                 ]
        echo [start]------------------------------------------------
        SETLOCAL enabledelayedexpansion
        echo BEGIN
        if not exist system.img ( echo [info]  system.img 不存在 >fail.txt
        goto end )
        if not exist SET.ini ( echo [info]  SET.ini  不存在 >>fail.txt
        goto end ) 
        if exist result.txt del result.txt
        for /f "tokens=*" %%i in (SET.ini) do (
            echo [ get ] %%i
            echo %%i>>result.txt
            grep.exe "%%i" system.img >>null
            ::echo !errorlevel!
            if !errorlevel!==1 (
                
                echo FAIL>>result.txt 
                
                
            ) else (
                echo PASS>>result.txt
                
            )
            
         )
        echo END
        echo [open result.txt to read ]---------------------------
        echo [stop]------------------------------------------------
        goto ppt
        :ppt
        if exist result.txt ( echo successful!  ) else ( echo [error] can't create result.txt )
        goto eof
        :end
        echo [error] 请查看[info]后信息
        pause
          
```

### 改写为Python程序

  整体的功能没有改变
  
```python

        import os
        import time
        class Compare(object):
            
            def __init__(self):
                print("[system - info] compare init")
            
            def fileisexist(self,filename):
                fail = open('fail.txt','w')
                if os.path.exists(filename):
                    print("[system - info] " + filename + " is exist")
                    return True
                else:
                    print("[system - error] " + filename + " is not exist")
                    fail.write(filename + " is not exist")
                    return False
                fail.close()
                
            def deletefile(self,filename):
                fail = open('fail.txt','w')
                if os.path.exists(filename):
                    try:
                        os.remove(filename)
                        print("[system - info] remove " + filename  + " successful!")
                    except Exception ,e:
                        fail.write(str(e))
                        sys.exit()
                else:
                    print("[system - info] " + filename  + " do not need delete!")
            
            def getpropfromimg(self,configfile,imgfile):
                config = open(configfile)
                findornot = open("result.txt",'w')
                for line in config.readlines():
                    if line.startswith(";;"):
                        print("[system - description] this is " + line)
                    else:
                        print("[system - finding] " + line)
                        if '\n' in line:
                            line = line[:-1]
                        findornot.write(line+"\n")
                        cmd = "grep.exe " + line + " system.img"
                        #print("[system - debug] " + cmd)
                        result = os.popen(cmd)
                        data = result.readline()
                        result.close()
                        if data:
                            print("[system - result]  successful\n")
                            findornot.write("PASS\n")
                        else:
                            print("[system - result]  failed\n")
                            findornot.write("FAIL\n")
                              
                config.close()
                findornot.close()
                
        if __name__ == "__main__":
            compare = Compare()
            if not compare.fileisexist("system.img"):
                sys.exit() 
            if not compare.fileisexist("SET.ini"):
                sys.exit()
            compare.deletefile("result.txt")
            compare.getpropfromimg("SET.ini","system.img")
```         

### 附上生成xml和html的程序

```python 
        #!/usr/bin/env python
        # -*- coding:utf-8 -*-
        #################################################################
        # @copyright:   All rights reserved (C)2016,MENGWEi author
        # @file     :   autoHtml.py
        # @author   :   mengwei
        # @version  :   0.11
        # @date     :   20160728
        #################################################################
        import os
        import sys
        import types
        import codecs
        from xml.dom import minidom
        def createHtml(self):
                f = open('result.txt','r')
                g = open('result.txt','r')
                
                
                reportFile = open('report.html','w')
                reportHead = "<html>\n<head >\n<title >\nPROP TEST REPORT\n</title>\n</head>\n<body>\n<h4 align=\"center\" bgcolor=\"red\"> PROP COMPARE REPORT</h4>\n<table frame=\"box\" align=\"center\" >\n<tr>\n<th bgcolor=\"yellow\" style=\"width:5px;\">PROP</th>\n<th bgcolor=\"yellow\">RESULT</th>\n</tr>\n"
                reportFile.write(reportHead)
                reportFile.write("\r\n")
                
                while True:
                    prop = g.readline()
                    result = g.readline()
                    reportlines = ""
                    if "PASS" in result:
                        reportlines = "<tr>\n<td cellspacing=\"100\" bgcolor=#32CD32>"+ prop +"</td>\n" + "<td bgcolor=#32CD32>"+result+"</td>\n</tr>"
                    else:
                        reportlines = "<tr>\n<td cellspacing=\"100\" bgcolor=#DB7093>"+ prop +"</td>\n" + "<td bgcolor=#DB7093>"+result+"</td>\n</tr>"
                    reportFile.write(reportlines)
                    if result:
                        print "continue"
                    else:
                        break
                reportEnd = "</table>\n</body>\n</html>"
                reportFile.write(reportEnd)
                reportFile.close()
                f.close()
                g.close()
        def createXml(self):
                g = open('result.txt','r')
                
                
                reportFile = open('report.xml','w')
                reportHead = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<testsuites >\n"
                reportFile.write(reportHead)
                while True:
                    prop = g.readline()
                    result = g.readline()
                    reportlines = ""
                    if result and ("PASS" in result):
                        reportlines = "<testsuite package=\""+ prop +"\">\n<testcase state=\"success\">\n</testcase>\n</testsuite>\n"
                    if result and ("FAIL" in result):
                        reportlines =  "<testsuite package=\""+ prop +"\">\n<testcase state=\"failure\">\n<error/>\n</testcase>\n</testsuite>\n"
                    reportFile.write(reportlines)
                    if result:
                        print "continue"
                    else:
                        break
                reportEnd = "</testsuites>"
                reportFile.write(reportEnd)
                reportFile.close()
                g.close()
                
        if __name__ == '__main__': 
            print"parse log file and create html report..."
            createHtml("result.txt")
            createXml("result.txt")
            print "parse log file and create html report finished!"
    #########################  TEXT END   #################################
```

### LINK
* github python 未上传