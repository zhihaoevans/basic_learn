package main
import "fmt"
func main() {
    a := 2
    switch a {
    case 1:
        fmt.Println("一")
    case 2:
        fmt.Println("二")
    default:
        fmt.Println("其他")
    }
} 