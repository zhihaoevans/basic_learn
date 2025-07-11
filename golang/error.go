package main
import (
    "errors"
    "fmt"
)
func div(a, b int) (int, error) {
    if b == 0 {
        return 0, errors.New("除数不能为0")
    }
    return a / b, nil
}
func main() {
    res, err := div(10, 0)
    if err != nil {
        fmt.Println("错误:", err)
    } else {
        fmt.Println("结果:", res)
    }
} 