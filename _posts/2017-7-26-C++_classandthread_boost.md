---
layout: post
title: C++ Thread in Class at windows
categories: C++
description: bookmark
keywords: c++,thread,class,windows,boost
---

C++ Thread in Class at windows

## 链接

* nothing here

##  摘要
    
    how to use a boost thread in windows?
    there is a sample to show.

### 1 - download boost

    visit the website of boost :
    http://www.boost.org/users/history/version_1_64_0.html

    choos the boost_1_64_0.7z(or zip) of windows to download .
    unzip the package to use it.

### 2 - include and lib

    when you unzip the  boost_1_64_0.7z, you would get the  boost_1_64_0 dir.
    include the boost to the vs include path.

### 3 - how to use it ?

#### 3.1  include
    
    at the source.h , include the thread.hpp

```c
    #include <boost\thread\thread.hpp>
    using namespace boost;
```

#### 3.2 class code
    
```c
    class Test{
    public :
        bool flag;
        void threadtest();
        thread * thread_test;
        void run();
    };
```
--------

```c
    void Test::threadtest()
    {
        while(true)
        {
            cout << "i am thread test" << endl;
            if (flag)
                break;
        }
    }

    void Test:run()
    {
        // this is the key to use thread in class
        thread_test = new boost::thread(boost::bind(&Test::threadtest,this));
        while(true)
        {
            cout << "i am run func" << endl;
        }
    }
```


### other

#### what's boost?

    look at the baidu 
    Boost库是一个可移植、提供源代码的C++库，作为标准库的后备，是C++标准化进程的开发引擎之一。 Boost库由C++标准委员会库工作组成员发起，其中有些内容有望成为下一代C++标准库内容。在C++社区中影响甚大，是不折不扣的“准”标准库。Boost由于其对跨平台的强调，对标准C++的强调，与编写平台无关。大部分boost库功能的使用只需包括相应头文件即可，少数（如正则表达式库，文件系统库等）需要链接库。但Boost中也有很多是实验性质的东西，在实际的开发中使用需要谨慎。
    Boost库是为C++语言标准库提供扩展的一些C++程序库的总称。
    Boost库由Boost社区组织开发、维护。其目的是为C++程序员提供免费、同行审查的、可移植的程序库。Boost库可以与C++标准库完美共同工作，并且为其提供扩展功能。Boost库使用Boost License来授权使用。
    Boost社区建立的初衷之一就是为C++的标准化工作提供可供参考的实现，Boost社区的发起人Dawes本人就是C++标准委员会的成员之一。在Boost库的开发中，Boost社区也在这个方向上取得了丰硕的成果。在送审的C++标准库TR1中，有十个Boost库成为标准库的候选方案。在更新的TR2中，有更多的Boost库被加入到其中。从某种意义上来讲，Boost库成为具有实践意义的准标准库。
    可下载Boost C++ Libraries安装boost库。大部分boost库功能的使用只需包括相应头文件即可，少数（如正则表达式库，文件系统库等）需要链接库。里面有许多具有工业强度的库，如graph库。

    the wiki
    Boost C++ 库（Libraries）是一组扩充C++功能的经过同行评审（Peer-reviewed）且开放源代码程序库。大多数的函数为了能够以开放源代码、封闭项目的方式运作，而授权于Boost软件许可协议（Boost Software License）之下。许多Boost的开发人员是来自C++标准委员会，而部分的Boost库成为C++的TR1标准之一。[1]
    为了要确保库的效率与弹性，Boost广泛的使用模板（template）功能。而它是针对各式领域的C++用户与应用领域（Application Domain）上，包含的库类别从像smart_ptr 库这种类通用库，到像是文件系统的操作系统抽象层，甚至能够利用Boost来开发额外的库或是给高级的C++用户利用，像是MPL。
    https://zh.wikipedia.org/wiki/Boost_C%2B%2B_Libraries

    and the boost official
    Welcome to Boost.org!
    Boost provides free peer-reviewed portable C++ source libraries.

    We emphasize libraries that work well with the C++ Standard Library. Boost libraries are intended to be widely useful, and usable across a broad spectrum of applications. The Boost license encourages both commercial and non-commercial use.

    We aim to establish "existing practice" and provide reference implementations so that Boost libraries are suitable for eventual standardization. Ten Boost libraries are included in the C++ Standards Committee's Library Technical Report (TR1) and in the new C++11 Standard. C++11 also includes several more Boost libraries in addition to those from TR1. More Boost libraries are proposed for standardization in C++17.

    Since 2006 an intimate week long annual conference related to Boost called C++ Now has been held in Aspen, Colorado each May. Boost has been a participant in the annual Google Summer of Code since 2007.

    Getting Started
    Boost works on almost any modern operating system, including UNIX and Windows variants. Follow the Getting Started Guide to download and install Boost. Popular Linux and Unix distributions such as Fedora, Debian, and NetBSD include pre-built Boost packages. Boost may also already be available on your organization's internal web server.
    Background
    Read on with the introductory material to help you understand what Boost is about and to help in educating your organization about Boost.
    Community
    Boost welcomes and thrives on participation from a variety of individuals and organizations. Many avenues for participation are available in the Boost Community.





> #### LINK

* nothing to show
