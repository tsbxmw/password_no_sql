---
layout: post
title: Java 设计模式 - 建造者模式 - 原型模式
categories: Java
description: 笔记
keywords: Java, design mode
---

Java 设计模式 - 建造者模式 - 原型模式

## 内容

### 建造者模式（Builder）

* 建造者模式是将各种产品集中起来进行管理，用来创建复合对象
* 复合对象就是指某个类具有不同的属性，就是前面抽象工厂模式与测试类相结合。

> 例子 - 建造者模式


```java

     public  class Builder{
          private List<Sender> list = new ArrayList<Sender>();

          public void produceMailSender(int count){
            for(int i=0;i<count;i++){
              list.add(new MailSender());
            }
          }
          public void produceSmsSender(int count){
            for(int i=0;i<count;i++){
              list.add(new SmsSender());
            }
          }
     }
```

* Test class

```java

     public class Test{
        public static void main(String[] args){
          Builder builder = new Builder();
          builder.produceMailSender(10);
        }
     }
```

> 建造者模式将很多功能集成到一个类里，这个类可以创造出比较复杂的东西。



### 原型模式（Prototype）

* 原型模式是创建型模式，但是与工程模式没有关系。
* 该模式的思想就是讲一个对象作为原型，对其进行复制，克隆，产生一个和原对象类似的新对象。

> 例子 - 原型模式 

```java

     public class Prototype implements Cloneable{

        public Object clone() throws CloneNotSupportedException{
          Prototype proto = (Prototype)super.clone();
          return proto;
        }
     }
```
> 一个原型类，只要实现Cloneable接口，覆写clone()方法

* 深复制 ： 将一个对象复制后，不论是基本数据类型还是引用类型，都是重新创建的。
* 浅复制 ： 讲一个对象复制后，基本数据类型的变量都会重新创建，引用类型指向的还是原对象所指向的

> 例子 - 深浅复制

```java
  
     public class Prototype implements Cloneable,Serializable {
        private static final long serialVersionUID = 1L;
        private String string;
        private SerializableObject obj;

        //浅复制
        public Object clone() throws CloneNotSupportedException {
            Prototype proto = (Prototype)super.clone();
            return proto;
        }

        //深复制
        public Object deepClone() throws IOException,ClassNotFoundException{
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(bos);
            oos.writeObject(this);

            ByteArrayInputStream bis = new ByteArrayInputStream();
            ObjectInputStream ois = new ObjectInputStream(bis);
            return ois.readObject();
        }

        public String getString(){
          return string;
        }
        public void setString(String string){
          this.string = string;
        }

        public SerializableObject getObj(){
          return obj;
        }
        public void setObj(SerializableObject obj){
          this.obj = obj;
        }
     }

     class SerializableObject implements Serializable{
        private static final long serialVersionUID = 1L;
     }

* 深复制，需要采用流的方式读入当前对象的二进制输入，再写出二进制数据对应的对象。

