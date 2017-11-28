---
layout: post
title: python md5 加密
categories: Python
description: 笔记
keywords: Python, md5
---

python md5 加密

## 链接

* [Python md5使用](http://mengweibbs.cn/2016/12/14/Python-md5jiami/)

##  内容

### md5

* Message Digest Algorithm MD5（中文名为消息摘要算法第五版）为计算机安全领域广泛使用的一种散列函数，用以提供消息的完整性保护。该算法的文件号为RFC 1321（R.Rivest,MIT Laboratory for Computer Science and RSA Data Security Inc. April 1992）。

> 特点

    MD5算法具有以下特点：

    1、压缩性：任意长度的数据，算出的MD5值长度都是固定的。

    2、容易计算：从原数据计算出MD5值很容易。

    3、抗修改性：对原数据进行任何改动，哪怕只修改1个字节，所得到的MD5值都有很大区别。

    4、强抗碰撞：已知原数据和其MD5值，想找到一个具有相同MD5值的数据（即伪造数据）是非常困难的。

> 应用

* 一致性验证
* 数字签名
* 安全访问认证

> 原理

    对MD5算法简要的叙述可以为：MD5以512位分组来处理输入的信息，且每一分组又被划分为16个32位子分组，经过了一系列的处理后，算法的输出由四个32位分组组成，将这四个32位分组级联后将生成一个128位散列值。
    总体流程如下图所示，
    表示第i个分组，每次的运算都由前一轮的128位结果值和第i块512bit值进行运算。
    MD5算法的整体流程图 

![](/images/blog/python/img_001.png)

* 填充 
* 初始化变量
* 处理分组数据
* 输出


> 使用

```python

    #!/usr/bin/env python

    import hashlib

    def md5(src):
        mymd5 = hashlib.md5() 
        mymd5.update(src)
        return mymd5.hexdigest()

    if __name__ == "__main__":
        print md5("hello")
```

* 输出 5d41402abc4b2a76b9719d911017c592
