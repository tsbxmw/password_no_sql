---
layout: post
title: Python tools
categories: Python
description: bookmark
keywords: Python
---
Python tools

## 链接

* nothing here

##  摘要
    
    Python usage infomation

----------

## 内容    

### pyinstaller

> install

```python
    pip install pyinstaller 
```
    using this command to install py2exe tool - pyinstaller

> use

    using cmd at windows to using it.

* cmd : pyinstaller -F pyx.py

    -F : would compile the pyx.py to only one exe file , it is easy to copy or use.

### delorean

> a cool time show 

```python
    from delorean import Delorean
    
    EST ="US/Eastern"
    d = Delorean(timezone=EST)
```

### prettytable

> a good terminal output 

```python


    from prettytable import PrettyTable

    table = PrettyTable(["animal", "ferocity"])

    table.add_row(["wolverine", 100])

    table.add_row(["grizzly", 87])

    table.add_row(["Rabbit of Caerbannog", 110])

    table.add_row(["cat", -1])

    table.add_row(["platypus", 23])

    table.add_row(["dolphin", 63])

    table.add_row(["albatross", 44])

    table.sort_key("ferocity")

    table.reversesort = True

    +----------------------+----------+

    |        animal        | ferocity |

    +----------------------+----------+

    | Rabbit of Caerbannog |   110    |

    |      wolverine       |   100    |

    |       grizzly        |    87    |

    |       dolphin        |    63    |

    |      albatross       |    44    |

    |       platypus       |    23    |

    |         cat          |    -1    |

    +----------------------+----------+
    
```

### sh
    
> import shell as function

```python
        

    from sh import find

    find("/tmp")

    /tmp/foo

    /tmp/foo/file1.json

    /tmp/foo/file2.json

    /tmp/foo/file3.json

    /tmp/foo/bar/file3.json


```


> #### LINK

* nothing to show
