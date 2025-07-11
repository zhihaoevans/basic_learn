#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>
#include <vector>

// Custom exception class
class CustomException : public std::exception {
private:
    std::string message;
public:
    CustomException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Class demonstrating RAII and exception safety
class Resource {
private:
    std::string name;
public:
    Resource(const std::string& n) : name(n) {
        std::cout << "Resource " << name << " acquired" << std::endl;
        if (name == "bad") {
            throw CustomException("Failed to acquire resource: " + name);
        }
    }
    
    ~Resource() {
        std::cout << "Resource " << name << " released" << std::endl;
    }
    
    void use() {
        std::cout << "Using resource " << name << std::endl;
    }
};

// Function demonstrating exception handling
void functionWithException(int value) {
    if (value < 0) {
        throw std::invalid_argument("Value cannot be negative");
    }
    if (value == 0) {
        throw std::runtime_error("Value cannot be zero");
    }
    std::cout << "Processing value: " << value << std::endl;
}

// Function demonstrating nested try-catch blocks
void nestedExceptionHandling(int x, int y) {
    try {
        std::cout << "Outer try block" << std::endl;
        try {
            if (x == 0) throw std::runtime_error("x is zero");
            if (y == 0) throw CustomException("y is zero");
            std::cout << "Result: " << x/y << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cout << "Inner catch: " << e.what() << std::endl;
            throw; // Re-throwing the exception
        }
    }
    catch (const std::exception& e) {
        std::cout << "Outer catch: " << e.what() << std::endl;
    }
}

// Function demonstrating exception specifications (C++17 noexcept)
void noexceptFunction() noexcept {
    std::cout << "This function cannot throw exceptions" << std::endl;
}

int main() {
    std::cout << "=== Exception Handling Examples ===" << std::endl;

    // 1. Basic try-catch
    std::cout << "\n1. Basic try-catch:" << std::endl;
    try {
        functionWithException(-1);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught invalid_argument: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught runtime_error: " << e.what() << std::endl;
    }

    // 2. Multiple exception types
    std::cout << "\n2. Multiple exception types:" << std::endl;
    try {
        functionWithException(0);
    }
    catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // 3. Custom exceptions
    std::cout << "\n3. Custom exceptions:" << std::endl;
    try {
        throw CustomException("This is a custom exception");
    }
    catch (const CustomException& e) {
        std::cout << "Caught custom exception: " << e.what() << std::endl;
    }

    // 4. RAII and exception safety
    std::cout << "\n4. RAII and exception safety:" << std::endl;
    try {
        Resource r1("good");
        r1.use();
        Resource r2("bad"); // This will throw
        r2.use();          // This won't be executed
    }
    catch (const CustomException& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // 5. Nested exceptions
    std::cout << "\n5. Nested exceptions:" << std::endl;
    nestedExceptionHandling(0, 1);
    nestedExceptionHandling(1, 0);

    // 6. Exception in constructors
    std::cout << "\n6. Exception in constructors:" << std::endl;
    try {
        std::vector<Resource> resources;
        resources.push_back(Resource("first"));
        resources.push_back(Resource("bad")); // This will throw
    }
    catch (const CustomException& e) {
        std::cout << "Caught exception while constructing: " << e.what() << std::endl;
    }

    // 7. noexcept function
    std::cout << "\n7. noexcept function:" << std::endl;
    noexceptFunction();

    // 8. Function try block
    std::cout << "\n8. Function try block:" << std::endl;
    class Test {
    public:
        Test() try : resource("good") {
            std::cout << "Constructor body" << std::endl;
        }
        catch (...) {
            std::cout << "Caught exception in constructor" << std::endl;
            throw; // Must re-throw from constructor function try block
        }
    private:
        Resource resource;
    };

    try {
        Test test;
    }
    catch (const std::exception& e) {
        std::cout << "Caught exception from Test constructor" << std::endl;
    }

    return 0;
} 