---
layout: post
title: leetcode - 对称二叉树 - 101
categories: leetcode
description: 对称二叉树 - 101
keywords: python3, leetcode, go
---

leetcode - 相同的树 - 101

# Question 1

    给定一个二叉树，检查它是否是镜像对称的。

    例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

       1
      / \
     2   2
    / \ / \
   3  4 4  3
    但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

       1
      / \
     2   2
      \   \
      3    3

    说明:

    如果你可以运用递归和迭代两种方法解决这个问题，会很加分。

## 思路

    
### 递归

    与 100 - 相同的树相比，这里只需要对比一棵树的左右子树。
    
    所以使用递归方法的话，只需要对比左子树和右子树即可。
    然后递归对比 {
        左子树的左子树和右子树的右子树
        左子树的右子树和右子树的左子树
    }

> 比如第一个例子

            1                1(id 1)
          /   \             /       \
         2     2        2(id 2)     2(id 3)
        / \   / \        /   \        /    \
       3   3 3   3  3(id 4) 3(id 5) 3(id 6) 3(id 7)


1. 对比 左子树 id=2  和 右子树 id=3 ==> 2 == 2
2. 对比 左子树 id=2 的 左子树 id=4 和 右子树 id=3 的 右子树 id=7 ==> 3 == 3
3. 对比 左子树 id=2 的 右子树 id=5 和 右子树 id=3 的 左子树 id=6 ==> 3 == 3



## 递归代码

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def isSymmetric(self, root: TreeNode) -> bool:
        
        def check(left, right):
            if left is None and right is None:
                return True
            if left is None or right is None:
                return False
            
            return left.val==right.val and check(left.left, right.right) and check(left.right, right.left)
        return check(root, root)
```