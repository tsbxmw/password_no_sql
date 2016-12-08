---
layout: post
title: Android APP 登录 注册 SAE 部署 - [0] 准备
categories: Android
description: 笔记
keywords: Android, login, SAE
---

Android APP 登录 注册 SAE 部署 - [0] 准备

## 链接

* [csdn link](http://blog.csdn.net/mengwei2275/article/details/51537991)

##  内容

## READ ME：    
    如果你需要一个自己使用的APP登录和注册的Android demo。
    使用的是JAVA Web发布APP需要的信息
    JAVA Web获取APP的请求信息后查询外部数据库Mysql，并返回结果。
    APP通过Http client获取发布的信息
    进行登录或者注册操作
    请往下看，不然出门右转
    
### 一、需要的开发环境

      1，eclipse j2ee 开发环境
      
      2，eclipse android 开发环境
      
      3，db4free.net 上的免费的 mysql 数据库（db4free mysql）
      
      4，SAE JVM运行环境（或者其他的云的JVM）
      
      5，一部android手机（android 6.0）
      
          到现在为止，所有的设备已经就绪。
      
### 二、mysql

        现在我们需要的是一个可以在公网中访问的mysql数据库，所以你需要db4free。
        
        1、打开www.db4free.net 去注册一个自己的数据库
        
        2、接下来通过Navicat for mysql （或者其他的mysql客户端）测试你申请的数据库是否可用
        
        3、如果可以使用，建立一张表login，包含两个字段username 、 password
        
        4、添加一行数据：test_user、test_pass
        
        5、记录下数据库的名字，主机名称为db4free.net，端口是3306，用户名密码即注册使用的。
        
     其他的免费数据库：
          https://www.freemysqlhosting.net/
     现在，我们需要的数据库便申请完了。
  
### 三、SAE

      你可以去使用其他的云，包括阿里云、腾讯云、百度云等等，不是打广告
      这些在sae帮助中含有：
      
      1、通过微博账号登录SAE
      
      2、在云应用中建立一个java应用
      
      3、然后你就拥有了一个只可以上传war包才能使用的java应用了
      
      4、最好实名认证，不然弹出框会造成困扰

### 四、搞完上面这些，便可以进行编程咯

    <不定期更新>

### NEXT -->Android APP 登录 注册 SAE 部署 - [1]
* [next](https://tsbxmw.github.io/2016/08/06/Android-app_test_1/)
