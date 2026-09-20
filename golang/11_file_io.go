// 主题说明：Go 文件读写 —— os.ReadFile/WriteFile 整读整写、os.Create + bufio.Scanner 逐行、
//           os.OpenFile 追加提示，以及 os.CreateTemp 临时文件 + defer 清理、defer Close 习惯。
// 运行命令：go run golang/11_file_io.go
// 预期输出（关键行）：
//   [1] os.ReadFile 读到 78 字节（中文按 UTF-8 每字 3 字节）
//   [2] os.Create + WriteString 写入 4 行
//   [3] Scanner 逐行读回：
//       | Go 文件读写三件套：
//   [4] 临时文件名以 basic_learn_11_ 开头: true （main 返回时由 defer 自动删除）
package main

import (
    "bufio"
    "fmt"
    "os"
    "path/filepath"
    "strings"
)

func main() {
    // 知识点 0：临时文件 —— os.CreateTemp 在系统临时目录创建名字唯一的文件。
    // 名字模式中的 * 会被替换成随机串（并发下也不冲突）；目录版是 os.MkdirTemp。
    // 用 defer 注册清理：无论 main 正常返回还是提前 return，临时文件都会被删除。
    tmp, err := os.CreateTemp("", "basic_learn_11_*.txt")
    if err != nil {
        fmt.Println("创建临时文件失败:", err)
        return
    }
    path := tmp.Name()
    tmp.Close()             // 先关掉初始句柄，后续统一按文件名操作
    defer os.Remove(path)   // defer 清理临时文件（后注册的后执行，见 defer.go）

    // 知识点 1：os.WriteFile / os.ReadFile —— 一步写入/读出整个文件，小文件首选
    //   WriteFile(文件名, 数据, 权限)：不存在则创建，存在则覆盖；0o644 = 属主读写、其他人只读
    content := "第一行：WriteFile 一次写入整文件\n第二行：演示文件共两行\n"
    if err := os.WriteFile(path, []byte(content), 0o644); err != nil {
        fmt.Println("写入失败:", err)
        return
    }
    data, err := os.ReadFile(path)
    if err != nil {
        fmt.Println("读取失败:", err)
        return
    }
    fmt.Printf("[1] os.ReadFile 读到 %d 字节（中文按 UTF-8 每字 3 字节）\n", len(data))

    // 知识点 2：os.Create + WriteString —— 显式句柄的写入方式，习惯搭配 defer Close
    f, err := os.Create(path) // 存在则清空重写（想要追加用 os.OpenFile + os.O_APPEND）
    if err != nil {
        fmt.Println("创建文件失败:", err)
        return
    }
    lines := []string{
        "Go 文件读写三件套：",
        "1) os.ReadFile / os.WriteFile 整读整写",
        "2) os.Open + bufio.Scanner 逐行处理",
        "3) os.CreateTemp + defer 清理临时文件",
    }
    for _, line := range lines {
        if _, err := f.WriteString(line + "\n"); err != nil {
            fmt.Println("写入失败:", err)
            return
        }
    }
    if err := f.Close(); err != nil { // 写完显式 Close 并检查错误（也可 defer，但会丢错到返回后）
        fmt.Println("关闭失败:", err)
        return
    }
    fmt.Println("[2] os.Create + WriteString 写入", len(lines), "行")

    // 知识点 3：os.Open + bufio.Scanner 逐行读取 —— 大文件的标准姿势（不会一次性进内存）
    rf, err := os.Open(path)
    if err != nil {
        fmt.Println("打开失败:", err)
        return
    }
    defer rf.Close() // defer Close：函数返回时统一释放句柄
    fmt.Println("[3] Scanner 逐行读回：")
    scanner := bufio.NewScanner(rf)
    for scanner.Scan() { // 每轮读一行；Text() 返回不含换行符的内容
        fmt.Println("    |", scanner.Text())
    }
    if err := scanner.Err(); err != nil { // 循环结束后统一检查扫描错误
        fmt.Println("扫描出错:", err)
    }

    // 知识点 4：确认临时文件机制 —— 名字唯一（含随机串），退出即被 defer 删除
    base := filepath.Base(path)
    fmt.Println("[4] 临时文件名以 basic_learn_11_ 开头:", strings.HasPrefix(base, "basic_learn_11_"),
        "（main 返回时由 defer 自动删除）")
}
