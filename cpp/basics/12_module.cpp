// 主题说明：C++ 模块组织 —— namespace 定义与嵌套、声明与定义分离（单文件内演示，
//           多文件等价写法见下方注释）、匿名命名空间（内部链接）、using 声明与指令、
//           命名空间别名。
// 运行命令：./cpp/basics/build/12_module
// 预期输出（关键行）：
//   math::add(3, 4) = 7
//   math::abs_diff(3, 10) = 7（实现细节隐藏在 detail 命名空间中）
//   math::mean(1..5) = 3
//   调用次数统计（模块内部状态）：3
//   using 声明后直接调用 add(10, 20) = 30
//   命名空间别名 m::add(1, 1) = 2
//   匿名命名空间 hiddenPad(41) = 42（对外不可见，等价于 C 的 static）

/*
 * 多文件等价写法（本目录按“每个 .cpp 一个可执行 target”组织，故在单文件内演示）：
 *   math_utils.h   —— 只放下方 namespace math 里的“声明”部分，配 include guard：
 *                       #pragma once
 *                       namespace math { int add(int a, int b); ... }
 *   math_utils.cpp —— 放“定义”部分，首行 #include "math_utils.h"
 *   12_module.cpp  —— 使用者 #include "math_utils.h" 后直接调用 math::add(...)
 *   构建时两个 .cpp 一起编译链接：
 *                       g++ -std=c++17 12_module.cpp math_utils.cpp -o 12_module
 * 若确需拆出第二个 .cpp，其中的自测 main 需参照 c/module 的条件屏蔽方案。
 */

#include <iostream>
#include <vector>

// ======================= 声明部分（相当于头文件 math_utils.h） =======================
namespace math {
int add(int a, int b);                     // 声明：只给签名，供使用者提前调用
int abs_diff(int a, int b);                // 声明
double mean(const std::vector<int>& xs);   // 声明

namespace detail {              // 嵌套命名空间：实现细节，使用者不应直接碰
void recordCall();             // 声明：记录一次公开函数调用（本例只累加计数）
extern int call_count;         // extern 声明：定义在下方
}  // namespace detail
}  // namespace math

// ==================== 内部链接：匿名命名空间（相当于 C 的 static） ====================
namespace {
// 只在本编译单元可见：别的 .cpp 里再定义同名 hiddenPad 也不会链接冲突
int hiddenPad(int x) { return x + 1; }
}  // namespace

// ======================= 定义部分（相当于实现文件 math_utils.cpp） =======================
namespace math {
namespace detail {
int call_count = 0;  // 定义：模块内部状态

void recordCall() {
    ++call_count;  // 真实项目中这里通常是打日志；外界无须关心实现
}
}  // namespace detail

int add(int a, int b) {  // 定义：签名必须与声明一致
    detail::recordCall();
    return a + b;
}

int abs_diff(int a, int b) {
    detail::recordCall();
    return a > b ? a - b : b - a;  // 两数差的绝对值：模块对外承诺的语义
}

double mean(const std::vector<int>& xs) {
    detail::recordCall();
    long long sum = 0;  // 用宽类型累加，避免大数溢出
    for (int v : xs) {
        sum += v;
    }
    return xs.empty() ? 0.0 : static_cast<double>(sum) / static_cast<double>(xs.size());
}
}  // namespace math

int main() {
    // ---- 1. 限定名调用：命名空间就是“姓氏”，避免全局名字冲突 ----
    std::cout << "math::add(3, 4) = " << math::add(3, 4) << "\n";
    std::cout << "math::abs_diff(3, 10) = " << math::abs_diff(3, 10)
              << "（实现细节隐藏在 detail 命名空间中）\n";

    std::vector<int> xs{1, 2, 3, 4, 5};
    std::cout << "math::mean(1..5) = " << math::mean(xs) << "\n";
    std::cout << "调用次数统计（模块内部状态）：" << math::detail::call_count << "\n";

    // ---- 2. using 声明：只引入一个名字，污染最小（推荐写法）----
    using math::add;  // 之后可直接写 add，不必加 math:: 前缀
    std::cout << "using 声明后直接调用 add(10, 20) = " << add(10, 20) << "\n";

    // ---- 3. using 指令：整包引入，方便但容易撞名（限定在小作用域内用）----
    {
        using namespace math;  // 只在这个块里生效
        std::cout << "using 指令（块内）直接调用 mean(xs) = " << mean(xs) << "\n";
    }  // 离开块后 math 里的名字不再直接可见

    // ---- 4. 命名空间别名：长名字的缩写（常用库版本命名空间，如 fs = std::filesystem）----
    namespace m = math;
    std::cout << "命名空间别名 m::add(1, 1) = " << m::add(1, 1) << "\n";

    // ---- 5. 匿名命名空间：本文件内可以直接用，别的编译单元看不到 ----
    std::cout << "匿名命名空间 hiddenPad(41) = " << hiddenPad(41)
              << "（对外不可见，等价于 C 的 static）\n";

    return 0;
}
