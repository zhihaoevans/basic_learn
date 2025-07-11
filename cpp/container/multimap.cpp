#include <iostream>
#include <map>
#include <string>

int main() {
    // 创建 multimap 并插入重复键值对
    std::multimap<std::string, int> scores;
    scores.insert({"Alice", 90});
    scores.insert({"Bob", 85});
    scores.insert({"Alice", 95});
    scores.insert({"Bob", 78});
    scores.insert({"Alice", 88});

    // 场景1：查找键为 "Alice" 的所有成绩 [1,10](@ref)
    std::cout << "--- Alice 的所有成绩 ---\n";
    auto lower = scores.lower_bound("Alice");
    auto upper = scores.upper_bound("Alice");
    
    for (auto it = lower; it != upper; ++it) {
        std::cout << it->first << ": " << it->second << "\n";
    }

    // 场景2：处理不存在的键 [2,4](@ref)
    std::cout << "\n--- 查找不存在的键 ---\n";
    const std::string key = "Charlie";
    auto not_found_low = scores.lower_bound(key);
    auto not_found_high = scores.upper_bound(key);
    
    if (not_found_low == not_found_high) {
        std::cout << "键 '" << key << "' 不存在\n";
    }

    // 场景3：结合 equal_range 的用法 [1,10](@ref)
    std::cout << "\n--- 使用 equal_range 查找 Bob ---\n";
    auto range = scores.equal_range("Bob");
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ": " << it->second << "\n";
    }

    return 0;
}