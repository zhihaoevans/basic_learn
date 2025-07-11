#include <iostream>
#include <map>

//UML表示：连接两个类的虚线 + 中间类框

class Student;
class Course;

// 关联类
class Enrollment {
    Student* student;
    Course* course;
    int grade;
public:
    Enrollment(Student* s, Course* c) : student(s), course(c), grade(0) {}
    
    void setGrade(int g) { grade = g; }
    int getGrade() const { return grade; }
};

class Student {
    std::map<Course*, Enrollment*> enrollments;
public:
    void enroll(Course* c) {
        enrollments[c] = new Enrollment(this, c);
    }
    
    void setGrade(Course* c, int grade) {
        enrollments[c]->setGrade(grade);
    }
};

class Course {
    // 反向关联...
};

int main() {
    Student s;
    Course c;
    s.enroll(&c);
    s.setGrade(&c, 85);
    return 0;
}