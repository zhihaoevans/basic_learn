// 主题说明：Go 泛型入门（Go 1.18+）—— [T any] 泛型函数、约束（any/comparable/cmp.Ordered
//           与自定义）、[K comparable] 映射键约束的泛型函数、泛型类型 Stack[T]。
// 运行命令：go run golang/15_generic.go
// 预期输出（关键行）：
//   [1] first([]int{3, 1, 2}) = 3
//   [2] maxOf(3, 7) = 7
//   [3] keysOf(string 键): 2 个；keysOf(int 键): 3 个
//   [4] int 栈 Pop: 20 剩余 Len: 1
//   空栈 Pop: "" false （返回零值 + false）
package main

import (
    "cmp"
    "fmt"
)

// 知识点 1：[T any] 泛型函数 —— 类型参数写在方括号里，调用时可自动推导也可显式指定
func first[T any](items []T) T { // any = interface{}：对类型无任何要求
    return items[0]
}

// 约束（constraint）就是"类型参数的类型"，限定了调用方能传入哪些类型：
//   any         任意类型
//   comparable  可用 == / != 比较的类型（能做 map 键、能判等）
//   cmp.Ordered 标准库现成的有序约束（Go 1.21+，涵盖所有数值与字符串类型）
//   自定义      用接口列举类型集合，如 ~int | ~float64（~ 表示"底层类型是"）
func maxOf[T cmp.Ordered](a, b T) T { // 早期实验库 x/exp/constraints 已被 cmp 取代
    if a > b {
        return a
    }
    return b
}

// 知识点 2：[K comparable, V any] —— 泛型 map 的键类型必须 comparable（可用 == 判等）
func keysOf[K comparable, V any](m map[K]V) []K {
    keys := make([]K, 0, len(m))
    for k := range m {
        keys = append(keys, k)
    }
    return keys
}

// 知识点 3：泛型类型 Stack[T] —— 类型参数也能用在结构体上，方法沿用 [T]
type Stack[T any] struct {
    items []T
}

func (s *Stack[T]) Push(v T) { s.items = append(s.items, v) }

func (s *Stack[T]) Pop() (T, bool) { // 返回 (弹出的值, 是否成功)
    if len(s.items) == 0 {
        var zero T // var zero T 就是 T 的零值（int→0，string→""）
        return zero, false
    }
    top := s.items[len(s.items)-1]
    s.items = s.items[:len(s.items)-1]
    return top, true
}

func (s *Stack[T]) Len() int { return len(s.items) }

func main() {
    // [T any]：同一份函数同时服务 int 与 string 切片，类型靠实参推导
    fmt.Println("[1] first([]int{3, 1, 2}) =", first([]int{3, 1, 2}))
    fmt.Println("    first([]string{\"a\", \"b\"}) =", first([]string{"a", "b"}))
    fmt.Println("    显式指定类型参数 first[string] =", first[string]([]string{"x", "y"}))

    // cmp.Ordered 约束：int 与 float64、string 都能比大小
    fmt.Println("[2] maxOf(3, 7) =", maxOf(3, 7))
    fmt.Println("    maxOf(2.5, 1.5) =", maxOf(2.5, 1.5))
    fmt.Println("    maxOf(\"go\", \"rust\") =", maxOf("go", "rust"))

    // [K comparable]：键类型既可以是 string 也可以是 int
    ages := map[string]int{"alice": 30, "bob": 25}
    scores := map[int]string{1: "A", 2: "B", 3: "C"}
    fmt.Println("[3] keysOf(string 键):", len(keysOf(ages)), "个；keysOf(int 键):", len(keysOf(scores)), "个")

    // 泛型类型 Stack[T]：一份实现，int 栈与 string 栈各用各的
    var is Stack[int]
    is.Push(10)
    is.Push(20)
    v, _ := is.Pop()
    fmt.Println("[4] int 栈 Pop:", v, "剩余 Len:", is.Len())
    var ss Stack[string]
    ss.Push("hello")
    s, ok := ss.Pop()
    fmt.Println("    string 栈 Pop:", s, ok)
    empty, ok2 := ss.Pop()
    fmt.Println("    空栈 Pop:", fmt.Sprintf("%q", empty), ok2, "（返回零值 + false）")
}
