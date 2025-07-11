#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <atomic>

// Mutex for synchronizing console output
std::mutex cout_mutex;

// Function to print with mutex
template<typename T>
void safe_print(T msg) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << msg << std::endl;
}

// Basic thread function
void basic_thread_function(int x) {
    safe_print("Thread " + std::to_string(x) + " is running");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    safe_print("Thread " + std::to_string(x) + " finished");
}

// Shared data for mutex example
class Counter {
    mutable std::mutex mutex;
    int value = 0;

public:
    int increment() {
        std::lock_guard<std::mutex> lock(mutex);
        return ++value;
    }

    int get() const {
        std::lock_guard<std::mutex> lock(mutex);
        return value;
    }
};

// Thread-safe queue for condition variable example
template<typename T>
class ThreadSafeQueue {
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable cond;

public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(value);
        cond.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock, [this] { return !queue.empty(); });
        T value = queue.front();
        queue.pop();
        return value;
    }
};

// Atomic counter
std::atomic<int> atomic_counter(0);

int main() {
    std::cout << "=== Thread Support Examples ===" << std::endl;

    // 1. Basic thread creation
    std::cout << "\n1. Basic thread creation:" << std::endl;
    std::thread t1(basic_thread_function, 1);
    std::thread t2(basic_thread_function, 2);
    t1.join();
    t2.join();

    // 2. Mutex example
    std::cout << "\n2. Mutex example:" << std::endl;
    Counter counter;
    std::thread t3([&counter]() {
        for(int i = 0; i < 3; ++i) {
            safe_print("Thread 3 counter: " + std::to_string(counter.increment()));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    std::thread t4([&counter]() {
        for(int i = 0; i < 3; ++i) {
            safe_print("Thread 4 counter: " + std::to_string(counter.increment()));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    t3.join();
    t4.join();

    // 3. Condition variable example
    std::cout << "\n3. Condition variable example:" << std::endl;
    ThreadSafeQueue<int> queue;
    std::thread producer([&queue]() {
        for(int i = 0; i < 5; ++i) {
            queue.push(i);
            safe_print("Produced: " + std::to_string(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    std::thread consumer([&queue]() {
        for(int i = 0; i < 5; ++i) {
            int value = queue.pop();
            safe_print("Consumed: " + std::to_string(value));
        }
    });
    producer.join();
    consumer.join();

    // 4. Atomic operations
    std::cout << "\n4. Atomic operations:" << std::endl;
    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i) {
        threads.emplace_back([]() {
            atomic_counter++;
            safe_print("Atomic counter: " + std::to_string(atomic_counter.load()));
        });
    }
    for(auto& t : threads) {
        t.join();
    }

    // 5. Thread with lambda and capture
    std::cout << "\n5. Thread with lambda and capture:" << std::endl;
    int local_var = 42;
    std::thread t5([local_var]() {
        safe_print("Captured value: " + std::to_string(local_var));
    });
    t5.join();

    return 0;
} 