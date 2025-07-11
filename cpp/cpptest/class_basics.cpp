#include <iostream>
#include <string>

// Basic class definition
class Person {
private:
    std::string name;
    int age;
    
public:
    // Default constructor
    Person() : name("Unknown"), age(0) {
        std::cout << "Default constructor called" << std::endl;
    }
    
    // Parameterized constructor
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Parameterized constructor called" << std::endl;
    }
    
    // Copy constructor
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "Copy constructor called" << std::endl;
    }
    
    // Destructor
    ~Person() {
        std::cout << "Destructor called for " << name << std::endl;
    }
    
    // Member functions
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { age = a; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    
    // Member function with implementation inside class
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
    
    // Static member function
    static void showCount() {
        std::cout << "Number of persons: " << count << std::endl;
    }
    
    // Friend function declaration
    friend void displayPerson(const Person& p);
    
    // Operator overloading
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
        }
        std::cout << "Assignment operator called" << std::endl;
        return *this;
    }
    
private:
    static int count;  // Static member variable
};

// Static member definition
int Person::count = 0;

// Friend function definition
void displayPerson(const Person& p) {
    std::cout << "Friend function: Name = " << p.name << ", Age = " << p.age << std::endl;
}

// Derived class (inheritance example)
class Student : public Person {
private:
    std::string studentId;
    
public:
    Student(const std::string& n, int a, const std::string& id) 
        : Person(n, a), studentId(id) {
        std::cout << "Student constructor called" << std::endl;
    }
    
    void display() const {
        Person::display();
        std::cout << "Student ID: " << studentId << std::endl;
    }
};

int main() {
    std::cout << "=== Class and Object Examples ===" << std::endl;

    // 1. Creating objects
    std::cout << "\n1. Creating objects:" << std::endl;
    Person p1;                     // Default constructor
    Person p2("Alice", 25);       // Parameterized constructor
    Person p3 = p2;               // Copy constructor

    // 2. Using member functions
    std::cout << "\n2. Using member functions:" << std::endl;
    p1.setName("Bob");
    p1.setAge(30);
    p1.display();
    
    // 3. Using getters
    std::cout << "\n3. Using getters:" << std::endl;
    std::cout << "p2's name: " << p2.getName() << std::endl;
    std::cout << "p2's age: " << p2.getAge() << std::endl;

    // 4. Using friend function
    std::cout << "\n4. Using friend function:" << std::endl;
    displayPerson(p2);

    // 5. Assignment operator
    std::cout << "\n5. Assignment operator:" << std::endl;
    Person p4;
    p4 = p2;
    p4.display();

    // 6. Inheritance
    std::cout << "\n6. Inheritance:" << std::endl;
    Student s1("Charlie", 20, "S12345");
    s1.display();

    // 7. Object pointers
    std::cout << "\n7. Object pointers:" << std::endl;
    Person* ptr = &p2;
    ptr->display();

    // 8. Dynamic object creation
    std::cout << "\n8. Dynamic object creation:" << std::endl;
    Person* dynamicPerson = new Person("David", 35);
    dynamicPerson->display();
    delete dynamicPerson;

    // 9. Array of objects
    std::cout << "\n9. Array of objects:" << std::endl;
    Person people[2] = {
        Person("Eve", 28),
        Person("Frank", 32)
    };
    for (const auto& person : people) {
        person.display();
    }

    return 0;
} 