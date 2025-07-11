package main
import "fmt"
func main() {
    defer fmt.Println("最后执行")
    fmt.Println("先执行")
} 