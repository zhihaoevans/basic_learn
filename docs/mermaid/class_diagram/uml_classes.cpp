#include "uml_classes.h"
#include <algorithm>
#include <iostream>

// ============================================================================
// Animal类实现
// ============================================================================

Animal::Animal(const std::string& name, int age) : name(name), age(age) {}

std::string Animal::getName() const {
    return name;
}

int Animal::getAge() const {
    return age;
}

// ============================================================================
// Dog类实现 - 继承关系
// ============================================================================

Dog::Dog(const std::string& name, int age, const std::string& breed) 
    : Animal(name, age), breed(breed) {}

void Dog::makeSound() const {
    std::cout << name << " the dog says: Woof! Woof!" << std::endl;
}

void Dog::bark() const {
    std::cout << name << " is barking loudly!" << std::endl;
}

std::string Dog::getBreed() const {
    return breed;
}

// ============================================================================
// Bird类实现 - 继承和实现关系
// ============================================================================

Bird::Bird(const std::string& name, int age, double wingspan) 
    : Animal(name, age), wingspan(wingspan) {}

void Bird::makeSound() const {
    std::cout << name << " the bird says: Tweet! Tweet!" << std::endl;
}

void Bird::fly() const {
    std::cout << name << " is flying with wingspan of " << wingspan << " meters!" << std::endl;
}

double Bird::getWingspan() const {
    return wingspan;
}

// ============================================================================
// Duck类实现 - 多重继承和实现
// ============================================================================

Duck::Duck(const std::string& name, int age, double wingspan) 
    : Bird(name, age, wingspan), waterproof(true) {}

void Duck::makeSound() const {
    std::cout << name << " the duck says: Quack! Quack!" << std::endl;
}

void Duck::swim() const {
    std::cout << name << " is swimming gracefully in the water!" << std::endl;
}

void Duck::dive() const {
    std::cout << name << " dives underwater to catch fish!" << std::endl;
}

// ============================================================================
// Engine类实现 - 组合关系中的组件
// ============================================================================

Engine::Engine(int hp, const std::string& type) : horsepower(hp), type(type) {
    std::cout << "Engine created: " << hp << "HP " << type << " engine" << std::endl;
}

void Engine::start() {
    std::cout << type << " engine started! (" << horsepower << "HP)" << std::endl;
}

void Engine::stop() {
    std::cout << type << " engine stopped." << std::endl;
}

int Engine::getHorsepower() const {
    return horsepower;
}

std::string Engine::getType() const {
    return type;
}

// ============================================================================
// Wheel类实现 - 组合关系中的组件
// ============================================================================

Wheel::Wheel(int size, const std::string& brand) : size(size), brand(brand) {
    std::cout << "Wheel created: " << size << "\" " << brand << " wheel" << std::endl;
}

void Wheel::rotate() {
    std::cout << brand << " wheel (" << size << "\") is rotating" << std::endl;
}

int Wheel::getSize() const {
    return size;
}

std::string Wheel::getBrand() const {
    return brand;
}

// ============================================================================
// Car类实现 - 组合关系
// ============================================================================

Car::Car(const std::string& model, int year) : model(model), year(year) {
    // 组合关系：Car创建时自动创建Engine和Wheels
    engine = std::make_unique<Engine>(200, "V6");
    
    // 创建4个轮子
    for (int i = 0; i < 4; ++i) {
        wheels.push_back(std::make_unique<Wheel>(18, "Michelin"));
    }
    
    std::cout << "Car created: " << year << " " << model << std::endl;
}

void Car::start() {
    std::cout << "Starting " << model << "..." << std::endl;
    engine->start();
    for (auto& wheel : wheels) {
        wheel->rotate();
    }
    std::cout << model << " is now running!" << std::endl;
}

void Car::stop() {
    std::cout << "Stopping " << model << "..." << std::endl;
    engine->stop();
    std::cout << model << " has stopped." << std::endl;
}

