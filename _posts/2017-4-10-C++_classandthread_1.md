---
layout: post
title: C++ Thread in Class at windows
categories: C++
description: bookmark
keywords: c++,thread,class,windows
---

C++ Thread in Class at windows

## 链接

* nothing here

##  摘要
    
    Last post is friend function of class.
    Another way to show it now.
    Write a thread function in class at windows 10 .

* 1、定义线程函数为全局函数
* 2、定义线程函数为静态成员函数
* 3、c++11.0 中的 std::thread 

----------

## 内容    

### 1、全局函数

```c

    #include <iostream>
    using namespace std;

    void ThreadFunc()
    {
        while(1)
            cout << " this is thread " << endl;
    }
    class Test{
        public:
        static int xxxx;
        static char yyyy;
    }
```

----------

### 2、静态成员函数
    
    静态成员函数只能访问静态成员变量。
    将this 作为参数传入Thread。

```c
    
    #include <iostream>
    using namespace std;

    class MyClass{
        public:
        void TestFunc();
        static int ThreadFunc(LPVOID pParam);
        private:
        int ThreadFuncKernal();
    }

    void MyClass::TestFunc(){
        AfxBeginThread(ThreadFunc,this);
    }
    int MyClass::ThreadFunc(LPVOID pParam){
        MyClass *mc = (MyClass *)pParam;
        return mc->ThreadFuncKernal();
    }
    int MyClass::ThreadFuncKernal()
    {
        while(1){
            cout << " this function test" << endl;
        }
        return 0;
    }
```


> #### LINK

* nothing to show
