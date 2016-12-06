---
layout: page
title: About
description: Main Page
keywords: MengWei,孟伟
comments: true
menu: 关于
permalink: /about/
---

我是孟伟，梦而生，梦而伟


## 联系

* GitHub:[@tsbxmw](https://github.com/tsbxmw)
* 博客：[{{ site.title }}]({{ site.url }})
* 微博: [@mengwei](http://weibo.com/jyhemw)
* 知乎: [@mengwei](https://www.zhihu.com/people/man-xiao-ne/activities)

## Skill Keywords

#### Software Engineer Keywords
<div class="btn-inline">
    {% for keyword in site.skill_software_keywords %}
    <button class="btn btn-outline" type="button">{{ keyword }}</button>
    {% endfor %}
</div>

#### Mobile Developer Keywords
<div class="btn-inline">
    {% for keyword in site.skill_mobile_app_keywords %}
    <button class="btn btn-outline" type="button">{{ keyword }}</button>
    {% endfor %}
</div>

#### Windows Developer Keywords
<div class="btn-inline">
    {% for keyword in site.skill_windows_keywords %}
    <button class="btn btn-outline" type="button">{{ keyword }}</button>
    {% endfor %}
</div>
