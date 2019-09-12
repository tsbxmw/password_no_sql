---
layout: post
title: go - consul 服务注册
categories: go
description: go - consul 服务注册
keywords: go
---

go - consul 服务注册

# consul

consul 是微服务架构中的 服务注册与发现 中间件。

## consul 安装

### 具体安装过程

> https://learn.hashicorp.com/consul/getting-started/install

### 官网 demo

> https://demo.consul.io/ui/

# 使用 go 进行连接

## go web 程序编写

使用 go 编写一个简单的 web 服务程序

> main.go

```go
package main

import (
  "fmt"
  "net/http"
)

// test 用来处理 来自 /test 的请求
func test(w http.ResponseWriter, r *http.Request) {
    fmt.Println(r.URL)
    w.Write([]byte("hello world"))
}

func main(){
  http.HandleFunc("/test", test)
  // 在端口 8099 启动服务器
  http.ListenAndServe(":8099", nil)
}

```
    

## 注册 consul

### 首选要获取 go 的 consul 包

```shell
go get -u github.com/hashicorp/consul/api
```
  
### 获取 go kit 包

```shell
go get -u github.com/go-kit/kit
```

### 使用 go 进行连接

> main.go

```go
package main

import (
    "fmt"
    "github.com/go-kit/kit/log"
    "github.com/go-kit/kit/sd/consul"
    "github.com/hashicorp/consul/api"
    "net/http"
)

func test(w http.ResponseWriter, r *http.Request) {
    fmt.Println(r.URL)
    w.Write([]byte("hello world"))
}

func main() {
    RegisterConsul()

    http.HandleFunc("/", test)
    http.ListenAndServe("localhost:8099", nil)
}

func RegisterConsul() {
    serviceName := "test"
    address := "localhost"
    port := 8099
    consulConfig := api.DefaultConfig()
    consulConfig.Address = "http://localhost:8500"
    consulClient, err := api.NewClient(consulConfig)
    if err != nil {
        fmt.Println("consul_err", err)
    }
    client := consul.NewClient(consulClient)
    asg := &api.AgentServiceRegistration{
        ID:      fmt.Sprintf("%s:%s:%d", serviceName, address, port),
        Name:    serviceName,
        Port:    port,
        Address: address,
        Check: &api.AgentServiceCheck{
            DeregisterCriticalServiceAfter: "5m",
            Interval:                       "10s",
            TCP:                            fmt.Sprintf("%s:%d", address, 8099),
        },
    }
    register := consul.NewRegistrar(client, asg, log.NewNopLogger())
    register.Register()
}

```

> 首先使用 api.DefaultConfig() 创建默认的 consulConfig

```go
consulConfig := api.DefaultConfig
consulConfig.Address = "http://localhost:8500"
```

> 然后使用 consulConfig 创建 consulClient

```go
consulClient := api.NewClient(consulConfig)
```

> 然后使用 go-kit consul 创建 client

```go
client := consul.NewClient(consulClient)
```

> 配置参数

```go
asg := &api.AgentServiceRegistration{
      ID:      fmt.Sprintf("%s:%s:%d", serviceName, address, port),
      Name:    serviceName,
      Port:    port,
      Address: address,
      Check: &api.AgentServiceCheck{
          DeregisterCriticalServiceAfter: "5m",
          Interval:                       "10s",
          TCP:                            fmt.Sprintf("%s:%d", address, 8099),
      },
  }
```

> 创建 register

```go
register := consul.NewRegistrar(client, asg, log.NewNopLogger())
```

> 注册

```go
register.Register()
```

