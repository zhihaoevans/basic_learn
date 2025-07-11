#include <iostream>
#include <memory>

// 抽象产品
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

// 具体产品
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a Rectangle" << std::endl;
    }
};

// 抽象工厂
class ShapeFactory {
public:
    virtual std::unique_ptr<Shape> createShape() = 0;
    virtual ~ShapeFactory() = default;
};

// 具体工厂
class CircleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Circle>();
    }
};

class RectangleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() override {
        return std::make_unique<Rectangle>();
    }
};

int main() {
    std::unique_ptr<ShapeFactory> factory = std::make_unique<CircleFactory>();
    auto shape = factory->createShape();
    shape->draw();

    factory = std::make_unique<RectangleFactory>();
    shape = factory->createShape();
    shape->draw();
    
    return 0;
}