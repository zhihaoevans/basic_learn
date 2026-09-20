// 主题说明：C++ 第一个程序 —— <iostream> 标准输出流、单行注释与块注释、
//           std::endl 与 '\n' 的区别（endl 换行并刷新缓冲区）。
// 运行命令：./cpp/basics/build/01_hello
// 预期输出（关键行）：
//   Hello, C++!
//   C++ 于 1998 年首次标准化
//   endl 换行并刷新缓冲区；'\n' 只换行

#include <iostream>  // std::cout / std::endl：标准输入输出流

/*
 * 块注释（多行注释）：编译器忽略其中全部内容，
 * 适合写成段的说明，或临时屏蔽一段代码。
 */

int main() {
    // 1. 最经典的输出：<< 把数据“流向”标准输出流 std::cout
    std::cout << "Hello, C++!" << std::endl;

    // 2. << 可以连续串联：整数与字符串混合输出
    int year = 1998;  // 单行注释：从 // 到行尾
    std::cout << "C++ 于 " << year << " 年首次标准化" << std::endl;

    // 3. std::endl 输出换行后立刻 flush（刷新）缓冲区；
    //    普通场景用 '\n' 即可，少一次刷新开销，性能更好
    std::cout << "endl 换行并刷新缓冲区；'\\n' 只换行\n";

    return 0;  // 返回 0 表示成功结束；main 函数里这句可以省略
}
