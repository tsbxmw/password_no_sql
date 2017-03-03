---
layout: post
title: Python ssh and sftp 
categories: python
description: bookmark
keywords: ssh,python,sftp
---

python - ssh - sftp 

## 链接

* [Google Test](http://mengweibbs/2017/3/3/Python-ssh)

##  摘要
    
    Using ssh and sftp by python 


----------

## 内容    
    
### SSH.py

----------

```python
  
  #-*- coding: utf-8 -*-
  #!/usr/bin/python 

  '''
  # version : 1.3
  # attention ：using paramiko module --- using 'pip install paramiko' to install the module
  # functon : ssh and sftp function
  # author : mengwei
  # date : 2017.03.01
  # modify : -add Sftp module to transport the file
  # modify : 2017.03.02 - change the Ssh() to Ssh(ip,user,pass)
  '''

  import paramiko
  import sys
  import time

  class Ssh(object):
      def __init__(self,ipadd,username,password):
          self.ip = ipadd
          self.username = username
          self.password = password

      def Connect(self):
          self.connect = paramiko.SSHClient()
          self.connect.set_missing_host_key_policy(paramiko.AutoAddPolicy())
          self.connect.connect(self.ip,22,self.username,self.password,timeout=5)

      def Exec(self,cmd):
          stdin, stdout, stderr = self.connect.exec_command(cmd)
          out = stdout.readlines()
          return out

      def Close(self):
          self.connect.close()

  class Sftp(object):
      def __init__(self,ipadd):
          self.ip = ipadd
          self.username = "root"
          self.password = "root"

      def Connect(self):
          try:
              self.sftp = paramiko.Transport(self.ip,22)
              self.sftp.connect(username=self.username,password=self.password)
              self.sf = paramiko.SFTPClient.from_transport(self.sftp)
        except Exception,e:
            print "[Sftp connect] : wrong with it -- " + str(e)

    def PutFile(self,localfile,remotefile):
        try:
           self.sf.put(localfile,remotefile)
        except Exception,e:
            print "[Sftp connect] : wrong with it -- " + str(e)

    def Close(self):
        self.sftp.close()

  if __name__ == "__main__":
      ssh = Ssh("192.168.11.1","root","root")
      ssh.Connect()
      ssh.Exec("reboot -n")            
      ssh.Close()
```

> #### LINK

* nothing to show
