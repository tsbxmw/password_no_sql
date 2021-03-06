---
layout: post
title: Python GC - 垃圾回收机制
categories: Python
description: Python - GC 垃圾回收机制
keywords: gpythono
---

python - GC 垃圾回收机制

# python的垃圾收集


## python 的垃圾回收主要通过以下方式进行

> 引用循环

找到涉及列表、元组、实例、类、字典和函数的引用循环。

> ```__del__``` 

- 使用 ```__del__``` 方法的实例是以一种合理的方式处理的。
- 所以向新类型添加gc支持很容易，只需要实现 ```__del__``` 即可。

> 按照代划分

- 分代回收工作良好（目前为三代）。
- 使用分代回收的Pybench测量的间接费用约为4%。
- 一个名为gc的新模块可用于调整收集器和设置调试选项。

> 收集器是可跨所有平台使用的。

- 自2.0版以来，可移植垃圾回收就包含在python中。
- 默认情况下启用。



## 引用计数 

> 什么是引用计数

    当前版本的python使用引用计数来跟踪分配的内存。python中的每个对象都有一个引用计数，它指示有多少对象指向它。当这个引用计数达到零时，对象被释放。

> 引用循环

    这对大多数程序都很有效。然而，参考计数有一个基本缺陷，这就是 引用环。

- ```引用环```的最简单示例是一个引用自身的对象。例如：

```python
l = []
l.append(l)
del l
```

    创建的列表的引用计数现在为1。但是，由于不能从python内部访问它，也不能再使用它，所以应该将其视为垃圾。在当前版本的python中，这个列表将永远不会被释放。

    创建 引用环 通常不是很好的编程实践，而且几乎总是可以避免的。然而，有时很难避免创建 引用环 ，而有时程序员甚至没有意识到它正在发生。对于长时间运行的程序（如服务器），这尤其麻烦。人们不希望服务器内存耗尽，因为引用计数无法释放无法访问的对象。对于大型程序，很难找到如何创建引用循环。

## 传统的垃圾收集

> “传统”垃圾收集怎么办？


1,  找到系统的根对象。这些是全局环境（如python中的主模块）和堆栈上的对象。

2, 从这些对象中搜索并找到所有可从中访问的对象。这些物体都是“活的”。

3, 释放所有其他对象。

> 不能工作在 python 中， 最好的办法是我们能找到一种既能使用```引用计数```又能避免```引用环```的方法。

- 由于扩展模块的工作方式，python永远无法完全确定根集。
- 如果不能准确地确定根集，我们就有可能从某个地方释放仍然被引用的对象。
- 即使扩展模块的设计不同，也无法通过可移植的方式找到C堆栈上当前的对象。
- 此外，引用计数在内存引用的局部性和终结器语义方面提供了一些python程序员所期望的好处。


> 如何设计这种方法？
  
    从概念上讲，这种方法与传统的垃圾收集相反。它不是试图找到所有可到达的对象，而是试图找到无法到达的对象。这更安全，因为如果算法失败，我们不会比没有垃圾收集更糟糕（除了浪费时间和空间）。

- 由于我们仍在使用```引用计数```，垃圾收集器只需找到```引用环```。
- ```引用计数```将处理释其他类型的垃圾。
- 首先，我们观察到```引用循环```只能由```容器```对象创建。
- 这些对象可以保存对其他对象的引用。在python中，```列表、字典、实例、类和元组```都是```容器对象```的示例。整数和字符串不是容器。通过这个观察，我们意识到为了垃圾收集的目的，可以忽略非容器对象。这是一个有用的优化，因为像整数和字符串这样的东西应该是快速和小的。


> 跟踪所有容器对象

- 有几种方法可以做到这一点，但最好的方法之一是在对象结构中使用具有链接字段的双链接列表。
- 这使得对象可以快速地从集合中插入和移除，并且不需要额外的内存分配。创建容器时，将其插入此集中，删除时将其删除。

> 既然我们可以访问所有容器对象，那么如何找到```引用环```呢？

1. 首先，除了两个链接指针之外，我们还向容器对象添加了另一个字段。我们将此字段称为gc_refs。
2. 以下是查找参考周期的步骤：

- 对于每个容器对象，将 ```gc_refs``` 设置为等于该对象的引用计数。

- 对于每个容器对象，查找它引用的容器对象，并减小被引用容器的 ```gc_refs``` 字段。

- 现在具有大于一个```gc_refs```字段的所有容器对象都是从容器对象集外部引用的。我们无法释放这些对象，所以我们将它们移动到另一个集合。

- 从移动的对象中的只要是被引用的任何对象也不能被释放。我们移动它们，而且所有的对象都是从他们可达的。

- 留在原始集合中的对象只被该集合中的对象引用（即，它们在python中不可访问并且是垃圾）。我们现在可以开始释放这些对象了。

## 终结器的问题

> 关于终结器的使用。

- 在python中，终结器执行的 ```__del__``` 是实例上的方法。
- 例如计数终结器工作正常。当对象的引用计数为零时，在释放对象之前调用终结器
- 对于垃圾收集，调用终结器成为一个棘手的问题，尤其是在 ```引用环``` 面前。

    如果一个引用周期中的两个对象都有终结器，应该怎么做？应该先叫哪个？调用第一个终结器后，无法释放对象，因为第二个终结器仍可以访问该对象。



    由于没有很好的解决方案来解决此问题，因此不会释放存在 ```引用环``` 的具有 ```终结器``` 的对象的内存。
    相反，这些对象被添加到一个不可收集垃圾的全局列表中。几乎总是可以重写程序，这样就不会发生这种情况。作为最后的手段，程序可以访问全局列表和释放 ```引用环```，这对应用程序是有意义的。


### 这样的代价呢？

    正如有些人所说，没有免费的午餐。然而，这种垃圾收集方式相当便宜。根据pybench的数据，对于当前版本的收集器，这一开销大约占了4%的减速。

- 最大的成本之一是每个容器对象所需的三个额外的内存字。
- 还有维护容器集的开销。

- 收集器当前跟踪三代对象。

      通过调整收集参数，可以使收集所花费的时间尽可能少。
      对于某些应用程序，禁用自动收集并显式调用收集例程可能是有意义的。
      但是，使用默认的收集参数，在运行pybench时，收集所花的时间似乎并不重要。
      显然，广泛分配容器对象的应用程序将导致花更多的时间收集。


