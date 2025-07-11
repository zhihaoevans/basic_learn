#include <iostream>
#include <vector>
#include <map>
#include <initializer_list>

// Custom class with initializer list constructor
class Matrix {
    std::vector<std::vector<int>> data;
public:
    Matrix(std::initializer_list<std::initializer_list<int>> init) {
        for (auto& row : init) {
            data.push_back(std::vector<int>(row));
        }
    }

    void print() const {
        for (const auto& row : data) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Class demonstrating multiple initializer list constructors
class NumberContainer {
    std::vector<int> numbers;
public:
    NumberContainer(std::initializer_list<int> list) 
        : numbers(list) {
        std::cout << "Initializer list constructor called" << std::endl;
    }

    // Function accepting initializer list
    void append(std::initializer_list<int> list) {
        numbers.insert(numbers.end(), list.begin(), list.end());
    }

    void print() const {
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
};

// Function accepting initializer list
template<typename T>
T sum(std::initializer_list<T> list) {
    T total = T();
    for (const T& value : list) {
        total += value;
    }
    return total;
}

int main() {
    std::cout << "=== Initializer List Examples ===" << std::endl;

    // 1. Basic container initialization
    std::cout << "\n1. Basic container initialization:" << std::endl;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Vector: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;

    // 2. Nested initialization
    std::cout << "\n2. Nested initialization:" << std::endl;
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    for (const auto& row : matrix) {
        for (int val : row) std::cout << val << " ";
        std::cout << std::endl;
    }

    // 3. Map initialization
    std::cout << "\n3. Map initialization:" << std::endl;
    std::map<std::string, int> ages = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 4. Custom class with initializer list
    std::cout << "\n4. Custom Matrix class initialization:" << std::endl;
    Matrix m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    m.print();

    // 5. NumberContainer example
    std::cout << "\n5. NumberContainer example:" << std::endl;
    NumberContainer numbers = {1, 2, 3, 4, 5};
    std::cout << "Initial numbers: ";
    numbers.print();
    
    numbers.append({6, 7, 8});
    std::cout << "After append: ";
    numbers.print();

    // 6. Function with initializer list
    std::cout << "\n6. Sum function with initializer list:" << std::endl;
    int sum_int = sum({1, 2, 3, 4, 5});
    double sum_double = sum({1.1, 2.2, 3.3});
    
    std::cout << "Sum of integers: " << sum_int << std::endl;
    std::cout << "Sum of doubles: " << sum_double << std::endl;

    // 7. Uniform initialization syntax
    std::cout << "\n7. Uniform initialization syntax:" << std::endl;
    int a{42};
    double b{3.14};
    std::string str{"Hello"};
    
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "str: " << str << std::endl;

    return 0;
} 