package main
import "fmt"
type Speaker interface {
    Speak()
}
type Dog struct{}
func (d Dog) Speak() {
    fmt.Println("汪汪")
}
func main() {
    var s Speaker = Dog{}
    s.Speak()
} 