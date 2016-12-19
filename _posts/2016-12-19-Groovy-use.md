---
layout: post
title: Groovy 语法
categories: Groovy
description: 笔记
keywords: Groovy 
---

Groovy 简单使用介绍

##  内容

### 注释

   单行 //
   多行 /*   */
   文档注释 /** */

### 标识符

#### 普通标识符
 
* 以字母、美元符号、下划线开始
    
    name  item3  with_item  $hello

#### 引号标识符

* 在点表达式后面可以使用一号标识符，比如a.b 可以表示为 a.'b' 或者 a."b"

#### 字符串

* java.lang.String
* groovy.lang.GString

#### 单引号字符串

* def a = 'hello'

   不支持插值

#### 三引号字符串

* 支持多行字符串

     def a='''
      line one
      line two
      line xxx
      '''
#### 三双引号字符串

* 与上面的类似，但是支持插值

#### 双引号字符串

* 没有插值表达式，就是Java.lang.String,如果有插值，就是groovy.lang.GString。

     def a = "hello"
     def b = "hello world ${a}"

#### 字符串插值

* 除了单引号和三引号字符串，其余都支持插值

     def name = 'hello ${world}'

* 使用点号的时候，可以只用$ 代替 ${}

#### 斜线字符串

* 除了使用括号来括住字符串，还可以使用 /
    
     def a = /.*xxxx.*/
     def b = '.*xxxx.*'

     def c = /"xxxx"/

#### 美元斜线字符串

* 使用 $/ 开始 使用 /$ 结束， 即转义 $

#### 字符

     char a = '1'
     def b = '2' as char
     def c = (char) '3'

#### 数字

* 可以自适应

     def a = 1

     def b = 232323212314

     def c = 213421432143242143242143

     def d = 123.456

* 如果强制指明一个数字的字面量类型，可以给字面量加上类型后缀

     BigInteger G g
     Long       L l
     Integer    I i
     BigDecimal G g
     Double     D d
     Float      F f

#### 列表

* 默认情况下的Groovy的列表使用的是 java.util.ArrayList ,使用 [] ， “，” 分隔

     def a = [1,2,3,4,5]

* 使用其他的类型的列表LinkedList 可以使用as 操作符

     def arrayList = [1,2,3]

     def LinkedList = [2,3,4]  as LinkedList

     LinkedList otherLinked = [3,4,5]

* 重载了 []  和 << ，可以通过List[x]访问指定元素，或者List << a 添加元素

     def a = [1,2,3,4]
     a << 5

#### 数组

* 需要使用as 显式指明

     String []a = ['a','b','c']

     def a = [1,2,3] as int[]

#### 映射

* 使用[] 来定义映射，包含key 和value，使用 " : "分隔，元素之间用 ","分隔

     def name = [a:1,b:2,c:3]

     name['a']

     name['d'] = 4
     
     name.e = 5

