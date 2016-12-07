---
layout: post
title: Jenkins环境搭建指导文档
categories: Jenkins
description: 笔记
keywords: Jenkins, Markdown, Table of Contents
---

Jenkins 入门系列之一：jenkins安装

## 链接

* [csdn link](http://blog.csdn.net/mengwei2275/article/details/52996775)

##  内容

###   1、使用jenkins windows安装文件进行安装。

####  （1）获取jenkins安装文件
    打开网址https://jenkins.io/index.html
    
![](/images/blog/jenkins0/clip_image001.png)
    
#### （2）点击Download Jenkins
![](/images/blog/jenkins0/clip_image003.png)
    
#### （3）下载对应版本， 这里下载的是发布的windows版本
![](/images/blog/jenkins0/clip_image005.png)
    
#### （4）保存文件到E:\Jenkins下
![](/images/blog/jenkins0/clip_image007.png)
    
#### （5）解压下载的压缩文件，双击jenkins.msi文件进行安装
![](/images/blog/jenkins0/clip_image009.png)
    
#### （6）打开安装文件
![](/images/blog/jenkins0/clip_image011.png)
    
#### （7）点击Next，点击Change选择安装路径。 
![](/images/blog/jenkins0/clip_image013.png)
    
#### （8）点击OK，继续点击Next，然后点击Install安装
![](/images/blog/jenkins0/clip_image015.png)
![](/images/blog/jenkins0/clip_image017.png)

#### （9）等待安装完成
![](/images/blog/jenkins0/clip_image019.png)
    
#### （10）完成
![](/images/blog/jenkins0/clip_image021.png)
    
#### （11）点击Finish后，会自动打开一个解锁Jenkins的网页
![](/images/blog/jenkins0/clip_image023.png)

#### （12）打开显示的的路径找到
    D:\Program Files\Jenkins\secrets\initialAdminPassword
    
![](/images/blog/jenkins0/clip_image025.png)

#### （13）右键使用notepad++打开，复制其中的内容
    fa888b5165364efcb80361ced0d24032
    粘贴到网页中去
    
![](/images/blog/jenkins0/clip_image027.png)
    
#### （14）点击Continue.进入设置界面。由于公司网络问题，会出现Offline，直接点击Skip Plugin Installation跳过。
![](/images/blog/jenkins0/clip_image029.png)

#### （15）创建管理员用户和密码
![](/images/blog/jenkins0/clip_image031.png)
    点击Save and Finish，进入下一步。
![](/images/blog/jenkins0/clip_image033.png)

#### （16）安装完成，点击Start using Jenkins即可开始使用jenkins活动了。安装完成后，地址一般为http://localhost:8080。
![](/images/blog/jenkins0/clip_image035.png)
    
#### 注意事项：
    局域网内的PC访问网址为：http://ip:8080
	ip为搭建jenkins的pc的ip地址。
	（查看ip：在cmd中输入ipconfig –all 即可查找到自己的pc 的ip）。

###  2、使用tomcat 和jenkins war文件进行搭建

#### （1）搭建tomcat环境。
    访问http://tomcat.apache.org/
    
![](/images/blog/jenkins0/clip_image037.png)

#### （2）选择Tomcat7进行下载。
![](/images/blog/jenkins0/clip_image039.png)

#### （3）页面下滑，根据对应操作系统下载zip包。
![](/images/blog/jenkins0/clip_image041.png)
    
#### （4）保存到E:\Tomcat中去
![](/images/blog/jenkins0/clip_image043.png)
    
#### （5）解压到当前目录，是个文件夹
![](/images/blog/jenkins0/clip_image045.png)

#### （6）进入文件夹apache-tomcat-7.0.70下的bin文件夹，双击startup.bat。
    如果没有配置好环境变量则会一闪就消失，启动失败。
    下面在startup.bat同级目录新建a.bat。文件内容为
    call startup.bat
    pause
    双击执行a.bat。会在cmd中显示错误原因。
    
![](/images/blog/jenkins0/clip_image047.png)
    
#### （7）针对错误原因，分析，不存在JAVA_HOME或者JRE_HOME环境变量。
    右击“计算机”选择“属性”，然后选择“高级系统设置”，选择“高级”->“环境变量”。
    
![](/images/blog/jenkins0/clip_image049.png)

#### （8）在系统变量中点击新建，变量名是JAVA_HOME，变量值是JDK安装路径，再次点击新建，变量名是JRE_HOME,变量值是JDK下的JRE目录。然后点击确定、确定、确定。
    
![](/images/blog/jenkins0/clip_image051.png)
![](/images/blog/jenkins0/clip_image053.png)
    PS：如果没有安装JDK，则需要手动安装。

#### （9）双击startup.bat已经可以启动tomcat了。
![](/images/blog/jenkins0/clip_image055.png)
    如果失败，则说明环境变量没有生效，在startup.bat同级目录下的setclasspath.bat中最上面添加两行
    set JRE_HOME=C:\Program Files (x86)\Java\jdk1.7.0_01\jre
    set JAVA_HOME=C:\Program Files (x86)\Java\jdk1.7.0_01
    然后双击startup.bat进行启动，出现Server startup in xxx ms便成功。

#### （10）部署jenkins环境到tomcat中。

#### （11）获取jenkins安装文件
    打开网址https://jenkins.io/index.html
![](/images/blog/jenkins0/clip_image057.png)
    
#### （12）点击Download Jenkins
   ![](/images/blog/jenkins0/clip_image059.png)

#### （13）点击2.7.2.war进行下载
   ![](/images/blog/jenkins0/clip_image061.png)
    
#### （14）拷贝jenkins.war到apache-tomcat-7.0.70\webapps下
   ![](/images/blog/jenkins0/clip_image063.png)
   ![](/images/blog/jenkins0/clip_image065.png)

#### （15）双击bin\目录下的startup.bat启动tomcat，可以看到jenkins is fully up and running，启动成功。
   ![](/images/blog/jenkins0/clip_image067.png)
   
#### （17）打开本地jenkins的网址http://localhost:8080/jenkins， 跟1中的步骤类似。
   ![](/images/blog/jenkins0/clip_image069.png)

#### （18）打开显示的的路径找到
    C:\Users\10192582.ZTE\.jenkins\secrets\initialAdminPassword
    
![](/images/blog/jenkins0/clip_image025.png)
    
#### （19）右键使用notepad++打开，复制其中的内容
   21fda9a73ff94280a3841b33978e5286粘贴到网页中去
   ![](/images/blog/jenkins0/clip_image027.png)
    
#### （20）点击Continue.进入设置界面。由于公司网络问题，会出现Offline，直接点击Skip Plugin Installation跳过。
   ![](/images/blog/jenkins0/clip_image029.png)

#### （21）创建管理员用户和密码
   ![](/images/blog/jenkins0/clip_image031.png)
    点击Save and Finish，进入下一步。
   ![](/images/blog/jenkins0/clip_image033.png)

#### （22）安装完成，点击Start using         Jenkins即可开始使用jenkins活动了。安装完成后，地址一般为http://localhost:8080/jenkins
   ![](/images/blog/jenkins0/clip_image035.png)
    
### 注意事项：
    局域网内的PC访问网址为：http://ip:8080/jenkins
	ip为搭建jenkins的pc的ip地址。
	（查看ip：在cmd中输入ipconfig –all 即可查找到自己的pc 的ip）。
