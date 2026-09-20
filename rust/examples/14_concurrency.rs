// 主题说明：并发入门 —— thread::spawn 创建线程并用 join 取回返回值、mpsc channel 跨线程传消息、
//           Arc<Mutex> 多线程共享可变状态。Rust 的借用检查在编译期就能拦住数据竞争。
// 运行命令：cargo run --example 14_concurrency
// 预期输出（关键行）：
//   子线程返回值 = 220
//   channel 收到 10 / 20 / 30（三条消息）
//   共享计数 = 4

use std::sync::mpsc;
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    // ---- spawn + join：线程返回值通过 JoinHandle 拿回 ----
    let handle = thread::spawn(|| {
        let mut total = 0;
        for i in 1..=10 {
            total += i;
        }
        total * 4 // 闭包的返回值即线程的返回值
    });
    println!("主线程不等 join 也能先干活");
    let value = handle.join().unwrap(); // join 等待结束，返回 Result<T>
    println!("子线程返回值 = {}", value);

    // ---- channel（mpsc：多生产者单消费者）----
    let (tx, rx) = mpsc::channel();
    let producer = thread::spawn(move || { // move：把 tx 的所有权搬进子线程
        let data = vec![1, 2, 3];
        for x in data {
            tx.send(x * 10).unwrap(); // send 的是值的所有权，发完即交出
        }
        // tx 在此 drop：通道关闭，接收端的迭代自然结束
    });
    for received in rx { // rx 直接迭代：收到一条处理一条，通道关闭则退出
        println!("channel 收到 {}", received);
    }
    producer.join().unwrap();

    // ---- Arc<Mutex>：共享可变状态的标配组合 ----
    // Arc：原子引用计数的"共享指针"，让多个线程持有同一份数据；
    // Mutex：互斥锁，同一时刻只允许一个线程拿到内部数据的访问权。
    let counter = Arc::new(Mutex::new(0i32));
    let mut handles = Vec::new();
    for id in 1..=4 {
        let counter = Arc::clone(&counter); // 引用计数 +1，克隆的是"句柄"
        handles.push(thread::spawn(move || {
            let mut num = counter.lock().unwrap(); // 拿锁，返回 MutexGuard
            *num += 1; // 通过 guard 解引用修改共享值
            println!("  线程 {} 把计数加到 {}", id, *num);
        })); // guard 在此 drop，锁自动释放（RAII）
    }
    for h in handles {
        h.join().unwrap();
    }
    println!("共享计数 = {}", *counter.lock().unwrap());

    // ---- 为什么不用锁就不行？编译器会拒绝 ----
    // 若直接把 &mut 共享给多线程，或忘记 Mutex 只共享只读数据还想改，
    // 都会在编译期报错（Send/Sync 约束）——这正是 Rust 的"无畏并发"。
    // 另：现代异步（async/await + tokio）属于进阶主题，本系列不展开。
}
