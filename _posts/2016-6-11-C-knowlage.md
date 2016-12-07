---
layout: post
title: C 知识点
categories: C
description: 笔记
keywords: Java, Markdown, Table of Contents
---

C 语音知识笔记

## 链接

* [csdn link](http://blog.csdn.net/mengwei2275/article/details/51537905）

## 内容
### 声明 定义区别

  声明是告诉编译器，这个名字已经匹配到一块内存上了

  定义是创建了对象并分配了内存

### 注意事项

  尽量少的使用全局变量

  参数命名合理 顺序恰当

  如果参数是指针 且只当做输入用 应加const 防止被修改

  不要省略返回值类型

### 内存 静态区 栈 堆

  堆栈 ： 栈 stack 堆 heap

  保存自动全局变量和Static 变量 局部变量

  整个程序的声明周期都存在，编译时分配

  Malloc 或 new 分布的内存，free 或者delete来释放

### 指针

  int *p = 0x00; 定义指针变量p，设置p=0x00;地址*p=0x00;
