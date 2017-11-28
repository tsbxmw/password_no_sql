---
layout: post
title: Google Test -- 1
categories: Test
description: bookmark
keywords: google test , Auto Test , C++
---

Google Test -- 1

## 链接

* [Google Test](http://mengweibbs/2017/2/15/Test-gtest_2/)

##  摘要
    
    Google Test , C++ test framework -- understanding 


----------

## 内容    
    
### C++ Test Framework

----------

> #### what is Google Test ?

  C++ test with google test framework

* link ： [test](https://github.com/google/googletest)

----------

> How to use gtest?

* int the other bolg , said the gtest rules
* link : [googletest](http://mengweibbs.cn/2017/02/09/Test-gtest_1/)
* now , let's learn how to use it .

--------

> First : get the source files 

* using the following commands to download the googletest files

```git

	git clone https://github.com/google/googletest

```

--------

> Second : open the project with VisualStudio (2010 - 2015)

* the project file should be in the directory : ~/googletest/googletest/msvc
* open it and generating the lib files 
* Debug should be : gtest.lib
* Release should be : gtestd.lib

--------

> Third : create new project and add the lib include files

* create a new project
* add include directory to the INCLUDEDIR
* add lib directory to the LIBRARYDIR
* add the gtest.lib or gtestd.lib to the libname

--------

> Fourth : add test cases and run test cases

* now we can star to write the test cases

--------

> #### LINK

*  [google test -- 1](http://mengweibbs.cn/2017/2/15/Test-gtest_2/)