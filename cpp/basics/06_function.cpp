// 主题说明：C++ 函数 —— 重载解析、默认实参、inline、lambda 表达式（各种捕获
//           列表：[] / [x] / [&] / [=] / 初始化捕获 / mutable）、函数对象与 std::function。
// 运行命令：./cpp/basics/build/06_function
// 预期输出（关键行）：
//   print(42) -> 整型版本
//   print(3.14) -> 浮点版本
//   print("str") -> 字符串版本
//   greet(x) = 你好，x；greet(x, 早) = 早，x
//   值捕获 base + 5 = 15（修改原变量不影响已捕获的拷贝）
//   引用捕获后 refTarget = 25
//   mutable 计数器：1 2 3（可修改按值捕获的拷贝）
//   函数对象 Multiplier{3}(7) = 21，经 std::function 包装 = 21

#include <functional>  // std::function
#include <iostream>
#include <string>

// ---- 1. 函数重载：同名不同参（参数个数或类型不同），编译器按实参选择 ----
void print(int v) { std::cout << "print(" << v << ") -> 整型版本\n"; }
void print(double v) { std::cout << "print(" << v << ") -> 浮点版本\n"; }
void print(const std::string& v) { std::cout << "print(\"" << v << "\") -> 字符串版本\n"; }

// ---- 2. 默认实参：从右往左连续给出，调用时可省略 ----
std::string greet(const std::string& name, const std::string& word = "你好") {
    return word + "，" + name;
}

// ---- 3. inline：建议编译器在调用点展开（现代编译器自行决定）----
inline int square(int x) { return x * x; }

// ---- 7. 函数对象：重载 operator() 的类，可以像函数一样调用 ----
struct Multiplier {
    int factor;
    int operator()(int x) const { return x * factor; }
};

int main() {
    print(42);
    print(3.14);
    print("str");

    std::cout << "greet(x) = " << greet("x")
              << "；greet(x, 早) = " << greet("x", "早") << "\n";
    std::cout << "inline square(9) = " << square(9) << "\n";

    // ---- 4. lambda：[捕获列表](参数) { 函数体 } ----
    auto add = [](int a, int b) { return a + b; };  // 不捕获，最纯粹的形式
    std::cout << "add(3, 4) = " << add(3, 4) << "\n";

    int base = 10;
    auto byValue = [base](int x) { return base + x; };  // [x] 按值捕获：拷贝一份
    base = 100;                                          // 之后再改原变量
    std::cout << "值捕获 base + 5 = " << byValue(5)
              << "（修改原变量不影响已捕获的拷贝）\n";

    int refTarget = 0;
    auto byRef = [&refTarget](int x) { refTarget += x; };  // [&x] 按引用捕获：改的是原变量
    byRef(10);
    byRef(15);
    std::cout << "引用捕获后 refTarget = " << refTarget << "\n";

    auto sumAll = [&](int a, int b) { return a + b + base + refTarget; };  // [&] 隐式引用捕获全部
    std::cout << "[&] 隐式捕获 a+b+base+refTarget = " << sumAll(1, 2) << "\n";

    auto counter = [count = 0]() mutable { return ++count; };  // 初始化捕获 + mutable
    std::cout << "mutable 计数器：" << counter() << " " << counter() << " " << counter()
              << "（可修改按值捕获的拷贝）\n";

    // ---- 5/6. std::function：能装下 lambda、函数指针、函数对象的通用容器 ----
    std::function<int(int)> op = Multiplier{3};
    std::cout << "函数对象 Multiplier{3}(7) = " << Multiplier{3}(7)
              << "，经 std::function 包装 = " << op(7) << "\n";
    op = [](int v) { return v * v; };  // 同一个变量换装 lambda
    std::cout << "std::function 换装 lambda 后 op(5) = " << op(5) << "\n";

    return 0;
}
