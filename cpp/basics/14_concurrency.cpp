// 主题说明：C++ 并发入门 —— std::thread 创建与 join、std::mutex 配
//           std::lock_guard 互斥保护共享数据、std::async + std::future 异步取结果。
// 运行命令：./cpp/basics/build/14_concurrency（由 CMake 链接 Threads::Threads）
// 预期输出（关键行）：
//   主线程：启动 4 个工作线程，每个自增 1000 次（受锁保护）
//   join 后 counter = 4000（无锁竞争丢失：mutex + lock_guard 保证正确性）
//   async 返回 12 的平方 = 144（future.get() 阻塞取结果）
//   async 返回字符串 = hello from async

#include <chrono>    // 线程内小睡，放大竞争窗口便于观察锁的作用
#include <future>    // std::async / std::future
#include <iostream>
#include <mutex>     // std::mutex / std::lock_guard
#include <string>
#include <thread>    // std::thread / std::this_thread
#include <vector>

int main() {
    // ---- 1. thread + mutex + lock_guard：多线程安全地修改共享计数器 ----
    std::mutex mtx;  // 互斥量：同一时刻只允许一个线程持有
    int counter = 0;

    auto worker = [&mtx, &counter](int times) {  // 引用捕获共享资源
        for (int i = 0; i < times; ++i) {
            std::lock_guard<std::mutex> lock(mtx);  // 构造时加锁，离开作用域自动解锁（RAII）
            ++counter;                              // 锁保护期间的临界区
        }
        // 小睡只为演示 this_thread；真实代码不要在循环里频繁加解锁
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    };

    std::cout << "主线程：启动 4 个工作线程，每个自增 1000 次（受锁保护）\n";
    std::vector<std::thread> pool;
    for (int t = 0; t < 4; ++t) {
        pool.emplace_back(worker, 1000);  // emplace_back 直接以参数构造线程
    }
    for (std::thread& t : pool) {
        t.join();  // join：等待线程结束，不 join 就析构会 std::terminate
    }
    std::cout << "join 后 counter = " << counter
              << "（无锁竞争丢失：mutex + lock_guard 保证正确性）\n";

    // ---- 2. async + future：把任务扔给后台，稍后用 get() 取结果 ----
    std::future<int> sq = std::async(std::launch::async, [](int x) { return x * x; }, 12);
    std::future<std::string> msg = std::async(std::launch::async, []() {
        return std::string("hello from async");
    });
    // get() 会阻塞到结果就绪；每个 future 只能 get 一次
    std::cout << "async 返回 12 的平方 = " << sq.get()
              << "（future.get() 阻塞取结果）\n";
    std::cout << "async 返回字符串 = " << msg.get() << "\n";

    std::cout << "本机支持并发线程数（参考值）：" << std::thread::hardware_concurrency()
              << "（数值因机器而异）\n";

    return 0;
}
