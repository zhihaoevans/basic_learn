#include <iostream>
#include <memory>
#include <typeinfo>

// Function overloads to demonstrate nullptr vs NULL
void process(int* ptr) {
    std::cout << "Processing pointer to int" << std::endl;
}

void process(int num) {
    std::cout << "Processing integer" << std::endl;
}

// Template function to show type deduction
template<typename T>
void showType(T value) {
    std::cout << "Type: " << typeid(value).name() << std::endl;
}

class MyClass {
public:
    void doSomething() {
        std::cout << "Doing something..." << std::endl;
    }
};

int main() {
    std::cout << "=== nullptr Examples ===" << std::endl;

    // 1. Basic nullptr usage
    std::cout << "\n1. Basic nullptr usage:" << std::endl;
    int* ptr1 = nullptr;
    if (ptr1 == nullptr) {
        std::cout << "ptr1 is null" << std::endl;
    }

    // 2. Function overloading with nullptr
    std::cout << "\n2. Function overloading:" << std::endl;
    int* ptr2 = nullptr;
    int num = 0;
    process(ptr2);    // Calls pointer version
    process(nullptr); // Calls pointer version
    process(nullptr);    // Changed from NULL to nullptr - calls pointer version unambiguously
    process(num);     // Calls integer version

    // 3. Type deduction
    std::cout << "\n3. Type deduction:" << std::endl;
    showType(nullptr);
    showType(NULL);

    // 4. Smart pointer initialization
    std::cout << "\n4. Smart pointer initialization:" << std::endl;
    std::unique_ptr<MyClass> smartPtr1(nullptr);
    std::shared_ptr<MyClass> smartPtr2 = nullptr;
    
    if (!smartPtr1) {
        std::cout << "smartPtr1 is null" << std::endl;
    }

    // 5. Pointer comparison
    std::cout << "\n5. Pointer comparison:" << std::endl;
    int* ptr3 = nullptr;
    int* ptr4 = NULL;
    
    if (ptr3 == nullptr) std::cout << "ptr3 is nullptr" << std::endl;
    if (ptr4 == nullptr) std::cout << "ptr4 is nullptr" << std::endl;

    // 6. Member function pointer
    std::cout << "\n6. Member function pointer:" << std::endl;
    void (MyClass::*memFuncPtr)() = nullptr;
    if (memFuncPtr == nullptr) {
        std::cout << "Member function pointer is null" << std::endl;
    }

    // 7. Converting nullptr to boolean
    std::cout << "\n7. Converting nullptr to boolean:" << std::endl;
    bool isNull = nullptr == nullptr;
    std::cout << "nullptr == nullptr: " << std::boolalpha << isNull << std::endl;

    return 0;
} 