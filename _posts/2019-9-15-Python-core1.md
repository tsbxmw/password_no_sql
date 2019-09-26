---
layout: post
title: Python 源码分析（1） 源码下载与使用
categories: Python
description: Python - 源码的下载与使用
keywords: python, source
---
pyhton 源码分析（1） 源码下载与使用

# 下载

> 官方网址

https://www.python.org/

> git clone

``` shell
git clone https://github.com/python/cpython.git
```

## Unix & Mac OS

### 编译

```shell
cd cpython
./configure --with-pydebug && make -j
```

### 测试

```
./python -m test -j3
```


## Windows 


### 编译

```shell
PCbuild\build.bat -e -d
```

### 测试

```
./python.exe -m test -j3
```


## 使用代码进行开发


### 安装 VS2017

### 打开解决方案

> PCBuild/pcbuild.sln

![](/images/blog/python-core/1-1.png)

### 点击 运行,Python 已经生成

![](/images/blog/python-core/1-2.png)

## 主要项目

### pythoncore

#### 我们主要关注 Modules 和 Objects

![](/images/blog/python-core/1-3.png)


| name | value | remark |
|----|----|----|
| include | 头文件 | |
| Modules | 内置模块 | |
| Objects | 内置对象 | |
| Parser | 语法分析 | |
| PC | windows 相关| |
| Python | python 编译主体 |

#### Modules python中的内置模块目录

- 像比较常见的 json math 等都可以看到

![](/images/blog/python-core/1-4.png)


### Objects 万物皆对象就是定义在这里

- 可以看到 bool 类型 boolobject.c

![](/images/blog/python-core/1-5.png)