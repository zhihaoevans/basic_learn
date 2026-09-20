// 主题说明：常用标准库速览 —— collections/迭代器/字符串方法链、Duration 与 Instant 计时、
//           env::args 命令行参数，以及 process::exit 的行为说明。仅标准库，无第三方依赖。
// 运行命令：cargo run --example 13_stdlib
// 预期输出（关键行）：
//   保留的长单词 = ["quick", "brown", "jumps"]
//   耗时 xx ms，累加结果 = 499999500000
//   启动参数个数 = 1

use std::collections::HashMap;
use std::env;
use std::time::{Duration, Instant};

fn main() {
    // ---- 字符串方法链：trim → to_lowercase → split → filter → collect ----
    let sentence = "  The quick brown fox jumps  ";
    let lower = sentence.trim().to_lowercase(); // 先落地一个 String，后续 split 才有得借
    let long_words: Vec<&str> = lower.split(' ').filter(|w| w.len() > 3).collect();
    println!("保留的长单词 = {:?}", long_words);

    // ---- collections：entry 计数 + 迭代器统计 ----
    let nums = vec![4, 8, 15, 16, 23, 42];
    let mut buckets: HashMap<bool, Vec<i32>> = HashMap::new();
    for n in &nums {
        buckets.entry(n % 2 == 0).or_default().push(*n); // or_default：按类型自动给空值
    }
    println!("按奇偶分桶：偶数 {:?}，奇数 {:?}", buckets.get(&true), buckets.get(&false));
    println!("迭代器统计：max = {:?}，sum = {}，平均 = {:.2}",
        nums.iter().max(),
        nums.iter().sum::<i32>(),
        nums.iter().sum::<i32>() as f64 / nums.len() as f64);

    // ---- 时间：Instant 计时 + Duration 表达时长 ----
    let start = Instant::now(); // 单调时钟，适合测耗时
    let mut acc: u64 = 0;
    for i in 0..1_000_000u64 {
        acc += i; // 数字字面量下划线增强可读性
    }
    let elapsed = start.elapsed(); // Duration
    println!("耗时 {:.2?}，累加结果 = {}", elapsed, acc);
    println!("Duration 换算：{}ms = {}µs = {}ns",
        Duration::from_millis(1500).as_millis(),
        Duration::from_millis(1500).as_micros(),
        Duration::from_millis(1500).as_nanos());
    // 暂停线程（如需等待）：thread::sleep(Duration::from_millis(10));

    // ---- env::args：命令行参数（args[0] 是程序自身路径）----
    let args: Vec<String> = env::args().collect();
    println!("启动参数个数 = {}，args[0] 末段 = {:?}", args.len(),
        args[0].rsplit('/').next());
    // 更稳妥的解析可配合 clap 等第三方库（本系列仅标准库，不引入）

    // ---- process::exit：立即终止进程 ----
    // std::process::exit(code) 会跳过局部变量的 Drop（不会执行析构），
    // 仅刷新部分 C 运行时缓冲；普通返回 main / 返回 Err 则会正常清理。
    // 约定：0 表示成功、非 0 表示失败；本示例正常结束，不实际调用。
    // 如需显式成功退出可用：std::process::exit(0);
    println!("示例正常结束");
}
