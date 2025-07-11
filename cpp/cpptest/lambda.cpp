#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::cout << "=== Lambda Expression Examples ===" << std::endl;

    // Basic lambda
    auto greet = []() { std::cout << "Hello from lambda!" << std::endl; };
    greet();

    // Lambda with parameters
    auto add = [](int a, int b) { return a + b; };
    std::cout << "2 + 3 = " << add(2, 3) << std::endl;

    // Lambda with capture by value
    int multiplier = 10;
    auto multiply = [multiplier](int x) { return x * multiplier; };
    std::cout << "5 * 10 = " << multiply(5) << std::endl;

    // Lambda with capture by reference
    int sum = 0;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::for_each(numbers.begin(), numbers.end(), 
                  [&sum](int x) { sum += x; });
    std::cout << "Sum of vector: " << sum << std::endl;

    // Lambda with capture all by value
    int a = 1, b = 2;
    auto capture_all_values = [=]() { return a + b; };
    std::cout << "Captured a + b = " << capture_all_values() << std::endl;

    // Lambda with capture all by reference
    auto capture_all_refs = [&]() { a *= 2; b *= 2; };
    capture_all_refs();
    std::cout << "After doubling: a = " << a << ", b = " << b << std::endl;

    // Lambda with mutable keyword
    int counter = 0;
    auto increment = [counter]() mutable { return ++counter; };
    std::cout << "Increment 1: " << increment() << std::endl;
    std::cout << "Increment 2: " << increment() << std::endl;

    // Using lambda with algorithms
    std::vector<int> vec = {13, 5, 7, 2, 8, 3};
    std::cout << "Original vector: ";
    for(int n : vec) std::cout << n << " ";
    std::cout << std::endl;

    // Sort using lambda
    std::sort(vec.begin(), vec.end(), 
             [](int a, int b) { return a < b; });
    
    std::cout << "Sorted vector: ";
    for(int n : vec) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
} 