#ifndef UML_CLASSES_H
#define UML_CLASSES_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

// 前向声明
class Person;
class Book;
class Student;

// ============================================================================
// 抽象类和接口定义
// ============================================================================

/**
 * 抽象动物类 - 展示继承关系的基类
 */
class Animal {
protected:
    std::string name;
    int age;

public:
    Animal(const std::string& name, int age);
    virtual ~Animal() = default;
    
    // 普通方法
    std::string getName() const;
    int getAge() const;
    
    // 纯虚函数 - 子类必须实现
    virtual void makeSound() const = 0;
};

/**
 * 飞行接口 - 展示实现关系
 */
class Flyable {
public:
    virtual ~Flyable() = default;
    virtual void fly() const = 0;
};

/**
 * 游泳接口 - 展示实现关系
 */
class Swimmable {
public:
    virtual ~Swimmable() = default;
    virtual void swim() const = 0;
};

// ============================================================================
// 动物类层次结构 - 展示继承和实现关系
// ============================================================================

/**
 * 狗类 - 继承Animal
 */
class Dog : public Animal {
private:
    std::string breed;

public:
    Dog(const std::string& name, int age, const std::string& breed);
    
    // 实现抽象方法
    void makeSound() const override;
    
    // 狗特有的方法
    void bark() const;
    std::string getBreed() const;
};

/**
 * 鸟类 - 继承Animal，实现Flyable接口
 */
class Bird : public Animal, public Flyable {
protected:
    double wingspan;

public:
    Bird(const std::string& name, int age, double wingspan);
    
    // 实现抽象方法
    void makeSound() const override;
    
    // 实现接口方法
    void fly() const override;
    
    // 鸟特有的方法
    double getWingspan() const;
};

/**
 * 鸭子类 - 继承Bird，实现Swimmable接口
 */
class Duck : public Bird, public Swimmable {
private:
    bool waterproof;

public:
    Duck(const std::string& name, int age, double wingspan);
    
    // 重写父类方法
    void makeSound() const override;
    
    // 实现游泳接口
    void swim() const override;
    
    // 鸭子特有的方法
    void dive() const;
};

// ============================================================================
// 汽车相关类 - 展示组合关系
// ============================================================================

/**
 * 引擎类 - 被Car组合
 */
class Engine {
private:
    int horsepower;
    std::string type;

public:
    Engine(int hp, const std::string& type);
    
    void start();
    void stop();
    int getHorsepower() const;
    std::string getType() const;
};

/**
 * 轮子类 - 被Car组合
 */
class Wheel {
private:
    int size;
    std::string brand;

public:
    Wheel(int size, const std::string& brand);
    
    void rotate();
    int getSize() const;
    std::string getBrand() const;
};

/**
 * 汽车类 - 组合Engine和Wheel
 */
class Car {
private:
    std::string model;
    int year;
    std::unique_ptr<Engine> engine;  // 组合关系 - 强拥有
    std::vector<std::unique_ptr<Wheel>> wheels;  // 组合关系

public:
    Car(const std::string& model, int year);
    ~Car() = default;  // 智能指针自动管理内存
    
    void start();
    void stop();
    std::string getModel() const;
    int getYear() const;
    
    // 禁用拷贝构造和赋值（因为包含unique_ptr）
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;
    
    // 支持移动语义
    Car(Car&&) = default;
    Car& operator=(Car&&) = default;
};

// ============================================================================
// 人员和组织类 - 展示聚合和关联关系
// ============================================================================

/**
 * 人员类 - 被Company聚合，与Department关联
 */
class Person {
private:
    std::string name;
    int id;

public:
    Person(const std::string& name, int id);
    
    std::string getName() const;
    int getId() const;
    void work() const;
};

/**
 * 部门类 - 与Person关联
 */
class Department {
private:
    std::string name;
    Person* manager;  // 关联关系 - 不拥有Person对象

public:
    Department(const std::string& name, Person* manager = nullptr);
    
    void setManager(Person* person);
    Person* getManager() const;
    std::string getName() const;
};

/**
 * 公司类 - 聚合Person
 */
class Company {
private:
    std::string name;
    std::vector<Person*> employees;  // 聚合关系 - 弱拥有

public:
    Company(const std::string& name);
    
    void addEmployee(Person* person);
    void removeEmployee(Person* person);
    int getEmployeeCount() const;
    std::string getName() const;
    
    // 获取所有员工
    const std::vector<Person*>& getEmployees() const;
};

// ============================================================================
// 学习相关类 - 展示依赖关系
// ============================================================================

/**
 * 书籍类 - 被Student依赖使用
 */
class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;

public:
    Book(const std::string& title, const std::string& author, const std::string& isbn);
    
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getIsbn() const;
};

/**
 * 学生类 - 依赖Book类
 */
class Student {
private:
    std::string studentId;
    std::string name;

public:
    Student(const std::string& id, const std::string& name);
    
    // 依赖关系 - 方法参数中使用Book
    void study(const Book& book) const;
    void takeExam() const;
    
    std::string getStudentId() const;
    std::string getName() const;
};

/**
 * 图书馆类 - 管理Book，为Student提供服务
 */
class Library {
private:
    std::vector<std::unique_ptr<Book>> books;

public:
    Library() = default;
    
    void addBook(std::unique_ptr<Book> book);
    Book* findBook(const std::string& title) const;
    
    // 依赖关系 - 方法参数中使用Student
    void lendBook(const std::string& title, const Student& student) const;
    
    int getBookCount() const;
};

#endif // UML_CLASSES_H