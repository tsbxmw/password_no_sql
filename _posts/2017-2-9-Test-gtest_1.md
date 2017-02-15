---
layout: post
title: Google Test -- 0
categories: Test
description: bookmark
keywords: google test , Auto Test , C++
---

Google Test 

## 链接

* [Google Test](https://tsbxmw.github.io/2017/2/9/Test-gtest_1/)

##  摘要
    
    Google Test , C++ test framework -- 断言


----------

## 内容    
    
### C++ Test Framework

----------

> #### what is Google Test ?

  C++ test with google test framework

* link ： [test](https://github.com/google/googletest)

----------

> #### how to use it ?

* 1、从 google 网站 download gtest 源码
   
   git clone https://github.com/google/googletest.git

* 2、使用 VS 打开 googletest\googletest\msvc 下的工程

* 3、设置 build 的属性，编译出 gtest.lib(release) 或者 gtestd.lib(debug) 

* 4、新建一个要测试的程序(win32 console )

* 5、将 googletest\googletest\include 添加到 IncludeDir
   
* 6、将 编译的 gtest.lib 或者 gtestd.lib 添加到 LibiraryDir
   
* 7、编写测试程序（例子在最后）
  

----------

> #### what is the rule ?

> ASSERT_* and EXPECT_*  
>  * ASSERT 退出测试 
>  * EXPECT 继续执行

| rule | assert | expect |  meaning |
|:-----:|:------:|:------:|:-------:|
| bool | ASSERT_TRUE(xxxx) | EXPECT_TRUE(xxxx) | xxxx == TRUE |
|  | ASSERT_FALSE(xxxx) | EXPECT_FALSE(xxxx) | xxxx == FALSE |
| isll | ASSERT_EQ(expect,actual) | EXPECT_EQ(expect,actual) | expect == actual |
|  | ASSERT_NE(expect,actual) | EXPECT_NE(expect,actual) | expect != actual |
|  | ASSERT_LT(expect,actual) | EXPECT_LT(expect,actual) | expect < actual |
|  | ASSERT_LE(expect,actual) | EXPECT_LE(expect,actual) | expect <= actual |
|  | ASSERT_GT(expect,actual) | EXPECT_GT(expect,actual) | expect > actual |
|  | ASSERT_GE(expect,actual) | EXPECT_GE(expect,actual) | expect >= actual |
| string | ASSERT_STREQ(expect,actual) | EXPECT_STREQ(expect,actual) | expect.equals(actual) |
|  | ASSERT_STRNE(expect,actual) | EXPECT_STRNE(expect,actual) | expect != actual |
|  | ASSERT_STRCASEEQ(expect,actual) | EXPECT_STRCASEEQ(expect,actual) | expect == actual in ignoring case |
|  | ASSERT_STRCASENE(expect,actual) | EXPECT_STRCASENE(expect,actual) | expect != actual in ignoring case |
| float | ASSERT_FLOAT_EQ(expect, actual) | EXPECT_FLOAT_EQ(expect, actual) | expect == actual |
| double | ASSERT_DOUBLE_EQ(expecte,actual) | EXPECT_DOUBLE_EQ(expect, actual) | expect == actual |
| near | ASSERT_NEAR(val1, val2, abs_error) | EXPECT_NEAR(val1, val2, abs_error) | val1 near v2 |


--------

> 成功或失败

* SUCCEED() 返回成功
* FAIL() 失败返回 
* ADD_FAILURE() 失败继续往下执行

--------

> 异常检查

| rule | assert | expect |  meaning |
|:-----:|:------:|:------:|:-------:|
|check |  ASSERT_THROW(statement,exception_type) |  EXPECT_THROW(statement,exception_type) | same type |
|      |  ASSERT_ANY_THROW(statement) |  EXPECT_ANT_THROW(statement) | any type |
|      |   ASSERT_NO_THROW(statement) |  EXPECT_NO_THROW(statement) | no type |

--------

> 输出

* ASSERT_PRED1(pred1, val1)
* EXPECT_PRED1(pred1, val1)
* ASSERT_PRED_FORMAT1(pred_format1, val1)
* EXPECT_PRED_FORMAT1(pred_format1, val1)




---------




> #### test.demo

```c
	
	// gtest_2.cpp : Defines the entry point for the console application.
	//

	// demo.cpp : 定义控制台应用程序的入口点。
	//

	#include "stdafx.h"
	#include <gtest\gtest.h>

	int Foo(int a, int b)
	{
	    if (a == 0 || b == 0)
	    {
	        throw "don't do that";
	    }
	    int c = a * b;
	    if (c == 40)
	        return b;
	    return Foo(b, c);
	}


	TEST(FooTest, HandleNoneZeroInput)
	{
	    ASSERT_EQ(10, Foo(4, 10));
	    //EXPECT_EQ(8, Foo(5 , 8));
	    
	}

	int _tmain(int argc, _TCHAR* argv[])
	{
	     testing::InitGoogleTest(&argc, argv);
	     

	     RUN_ALL_TESTS();

	}
		
```

--------

> #### LINK

*  [google test -- 1](http://mengweibbs.cn/2017/02/15/Test-gtest_2/)