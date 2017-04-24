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

> #### LINK

* nothing to show
