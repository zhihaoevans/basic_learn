// 主题说明：C++ 映射容器 —— std::map（红黑树，按 key 有序）与 unordered_map
//           （哈希表，平均 O(1)）、operator[] 与 at 的差异、insert/emplace，
//           以及最经典的单词计数统计。
// 运行命令：./cpp/basics/build/08_map
// 预期输出（关键行）：
//   map 按键有序遍历：alice:90 bob:75 carol:88
//   当前 size = 3，operator[] 读取缺失键会自动插入默认值：missing 被插入为 0
//   at() 读取缺失键抛 out_of_range（已捕获）
//   insert 已存在的键返回 second = 0（即 false，不覆盖原值 90）
//   词频统计（map 保证输出有序，此处仅展示重复词与 dog）：dog:1 fox:2 the:3
//   unordered_map 查询 fox = 2（遍历顺序不保证，不用于有序输出）

#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>  // std::out_of_range
#include <string>
#include <unordered_map>

int main() {
    // ---- 1. std::map：按 key 排序的映射，遍历顺序确定 ----
    std::map<std::string, int> scores;
    scores["carol"] = 88;   // operator[]：不存在则插入，存在则覆盖
    scores["alice"] = 90;
    scores["bob"] = 75;
    std::cout << "map 按键有序遍历：";
    for (const auto& kv : scores) {  // kv 是 pair<const string, int>
        std::cout << kv.first << ":" << kv.second << " ";
    }
    std::cout << "\n";

    // ---- 2. operator[] 与 at() 的关键差异 ----
    if (!scores.count("missing")) {
        std::cout << "当前 size = " << scores.size() << "，";
    }
    int zero = scores["missing"];  // 危险：读取不存在的键也会插入并返回默认值 0
    std::cout << "operator[] 读取缺失键会自动插入默认值：missing 被插入为 " << zero << "\n";
    try {
        int bad = scores.at("ghost");  // at()：不存在则抛异常
        std::cout << bad << "\n";      // 不会执行到这里
    } catch (const std::out_of_range&) {
        // what() 文本平台相关（libstdc++ 与 libc++ 措辞不同），故打印固定说明
        std::cout << "at() 读取缺失键抛 out_of_range（已捕获）\n";
    }

    // ---- 3. insert / emplace：键已存在时不覆盖 ----
    auto result = scores.insert(std::make_pair(std::string("alice"), 59));
    std::cout << "insert 已存在的键返回 second = " << result.second
              << "（即 false，不覆盖原值 " << result.first->second << "）\n";
    scores.emplace("dave", 66);  // emplace：原地构造键值对
    std::cout << "emplace 后 size = " << scores.size() << "\n";

    // ---- 4. 经典例：统计一段话里每个单词出现的次数 ----
    std::string text = "the quick brown fox jumps over the lazy dog the fox";
    std::map<std::string, int> freq;         // 用 map 而非 unordered_map：输出有序
    std::istringstream in(text);
    std::string word;
    while (in >> word) {
        ++freq[word];                        // 缺失键自动插入 0 再自增，词频统计核心一行
    }
    std::cout << "词频统计（map 保证输出有序，此处仅展示重复词与 dog）：";
    for (const auto& kv : freq) {
        if (kv.second >= 2 || kv.first == "dog") {  // 只展示重复词和一个单次词做对照
            std::cout << kv.first << ":" << kv.second << " ";
        }
    }
    std::cout << "\n";

    // ---- 5. unordered_map：哈希表实现，查找平均 O(1)，但遍历顺序不确定 ----
    std::unordered_map<std::string, int> fast;
    fast["fox"] = 2;
    fast["the"] = 3;
    std::cout << "unordered_map 查询 fox = " << fast["fox"]
              << "（遍历顺序不保证，不用于有序输出）\n";

    return 0;
}
