---
layout: post
title: leetcode - 盛水最多的容器 11
categories: python3
description: leetcode - 盛水最多的容器
keywords: python3, leetcode, go
---

leetcode - 盛水最多的容器 - 11

# Question 1

    给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
    在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。
    找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

    说明：你不能倾斜容器，且 n 的值至少为 2。

![](/images/blog/leetcode/3.jpg)

## 思路

    
- 盛水的多少，取决于底和高。

    高只取决于最低的那条边，所以取 min(height[head], height[tail])

    底就是当前两条高之间的距离, tail - head

    所以面积为 : (tail-head) * min(height[head], height[tail])

- 何时更新 head 和 tail 呢？

    当 height[head] < height[tail] 时，继续更新 tail = tail-1 则 损失了可能作为 高 的 height[tail], 而且 底 是在减小的， 所以只会获取更小的值。

    1， 当前值 height[head] * (tail-head)
    2， 更新值 height[head+1] * (tail-head)
    

- 整体逻辑

```python
    while head < tail:
        area = max(area, (tail-head)*min(height[head], height[tail]))
        if height[head]<height[tail]:
            head += 1
        else :
            tail -= 1
```

### 暴力法

    遍历每组可能出现的组合，寻找最大值。
    
> 分析

    时间复杂度为 O(n*(n-1))

```go
func maxArea(height []int) int {
    maxArea := 0
    length := len(height)
    for i:=0; i<length; i++ {
        for j:=i+1; j<length; j++ {
            tempHeight := height[j]
            if height[i]<height[j]{
                tempHeight = height[i]
            }
            tempArea := (j-i) * tempHeight
            if tempArea > maxArea {
                maxArea = tempArea
            }
        }
    }
    return maxArea
}
```

### 双指针法

    头指针与尾指针向中间遍历。

> 分析

    前后双指针

```go
func maxArea(height []int) int {
    maxArea := 0
    length := len(height)
    head := 0
    tail := length - 1
    for ;; {
        if head >= tail{
            break
        }
        tempHeight := height[tail]
        if height[head] < height[tail]{
            tempHeight = height[head]
        } 
        areaTemp := tempHeight * (tail-head)
        if areaTemp > maxArea{
            maxArea = areaTemp
        }
        
        if height[head] > height[tail]{
            tail = tail - 1
        } else {
            head = head + 1
        }
    }
    return maxArea
}
```
