#include <iostream>
#include <string>
#include <source_location>
// 旧版日志接口
class LegacyLogger {
public:
    void log(const std::string& msg, int priority) {
        std::cout << "Legacy: " << msg << " (" << priority << ")\n";
    }
};

// 新日志接口
class NewLogger {
public:
    virtual void log(const std::string& msg, std::source_location loc 
                    = std::source_location::current()) = 0;
};

// 适配器类
class LoggerAdapter : public NewLogger {
    LegacyLogger legacyLogger;
public:
    void log(const std::string& msg, std::source_location loc) override {
        int severity = loc.line() > 10 ? 1 : 0; // 转换逻辑
        legacyLogger.log(msg, severity);
    }
};

int main() {
    // 使用示例
    NewLogger* logger = new LoggerAdapter();
    logger->log("Adapter pattern demo");
    return 0;
}