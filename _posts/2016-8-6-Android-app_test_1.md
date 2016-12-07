---
layout: post
title: Android APP 登录 注册 SAE 部署 - [1] 服务器部署
categories: Java
description: 笔记
keywords: Android, login, SAE, Java, Web
---

Android APP 登录 注册 SAE 部署 - [1] 服务器部署

## 链接
* [pre](https://tsbxmw.github.io/2016/08/05/Android-app_test/)
* [csdn link](http://blog.csdn.net/mengwei2275/article/details/51537991)
* [next](https://tsbxmw.github.io/2016/08/10/Android-app_test_2/)

##  内容

## READ ME：    
  如果你需要一个自己使用的APP登录和注册的Android demo。
  使用的是JAVA Web发布APP需要的信息
  JAVA Web获取APP的请求信息后查询外部数据库Mysql，并返回结果。
  APP通过Http client获取发布的信息
  进行登录或者注册操作
  请往下看，不然出门右转
    
###  一、SAE

  SAE的使用文档见

  http://www.sinacloud.com/doc/sae/
    
  看一下eclips的插件

  http://www.sinacloud.com/doc/sae/docker/java-eclipse-plugin.html

#### Java应用部署指南

#### 入门指南
#### 准备工作

* 首先，我们先从github上clone一个Java的示例程序。

      $ git clone https://github.com/sinacloud/java-getting-started.git
      $ cd java-getting-started
      $ ls
    pom.xml  Procfile  README.md  src  system.properties

    这个示例程序是一个使用 Maven 创建的小应用，应用采用了内置Jetty启动的方式， Procfile 文件中描述了应用启动的方式， system.properties 文件指定了使用的JDK版本，示例中使用的是JDK1.8。

* 本地编译运行（本地需要有Maven和Java环境）：

    $ mvn package
    $ java -jar target/dependency/jetty-runner.jar --port 5050 target/*.war
  
  如果启动无错误，可以通过 http://localhost:5050 来访问。

* 创建应用

  登录『新浪云控制台』，点击『创建新应用』，运行环境选择『语言／云容器』，应用名为 helloworld 。
![](/images/blog/sae/img_001.png)

  根据您的应用需求，选择你想要的规格的容器。

![](/images/blog/sae/img_002.png)
  点击创建，创建一个新的容器应用。

* 部署应用

  应用创建完后，会显示你的应用的 git 仓库地址以及如何将代码提交到该 git 仓库，按照说明提交代码。

    $ git remote add sinacloud https:://git.sinacloud.com/helloworld
    $ git push sinacloud master
    ...
    remote: Exporting git code...
    remote: Uploading...
    -----> Xxx app detected
    -----> Creating runtime environment
    ...
    remote: Deploy and waiting for app to be ready .....
    To https://git.sinacloud.com/ymp9vm2385
    + 74d7d50...470cb46 master -> master
  部署的时候，git 会显示当前的进度，如果部署失败，会提示相应的错误信息（比如 package.json 格式问题等）。

  部署完成后，我们就可以通过 http://helloworld.applinzi.com 来访问我们的应用了。

* 容器管理

  在应用页面的左侧导航栏选择［容器管理］，在这个页面可以管理您刚才部署的容器实例。
![](/images/blog/sae/img_003.png)

#### 构建和运行说明
* 如何识别应用是Java应用？

    构建程序通过判断应用的根目录下是否有 pom.xml 文件来判断一个应用是否是Java应用。

* 如何修改使用的JDK版本？

    在 system.proerties 文件中指定即可。

    java.runtime.version=1.8

###  二、JavaWeb

    此应用使用http传递和获取信息
    
#### Java web 的编写与部署

#### link

* [github](https://github.com/tsbxmw/xxx1_server_web)

#### 编码

    写一个简单的JavaWeb应用，不需要有界面或者有简单的调试页面即可。

  
    <不定期更新>

#### NEXT -->Android APP 登录 注册 SAE 部署 - [2] JavaWeb的编写与部署
* [next](https://tsbxmw.github.io/2016/08/10/Android-app_test_2/)
