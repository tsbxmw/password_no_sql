---
layout: post
title: go - websocket
categories: go
description: go - websocket
keywords: websocket, go
---

go websocket 使用与封装

# WebSocket

## websocket 协议

WebSocket 是 HTML5 开始提供的一种在单个 TCP 连接上进行全双工通讯的协议。

### Web 中前端获取后端实时信息的方法

> 前端通过对 api 进行轮询 （pull 的方式）

    现在，很多网站为了实现推送技术，所用的技术都是 Ajax 轮询。轮询是在特定的的时间间隔（如每1秒），由浏览器对服务器发出HTTP请求，然后由服务器返回最新的数据给客户端的浏览器。这种传统的模式带来很明显的缺点，即浏览器需要不断的向服务器发出请求，然而HTTP请求可能包含较长的头部，其中真正有效的数据可能只是很小的一部分，显然这样会浪费很多的带宽等资源。

> websocket

    WebSocket 使得客户端和服务器之间的数据交换变得更加简单，允许服务端主动向客户端推送数据。在 WebSocket API 中，浏览器和服务器只需要完成一次握手，两者之间就直接可以创建持久性的连接，并进行双向数据传输。

    在 WebSocket API 中，浏览器和服务器只需要做一个握手的动作，然后，浏览器和服务器之间就形成了一条快速通道。两者之间就直接可以数据互相传送。

## 前端技术

可以用来测试 websocket 后端接口的网址 http://www.websocket-test.com

> WebSocket 的属性

| 属性 | 作用 |
|--|--|
| readyState | 连接状态 |
| bufferedAmount | 放入 队列 但还没发出的字节数|

> 代码

```html
<!DOCTYPE HTML>
<html>
   <head>
   <meta charset="utf-8">
   <title>testWebsocket</title>
    
      <script type="text/javascript">
         var ws = null;
         var message = "";
         function connect(){
            if(ws != null) {
            } else {
               var inputValue = document.getElementById("socketurl").value;
               ws = new WebSocket(inputValue);
               console.log(ws)
            }

            ws.onmessage = function (evt) 
            { 
               message +=  "\nreceived : " + evt.data;
               document.getElementById("receive").value = message;
            };

            message +=  "\nconnect : " + ws.url;
            document.getElementById("receive").value = message;
         }

         function disconnect() {
            console.log(ws)
            if(ws != null) {
               ws.close()
            } 
            message +=  "\nclose ";
            document.getElementById("receive").value = message;
         }

         function send() {
            var inputValue = document.getElementById("inputtest").value;
            ws.send(inputValue);
            message +=  "\nsend : " + inputValue;
            document.getElementById("receive").value = message;
         }

      </script>
        
   </head>
   <body>
      <div>
         Socket Url 
         <div>
            <input id="socketurl" value="ws://localhost:8080/ws" />
            <a href="javascript:connect()"> 连接 </a>
            <a href="javascript:disconnect()"> 断开 </a>
         </div>
      </div>
      <div id="sse">
         <input id="inputtest" />
         <a href="javascript:send()">发送</a>
      </div>
      <div>
         <textarea id="receive" rows="10" cols="30" readonly=true>
         </textarea>
      </div>
      
   </body>
</html>
```


## 后端技术

这里，我们使用 go 来构建后端程序

### 原理

> websocket 是基于 tcp 协议实现的双向通信协议。

- 通过 http 协议进行连接的建立，然后升级到 websocket 协议。

- 连接建立成功后，前后端通过 websocket 进行通信

### 1 - 首先，启动一个 web 服务

```go
package main

import (
    "net/http"
)

func ws(res http.ResponseWriter, r *http.Request) {
    res.Write([]byte("helloworld"))
}

func main() {
    http.HandleFunc("/ws", ws)
    http.ListenAndServe(":8080", nil)
}

```

> 访问 http://localhost:8080/ws 可以获取返回值

```shell
helloworld
```

### 2 - 进行协议的转换，由 http 升级为 websocket

```go
package main

import (
    "fmt"
    "github.com/gogf/gf/third/github.com/gorilla/websocket"
    "net/http"
)

func websocketTest(res http.ResponseWriter, r *http.Request) {
    var (
        // websocket 的连接
        conn *websocket.Conn
        // 错误
        err error
        // 声明 upgrader，用于协议升级
        upgrader = websocket.Upgrader{
            // 用于进行跨域检测
            CheckOrigin: func(r *http.Request) bool {
                return true
            },
        }
    )
    // 这里进行协议的升级，由 res,r 进行转换为 websocket.Conn
    if conn, err = upgrader.Upgrade(res, r, nil); err != nil {
        return
    }

    for ; ; {
        var msgType int
        var data []byte
        var err error
        // 接收消息
        if msgType, data, err = conn.ReadMessage(); err != nil {
            conn.Close()
            return
        }
        fmt.Println(msgType)
        fmt.Println(data)
        // 回写消息
        if err = conn.WriteMessage(msgType, data); err != nil {
            conn.Close()
            return
        }
    }
}

func main() {
    http.HandleFunc("/ws", websocketTest)
    http.ListenAndServe(":8080", nil)
}

```

