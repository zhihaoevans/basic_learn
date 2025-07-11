#include <iostream>
#include <mutex>

class Logger {
private:
    static Logger* instance;
    static std::mutex mtx;
    
    Logger() {} // 私有构造函数

public:
    static Logger* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "LOG: " << message << std::endl;
    }

    // 删除拷贝构造函数和赋值运算符
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;
};

// 静态成员初始化
Logger* Logger::instance = nullptr;
std::mutex Logger::mtx;

int main() {
    Logger::getInstance()->log("Application started");
    Logger::getInstance()->log("Processing data...");
    return 0;
}