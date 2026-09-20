// 主题说明：C++ 常用标准库速览 —— <algorithm>（sort / find_if / count / count_if）、
//           <numeric>（accumulate 累加）、<chrono>（计时）、<string_view>（零拷贝视图）。
// 运行命令：./cpp/basics/build/13_stdlib
// 预期输出（关键行）：
//   默认升序 sort: 1 2 5 8 9
//   lambda 降序 sort: 9 8 5 2 1
//   find_if 找到第一个 > 4 的元素：5（下标 2）
//   count 等于 2 的个数：1；count_if 偶数个数：2
//   accumulate 求和 = 25（初值用 0，浮点则必须 0.0）
//   string_view 去首尾空白后: hello string_view（长度 17）

#include <algorithm>  // sort / find_if / count / count_if
#include <chrono>     // 计时
#include <cstddef>    // std::size_t
#include <iostream>
#include <numeric>    // accumulate
#include <string>
#include <string_view>
#include <vector>

int main() {
    std::vector<int> v{5, 2, 9, 1, 8};

    // ---- 1. sort：默认升序，也可以传 lambda 比较器 ----
    std::sort(v.begin(), v.end());
    std::cout << "默认升序 sort:";
    for (int x : v) {
        std::cout << " " << x;
    }
    std::cout << "\n";
    std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });  // 降序
    std::cout << "lambda 降序 sort:";
    for (int x : v) {
        std::cout << " " << x;
    }
    std::cout << "\n";

    // ---- 2. find_if：按条件找第一个，返回迭代器，找不到等于 end() ----
    std::sort(v.begin(), v.end());  // 恢复升序：1 2 5 8 9
    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x > 4; });
    if (it != v.end()) {
        std::cout << "find_if 找到第一个 > 4 的元素：" << *it
                  << "（下标 " << it - v.begin() << "）\n";
    }

    // ---- 3. count / count_if：计数 ----
    int twos = std::count(v.begin(), v.end(), 2);
    int evens = std::count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    std::cout << "count 等于 2 的个数：" << twos << "；count_if 偶数个数：" << evens << "\n";

    // ---- 4. accumulate：把区间折叠成一个值（求和最常用）----
    // 注意初值类型决定累加类型：0 是 int，0.0 才是 double——经典陷阱
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "accumulate 求和 = " << sum << "（初值用 0，浮点则必须 0.0）\n";

    // ---- 5. chrono：steady_clock 适合测量时间段 ----
    auto start = std::chrono::steady_clock::now();
    long long total = 0;
    for (int i = 1; i <= 1000000; ++i) {
        total += i;
    }
    auto stop = std::chrono::steady_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    std::cout << "1..1000000 求和 = " << total << "，耗时 " << us
              << " 微秒（因机器而异，仅演示计时方法）\n";

    // ---- 6. string_view：不拥有字符串的只读视图，传参零拷贝（C++17）----
    std::string_view raw = "  hello string_view  ";
    std::string_view sv = raw;
    while (!sv.empty() && sv.front() == ' ') {
        sv.remove_prefix(1);  // 手工去掉开头空白
    }
    while (!sv.empty() && sv.back() == ' ') {
        sv.remove_suffix(1);  // 去掉结尾空白
    }
    std::cout << "string_view 去首尾空白后: " << sv << "（长度 " << sv.size() << "）\n";
    // 提醒：string_view 不拥有数据——别让它比所指的字符串活得久

    return 0;
}
