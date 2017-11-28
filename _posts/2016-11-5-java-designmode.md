---
layout: post
title: Java 设计模式 - 工厂方法模式
categories: Java
description: 笔记
keywords: Java, design mode
---

Java 设计模式 - 原则 - 工厂方法模式

## 内容

### 设计模式的6大原则

> 1 - 开闭原则（Open Close Principle）
  
  开闭原则就是说对扩展开放，对修改关闭。在程序需要进行拓展的时候，不能去修改原有的代码，实现一个热插拔的效果。所以一句话概括就是：为了使程序的扩展性好，易于维护和升级。想要达到这样的效果，我们需要使用接口和抽象类，后面的具体设计中我们会提到这点。

> 2 - 里氏代换原则（Liskov Substitution Principle）
  
  里氏代换原则(Liskov Substitution Principle LSP)面向对象设计的基本原则之一。 里氏代换原则中说，任何基类可以出现的地方，子类一定可以出现。 LSP是继承复用的基石，只有当衍生类可以替换掉基类，软件单位的功能不受到影响时，基类才能真正被复用，而衍生类也能够在基类的基础上增加新的行为。里氏代换原则是对“开-闭”原则的补充。实现“开-闭”原则的关键步骤就是抽象化。而基类与子类的继承关系就是抽象化的具体实现，所以里氏代换原则是对实现抽象化的具体步骤的规范

> 3 - 依赖倒转原则（Dependence Inversion Principle）
  
  这个是开闭原则的基础，具体内容：真对接口编程，依赖于抽象而不依赖于具体。。

> 4 - 接口隔离原则（Interface Segregation Principle）
  
  这个原则的意思是：使用多个隔离的接口，比使用单个接口要好。还是一个降低类之间的耦合度的意思，从这儿我们看出，其实设计模式就是一个软件的设计思想，从大型软件架构出发，为了升级和维护方便。所以上文中多次出现：降低依赖，降低耦合。

> 5 - 迪米特法则（最少知道原则）（Demeter Principle）
  
  为什么叫最少知道原则，就是说：一个实体应当尽量少的与其他实体之间发生相互作用，使得系统功能模块相对独立。

> 6 - 合成复用原则（Composite Reuse Principle）
  
  原则是尽量使用合成/聚合的方式，而不是使用继承。


### 工厂方法模式（Factory  Method）

#### 普通工厂模式

* 就是建立一个工厂类，对实现了同一接口的一些类进行实例的创建

> 例子

* 公共的接口 Sender

```java

        public interface Sender {
            public void Send();
        }
```

* 实现类 MailSender

```java

        public calss MailSender implements Sender {
            @Override
            public void Send(){
                System.out.println("this is MailSender");
            }
        }
```

* 实现类 SmsSender

```java

        public calss SmsSender implements Sender {
            @Override
            public void Send() {
                System.out.println("this is SmsSender");
            }
        }
```

* 实现工厂类 SendFactory

```java

        public class SendFactory {
            public Sender produce(String type){
                if("mail".equals(type)){
                    return new MailSender();
                }
                if("sms".equals(type)){
                    return new SmsSender();
                }
                else{
                    System.out.println("please input the right type");
                    return null;
                }
            }
        }
```

* 测试工厂类 FactoryTest

```java

        public class FactoryTest{
            public static void main(String [] args){
                SendFactory sendFactory = new SendFactory();
                Sender sender = sendFactory.produce("sms");
                sender.Send();
            }
        }
```

#### 多个工厂方法模式

* 就是对普通工厂方法模式的改进，在普通工厂方法模式中，如果传递的字符串出错，则不能正确的创建对象，而多个工厂方法模式是提供多个工厂方法，分别创建对象。

> 例子

* 公共的接口 Sender

```java

        public interface Sender {
            public void Send();
        }
```

* 实现类 MailSender

```java

        public calss MailSender implements Sender {
            @Override
            public void Send(){
                System.out.println("this is MailSender");
            }
        }
```

* 实现类 SmsSender

```java

        public calss SmsSender implements Sender {
            @Override
            public void Send() {
                System.out.println("this is SmsSender");
            }
        }
```

* 实现工厂类 SendFactory

```java

        public class SendFactory {
            public Sender produceMail(){
                return new MailSender();
            }
            
            public Sender produceSms(){
                return new SmsSender();
            }
            
        }
```

* 测试工厂类 FactoryTest

```java

        public class FactoryTest{
            public static void main(String [] args){
                SendFactory sendFactory = new SendFactory();
                Sender sender = sendFactory.producMail();
                sender.Send();
            }
        }
```

#### 静态工厂方法模式

* 就是将多个工厂方法模式里的方法设置为静态的，不需要创建实例，直接调用即可。

> 例子

* 公共的接口 Sender

```java

        public interface Sender {
            public void Send();
        }
```

* 实现类 MailSender

```java

        public calss MailSender implements Sender {
            @Override
            public void Send(){
                System.out.println("this is MailSender");
            }
        }
```

* 实现类 SmsSender

```java

        public calss SmsSender implements Sender {
            @Override
            public void Send() {
                System.out.println("this is SmsSender");
            }
        }
```

* 实现工厂类 SendFactory

```java

        public class SendFactory {
            public static Sender produceMail(){
                return new MailSender();
            }
            
            public static Sender produceSms(){
                return new SmsSender();
            }
        }
```

* 测试工厂类 FactoryTest

```java

        public class FactoryTest{
            public static void main(String [] args){
                Sender sender = SendFactory.produceMail();
                sender.Send();
            }
        }
```

#### 抽象工厂模式（Abstract  Factory）

* 工厂方法模式：类的创建依赖工厂类，也就是说，要想扩展程序，必须要对工厂类进行修改，这违背了闭包原则，
* 所以使用抽象工厂模式，创建多个工厂类，一旦需要增加新的功能，直接增加新的工厂类就可以了，不需要修改之前的代码。

> 例子


* 公共的接口 Sender

```java

        public interface Sender {
            public void Send();
        }
```

* 实现类 MailSender

```java

        public calss MailSender implements Sender {
            @Override
            public void Send(){
                System.out.println("this is MailSender");
            }
        }
```

* 实现类 SmsSender

```java

        public calss SmsSender implements Sender {
            @Override
            public void Send() {
                System.out.println("this is SmsSender");
            }
        }
```

* 公共的工厂类接口 Provider

```java

        public interface Provider{
            public Sender produce();
        }
```


* 实现工厂类 SendMailFactory

```java

        public class SendMailFactory implements Provider{
            @Override
            public Sender produce(){
                return new MailSender();
            }
        }
```

* 实现工厂类 SendSmsFactory

```java

        public class SendSmsFactory implements Provider{
            @Override
            public Sender produce(){
                return new SmsSender();
            }
        }
```

* 测试工厂类 FactoryTest

```java

        public class FactoryTest{
            public static void main(String [] args){
                Provider provider = new SendMailFactory();
                Sender sender = provider.produce();
                sender.Send();
            }
        }
```

### 总结

* 总体来说，工厂模式适合：凡是出现了大量的产品需要创建，并且具有共同的接口时，可以通过工厂方法模式进行创建。在以上的三种模式中，第一种如果传入的字符串有误，不能正确创建对象，第三种相对于第二种，不需要实例化工厂类，所以，大多数情况下，我们会选用第三种——静态工厂方法模式。

*  抽象工厂模式好处就是，如果你现在想增加一个功能：发及时信息，则只需做一个实现类，实现Sender接口，同时做一个工厂类，实现Provider接口，就OK了，无需去改动现成的代码。这样做，拓展性较好！