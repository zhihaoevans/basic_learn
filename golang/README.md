# Go 基础语法示例

Go（Golang）是 Google 开源的静态强类型编译型语言，以语法精简、编译飞快、原生并发（goroutine/channel）与齐全的标准库著称，广泛用于云原生、后端服务与命令行工具。本目录按 [TOPICS.md](../TOPICS.md) 的统一主题清单组织：一个主题一个自包含的可运行示例（`package main` + `main` 函数），用 `fmt.Println` 逐个知识点演示结果。

- 官方文档：[Go 官方之旅（中文）](https://go.dev/tour/list) ｜ [Effective Go](https://go.dev/doc/effective_go) ｜ [标准库参考 pkg.go.dev](https://pkg.go.dev/std)

## 环境要求

- **Go 1.23+**（仅 13_stdlib 的 maps.Keys 需要；其余示例 1.20+ 即可）
- 安装：从 [go.dev/dl](https://go.dev/dl/) 下载安装，`go version` 确认版本
- 全部示例仅用标准库，无需任何第三方依赖，也无需 go.mod（逐文件运行）

## 如何运行

在仓库根目录执行（与 CI 的验证方式相同）：

```bash
go run golang/03_operator.go
```

一次性 vet + 运行全部示例（本地门禁，CI 同款）：

```bash
for f in golang/*.go; do go vet "$f" && go run "$f" >/dev/null || echo "FAIL: $f"; done
```

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [hello.go](hello.go) | `go run golang/hello.go` | Hello World 与 fmt.Println |
| 02 variable | [variable.go](variable.go) | `go run golang/variable.go` | var 声明、:= 短声明与类型推断 |
| 02 variable | [const.go](const.go) | `go run golang/const.go` | const 常量 |
| 03 operator | [03_operator.go](03_operator.go) | `go run golang/03_operator.go` | 算术/比较/逻辑短路、位运算（含 &^）、++ 是语句、优先级 |
| 04 string | [04_string.go](04_string.go) | `go run golang/04_string.go` | 不可变、len 按字节、rune 遍历、strings/strconv、fmt 动词 |
| 05 control | [if.go](if.go) | `go run golang/if.go` | if/else |
| 05 control | [for.go](for.go) | `go run golang/for.go` | for 循环（Go 唯一的循环关键字） |
| 05 control | [switch.go](switch.go) | `go run golang/switch.go` | switch 分支 |
| 06 function | [func.go](func.go) | `go run golang/func.go` | 函数定义与调用 |
| 07 collection | [array.go](array.go) | `go run golang/array.go` | 定长数组 |
| 07 collection | [slice.go](slice.go) | `go run golang/slice.go` | 切片与 append |
| 08 map | [map.go](map.go) | `go run golang/map.go` | map 字面量与访问 |
| 09 oop | [struct.go](struct.go) | `go run golang/struct.go` | 结构体定义与初始化 |
| 09 oop | [method.go](method.go) | `go run golang/method.go` | 值接收者方法 |
| 09 oop | [interface.go](interface.go) | `go run golang/interface.go` | 接口与隐式实现 |
| 10 error | [error.go](error.go) | `go run golang/error.go` | error 多返回值与检查 |
| 11 file_io | [11_file_io.go](11_file_io.go) | `go run golang/11_file_io.go` | ReadFile/WriteFile、Scanner 逐行、CreateTemp+defer 清理 |
| 12 module | [package.go](package.go) | `go run golang/package.go` | 包导入（import）与标准库调用 |
| 13 stdlib | [13_stdlib.go](13_stdlib.go) | `go run golang/13_stdlib.go` | strings/slices/maps/strconv/time 常用标准库速览 |
| 14 concurrency | [goroutine.go](goroutine.go) | `go run golang/goroutine.go` | go 关键字启动协程 |
| 14 concurrency | [channel.go](channel.go) | `go run golang/channel.go` | 无缓冲通道收发 |
| 14 concurrency | [select.go](select.go) | `go run golang/select.go` | select 多路复用 |
| 15 generic | [15_generic.go](15_generic.go) | `go run golang/15_generic.go` | [T any] 泛型函数、comparable 键约束、Stack[T] 泛型类型 |
| + 特色 | [defer.go](defer.go) | `go run golang/defer.go` | defer 延迟执行（LIFO） |
| + 特色 | [recover.go](recover.go) | `go run golang/recover.go` | panic/recover 兜底 |
| + 特色 | [pointer.go](pointer.go) | `go run golang/pointer.go` | 指针与 * 取值 |

## 进阶说明

- 新增的 5 个示例（03/04/11/13/15）文件头部注释标明主题说明、运行命令与预期输出，适合按主题顺序阅读；早期 21 个示例保持极简风格
- 之后的进阶方向：错误包装（errors.Is/As）、并发原语（sync.Mutex/WaitGroup/context）、单元测试（testing）、泛型约束进阶（cmp.Ordered 与迭代器 range over func）
- 仓库内的 Go 专题练习见 [languages/go](../languages/go/)（早期章节式结构，以 go test 验证）
