// 主题说明：C++ 面向对象 —— class 封装（私有数据 + 公有接口）、构造与析构顺序、
//           继承与 virtual/override、纯虚函数与抽象类、经基类指针的多态调用。
// 运行命令：./cpp/basics/build/09_oop
// 预期输出（关键行）：
//   --- 作用域块结束，析构顺序与构造相反：派生类先析构 ---
//     [析构] ~Rectangle
//     [析构] ~Shape(rect)
//   多态调用（基类指针 -> 派生类 area()）：
//   circle 面积 = 12.5664
//   rect 面积 = 15
//   总面积 = 27.5664
//   图形个数 = 2（经基类接口使用）

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// ---- 抽象基类：含纯虚函数，不能创建对象，只能被继承 ----
class Shape {
public:
    explicit Shape(std::string name) : name_(std::move(name)) {  // 构造：先构造基类部分
        std::cout << "    [构造] Shape(" << name_ << ")\n";
    }
    virtual ~Shape() {  // 虚析构：经 Shape* 删除派生对象时保证派生类析构被调用
        std::cout << "    [析构] ~Shape(" << name_ << ")\n";
    }
    Shape(const Shape&) = delete;             // 本例聚焦多态，禁止拷贝
    Shape& operator=(const Shape&) = delete;

    const std::string& name() const { return name_; }  // getter：只读访问私有数据
    virtual double area() const = 0;                   // 纯虚函数：派生类必须实现
    void describe() const {                            // 普通成员函数复用虚函数
        std::cout << name_ << " 面积 = " << area() << "\n";
    }

private:
    std::string name_;  // 封装：数据私有，外部只能走公有接口
};

// ---- 派生类 1：Circle ----
class Circle : public Shape {
public:
    explicit Circle(double r) : Shape("circle"), r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }  // override：显式标注重写
    ~Circle() override { std::cout << "    [析构] ~Circle\n"; }

private:
    double r_;
};

// ---- 派生类 2：Rectangle（演示成员初始化列表）----
class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : Shape("rect"), w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    ~Rectangle() override { std::cout << "    [析构] ~Rectangle\n"; }

private:
    double w_;
    double h_;
};

int main() {
    // ---- 1. 构造与析构顺序：基类构造在前，析构顺序正好相反 ----
    std::cout << "--- 进入作用域块，构造顺序：基类在前 ---\n";
    {
        Rectangle rect(3, 5);
    }  // 离开作用域：rect 自动析构
    std::cout << "--- 作用域块结束，析构顺序与构造相反：派生类先析构 ---\n\n";

    // ---- 2. 多态：基类指针（这里用 unique_ptr 管理）指向派生类对象 ----
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 5.0));

    std::cout << "多态调用（基类指针 -> 派生类 area()）：\n";
    double total = 0;
    for (const auto& s : shapes) {  // 同一句 s->area() 按实际类型分派
        s->describe();
        total += s->area();
    }
    std::cout << "总面积 = " << total << "\n";
    std::cout << "图形个数 = " << shapes.size() << "（经基类接口使用）\n";

    // ---- 3. 抽象类不能实例化：Shape s("x"); // 编译错误：area 是纯虚函数 ----
    return 0;
}