> 继续访问上面给出的网址 http://localhost:8080/ws 我们获得

```shell
Bad Request
```

```shell
Request URL: http://localhost:8080/ws
Request Method: GET
Status Code: 400 Bad Request
Remote Address: [::1]:8080
Referrer Policy: no-referrer-when-downgrade
```

> 此时的协议已经由 http 转换为 websocket，所以只能由 ws:// 请求

- 打开 html 文件，由上面的代码写入 test.html 构成

![](/images/blog/go/websocket-1.png)

- 输入 ws://localhost:8080/ws
- 可以看到连接建立
- 输入发送的信息，点击发送
- 获得服务端回写的信息
- 最后点击 close

```shell
connect : ws://localhost:8080/ws
send : 123
received : 123
close 
```

![](/images/blog/go/websocket-2.png)


### 进行封装

```go
package impl

import (
    "errors"
    "github.com/gogf/gf/third/github.com/gorilla/websocket"
    "net/http"
    "sync"
)
// 改编于 慕课网课程代码

type Connection struct {
    wsConn *websocket.Conn
    // 接收流
    inChan    chan []byte
    // 输入流
    outChan   chan []byte
    // 关闭流
    closeChan chan byte
    // 锁
    mutex sync.Mutex
    // 是否已关闭
    isClosed  bool
}

func InitConnection(res http.ResponseWriter, r *http.Request) (connNew *Connection, err error) {
    var (
        upgrader = websocket.Upgrader{
            CheckOrigin: func(r *http.Request) bool {
                return true
            },
        }
        conn *websocket.Conn
    )
    if conn, err = upgrader.Upgrade(res, r, nil); err != nil {
        return
    }

    connNew = &Connection{
        wsConn:    conn,
        inChan:    make(chan []byte, 1000),
        outChan:   make(chan []byte, 1000),
        closeChan: make(chan byte, 1),
    }
    go connNew.readLoop()

    go connNew.writeLoop()
    return
}

func (conn *Connection) ReadMessage() (data []byte, err error) {
    select {
    case data = <-conn.inChan:
    case <- conn.closeChan:
        err = errors.New("connection is closed")
    }
    return
}

func (conn *Connection) WriteMessage(data []byte) (err error) {
    select {
    case conn.outChan <- data:
    case <-conn.closeChan:
        err = errors.New("connection is closed")
    }
    return
}

func (conn *Connection) Close() {
    conn.wsConn.Close()
    conn.mutex.Lock()
    if !conn.isClosed{
        close(conn.closeChan)
        conn.isClosed = true
    }
    conn.mutex.Unlock()
}

func (conn *Connection) readLoop() {
    var (
        data []byte
        err  error
    )
    for ; ; {
        if _, data, err = conn.wsConn.ReadMessage(); err != nil {
            conn.Close()
        }
        select {
        case conn.inChan <- data:
        case <-conn.closeChan:
            conn.Close()
            return
        }
    }
    return
}

func (conn *Connection) writeLoop() {
    var (
        data []byte
        err  error
    )
    for ; ; {
        select {
        case data = <-conn.outChan:
        case <-conn.closeChan:
            conn.Close()
        }

        if err = conn.wsConn.WriteMessage(websocket.TextMessage, data); err != nil {
            conn.Close()
        }
    }
    return
}

```

### 使用方法

```go
package main

import (
    "net/http"
    "time"
    connImpl "ws/impl"
)

func ws(res http.ResponseWriter, r *http.Request) {
    var (
        data []byte
        err  error
    )

    var connNew *connImpl.Connection
    if connNew, err = connImpl.InitConnection(res, r); err != nil {
        return
    }

    //增加了 heartbeat
    go func() {
        var (
            err error
        )
        for ; ; {
            if err = connNew.WriteMessage([]byte("heart beat")); err != nil {
                return
            }
            time.Sleep(time.Second * 1)
        }
    }()

    for ; ; {
        if data, err = connNew.ReadMessage(); err != nil {
            connNew.Close()
            return
        }
        if err = connNew.WriteMessage(data); err != nil {
            connNew.Close()
            return
        }

    }

}

func main() {
    http.HandleFunc("/ws", ws)

    http.ListenAndServe(":8080", nil)
}

```

