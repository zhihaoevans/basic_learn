// 主题说明：Go 字符串操作 —— string 不可变、len 按字节计、下标取字节 vs range 遍历 rune、
//           按字节切片、strings 包常用函数、strconv 互转与 fmt 格式化动词。
// 运行命令：go run golang/04_string.go
// 预期输出（关键行）：
//   [1] 原串: Hello, 世界 → 新串: wello, 世界
//   len(s) = 13 （字节长度：7 个 ASCII + 2 个汉字 × 3 字节）
//   utf8.RuneCountInString(s) = 9 （字符个数）
//   s[7:] = 世界 （从「世」的字节起点切到末尾）
//   [6] Atoi("42") + 1 = 43
package main

import (
    "fmt"
    "strconv"
    "strings"
    "unicode/utf8"
)

func main() {
    s := "Hello, 世界" // UTF-8 源码，字符串就是字节序列

    // 知识点 1：字符串不可变 —— 不能 s[0] = 'h'（编译错误），"修改"只能生成新串
    // s[0] = 'h' // 编译错误：cannot assign to s[0] (value of type byte)
    t := "w" + s[1:] // 拼接/切片都返回新字符串，原串不受影响
    fmt.Println("[1] 原串:", s, "→ 新串:", t)

    // 知识点 2：len 按字节计 —— UTF-8 里一个汉字占 3 字节；数"字符"要用 rune
    fmt.Println("[2] len(s) =", len(s), "（字节长度：7 个 ASCII + 2 个汉字 × 3 字节）")
    fmt.Println("    utf8.RuneCountInString(s) =", utf8.RuneCountInString(s), "（字符个数）")

    // 知识点 3：下标取到字节，range 遍历到 rune —— 处理中文的关键区别
    fmt.Printf("[3] s[0]='%c'（字节）；s[7:10]=%s（按字节切出「世」）\n", s[0], s[7:10])
    fmt.Println("    range 遍历「Hi世」：")
    for i, r := range "Hi世" { // i 是字节下标，r 是 rune（Unicode 码点）
        fmt.Printf("      字节下标 %d: %c\n", i, r)
    }

    // 知识点 4：切片 —— 与切片语法一致但按字节切，多字节字符边界要小心
    fmt.Println("[4] s[0:5] =", s[0:5], "（ASCII 段随便切）")
    fmt.Println("    s[7:] =", s[7:], "（从「世」的字节起点切到末尾）")

    // 知识点 5：strings 包常用函数
    fmt.Println("[5] ToUpper:", strings.ToUpper("go"))
    fmt.Println("    Contains(s, \"世界\"):", strings.Contains(s, "世界"))
    fmt.Println("    Replace(\"a-b-c\", \"-\", \"+\", 2):", strings.Replace("a-b-c", "-", "+", 2))
    fmt.Println("    Split(\"a,b,c\", \",\"):", strings.Split("a,b,c", ","))
    fmt.Println("    Join([2026 09 19], \"-\"):", strings.Join([]string{"2026", "09", "19"}, "-"))
    fmt.Printf("    TrimSpace(\"  hi  \"): %q|\n", strings.TrimSpace("  hi  "))
    fmt.Println("    HasPrefix(\"main.go\", \"main\"):", strings.HasPrefix("main.go", "main"),
        " HasSuffix(\"main.go\", \".go\"):", strings.HasSuffix("main.go", ".go"))
    fmt.Println("    Repeat(\"go\", 3):", strings.Repeat("go", 3))
    fmt.Println("    Count(\"banana\", \"an\"):", strings.Count("banana", "an"),
        " Index(\"banana\", \"na\"):", strings.Index("banana", "na"))

    // 知识点 6：strconv 字符串互转 与 fmt 格式化动词
    v, err := strconv.Atoi("42") // 字符串 → int，返回 (值, error)
    if err == nil {
        fmt.Println("[6] Atoi(\"42\") + 1 =", v+1)
    }
    fmt.Println("    Itoa(255):", strconv.Itoa(255)) // int → 字符串
    f, _ := strconv.ParseFloat("3.14", 64)           // 字符串 → float64
    fmt.Println("    ParseFloat(\"3.14\"):", f)
    fmt.Printf("    fmt 动词：int=%d str=%s float=%.2f bool=%t 带引号=%q\n", 42, "go", 3.14159, true, "引号")
    fmt.Printf("    %%v 万能占位：切片=%v 映射=%v 指针类型=%T\n", []int{1, 2}, map[string]int{"a": 1}, new(int))
}
