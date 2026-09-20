// 主题说明：C++ 文件与流 —— ofstream 写文件、ifstream 配合 getline 逐行读、
//           stringstream（istringstream 解析 / ostringstream 拼接）。
// 运行命令：./cpp/basics/build/11_file_io
// 预期输出（关键行）：
//   写入 3 行到 basics_11_demo.txt
//   第 1 行：第一行：整数 42
//   第 2 行：第二行：浮点 3.14
//   第 3 行：3 4
//   共读到 3 行（以 getline 返回值作循环条件，避免 eof 陷阱）
//   istringstream 解析 "3 4" -> 3 + 4 = 7
//   ostringstream 拼接结果：x = 3, y = 4
//   临时文件已删除

#include <cstdio>  // std::remove
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    const std::string path = "basics_11_demo.txt";  // 在当前工作目录创建演示文件

    // ---- 1. ofstream：写文件（构造即打开，析构自动关闭，这也是 RAII）----
    std::ofstream out(path);
    if (!out.is_open()) {  // 打开失败要检查
        std::cerr << "无法打开写入：" << path << "\n";
        return 1;
    }
    out << "第一行：整数 " << 42 << "\n";      // << 用法与 cout 完全一致
    out << "第二行：浮点 " << 3.14 << "\n";
    out << "3 4\n";                            // 留给 stringstream 解析
    out.close();                               // 也可不调用，析构时自动关闭
    std::cout << "写入 3 行到 " << path << "\n";

    // ---- 2. ifstream + std::getline：逐行读取（文件不存在则打开失败）----
    std::ifstream in(path);
    if (!in) {
        std::cerr << "无法打开读取：" << path << "\n";
        return 1;
    }
    std::string line;
    int count = 0;
    while (std::getline(in, line)) {  // 循环条件是 getline 的返回值：
        ++count;                      // 读到文件尾返回 falsy，不会多读一行
        std::cout << "第 " << count << " 行：" << line << "\n";
    }
    std::cout << "共读到 " << count << " 行（以 getline 返回值作循环条件，避免 eof 陷阱）\n";

    // ---- 3. istringstream：像读流一样解析字符串 ----
    std::istringstream parser("3 4");
    int a = 0;
    int b = 0;
    parser >> a >> b;  // >> 跳过空白依次读入两个整数
    std::cout << "istringstream 解析 \"3 4\" -> " << a << " + " << b << " = " << a + b << "\n";

    // ---- 4. ostringstream：像写流一样拼接字符串（任意类型自动转文本）----
    std::ostringstream buf;
    buf << "x = " << a << ", y = " << b;
    std::cout << "ostringstream 拼接结果：" << buf.str() << "\n";

    // ---- 5. 清理演示文件，不留垃圾 ----
    if (std::remove(path.c_str()) == 0) {
        std::cout << "临时文件已删除\n";
    } else {
        std::cerr << "删除失败：" << path << "\n";
        return 1;
    }

    return 0;
}
