// 主题说明：Go 常用标准库速览 —— strings 进阶（Builder/Cut）、strconv 带进制互转、
//           slices 与 maps 泛型工具（1.21+，Keys 需 1.23+）、time 参考时间格式化、常用包一览。
// 运行命令：go run golang/13_stdlib.go
// 预期输出（关键行）：
//   [1] Builder 拼接: go, rust, python
//   [2] FormatInt(255, 16): ff
//   [3] slices.Sort: [1 2 3]
//   [4] maps.Clone 副本 3 人，原 map 2 人
//   maps.Keys 排序后: [alice bob]
//   [5] Format: 2026-09-19 14:30:00
package main

import (
    "fmt"
    "maps"
    "slices"
    "strconv"
    "strings"
    "time"
)

func main() {
    // 知识点 1：strings 进阶 —— Builder 高效拼接、Fields 按任意空白切、Cut 一刀两段
    var b strings.Builder // 循环拼接时比 + 高效（内部维护 []byte，不反复分配新串）
    for _, w := range []string{"go", "rust", "python"} {
        b.WriteString(w)
        b.WriteString(", ")
    }
    fmt.Println("[1] Builder 拼接:", strings.TrimSuffix(b.String(), ", "))
    fmt.Println("    Fields:", strings.Fields("  a  b\tc\n")) // 连续多种空白都算分隔
    before, after, found := strings.Cut("name=alice", "=")
    fmt.Printf("    Cut: %q %q %v\n", before, after, found)
    fmt.Println("    EqualFold(\"Go\", \"gO\"):", strings.EqualFold("Go", "gO")) // 忽略大小写比较

    // 知识点 2：strconv 进阶 —— 带进制的整数与字符串互转
    fmt.Println("[2] FormatInt(255, 16):", strconv.FormatInt(255, 16)) // 十六进制
    fmt.Println("    FormatInt(255, 2):", strconv.FormatInt(255, 2))  // 二进制
    if v, err := strconv.ParseInt("cafe", 16, 64); err == nil {       // 按 16 进制解析
        fmt.Println("    ParseInt(\"cafe\", 16):", v)
    }
    if ok, err := strconv.ParseBool("true"); err == nil {
        fmt.Println("    ParseBool(\"true\"):", ok)
    }

    // 知识点 3：slices（Go 1.21+）—— 泛型切片工具，任意元素类型通吃
    nums := []int{3, 1, 2}
    slices.Sort(nums) // 原地排序
    fmt.Println("[3] slices.Sort:", nums)
    fmt.Println("    Contains(nums, 2):", slices.Contains(nums, 2),
        " Index(nums, 1):", slices.Index(nums, 1), " Max:", slices.Max(nums))
    cp := slices.Clone(nums) // Clone 返回独立副本
    cp[0] = 99
    fmt.Println("    Clone 改副本:", cp, "原切片不变:", nums)

    // 知识点 4：maps（Clone 需 Go 1.21+；Keys 迭代器需 1.23+）—— 映射工具
    ages := map[string]int{"alice": 30, "bob": 25}
    cp2 := maps.Clone(ages) // 浅拷贝：改副本不增删原 map 的键
    cp2["carol"] = 28
    fmt.Println("[4] maps.Clone 副本", len(cp2), "人，原 map", len(ages), "人")
    keys := slices.Collect(maps.Keys(ages)) // Keys 迭代器 → Collect 收集成切片
    slices.Sort(keys)                       // map 遍历无序，展示前先排序
    fmt.Println("    maps.Keys 排序后:", keys)

    // 知识点 5：time —— 格式化用"参考时间" 2006-01-02 15:04:05 当模板（数字本身好记：1 2 3 4 5 6）
    t := time.Date(2026, 9, 19, 14, 30, 0, 0, time.UTC)
    fmt.Println("[5] Format:", t.Format("2006-01-02 15:04:05"))
    fmt.Println("    自定义模板:", t.Format("2006/01/02 15:04"))
    d := 90 * time.Second
    fmt.Println("    Duration:", d, "Round 到分钟:", d.Round(time.Minute))

    // 知识点 6：更多常用标准库速览（用到时查 pkg.go.dev）
    fmt.Println("[6] 常用包速览：fmt 格式化｜os 文件与环境变量｜regexp 正则｜sort 经典排序｜net/http 服务与请求｜encoding/json 序列化｜errors 错误包装")
}
