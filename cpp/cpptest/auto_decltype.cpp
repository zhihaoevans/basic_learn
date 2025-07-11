#include <iostream>
#include <vector>
#include <string>

// Function to demonstrate decltype usage
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

int main() {
    std::cout << "=== Auto and Decltype Examples ===" << std::endl;

    // Auto with different types
    auto i = 42;                    // int
    auto d = 42.5;                  // double
    auto s = "Hello C++11";         // const char*
    auto v = std::vector<int>{1,2}; // vector<int>

    std::cout << "Auto variables:" << std::endl;
    std::cout << "i: " << i << " (int)" << std::endl;
    std::cout << "d: " << d << " (double)" << std::endl;
    std::cout << "s: " << s << " (const char*)" << std::endl;

    // Decltype examples
    int x = 5;
    const int& rx = x;
    decltype(rx) y = x;  // Type will be const int&

    // Using decltype in expressions
    std::vector<int> numbers{1, 2, 3};
    decltype(numbers)::value_type first = numbers[0];  // int

    // Using our templated add function
    auto result1 = add(5, 3.14);    // Will deduce to double
    auto result2 = add(std::string("Hello "), "World"); // Will work with strings

    std::cout << "\nDecltype examples:" << std::endl;
    std::cout << "add(5, 3.14) = " << result1 << std::endl;
    std::cout << "add(\"Hello \", \"World\") = " << result2 << std::endl;

    return 0;
} 