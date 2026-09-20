// 主题说明：C++ 字符串 std::string —— + 与 += 拼接、substr 截取、find 查找与
//           string::npos、replace 替换、to_string/stoi 数值互转、原始字符串 R"(...)"。
// 运行命令：./cpp/basics/build/04_string
// 预期输出（关键行）：
//   full = C++ Primer 第 5 版
//   substr(0, 3) = "C++"
//   "Primer" 位于下标 4
//   "go" 未找到（find 返回 string::npos）
//   替换后：C++ Pocket 第 5 版
//   stoi("42kg") = 42，to_string(3.14) = 3.140000
//   stoi 带位置参数：解析出 2024，停在下标 4
//   原始字符串：C:\tools\bin（反斜杠不再需要转义）

#include <iostream>
#include <string>

int main() {
    // ---- 1. 拼接与比较：+、+=、== ----
    std::string part1 = "C++";
    std::string part2 = " Primer";
    std::string full = part1 + part2;      // + 拼接生成新串
    full += " 第 5 版";                    // += 追加到自身
    std::cout << "full = " << full << "\n";
    if (part1 == "C++") {                  // string 可直接用 == 比较（不像 C 的 strcmp）
        std::cout << "string 支持 == 直接比较内容\n";
    }

    // ---- 2. substr：截取子串（起点下标，长度）----
    std::cout << "substr(0, 3) = \"" << full.substr(0, 3) << "\"\n";
    std::cout << "substr(4) = \"" << full.substr(4) << "\"（省略长度取到结尾）\n";

    // ---- 3. find：查找子串，找不到返回 string::npos ----
    std::string::size_type pos = full.find("Primer");
    std::cout << "\"Primer\" 位于下标 " << pos << "\n";
    if (full.find("go") == std::string::npos) {
        std::cout << "\"go\" 未找到（find 返回 string::npos）\n";
    }

    // ---- 4. replace：从指定位置替换指定长度 ----
    std::string replaced = full;
    replaced.replace(4, 6, "Pocket");  // 把 "Primer"（下标 4，长 6）换成 "Pocket"
    std::cout << "替换后：" << replaced << "\n";

    // ---- 5. 数值与字符串互转 ----
    int n = std::stoi("42kg");          // 解析前导整数，遇到非数字停下
    std::string s = std::to_string(3.14);
    std::cout << "stoi(\"42kg\") = " << n << "，to_string(3.14) = " << s << "\n";
    std::string::size_type stop = 0;
    int parsed = std::stoi("2024abc", &stop);  // &stop 带回解析停在哪里
    std::cout << "stoi 带位置参数：解析出 " << parsed << "，停在下标 " << stop << "\n";

    // ---- 6. 原始字符串字面量：R"(...)" 内不处理任何转义 ----
    std::string path = R"(C:\tools\bin)";   // 等价于 "C:\\tools\\bin"
    std::cout << "原始字符串：" << path << "（反斜杠不再需要转义）\n";

    // ---- 附：length/size 相同，[] 与 at 访问单个字符 ----
    std::cout << "full 长度 = " << full.size() << "，full[0] = " << full[0] << "\n";

    return 0;
}
