package main
import "fmt"
type Person struct {
    Name string
    Age  int
}
func main() {
    p := Person{"张三", 20}
    fmt.Println(p)
} 