// 主题说明：C++ 特色——RAII 资源获取即初始化：构造函数获取资源、析构函数自动释放，
//           由此获得异常安全；std::unique_ptr 独占所有权、std::lock_guard 的实现原理。
// 运行命令：./cpp/basics/build/16_raii
// 预期输出（关键行）：
//   --- 1. 嵌套作用域：构造顺序与析构顺序正好相反 ---
//   外层资源就绪
//   内层资源就绪
//   内层资源已释放（离开内层块）
//   外层资源已释放（离开外层块）
//   --- 3. 异常安全：即使抛异常，析构仍然执行 ---
//   [FileGuard 构造] 打开 raii_demo.txt
//   捕获异常：boom（注意析构在上面的输出里已经先执行过了）
//   --- 4. lock_guard 原理：构造加锁、析构解锁 ---
//   MiniLock 构造即加锁，修改 shared = 42
//   MiniLock 析构已解锁
//   std::lock_guard 用法相同：需要锁保护的区间

#include <cstdio>     // std::FILE / fopen / fclose / fputs / remove
#include <iostream>
#include <memory>     // std::unique_ptr / make_unique
#include <mutex>      // std::mutex / std::lock_guard
#include <stdexcept>  // std::runtime_error
#include <string>
#include <utility>    // std::move

// ---- 1. 手写 RAII 资源类：构造获取、析构释放、禁止拷贝 ----
class FileGuard {
public:
    explicit FileGuard(const std::string& path)
        : file_(std::fopen(path.c_str(), "w")) {  // 构造：获取（打开）资源
        std::cout << "[FileGuard 构造] 打开 " << path << "\n";
    }
    ~FileGuard() {  // 析构：释放资源——正常返回、提前 return、抛异常都会走到这里
        if (file_ != nullptr) {
            std::fclose(file_);
            std::cout << "[FileGuard 析构] 文件已关闭（无论是否发生异常）\n";
        }
    }
    FileGuard(const FileGuard&) = delete;             // 资源句柄持有唯一所有权
    FileGuard& operator=(const FileGuard&) = delete;  // 拷贝会造成二次释放，直接禁掉

    bool valid() const { return file_ != nullptr; }
    void write(const std::string& s) {
        if (file_ != nullptr) {
            std::fputs(s.c_str(), file_);
        }
    }

private:
    std::FILE* file_;
};

// ---- 2. lock_guard 的原理就是一个 RAII 锁包装（这里手写一个缩小版）----
class MiniLock {
public:
    explicit MiniLock(std::mutex& m) : m_(m) {
        m_.lock();  // 构造：加锁
        std::cout << "MiniLock 构造即加锁，";
    }
    ~MiniLock() {
        m_.unlock();  // 析构：无论因何离开作用域都会解锁——不会忘记，也不会死锁于泄漏
        std::cout << "MiniLock 析构已解锁\n";
    }
    MiniLock(const MiniLock&) = delete;
    MiniLock& operator=(const MiniLock&) = delete;

private:
    std::mutex& m_;
};

// ---- 3. 一个能看到析构日志的普通类，用于演示 unique_ptr ----
class Widget {
public:
    explicit Widget(int id) : id_(id) {
        std::cout << "Widget " << id_ << " 构造\n";
    }
    ~Widget() { std::cout << "Widget " << id_ << " 析构（unique_ptr 自动释放）\n"; }
    int id() const { return id_; }

private:
    int id_;
};

int main() {
    // ---- 1. 作用域嵌套：后构造的先析构（栈的对称性）----
    std::cout << "--- 1. 嵌套作用域：构造顺序与析构顺序正好相反 ---\n";
    {
        std::cout << "外层资源就绪\n";  // 想象成 FileGuard outer(...)
        {
            std::cout << "内层资源就绪\n";
        }
        std::cout << "内层资源已释放（离开内层块）\n";
    }
    std::cout << "外层资源已释放（离开外层块）\n\n";

    // ---- 2. unique_ptr：独占所有权的智能指针，析构自动 delete ----
    std::cout << "--- 2. unique_ptr：独占所有权 ---\n";
    {
        std::unique_ptr<Widget> w1 = std::make_unique<Widget>(1);
        std::cout << "w1->id() = " << w1->id() << "\n";
        std::unique_ptr<Widget> w2 = std::move(w1);  // 只能移动，不能拷贝
        std::cout << "移动后 w1 为空：" << std::boolalpha << (w1 == nullptr)
                  << "，w2->id() = " << w2->id() << std::noboolalpha << "\n";
        w2.reset();  // 提前释放（不必等到作用域结束）
        std::cout << "reset() 后指针为空，析构日志已在上一行之前打印\n";
    }
    std::cout << "\n";

    // ---- 3. 异常安全：抛异常也会 unwind 析构——RAII 的核心价值 ----
    std::cout << "--- 3. 异常安全：即使抛异常，析构仍然执行 ---\n";
    try {
        FileGuard g("raii_demo.txt");  // 作用域是整个 try 块
        g.write("hello raii\n");
        throw std::runtime_error("boom");  // 抛出点之后不再有任何显式代码
    } catch (const std::runtime_error& e) {
        // 栈展开时 g 的析构已经先执行（见上一行输出），资源没有泄漏
        std::cout << "捕获异常：" << e.what() << "（注意析构在上面的输出里已经先执行过了）\n";
    }
    std::cout << "\n";

    // ---- 4. lock_guard 原理：标准库的 std::lock_guard 就是 MiniLock 的完全体 ----
    std::cout << "--- 4. lock_guard 原理：构造加锁、析构解锁 ---\n";
    std::mutex mtx;
    int shared = 0;
    {
        MiniLock lock(mtx);  // 想象锁到这就位
        shared = 42;         // 临界区：锁保护中的共享数据
        std::cout << "修改 shared = " << shared << "\n";
    }
    {
        std::lock_guard<std::mutex> lock(mtx);  // 标准库版：同一原理
        std::cout << "std::lock_guard 用法相同：需要锁保护的区间\n";
    }

    // ---- 5. 清理演示文件 ----
    if (std::remove("raii_demo.txt") == 0) {
        std::cout << "演示文件 raii_demo.txt 已删除\n";
    }

    return 0;
}
