---
layout: post
title: Java 类的区分
categories: Java
description: 笔记
keywords: Java, Markdown, Table of Contents
---



## 链接

* [csdn link](http://blog.csdn.net/mengwei2275/article/details/51537918)

## 内容

### 内部类
    在其他内部定义的类。

### 静态内部类 和 非静态内部类：

    class 前加static ，不可以直接访问宿主类成员，只有通过对象来访问外部类，使用对象成员调用。

    宿主类访问内部类需要内部类对象调用。

### 局部内部类：

    变量定义在类中叫做成员变量，定义在方法中叫做局部标量。

    类定义在方法中叫做局部内部类。

### 匿名内部类：

    没有名字的内部类。

    直接构造对象，方便的构造当前使用的对象

    对象克隆，创建并返回对象的一个副本。

    protected Object clone() throws CloneVotSupportedException

    得到的是Object队象，需要的是进行类型转换。

### 抽象类： abstract

    在类中定义方法，在子类中去实现

    抽象方法：public abstract int hello()

    抽象类不可以被实例化，对于子类可以进行实例化。

### Object 类：所有类的祖先类。

    可以存储各种对象，却丢失类型

    equals() 函数，只有两个对象指向一个对象时才会相同。

### 接口和内部类：

    定义了一系列的抽象方法和常量，形成一个属性结合，接口修饰符为默认或者public

    默认时接口所在包之外的类不可用 。 public 可以用

    接口内变量被设置为 public static final

    接口方法为抽象，并为public

    接口不可实例化
    
### 其他
    public 公共

    protected 子类可访问

    private 所在类访问