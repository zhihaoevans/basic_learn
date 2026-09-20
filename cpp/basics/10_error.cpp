// 主题说明：C++ 异常处理 —— throw 抛出、try-catch 按 const 引用捕获、
//           catch 子句从派生到基类的匹配顺序、自定义异常类（继承 std::runtime_error）、
//           标准异常层次（logic_error / runtime_error）、noexcept 承诺。
// 运行命令：./cpp/basics/build/10_error
// 预期输出（关键行）：
//   safeDivide(10, 2) = 5
//   捕获自定义异常 DivideError：除零错误: 1.000000 / 0
//   捕获标准异常 out_of_range（vector::at 下标越界，标准库自己抛的）
//   兜底 catch(const std::exception&)：boom
//   noexcept(sizeHint()) = true，noexcept(safeDivide(1, 1)) = false

#include <iostream>
#include <stdexcept>  // 标准异常层次
#include <string>
#include <vector>

// ---- 自定义异常类：继承 std::runtime_error，构造时把细节拼进 what() ----
class DivideError : public std::runtime_error {
public:
    explicit DivideError(const std::string& detail)
        : std::runtime_error("除零错误: " + detail) {}
};

// ---- 可能抛异常的函数 ----
double safeDivide(double a, double b) {
    if (b == 0) {
        throw DivideError(std::to_string(a) + " / 0");  // 抛出：沿调用链向外传播
    }
    return a / b;
}

// ---- noexcept：向调用方和编译器承诺不抛异常 ----
int sizeHint() noexcept { return 42; }

int main() {
    // ---- 1. 正常路径 ----
    std::cout << "safeDivide(10, 2) = " << safeDivide(10.0, 2.0) << "\n";

    // ---- 2. 捕获自定义异常：catch 按引用（const&）避免切片与拷贝 ----
    try {
        safeDivide(1.0, 0.0);
    } catch (const DivideError& e) {
        std::cout << "捕获自定义异常 DivideError：" << e.what() << "\n";
    }

    // ---- 3. 标准库自己抛的异常：vector::at 越界抛 std::out_of_range ----
    std::vector<int> v{1, 2, 3};
    try {
        int bad = v.at(10);          // at 带边界检查
        std::cout << bad << "\n";    // 不会执行到这里
    } catch (const std::out_of_range&) {
        // what() 的文本是平台相关的（libstdc++ 与 libc++ 措辞不同），故打印固定说明
        std::cout << "捕获标准异常 out_of_range（vector::at 下标越界，标准库自己抛的）\n";
    }

    // ---- 4. catch 匹配顺序：从最派生到最基类，兜底用 std::exception ----
    try {
        throw std::runtime_error("boom");
    } catch (const DivideError& e) {         // 更派生：先匹配（runtime_error 不会命中这里）
        std::cout << "不会进来：" << e.what() << "\n";
    } catch (const std::exception& e) {      // 基类兜底：runtime_error 命中
        std::cout << "兜底 catch(const std::exception&)：" << e.what() << "\n";
    }

    // ---- 5. noexcept 运算符：编译期判断一个表达式是否声明为不抛 ----
    std::cout << std::boolalpha
              << "noexcept(sizeHint()) = " << noexcept(sizeHint())
              << "，noexcept(safeDivide(1, 1)) = " << noexcept(safeDivide(1.0, 1.0))
              << std::noboolalpha << "\n";
    std::cout << "sizeHint() = " << sizeHint() << "（noexcept 函数正常返回）\n";

    return 0;
}
