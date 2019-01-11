---
layout: post
title: leetcode - 807 保持城市天际线， 78 子集
categories: python3
description: leetcode - 807 保持城市天际线， 78 子集
keywords: python3, leetcode
---

leetcode - 数字字母， 全排列

# Question 1

    给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

    给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

    {'2':'abc', '3':'def', '4':'ghi', '5':'jkl', '6':'mno', '7':'pqrs', '8':'tuv', '9':'wxyz'}

    示例:

    输入："23"
    输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

## 思路

- 深度搜索

## Code

```python
    class Solution:
        def letterCombinations(self, digits):
            """
            :type digits: str
            :rtype: List[str]
            """
            ln = {'2':'abc', '3':'def', '4':'ghi', '5':'jkl', '6':'mno', '7':'pqrs', '8':'tuv', '9':'wxyz'}
                        
            result = []
            ld = len(digits)
            if ld==0:
                return result
            if ld==1:
                return [x for x in ln[digits]]
            
            def dfs(s, flag):
                if flag>=ld:
                    result.append(s)
                    return
                for x in ln[digits[flag]]:
                    dfs(s+x, flag+1)
                    
            dfs("", 0)
            return result
```

# Question 2 

    给定一组不含重复元素的整数数组 nums，返回该数组所有可能的排列。

    说明：解集不能包含重复的子集。
    
    示例:
    
    输入: nums = [1,2,3]
    输出:
    [
        [1,2,3],
        [1,3,2],
        [2,1,3],
        [2,3,1],
        [3,1,2],
        [3,2,1]
    ]
    
## 思路

- 回溯

## Code

```python
    class Solution:
        def subsets(self, nums):
            """
            :type nums: List[int]
            :rtype: List[List[int]]
            """
            ln = len(nums)
            if ln == 0:
                return []
            def find(temp, flag, rev):
                if flag==ln:
                    rev.append(temp)
                else:
                    for num in nums:
                        if num not in temp:
                            temp = copy.deepcopy(temp)
                            temp.append(num)
                            find(temp, flag+1, rev)
                            temp.remove(num)
            rev=[]
            find([], 0, rev)
            return rev
```
