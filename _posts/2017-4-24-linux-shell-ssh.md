---
layout: post
title: linux shell ssh 
categories: linux
description: bookmark
keywords: linux, shell , ssh 
---

linux shell ssh 

## 链接

* nothing here

##  摘要
    
    自动登陆到远程，并执行命令

----------

## 内容    

### example.sh

```shell

    #!/usr/bin/expect
    set USER root
    set IP 192.168.1.105
    set PASS root123
    set COMD "./test.sh"
    spawn ssh "$USER@$IP" $COMD
    expect {
        "yes/no"  { send "yes\r"; exp_continue }
        "password:" {send "$PASS\r"; exp_continue}
    }
```

    只需要更改IP USER PASS COMD 即可。

### 查找文件中存在某字符串的行

```shell

    #!/usr/bin/bash
    set STR helloworld
    set STRPATH /home/root/hello.txt
    find $STRPATH | xargs grep $STR 
```

### py 可以使用文件备份

```python

    #!/usr/bin/python
    from datetime import datetime
    import os,sys

    reload(sys)
    sys.setdefaultencoding('utf-8')

    file = open('/home/slamtec/testrealsense/log','r')
    line = None
    i = 0
    for fl in file.readlines():
        if fl.startswith('2017'):
            i = i + 1
            line = fl
    file.close()
    a,b,c,d,e,f = line.split(' ')
    g,h,l = e.split(':')

    m,n = str(datetime.now()).split(' ')
    o,p,q = n.split(':')

    print str(i) + "] tn : h="+o + " m=" +p + " tl : h=" + g + " m=" + h

    if int(o) == int(g):
        minute = int(p) - int(h) 
    if ((int(o) - int(g)) >=1) or ((int(o) - int(g)) < 0) :
        minute = int(p) - int(h) + 60

    print "minute : " + str(minute)
    if minute >= 4:
        print "------- get log -------"
        logdirname = m + "-" + o  + "_" + p + "_log"
        os.system("/home/slamtec/testrealsense/getlog.sh " + logdirname )
    else :
        print "do not get log"

```

> #### LINK

* nothing to show
