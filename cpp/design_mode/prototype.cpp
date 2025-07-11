// prototype.cpp
#include <iostream>
#include <memory>
#include <unordered_map>

class Shape {
public:
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    Circle(int x, int y, int r) : x_(x), y_(y), radius_(r) {}
    
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }
    
    void draw() const override {
        std::cout << "Drawing Circle at (" << x_ << "," << y_ 
                  << ") with radius " << radius_ << std::endl;
    }

private:
    int x_, y_, radius_;
};

class ShapeCache {
public:
    void addPrototype(const std::string& key, std::unique_ptr<Shape> shape) {
        prototypes_[key] = std::move(shape);
    }

    std::unique_ptr<Shape> getClone(const std::string& key) {
        return prototypes_.at(key)->clone();
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Shape>> prototypes_;
};

int main() {
    ShapeCache cache;
    cache.addPrototype("unit_circle", std::make_unique<Circle>(0, 0, 1));
    cache.addPrototype("big_circle", std::make_unique<Circle>(0, 0, 10));

    auto circle1 = cache.getClone("unit_circle");
    circle1->draw();

    auto circle2 = cache.getClone("big_circle");
    circle2->draw();

    return 0;
}