#include <iostream>
#include <memory>

//UML表示：实线菱形箭头（整体类 → 部分类）

// 部分类
class Engine {
public:
    void start() const {
        std::cout << "Engine started" << std::endl;
    }
};

// 整体类
class Car {
    std::unique_ptr<Engine> engine; // 独占所有权
public:
    Car() : engine(std::make_unique<Engine>()) {}
    
    void start() const {
        engine->start();
        std::cout << "Car is running" << std::endl;
    }
};

int main() {
    Car car;
    car.start(); 
    // 输出: 
    // Engine started
    // Car is running
    return 0;
}