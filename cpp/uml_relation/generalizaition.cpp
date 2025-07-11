#include <iostream>

//UML表示：空心三角形箭头（子类 → 父类)

// 基类
class Shape {
public:
    virtual void draw() const {
        std::cout << "Drawing a shape" << std::endl;
    }
    virtual ~Shape() = default;
};

// 派生类
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

int main() {
    Circle c;
    c.draw();        // 输出: Drawing a circle
    Shape& s = c;
    s.draw();        // 多态输出: Drawing a circle
    return 0;
}