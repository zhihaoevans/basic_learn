package main
import "fmt"
type Person struct {
    Name string
}
func (p Person) SayHello() {
    fmt.Println("你好，我是", p.Name)
}
func main() {
    p := Person{"李四"}
    p.SayHello()
} 