#include <iostream>
#include <vector>

//UML表示：类框右上角带模板参数

template<typename T>
class Container {
    std::vector<T> items;
public:
    void add(const T& item) {
        items.push_back(item);
    }
    
    void showAll() const {
        for (const auto& item : items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Container<int> intContainer;
    intContainer.add(1);
    intContainer.add(2);
    intContainer.showAll(); // 输出: 1 2

    Container<std::string> strContainer;
    strContainer.add("Hello");
    strContainer.add("World");
    strContainer.showAll(); // 输出: Hello World
    return 0;
}