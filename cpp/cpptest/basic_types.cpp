#include <iostream>
#include <iomanip>
#include <limits>

int main() {
    std::cout << "=== Basic Types and Operators Examples ===" << std::endl;

    // 1. Integer types and their sizes
    std::cout << "\n1. Integer types and sizes:" << std::endl;
    std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "Size of short: " << sizeof(short) << " bytes" << std::endl;
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of long: " << sizeof(long) << " bytes" << std::endl;
    std::cout << "Size of long long: " << sizeof(long long) << " bytes" << std::endl;

    // 2. Floating point types
    std::cout << "\n2. Floating point types:" << std::endl;
    float f = 3.14159f;
    double d = 3.14159265359;
    long double ld = 3.14159265359L;
    
    std::cout << std::fixed << std::setprecision(7);
    std::cout << "float: " << f << std::endl;
    std::cout << "double: " << d << std::endl;
    std::cout << "long double: " << ld << std::endl;

    // 3. Character and Boolean types
    std::cout << "\n3. Character and Boolean types:" << std::endl;
    char c = 'A';
    bool b = true;
    std::cout << "char '" << c << "' as integer: " << static_cast<int>(c) << std::endl;
    std::cout << "bool: " << std::boolalpha << b << std::endl;

    // 4. Arithmetic operators
    std::cout << "\n4. Arithmetic operators:" << std::endl;
    int a = 10, b2 = 3;
    std::cout << "a = " << a << ", b = " << b2 << std::endl;
    std::cout << "Addition: " << a + b2 << std::endl;
    std::cout << "Subtraction: " << a - b2 << std::endl;
    std::cout << "Multiplication: " << a * b2 << std::endl;
    std::cout << "Division: " << a / b2 << std::endl;
    std::cout << "Modulus: " << a % b2 << std::endl;

    // 5. Increment/Decrement operators
    std::cout << "\n5. Increment/Decrement operators:" << std::endl;
    int x = 5;
    std::cout << "x = " << x << std::endl;
    std::cout << "Pre-increment: " << ++x << std::endl;
    std::cout << "Post-increment: " << x++ << std::endl;
    std::cout << "After post-increment: " << x << std::endl;
    std::cout << "Pre-decrement: " << --x << std::endl;
    std::cout << "Post-decrement: " << x-- << std::endl;
    std::cout << "After post-decrement: " << x << std::endl;

    // 6. Bitwise operators
    std::cout << "\n6. Bitwise operators:" << std::endl;
    unsigned int n1 = 5;  // 0101 in binary
    unsigned int n2 = 3;  // 0011 in binary
    std::cout << "n1 = " << n1 << " (0101), n2 = " << n2 << " (0011)" << std::endl;
    std::cout << "Bitwise AND: " << (n1 & n2) << std::endl;
    std::cout << "Bitwise OR: " << (n1 | n2) << std::endl;
    std::cout << "Bitwise XOR: " << (n1 ^ n2) << std::endl;
    std::cout << "Bitwise NOT n1: " << (~n1) << std::endl;
    std::cout << "Left shift n1 << 1: " << (n1 << 1) << std::endl;
    std::cout << "Right shift n1 >> 1: " << (n1 >> 1) << std::endl;

    // 7. Type limits
    std::cout << "\n7. Type limits:" << std::endl;
    std::cout << "Int min value: " << std::numeric_limits<int>::min() << std::endl;
    std::cout << "Int max value: " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "Unsigned int max value: " << std::numeric_limits<unsigned int>::max() << std::endl;
    std::cout << "Float min value: " << std::numeric_limits<float>::min() << std::endl;
    std::cout << "Float max value: " << std::numeric_limits<float>::max() << std::endl;

    // 8. Type conversion
    std::cout << "\n8. Type conversion:" << std::endl;
    int i = 42;
    float f2 = static_cast<float>(i);
    char c2 = static_cast<char>(65);
    std::cout << "int to float: " << f2 << std::endl;
    std::cout << "int to char: " << c2 << std::endl;

    return 0;
} 