std::string Car::getModel() const {
    return model;
}

int Car::getYear() const {
    return year;
}

// ============================================================================
// Person类实现 - 聚合和关联关系中的实体
// ============================================================================

Person::Person(const std::string& name, int id) : name(name), id(id) {
    std::cout << "Person created: " << name << " (ID: " << id << ")" << std::endl;
}

std::string Person::getName() const {
    return name;
}

int Person::getId() const {
    return id;
}

void Person::work() const {
    std::cout << name << " is working hard!" << std::endl;
}

// ============================================================================
// Department类实现 - 关联关系
// ============================================================================

Department::Department(const std::string& name, Person* manager) 
    : name(name), manager(manager) {
    std::cout << "Department created: " << name;
    if (manager) {
        std::cout << " (Manager: " << manager->getName() << ")";
    }
    std::cout << std::endl;
}

void Department::setManager(Person* person) {
    manager = person;
    if (person) {
        std::cout << person->getName() << " is now the manager of " << name << std::endl;
    }
}

Person* Department::getManager() const {
    return manager;
}

std::string Department::getName() const {
    return name;
}

// ============================================================================
// Company类实现 - 聚合关系
// ============================================================================

Company::Company(const std::string& name) : name(name) {
    std::cout << "Company created: " << name << std::endl;
}

void Company::addEmployee(Person* person) {
    if (person && std::find(employees.begin(), employees.end(), person) == employees.end()) {
        employees.push_back(person);
        std::cout << person->getName() << " joined " << name << std::endl;
    }
}

void Company::removeEmployee(Person* person) {
    auto it = std::find(employees.begin(), employees.end(), person);
    if (it != employees.end()) {
        std::cout << (*it)->getName() << " left " << name << std::endl;
        employees.erase(it);
    }
}

int Company::getEmployeeCount() const {
    return static_cast<int>(employees.size());
}

std::string Company::getName() const {
    return name;
}

const std::vector<Person*>& Company::getEmployees() const {
    return employees;
}

// ============================================================================
// Book类实现 - 依赖关系中的被依赖对象
// ============================================================================

Book::Book(const std::string& title, const std::string& author, const std::string& isbn) 
    : title(title), author(author), isbn(isbn) {
    std::cout << "Book created: \"" << title << "\" by " << author << std::endl;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getIsbn() const {
    return isbn;
}

// ============================================================================
// Student类实现 - 依赖关系
// ============================================================================

Student::Student(const std::string& id, const std::string& name) 
    : studentId(id), name(name) {
    std::cout << "Student created: " << name << " (ID: " << id << ")" << std::endl;
}

void Student::study(const Book& book) const {
    // 依赖关系：Student使用Book对象进行学习
    std::cout << name << " is studying \"" << book.getTitle() 
              << "\" by " << book.getAuthor() << std::endl;
}

void Student::takeExam() const {
    std::cout << name << " is taking an exam!" << std::endl;
}

std::string Student::getStudentId() const {
    return studentId;
}

std::string Student::getName() const {
    return name;
}

// ============================================================================
// Library类实现 - 依赖关系和管理关系
// ============================================================================

void Library::addBook(std::unique_ptr<Book> book) {
    if (book) {
        std::cout << "Added book to library: \"" << book->getTitle() << "\"" << std::endl;
        books.push_back(std::move(book));
    }
}

Book* Library::findBook(const std::string& title) const {
    for (const auto& book : books) {
        if (book->getTitle() == title) {
            return book.get();
        }
    }
    return nullptr;
}

void Library::lendBook(const std::string& title, const Student& student) const {
    // 依赖关系：Library的方法使用Student对象
    Book* book = findBook(title);
    if (book) {
        std::cout << "Library lends \"" << book->getTitle() 
                  << "\" to student " << student.getName() << std::endl;
    } else {
        std::cout << "Book \"" << title << "\" not found in library" << std::endl;
    }
}

int Library::getBookCount() const {
    return static_cast<int>(books.size());
}