#include <iostream>
#include <string>
#include <vector>

class MyString {
    char* data;
    size_t size;

public:
    // Constructor
    MyString(const char* str = "") {
        size = strlen(str);
        data = new char[size + 1];
        strcpy(data, str);
        std::cout << "Constructor called for: " << data << std::endl;
    }

    // Copy constructor
    MyString(const MyString& other) {
        size = other.size;
        data = new char[size + 1];
        strcpy(data, other.data);
        std::cout << "Copy constructor called for: " << data << std::endl;
    }

    // Move constructor
    MyString(MyString&& other) noexcept {
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor called" << std::endl;
    }

    // Move assignment operator
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        std::cout << "Move assignment called" << std::endl;
        return *this;
    }

    // Destructor
    ~MyString() {
        if (data) {
            std::cout << "Destructor called for: " << data << std::endl;
        } else {
            std::cout << "Destructor called for empty string" << std::endl;
        }
        delete[] data;
    }

    // Get string
    const char* get() const { return data ? data : ""; }
};

// Function demonstrating perfect forwarding
template<typename T>
void perfectForward(T&& arg) {
    std::cout << "Forwarding: " << std::forward<T>(arg).get() << std::endl;
}

MyString createString(const char* str) {
    return MyString(str);
}

int main() {
    std::cout << "=== Rvalue References and Move Semantics Examples ===" << std::endl;

    std::cout << "\n1. Basic move example:" << std::endl;
    MyString str1("Hello");
    MyString str2 = std::move(str1);  // Move constructor
    std::cout << "str2: " << str2.get() << std::endl;
    std::cout << "str1 (after move): " << str1.get() << std::endl;

    std::cout << "\n2. Return value optimization:" << std::endl;
    MyString str3 = createString("World");  // Might use RVO/NRVO

    std::cout << "\n3. Vector reallocation with move:" << std::endl;
    std::vector<MyString> vec;
    vec.push_back(MyString("First"));
    vec.push_back(MyString("Second"));
    vec.push_back(MyString("Third"));

    std::cout << "\n4. Perfect forwarding example:" << std::endl;
    MyString str4("Perfect");
    perfectForward(str4);                  // Forwards lvalue
    perfectForward(MyString("Forward"));   // Forwards rvalue

    return 0;
} 