// 主题说明：C++ 泛型 —— 函数模板、类模板（Stack<T>）、非类型模板参数 N（编译期
// 常量）、auto 返回类型推导（int*double 自动返回 double）。
// 运行命令：./cpp/basics/build/15_generic
// 预期输出（关键行）：
//   maxOf(3, 7) = 7，maxOf(2.5, 1.5) = 2.5（同一份代码适配多种类型）
//   sumOf(std::array<int, 4>) = 10（N = 4 是编译期常量）
//   sumOf(std::array<double, 3>) = 6（同一个模板适配 double）
//   int 栈：push 1 2 3 后 pop 出 3，剩 2 个
//   string 栈：pop 出 "beta"
//   mul(7, 2.0) = 14（auto 返回类型推导为 double）

#include <array>
#include <cstddef>  // std::size_t
#include <iostream>
#include <string>
#include <type_traits>  // std::is_same
#include <vector>

// ---- 1. 函数模板：类型 T 是参数，编译器按调用实参实例化 ----
template <typename T>
const T& maxOf(const T& a, const T& b) {
    return (a < b) ? b : a;  // 只要求 T 支持 operator<（鸭子类型的编译期版本）
}

// ---- 2. 非类型模板参数：N 是编译期常量，参与类型的一部分 ----
template <typename T, std::size_t N>  // array<int,4> 与 array<int,5> 是不同类型
T sumOf(const std::array<T, N>& xs) {
    T total{};  // 值初始化：int 得 0，double 得 0.0
    for (const T& v : xs) {
        total += v;
    }
    return total;
}

// ---- 3. 类模板：整个类的成员都依赖类型参数 T ----
template <typename T>
class Stack {
public:
    void push(T v) { data_.push_back(std::move(v)); }
    bool pop(T& out) {  // 通过出参返回值 + bool 表示是否成功（空栈返回 false）
        if (data_.empty()) {
            return false;
        }
        out = std::move(data_.back());
        data_.pop_back();
        return true;
    }
    std::size_t size() const { return data_.size(); }

private:
    std::vector<T> data_;
};

// ---- 4. auto 返回类型：编译器按 return 表达式推导返回类型 ----
template <typename A, typename B>
auto mul(A a, B b) {
    return a * b;  // int * double -> double；换成矩阵类型则返回矩阵
}

int main() {
    // 函数模板：调用处不需要写 <int>，实参推导自动完成
    std::cout << "maxOf(3, 7) = " << maxOf(3, 7)
              << "，maxOf(2.5, 1.5) = " << maxOf(2.5, 1.5)
              << "（同一份代码适配多种类型）\n";

    // 非类型参数：N 在编译期已知，可当作数组长度、循环边界等常量使用
    std::array<int, 4> ai{1, 2, 3, 4};
    std::array<double, 3> ad{1.5, 2.0, 2.5};
    std::cout << "sumOf(std::array<int, 4>) = " << sumOf(ai)
              << "（N = 4 是编译期常量）\n";
    std::cout << "sumOf(std::array<double, 3>) = " << sumOf(ad)
              << "（同一个模板适配 double）\n";

    // 类模板：Stack<int> 与 Stack<std::string> 是两个独立实例化的类型
    Stack<int> si;
    si.push(1);
    si.push(2);
    si.push(3);
    int top = 0;
    si.pop(top);
    std::cout << "int 栈：push 1 2 3 后 pop 出 " << top << "，剩 " << si.size() << " 个\n";

    Stack<std::string> ss;
    ss.push("alpha");
    ss.push("beta");
    std::string s;
    ss.pop(s);
    std::cout << "string 栈：pop 出 \"" << s << "\"\n";

    // auto 返回：7 * 2.0 的积是 double，返回类型就推导为 double
    auto m = mul(7, 2.0);
    static_assert(std::is_same<decltype(m), double>::value, "应为 double");  // 编译期验证
    std::cout << "mul(7, 2.0) = " << m << "（auto 返回类型推导为 double）\n";

    return 0;
}
