---
layout: post
title: leetcode - 相同的树 - 100
categories: leetcode
description: 相同的树 - 100
keywords: python3, leetcode, go
---

leetcode - 相同的树 - 100

# Question 1

    给定两个二叉树，编写一个函数来检验它们是否相同。

    如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

    示例 1:

    输入:     1         1
             / \       / \
            2   3     2   3

            [1,2,3],   [1,2,3]

    输出: true
    示例 2:

    输入:     1         1
            /           \
           2             2

        [1,2],     [1,null,2]

    输出: false
    示例 3:

    输入:     1         1
            / \       / \
           2   1     1   2

          [1,2,1],   [1,1,2]

    输出: false

## 思路

    
- 递归

    不断对比树的相同位置的节点值。

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def isSameTree(self, p: TreeNode, q: TreeNode) -> bool:
        # 如果当前节点都是 空，则返回 True
        if not p and not q:
            return True
        # 如果只有一个节点存在，则返回 False
        if ( not p or not q ) or p.val != q.val:
            return False
        # 遍历左子树
        if not self.isSameTree(p.left, q.left):
            return False
        # 遍历右子树
        if not self.isSameTree(p.right, q.right):
            return False
        
        return True
```