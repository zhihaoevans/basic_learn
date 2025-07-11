#include <iostream>

//UML表示：实线箭头（类 → 类）

class Professor; // 前向声明

class Course {
    Professor* coordinator; // 单向关联
public:
    void setCoordinator(Professor* p) {
        coordinator = p;
    }
};

class Professor {
    Course* teachingCourse; // 双向关联
public:
    void assignCourse(Course* c) {
        teachingCourse = c;
        c->setCoordinator(this);
    }
};

int main() {
    Professor prof;
    Course cs101;
    prof.assignCourse(&cs101);
    return 0;
}