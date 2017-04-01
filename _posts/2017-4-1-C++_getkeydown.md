---
layout: post
title: C++ how to get key status at background
categories: C++
description: bookmark
keywords: c++,keydown,background
---

C++ get key down

## 链接

* nothing here

##  摘要
    
    Get the key down status at background in windows


----------

## 内容    
    
### getkeydown.cpp

----------

```c

    #include<iostream>
    #include<windows.h>

    #define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //必要的，我是背下来的 

    using namespace std;


    void check(char c){//检测11111
        if(KEY_DOWN(c))
        {
            WinExec("DEMO_OFMOVE.exe",SW_HIDE);
            cout << " 1 is down " << endl;
        }
    }

    int main(){
        while(1){
            check('1');
            
            Sleep(20);//循环时间间隔，防止太占内存 
        }

        return 0;
    }
```

> #### LINK

* nothing to show
