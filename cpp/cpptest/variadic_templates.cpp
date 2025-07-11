#include <iostream>
#include <string>
#include <tuple>

// Base case for variadic template recursion
void print() {
    std::cout << std::endl;
}

// Variadic template for print function
template<typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << " ";
    print(args...);
}

// Sum function using variadic templates
template<typename T>
T sum(T t) {
    return t;
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}

// Variadic template class example
template<typename... Types>
class Tuple {
public:
    static constexpr size_t size = sizeof...(Types);
};

// Recursive template for getting type names
template<typename T>
std::string getTypeName() {
    if (std::is_same<T, int>::value) return "int";
    if (std::is_same<T, double>::value) return "double";
    if (std::is_same<T, std::string>::value) return "string";
    return "unknown";
}

template<typename... Args>
void printTypes() {
    std::cout << "Types: ";
    // Using fold expression equivalent in C++11
    int dummy[] = { 0, ((std::cout << getTypeName<Args>() << " "), 0)... };
    (void)dummy; // Suppress unused variable warning
    std::cout << std::endl;
}

// Perfect forwarding with variadic templates
template<typename... Args>
void forwardFunction(Args&&... args) {
    print(std::forward<Args>(args)...);
}

int main() {
    std::cout << "=== Variadic Templates Examples ===" << std::endl;

    // Basic variadic template function
    std::cout << "\n1. Print function with different types:" << std::endl;
    print(1, 2.5, "Hello", 'c');

    // Sum function
    std::cout << "\n2. Sum function examples:" << std::endl;
    std::cout << "Sum of integers: " << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Sum of doubles: " << sum(1.1, 2.2, 3.3) << std::endl;

    // Tuple example
    std::cout << "\n3. Tuple size example:" << std::endl;
    Tuple<int, double, std::string> t;
    std::cout << "Tuple size: " << t.size << std::endl;

    // Type printing
    std::cout << "\n4. Print parameter types:" << std::endl;
    printTypes<int, double, std::string>();

    // Perfect forwarding
    std::cout << "\n5. Perfect forwarding example:" << std::endl;
    forwardFunction(1, "test", 3.14);

    // std::tuple example
    std::cout << "\n6. std::tuple example:" << std::endl;
    auto tuple = std::make_tuple(42, "Hello", 3.14);
    std::cout << "First element: " << std::get<0>(tuple) << std::endl;
    std::cout << "Second element: " << std::get<1>(tuple) << std::endl;
    std::cout << "Third element: " << std::get<2>(tuple) << std::endl;

    return 0;
} 