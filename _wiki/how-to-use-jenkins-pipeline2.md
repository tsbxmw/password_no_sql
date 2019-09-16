---
layout: wiki
title: how to use jenkins pipeline
categories: Recommends
description: how to use jenkins with groovy pipeline script ?
keywords: jenkins, pipeline script
---
Jenkins pipeline script

## 目录

* (line)[http://jenkins.slamtec.com/workflow-cps-snippetizer/dslReference]

### 1 - bat 

    bat is to run a windows batch command .

> example : to run dir at windows with bat command 

```java
    bat_string = "dir > ls.txt"
    bat bat_string
```

--------- 

### 2 - build 

    build is to build other project like a new job

> example : to build a job : TEST_SCRIPT with parameters : TEST_STAGES 

```java
    build job: 'TEST_SCRIPT', parameters: [[$class: 'StringParameterValue', name: 'TEST_STAGES', value: 'sss']], propagate: false
```

### 3 - checkout

    checkout is to git or scm the code form git or svn

> example : to checkout code from git

```java
    checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], gitTool: 'windowsGit', submoduleCfg: [], userRemoteConfigs: [[credentialsId: '1234f2b3-1929-4351-82cf-e80c0c9a4c73', url: 'https://github.com/tsbxmw/xxxx.git']]])
```
### 4 - dir

    change current directory

> example : change the dir to the e:

```java
    dir("e:\\")
    {
        echo "i am at e"
    }
```

### 5 - isUnix

    checks if running on a Unix-like node

> example : check 

```java
    if (isUnix())
    {

    }
```

### 6 - load

    evaluate a gorrvy source file into the pipeline script

> example : load file from e:\\jenkins\\hello.xxx

```java
    load 'e:\\jenkins\\hello.xxx'
```

### 7 - mail

    mail to some body 

> example : mail to aaa@aaa.com.cn \ cc to bbb@aaa.com.cn \ bcc to ccc@aaa.com.cn \ subject is welcome to aaa bbb cc join the abc.inc \ body is haha , this hr . \ from is .replyTo:

```java
    mail bcc:'ccc@aaa.com.cn' , body:'haha , this hr .', cc:'bbb@aaa.com.cn',subject:'welcome to aaa bbb cc join the abc.inc ',from ".replyTo:",to:'aaa@aaa.com.cn'
```

### 8 - node

    Allocate node

> example : switch to new node

```java
    node('TEST_WINDOWS'){

    }
```







