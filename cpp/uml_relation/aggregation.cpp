#include <iostream>
#include <vector>

//UML表示：空心菱形箭头（整体类 → 部分类）

// 部分类
class Student {
public:
    void attendClass() const {
        std::cout << "Student attending class" << std::endl;
    }
};

// 整体类
class Classroom {
    std::vector<Student*> students; // 非独占所有权
public:
    void addStudent(Student* s) {
        students.push_back(s);
    }
    
    void conductClass() const {
        std::cout << "Class begins" << std::endl;
        for (auto s : students) {
            s->attendClass();
        }
    }
};

int main() {
    Student s1, s2;
    Classroom room;
    
    room.addStudent(&s1);
    room.addStudent(&s2);
    room.conductClass();
    /* 输出:
       Class begins
       Student attending class
       Student attending class */
    return 0;
}