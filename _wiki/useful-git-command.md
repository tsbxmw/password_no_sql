---
layout: wiki
title: Useful git command
categories: Git
description: git commands
keywords: git, cmd
---


# useful git command 


links

[gitignore](https://github.com/github/gitignore)
[gitscm](https://git-scm.com/)


## git log

* show different of every commit
 
    git log -p  

* show files different

    git log --stat

* show --stat modify information

    git log --shortstat

* show file list after commit

    git log --name-only

* show new.modify.delete file list

    git log --name-status

* show sha-1 the head numbers not full

    git log --abbrev-commit

* use short time show

    git log --relative-date

* show ascii graph commit history

    git log --graph

* show other format commit history log

    git log --pretty

    here has lot : short , full , fuller , format , oneline

    git log --pretty=oneline  : show information at one line one commit
    git log --pretty=short    : show short information
    git log --pretty=full     : show full information
    git log --pretty=fuller   : show fuller information

    git log --pretty=format:"%h - %t"

|| 选项 || 说明 ||
| %H | 提交对象（commit）的完整哈希字串 |
| %h | 提交对象的简短哈希字串 |
| %T | 树对象（tree）的完整哈希字串 |
| %t | 树对象的简短哈希字串 |
| %P | 父对象（parent）的完整哈希字串 |
| %p | 父对象的简短哈希字串 | 
| %an | 作者（author）的名字 |
| %ae | 作者的电子邮件地址 |
| %ad | 作者修订日期（可以用 --date= 选项定制格式） |
| %ar | 作者修订日期，按多久以前的方式显示 |
| %cn | 提交者（committer）的名字 |
| %ce | 提交者的电子邮件地址 |
| %cd | 提交日期 | 
| %cr | 提交日期，按多久以前的方式显示 |
| %s | 提交说明 |

* show last n commit
    
    n is number
    git log -n

* show information at current date

    git log --since=2.week
    git log --since=2017-10-13
    git log --after=2017-10-12
    git log --until=today
    git log --before=today

* show information of author

    git log --author=wei.meng

* show infromation of committer
 
    git log --committer=wei.meng

* show key words commit

    git log --grep=hello

* show Key

    git log -Shelloworld


## git 撤销对文件的修改

* 重新提交

    git commit --amend 

* 取消暂存的文件

    git reset HEAD <file>

* 撤销对文件的修改(dangerous>

    git checkout -- file

## git remote use

* 查看远程仓库

    git remote -v

* 添加远程仓库

    git remote add name url

* 从远程仓库抓取或者拉取

    git fetch remote-name <branch>
 
    git pull remote-name <branch>

* 查看远程仓库

    git remote show origin 

* 移除与重命名

    git remote rename abc cab
    git remote rm cab

## git tag

* 列出标签

    git tag

* 创建标签

    git tag -a tag-name -m "tag-information"

* 创建轻量标签
    
    git tag

* 后期打标签

    git tag -a commit-id

* 共享标签

    git push origin tagname

    git push origin --tags



## git 别名

* 设置别名

    git config --global alias.co checkout


