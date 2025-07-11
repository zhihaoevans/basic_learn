#include <iostream>

//UML表示：虚线空心三角形箭头（实现类 → 接口）

// 接口
class Drawable {
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

// 实现类
class Square : public Drawable {
public:
    void draw() const override {
        std::cout << "Drawing a square" << std::endl;
    }
};

int main() {
    Square sq;
    sq.draw(); // 输出: Drawing a square
    return 0;
}