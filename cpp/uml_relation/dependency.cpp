#include <iostream>

//UML表示：虚线箭头（类 → 类）

// 被依赖类
class Logger {
public:
    static void log(const std::string& msg) {
        std::cout << "LOG: " << msg << std::endl;
    }
};

// 依赖类
class DataProcessor {
public:
    void process() {
        Logger::log("Processing started"); // 临时性依赖
        // 处理逻辑...
        Logger::log("Processing completed");
    }
};

int main() {
    DataProcessor processor;
    processor.process();
    /* 输出:
       LOG: Processing started
       LOG: Processing completed */
    return 0;
}