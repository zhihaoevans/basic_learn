#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <array>

// Custom container class with begin() and end() support
class NumberSequence {
    int start;
    int endNum;
public:
    NumberSequence(int s, int e) : start(s), endNum(e) {}

    class iterator {
        int num;
    public:
        iterator(int n) : num(n) {}
        iterator& operator++() { ++num; return *this; }
        bool operator!=(const iterator& other) const { return num != other.num; }
        int operator*() const { return num; }
    };

    iterator begin() const { return iterator(start); }
    iterator end() const { return iterator(endNum); }
};

int main() {
    std::cout << "=== Range-based For Loop Examples ===" << std::endl;

    // 1. Basic array example
    std::cout << "\n1. Array iteration:" << std::endl;
    int numbers[] = {1, 2, 3, 4, 5};
    for (const int& n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 2. Vector example
    std::cout << "\n2. Vector iteration:" << std::endl;
    std::vector<std::string> fruits {"apple", "banana", "orange"};
    for (const auto& fruit : fruits) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;

    // 3. Map example
    std::cout << "\n3. Map iteration:" << std::endl;
    std::map<std::string, int> ages {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 4. std::array example
    std::cout << "\n4. std::array iteration:" << std::endl;
    std::array<double, 4> values {3.14, 2.718, 1.414, 1.732};
    for (auto value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // 5. Custom container example
    std::cout << "\n5. Custom container iteration:" << std::endl;
    NumberSequence seq(1, 5);
    for (int n : seq) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 6. String iteration (by character)
    std::cout << "\n6. String iteration:" << std::endl;
    std::string text = "Hello";
    for (char c : text) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    // 7. Modifying elements
    std::cout << "\n7. Modifying elements:" << std::endl;
    std::vector<int> nums {1, 2, 3, 4, 5};
    for (auto& num : nums) {
        num *= 2;
    }
    for (const auto& num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
} 