---
layout: post
title: leetcode - 807 保持城市天际线， 78 子集
categories: leetcode
description: leetcode - 807 保持城市天际线， 78 子集
keywords: python3, leetcode
---

leetcode - 807 保持城市天际线， 78 子集

# Question 1

    在二维数组grid中，grid[i][j]代表位于某处的建筑物的高度。 我们被允许增加任何数量（不同建筑物的数量可能不同）的建筑物的高度。 高度 0 也被认为是建筑物。

    最后，从新数组的所有四个方向（即顶部，底部，左侧和右侧）观看的“天际线”必须与原始数组的天际线相同。 城市的天际线是从远处观看时，由所有建筑物形成的矩形的外部轮廓。 请看下面的例子。

    建筑物高度可以增加的最大总和是多少？

    例子：
    输入： grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
    输出： 35
    解释： 
    The grid is:
    [ 
    [3, 0, 8, 4], 
    [2, 4, 5, 7],
    [9, 2, 6, 3],
    [0, 3, 1, 0] ]

    从数组竖直方向（即顶部，底部）看“天际线”是：[9, 4, 8, 7]
    从水平水平方向（即左侧，右侧）看“天际线”是：[8, 7, 9, 3]

    在不影响天际线的情况下对建筑物进行增高后，新数组如下：

    gridNew = [ [8, 4, 8, 7],
                [7, 4, 7, 7],
                [9, 4, 8, 7],
                [3, 3, 3, 3] ]
    说明:

    1 < grid.length = grid[0].length <= 50。
    grid[i][j] 的高度范围是： [0, 100]。
    一座建筑物占据一个grid[i][j]：换言之，它们是 1 x 1 x grid[i][j] 的长方体。

## 思路

- 天际线 分 2个方向， 即‘列天际线’ 和 ‘行天际线‘
- 首先获取 2 个方向的天际线： 即 [9, 4, 8, 7] & [8, 7, 9, 3]
- 填充 原数组，i,j  所在位置的最大值 为 行[i] 和 列[j] 的 最小值
- 故 rev+=(min([x, y]) - grid[i][j])

## Code

```python
    class Solution:
    def maxIncreaseKeepingSkyline(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        lm = len(grid)
        if lm == 0:
            return 0
        ln = len(grid[0])
        if ln == 0:
            return 0
        t_r = []
        t_c = []
        for g in grid:
            t_r.append(max(g))
        for i in range(ln):
            t_c.append(max([grid[x][i] for x in range(lm)]))
                            
        rev = 0
        for i, x in enumerate(t_r):
            for j, y in enumerate(t_c):
                rev+=(min([x, y]) - grid[i][j])
        return rev              
```

# Question 2 

    给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

    说明：解集不能包含重复的子集。
    
    示例:
    
    输入: nums = [1,2,3]
    输出:
    [
      [3],
      [1],
      [2],
      [1,2,3],
      [1,3],
      [2,3],
      [1,2],
      []
    ]
    
## 思路

- 深度搜索
- 生成原始列表 [[]]
- 逐步根据元素扩展 原始列表
- 1, [[]]  -  1 --> [[], [1]]
- 2, [[], [1]] - 2 --> [[], [1], [2], [1, 2]]
- 3, [[], [1], [2], [1, 2]] - 3 --> [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]

## Code

```python
    class Solution:
        def subsets(self, nums):
            """
            :type nums: List[int]
            :rtype: List[List[int]]
            """
            rev = [[]]
            ln = len(nums)
            def dfs(flag, r, rev):
                if flag == ln:
                    return rev
    
                for x in r:
                    x.append(nums[flag])
                    rev.append(x)
                temp = []
                for x in rev:
                    t=[]
                    for y in x:
                        t.append(y)
                    temp.append(t)
                dfs(flag+1, temp, rev)
                
            dfs(0, [[]], rev)
            return rev
```
