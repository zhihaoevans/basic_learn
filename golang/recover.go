package main
import "fmt"
func main() {
    defer func() {
        if r := recover(); r != nil {
            fmt.Println("捕获到异常:", r)
        }
    }()
    panic("发生错误")
} 