#include <iostream>
#include <memory>

//UML表示：虚线空心三角形箭头 + <>

// 接口类
class Serializable {
public:
    virtual std::string serialize() const = 0;
    virtual ~Serializable() = default;
};

// 实现类
class User : public Serializable {
    std::string name;
public:
    User(std::string n) : name(n) {}
    
    std::string serialize() const override {
        return "User: " + name;
    }
};

void saveToFile(const Serializable& obj) {
    std::cout << "Saving: " << obj.serialize() << std::endl;
}

int main() {
    User user("Alice");
    saveToFile(user); // 输出: Saving: User: Alice
    return 0;
}