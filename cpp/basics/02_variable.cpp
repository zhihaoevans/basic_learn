// 主题说明：C++ 变量与基本类型 —— auto 类型推导、const 与 constexpr 常量、
//           花括号统一初始化（禁止收窄）、static_cast 显式类型转换、sizeof。
// 运行命令：./cpp/basics/build/02_variable
// 预期输出（关键行）：
//   count = 42, price = 9.5
//   auto 推导：total = 28.5（int * double 提升为 double）
//   area = 12.5664
//   统一初始化：n = 10, d = 7
//   static_cast<int>(9.99) = 9（截断，不四舍五入）
//   7 / 2 整除 = 3；static_cast<double>(7) / 2 = 3.5
//   sizeof(int)=4, sizeof(double)=8, sizeof(char)=1

#include <iostream>
#include <string>

int main() {
    // ---- 1. 基本类型：整型、浮点、字符、布尔 ----
    int count = 42;      // 整型（教学平台均为 32 位）
    double price = 9.5;  // 双精度浮点
    char grade = 'A';    // 字符：底层是 1 字节整数
    bool ok = true;      // 布尔

    std::cout << "count = " << count << ", price = " << price << "\n";
    std::cout << "grade = " << grade << "（ASCII " << static_cast<int>(grade)
              << "），ok = " << std::boolalpha << ok << std::noboolalpha << "\n";

    // ---- 2. auto：让编译器按初始值推导类型（C++11）----
    auto apples = 3;              // 推导为 int
    auto total = apples * price;  // int * double 算术提升 -> double
    std::cout << "auto 推导：total = " << total << "（int * double 提升为 double）\n";

    // ---- 3. const 与 constexpr ----
    const std::string name = "C++";   // 运行期常量：初始化后不能修改
    constexpr double kPi = 3.14159;   // 编译期常量：可用于数组长度、模板实参等
    double area = kPi * 2 * 2;
    std::cout << "area = " << area << "\n";
    std::cout << "constexpr kPi = " << kPi << "，const name = " << name << "\n";

    // ---- 4. 花括号统一初始化：禁止“收窄”转换，写错直接编译失败 ----
    int n{10};    // OK
    double d{7};  // OK：整数放大成 double 不算收窄
    // int bad{3.14};  // 编译错误：double -> int 丢失精度，花括号初始化禁止
    std::cout << "统一初始化：n = " << n << ", d = " << d << "\n";

    // ---- 5. static_cast：C++ 风格的显式类型转换（意图明确、可检索）----
    double exact = 9.99;
    int truncated = static_cast<int>(exact);  // 截断小数部分
    std::cout << "static_cast<int>(9.99) = " << truncated << "（截断，不四舍五入）\n";
    int a = 7, b = 2;
    double ratio = static_cast<double>(a) / b;  // 不转换则 7/2 整除得 3
    std::cout << "7 / 2 整除 = " << a / b << "；static_cast<double>(7) / 2 = " << ratio << "\n";

    // ---- 6. sizeof：查询类型占用的字节数（编译期常量）----
    std::cout << "sizeof(int)=" << sizeof(int) << ", sizeof(double)=" << sizeof(double)
              << ", sizeof(char)=" << sizeof(char) << "\n";

    return 0;
}
