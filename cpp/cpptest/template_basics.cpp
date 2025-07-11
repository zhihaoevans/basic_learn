#include <iostream>
#include <string>
#include <type_traits>

// 1. Function template
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// 2. Function template with multiple types
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

// 3. Class template
template<typename T>
class Container {
private:
    T data;
public:
    Container(T value) : data(value) {}
    T getValue() const { return data; }
    void setValue(T value) { data = value; }
    void display() const { std::cout << "Value: " << data << std::endl; }
};

// 4. Class template with multiple parameters
template<typename T, int Size>
class Array {
private:
    T data[Size];
public:
    Array() {
        for(int i = 0; i < Size; ++i) {
            data[i] = T();
        }
    }
    
    T& operator[](int index) {
        if(index < 0 || index >= Size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    int getSize() const { return Size; }
};

// 5. Template specialization
template<typename T>
class TypeInfo {
public:
    static std::string name() { return "unknown"; }
};

// Specializations for specific types
template<>
class TypeInfo<int> {
public:
    static std::string name() { return "integer"; }
};

template<>
class TypeInfo<std::string> {
public:
    static std::string name() { return "string"; }
};

// 6. Template with default parameter
template<typename T = int>
class DefaultType {
public:
    T value;
    DefaultType(T v = T()) : value(v) {}
};

// 7. Member function templates
class MemFuncTemplate {
public:
    template<typename T>
    void print(T value) {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    std::cout << "=== Template Examples ===" << std::endl;

    // 1. Function template usage
    std::cout << "\n1. Function template:" << std::endl;
    std::cout << "Max of 10 and 20: " << maximum(10, 20) << std::endl;
    std::cout << "Max of 3.14 and 2.72: " << maximum(3.14, 2.72) << std::endl;
    std::cout << "Max of 'a' and 'b': " << maximum('a', 'b') << std::endl;

    // 2. Function template with multiple types
    std::cout << "\n2. Function template with multiple types:" << std::endl;
    std::cout << "Add int and double: " << add(5, 3.14) << std::endl;
    std::cout << "Add double and int: " << add(3.14, 5) << std::endl;

    // 3. Class template usage
    std::cout << "\n3. Class template:" << std::endl;
    Container<int> intContainer(42);
    Container<std::string> strContainer("Hello");
    intContainer.display();
    strContainer.display();

    // 4. Array template usage
    std::cout << "\n4. Array template:" << std::endl;
    Array<int, 5> intArray;
    for(int i = 0; i < intArray.getSize(); ++i) {
        intArray[i] = i * 2;
    }
    for(int i = 0; i < intArray.getSize(); ++i) {
        std::cout << "intArray[" << i << "] = " << intArray[i] << std::endl;
    }

    // 5. Template specialization usage
    std::cout << "\n5. Template specialization:" << std::endl;
    std::cout << "Type of int: " << TypeInfo<int>::name() << std::endl;
    std::cout << "Type of string: " << TypeInfo<std::string>::name() << std::endl;
    std::cout << "Type of double: " << TypeInfo<double>::name() << std::endl;

    // 6. Default template parameter
    std::cout << "\n6. Default template parameter:" << std::endl;
    DefaultType<> defaultInt(42);        // Uses default type (int)
    DefaultType<double> defaultDouble(3.14);
    std::cout << "Default int: " << defaultInt.value << std::endl;
    std::cout << "Default double: " << defaultDouble.value << std::endl;

    // 7. Member function template
    std::cout << "\n7. Member function template:" << std::endl;
    MemFuncTemplate obj;
    obj.print(42);
    obj.print(3.14);
    obj.print("Hello");

    return 0;
} 