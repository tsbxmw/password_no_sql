---
layout: post
title: Java 设计模式 - 单例模式
categories: Java
description: 笔记
keywords: Java, design mode
---

Java 设计模式 - 单例模式

## 内容

### 单例模式（Singleton）

* 单例对象， 是一种常用的设计模式。在Java应用中，单例对象能保证在一个JVM中，只有一个实例存在。

> 好处就是：

* 某些类的创建比较频繁，对于一些大型的对象，这是一笔很大系统开销
* 省去了new操作符，降低了系统内存的使用频率，减轻GC压力
* 核心的进程类似windows资源管理器，如果创建多个，就会crash

> 例子 - 单例类


```java

     public  class Singleton{
        private static Singleton instance = null;
        private Singleton(){

        }
        public static Singleton getInstance(){
            if(instance == null){
                instance = new Singleton();
            }
            reutn instance;
        }
        public Object readResolve(){
            return instance;
        }
     }
```

* 上面的类可以实现单例模式，但再多线程情况下，没有线程保护，会出现问题。

> 添加线程保护 -- 对getInstance 方法添加synchronized 关键字


```java

     public static synchronized Singleton getInstance(){
        if(instance == null){
            instance = new Singleton();
        }
        return instance;
     }
```

> 但是锁住这个对象，每次调用getInstance()都要加锁，会使性能下降。
> 实际上，只有在第一次创建对象的时候需要加锁，之后就不需要了。


```java

     public static Singleton getInstance(){
        if ( instance == null ){
            synchronized(instance){
                if(instance == null){
                    instance == new Singleton();
                }
            }
        }
        return instance;
     }
```
> 这样解决了性能的问题，
> 但：在java指令中创建对象和赋值操作是分开进行的
>    instance = new Singleton(); 是分配内存，然后赋值，最后实例化。

  以 A B 两个线程为例：
  a --  A B 同时进入if(instance==null)

  b --  A 先进入 synchronized(instance),instance 是 null 的，所以执行instance= new Singleton()

  c --  JVM先划出了一部分内存，分给Singleton实例，并赋值给instance，A离开了synchronized块

  d --  B进入 synchronized(instance)，instance此时不是null，所以离开了块synchronized(instance)，并将结果返回给调用者
  
  e --  此时B直接使用Singleton的实例，但是还没有初始化，所以crash了

> 优化 -- 内部类（工厂类）

```java

     private static class SingletonFactoy{
        private static Singleton instance = new Singleton();
     }
     public static Singleton getInstance(){
        return SingletonFactory.instance;
     }
```

> 实际情况是，单例模式使用内部类来维护单例的实现，JVM内部的机制能够保证当一个类被加载的时候，这个类的加载过程是线程互斥的。这样当我们第一次调用getInstance的时候，JVM能够帮我们保证instance只被创建一次，并且会保证把赋值给instance的内存初始化完毕，这样我们就不用担心上面的问题。同时该方法也只会在第一次调用的时候使用互斥机制，这样就解决了低性能问题。这样我们暂时总结一个完美的单例模式：

```java
   
      public  class Singleton{
        private Singleton(){

        }
        private static class SingletonFactoy{
            private static Singleton instance = new Singleton();
        }
        public static Singleton getInstance(){
            return SingletonFactory.instance;
        }
        public Object readResolve(){
            return instance;
        }
     }
```

> 其实说它完美，也不一定，如果在构造函数中抛出异常，实例将永远得不到创建，也会出错。所以说，十分完美的东西是没有的，我们只能根据实际情况，选择最适合自己应用场景的实现方法。也有人这样实现：因为我们只需要在创建类的时候进行同步，所以只要将创建和getInstance()分开，单独为创建加synchronized关键字，也是可以的：

```java

    public  class Singleton{
        private static SingletonTest instance = null;
        private Singleton(){

        }
        private static synchronized void syncInit(){
            if(instance == null){
                instance==new SingeletonTest();
            }
        }

        public static SingletonTest getInstance(){
            if(instance == null){
                syncInit();
            }
            return instance;
        }
        public Object readResolve(){
            return instance;
        }
     }
```

> 考虑性能的话，整个程序只需创建一次实例，所以性能也不会有什么影响。

```java

      public  class Singleton{
        private static SingletonTest instance = null;
        private Vector properties = null;

        private Singleton(){

        }
        public Vector getProperties(){
            return properties;
        }
        private static synchronized void syncInit(){
            if(instance == null){
                instance==new SingeletonTest();
            }
        }

        public static SingletonTest getInstance(){
            if(instance == null){
                syncInit();
            }
            return instance;
        }
        public void updateProperties(){
            SingletonTest shadow = new SingletonTest();
            properties = shadow.getProperties();
        }
     }
```

### 总结--通过单例模式的学习告诉我们：

* 1、单例模式理解起来简单，但是具体实现起来还是有一定的难度。

* 2、synchronized关键字锁定的是对象，在用的时候，一定要在恰当的地方使用（注意需要使用锁的对象和过程，可能有的时候并不是整个对象及整个过程都需要锁）。

> others

* 首先，静态类不能实现接口。（从类的角度说是可以的，但是那样就破坏了静态了。因为接口中不允许有static修饰的方法，所以即使实现了也是非静态的）

* 其次，单例可以被延迟初始化，静态类一般在第一次加载是初始化。之所以延迟加载，是因为有些类比较庞大，所以延迟加载有助于提升性能。

* 再次，单例类可以被继承，他的方法可以被覆写。但是静态类内部方法都是static，无法被覆写。

* 最后一点，单例类比较灵活，毕竟从实现上只是一个普通的Java类，只要满足单例的基本需求，你可以在里面随心所欲的实现一些其它功能，但是静态类不行。从上面这些概括中，基本可以看出二者的区别，但是，从另一方面讲，我们上面最后实现的那个单例模式，内部就是用一个静态类来实现的，所以，二者有很大的关联，只是我们考虑问题的层面不同罢了。两种思想的结合，才能造就出完美的解决方案，就像HashMap采用数组+链表来实现一样，其实生活中很多事情都是这样，单用不同的方法来处理问题，总是有优点也有缺点，最完美的方法是，结合各个方法的优点，才能最好的解决问题！