// 主题说明：C++ 控制流 —— if/switch 的初始化语句（C++17 新语法）、range-for
//           范围遍历、while 与 do-while、break 跳出与 continue 提前进入下一轮。
// 运行命令：./cpp/basics/build/05_control
// 预期输出（关键行）：
//   15 是奇数（if 初始化语句把 n 的作用域限制在 if 内）
//   code = 3：重试（switch 初始化语句，C++17）
//   总和 = 210（range-for 遍历 vector）
//   斐波那契： 1 1 2 3 5 8 13 21 34 55 89
//   倒计时：3 2 1 起飞！（do-while 至少执行一次）
//   输出 7 以内的奇数后 break：1 3 5 7

#include <iostream>
#include <vector>

int main() {
    // ---- 1. if 初始化语句（C++17）：变量 n 只在 if/else 里可见，不污染外层 ----
    if (int n = 15; n % 2 == 0) {
        std::cout << n << " 是偶数\n";
    } else {
        std::cout << n << " 是奇数（if 初始化语句把 n 的作用域限制在 if 内）\n";
    }

    // ---- 2. switch 初始化语句（C++17）+ case 穿越的刻意利用 ----
    switch (int code = 3; code) {
        case 1:
            std::cout << "code = 1：成功\n";
            break;
        case 2:
        case 3:  // 2 和 3 共用一段逻辑（穿越写法）
            std::cout << "code = 3：重试（switch 初始化语句，C++17）\n";
            break;
        default:
            std::cout << "未知 code\n";
            break;
    }

    // ---- 3. range-for：遍历容器最简洁的写法 ----
    std::vector<int> nums{10, 20, 30, 40, 50, 60};
    int sum = 0;
    for (int v : nums) {  // 逐个拷贝元素
        sum += v;
    }
    std::cout << "总和 = " << sum << "（range-for 遍历 vector）\n";
    for (int& v : nums) {  // 用引用才能修改元素
        v *= 2;
    }
    std::cout << "翻倍后首个元素 = " << nums.front() << "\n";

    // ---- 4. while：条件循环（斐波那契数列不超过 100）----
    std::cout << "斐波那契：";
    int a = 1, b = 1;
    while (a < 100) {
        std::cout << " " << a;
        int next = a + b;
        a = b;
        b = next;
    }
    std::cout << "\n";

    // ---- 5. do-while：先执行一次再判断条件 ----
    std::cout << "倒计时：";
    int down = 3;
    do {
        std::cout << down-- << " ";
    } while (down > 0);
    std::cout << "起飞！（do-while 至少执行一次）\n";

    // ---- 6. break 与 continue：跳出循环 / 跳过本轮 ----
    std::cout << "输出 7 以内的奇数后 break：";
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            continue;  // 偶数：跳过本轮，进入下一次
        }
        if (i > 7) {
            break;     // 第一个大于 7 的奇数出现，整个循环结束
        }
        std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}
