#include "uml_classes.h"
#include <iostream>
#include <memory>

void demonstrateInheritanceAndRealization() {
    std::cout << "\n=== 继承和实现关系演示 ===" << std::endl;
    
    // 创建不同的动物对象
    Dog dog("Buddy", 3, "Golden Retriever");
    Bird bird("Robin", 1, 0.3);
    Duck duck("Donald", 2, 0.5);
    
    // 多态性演示 - 通过基类指针调用虚函数
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Max", 5, "German Shepherd"));
    animals.push_back(std::make_unique<Duck>("Daffy", 3, 0.4));
    
    std::cout << "\n多态性演示:" << std::endl;
    for (const auto& animal : animals) {
        std::cout << "Animal: " << animal->getName() << ", Age: " << animal->getAge() << std::endl;
        animal->makeSound();
    }
    
    // 接口实现演示
    std::cout << "\n接口实现演示:" << std::endl;
    bird.fly();
    duck.fly();
    duck.swim();
    duck.dive();
    
    // 子类特有方法
    std::cout << "\n子类特有方法:" << std::endl;
    dog.bark();
    std::cout << "Dog breed: " << dog.getBreed() << std::endl;
    std::cout << "Bird wingspan: " << bird.getWingspan() << " meters" << std::endl;
}

void demonstrateComposition() {
    std::cout << "\n=== 组合关系演示 ===" << std::endl;
    
    // 创建汽车对象 - 自动创建引擎和轮子（组合关系）
    Car car("Toyota Camry", 2023);
    
    std::cout << "\n汽车操作:" << std::endl;
    car.start();
    std::cout << "Driving the " << car.getYear() << " " << car.getModel() << "..." << std::endl;
    car.stop();
    
    // 当car对象销毁时，engine和wheels也会自动销毁（组合关系的特点）
    std::cout << "\n组合关系特点: 当Car对象销毁时，Engine和Wheel对象也会自动销毁" << std::endl;
}

void demonstrateAggregationAndAssociation() {
    std::cout << "\n=== 聚合和关联关系演示 ===" << std::endl;
    
    // 创建人员对象
    Person alice("Alice Johnson", 1001);
    Person bob("Bob Smith", 1002);
    Person charlie("Charlie Brown", 1003);
    
    // 创建公司对象 - 聚合关系
    Company company("Tech Solutions Inc.");
    company.addEmployee(&alice);
    company.addEmployee(&bob);
    company.addEmployee(&charlie);
    
    std::cout << "\n公司员工数量: " << company.getEmployeeCount() << std::endl;
    
    // 创建部门对象 - 关联关系
    Department itDept("IT Department", &alice);
    Department hrDept("HR Department", &bob);
    
    std::cout << "\n部门信息:" << std::endl;
    std::cout << itDept.getName() << " 经理: " << itDept.getManager()->getName() << std::endl;
    std::cout << hrDept.getName() << " 经理: " << hrDept.getManager()->getName() << std::endl;
    
    // 员工工作
    std::cout << "\n员工工作状态:" << std::endl;
    for (const auto& employee : company.getEmployees()) {
        employee->work();
    }
    
    // 移除员工 - 聚合关系特点：员工对象仍然存在
    company.removeEmployee(&charlie);
    std::cout << "\n移除员工后，公司员工数量: " << company.getEmployeeCount() << std::endl;
    std::cout << "Charlie仍然存在: " << charlie.getName() << " (ID: " << charlie.getId() << ")" << std::endl;
}

void demonstrateDependency() {
    std::cout << "\n=== 依赖关系演示 ===" << std::endl;
    
    // 创建图书馆和书籍
    Library library;
    library.addBook(std::make_unique<Book>("C++ Primer", "Stanley Lippman", "978-0321714114"));
    library.addBook(std::make_unique<Book>("Design Patterns", "Gang of Four", "978-0201633612"));
    library.addBook(std::make_unique<Book>("Clean Code", "Robert Martin", "978-0132350884"));
    
    // 创建学生
    Student student1("S001", "Emma Wilson");
    Student student2("S002", "James Davis");
    
    std::cout << "\n图书馆书籍数量: " << library.getBookCount() << std::endl;
    
    // 依赖关系演示1: Student使用Book学习
    std::cout << "\n学生学习演示 (依赖关系):" << std::endl;
    Book cppBook("Effective C++", "Scott Meyers", "978-0321334879");
    student1.study(cppBook);  // Student依赖Book
    
    // 依赖关系演示2: Library为Student提供服务
    std::cout << "\n图书馆服务演示 (依赖关系):" << std::endl;
    library.lendBook("C++ Primer", student1);  // Library依赖Student
    library.lendBook("Design Patterns", student2);
    library.lendBook("Nonexistent Book", student1);  // 测试书籍不存在的情况
    
    // 学生考试
    std::cout << "\n学生考试:" << std::endl;
    student1.takeExam();
    student2.takeExam();
}

void demonstratePolymorphism() {
    std::cout << "\n=== 多态性综合演示 ===" << std::endl;
    
    // 使用基类指针存储不同的派生类对象
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Dog>("Rex", 4, "Labrador"));
    zoo.push_back(std::make_unique<Bird>("Eagle", 6, 2.0));
    zoo.push_back(std::make_unique<Duck>("Mallard", 2, 0.6));
    
    std::cout << "\n动物园里的动物们:" << std::endl;
    for (const auto& animal : zoo) {
        std::cout << "- " << animal->getName() << " (" << animal->getAge() << " years old)" << std::endl;
        animal->makeSound();
    }
    
    // 接口多态性演示
    std::cout << "\n会飞的动物们:" << std::endl;
    std::vector<Flyable*> flyingAnimals;
    
    Bird* bird = new Bird("Sparrow", 1, 0.2);
    Duck* duck = new Duck("Rubber Duck", 1, 0.3);
    
    flyingAnimals.push_back(bird);
    flyingAnimals.push_back(duck);
    
    for (Flyable* flyer : flyingAnimals) {
        flyer->fly();
    }
    
    // 清理内存
    delete bird;
    delete duck;
}

int main() {
    std::cout << "UML类图关系演示程序" << std::endl;
    std::cout << "===================" << std::endl;
    
    try {
        // 演示各种UML关系
        demonstrateInheritanceAndRealization();
        demonstrateComposition();
        demonstrateAggregationAndAssociation();
        demonstrateDependency();
        demonstratePolymorphism();
        
        std::cout << "\n=== 程序执行完成 ===" << std::endl;
        std::cout << "所有UML关系演示已完成！" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "程序执行出错: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}