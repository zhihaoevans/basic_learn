// 主题说明：【Rust 特色】所有权系统 —— Move 与 Copy 语义、不可变/可变借用规则、生命周期标注。
//           每个值有唯一所有者，离开作用域自动释放；这是 Rust 无 GC 也能内存安全的核心机制。
// 运行命令：cargo run --example 16_ownership
// 预期输出（关键行）：
//   s2 = hello（s1 的所有权已转移给 s2）
//   len = 6，s 仍可用：borrow
//   可变借用后：可变借用，被修改
//   更长的是：长长的字符串

// 参数按值传递 = 接收所有权，函数结束时随 s 一起释放
fn take_ownership(s: String) {
    println!("获得所有权：{}", s);
} // s 在此 drop，堆内存释放

// 参数按引用传递 = 借用：用完就还，不改变所有权
fn borrow(s: &String) -> usize {
    s.len()
}

// 可变借用：一次只能有一个 &mut，且与不可变借用互斥
fn mutate(s: &mut String) {
    s.push_str("，被修改");
}

// 生命周期标注 'a：告诉编译器"返回的引用至少活到入参里较短的那个为止"。
// 它不改变任何寿命，只是描述引用之间的关系，让借用检查器验证安全。
fn longest<'a>(a: &'a str, b: &'a str) -> &'a str {
    if a.len() >= b.len() { a } else { b }
}

// Copy 类型：整数、浮点、bool、char 及全 Copy 字段的结构体——赋值即按位复制，原值继续可用
#[derive(Debug, Clone, Copy)]
struct Point {
    x: i32,
    y: i32,
}

fn main() {
    // ---- Move：堆上数据的默认语义 ----
    let s1 = String::from("hello");
    let s2 = s1; // 所有权从 s1 转移到 s2（栈上的指针/长度/容量复制，堆内存只有一份）
    // println!("{}", s1); // 取消注释报错：borrow of moved value `s1`
    println!("s2 = {}（s1 的所有权已转移给 s2）", s2);

    let s = String::from("clone 演示");
    let s_copy = s.clone(); // 显式深拷贝：两份独立的堆数据，都可用
    println!("clone 后两者都可用：{} / {}", s, s_copy);

    // ---- 所有权传入函数 ----
    let s = String::from("我要被移走");
    take_ownership(s); // 值移进函数，函数返回后 s 不可再用
    // println!("{}", s); // 取消注释报错：value borrowed after move

    // ---- 不可变借用 &T：可同时存在多个，被借用的值仍可读 ----
    let s = String::from("borrow");
    let len = borrow(&s);
    println!("len = {}，s 仍可用：{}", len, s);

    // ---- 可变借用 &mut T：同一时刻只能有一个 ----
    let mut s = String::from("可变借用");
    mutate(&mut s);
    // let r1 = &mut s; let r2 = &mut s; // 取消注释报错：cannot borrow as mutable more than once
    println!("可变借用后：{}", s);

    // 借用规则的意义：写的时候没人读、读的时候没人写 → 数据竞争在编译期被消灭
    let mut v = vec![1, 2, 3];
    let first = &v[0]; // 不可变借用
    println!("first = {}", first); // 先用完 first
    v.push(4); // 之后再可变借用才合法；若 push 在前，first 变悬垂引用，编译器直接拒绝

    // ---- Copy：栈上简单类型赋值即复制 ----
    let p1 = Point { x: 1, y: 2 };
    let p2 = p1; // Copy 语义：p1 没有失效
    println!("p1 = {:?}，p2 = {:?}（Copy 类型赋值后原值仍可用）", p1, p2);
    println!("字段直读：p2.x = {}, p2.y = {}", p2.x, p2.y);
    let a = 42;
    let b = a;
    println!("i32 也是 Copy：a = {}, b = {}", a, b);

    // ---- 生命周期：编译器防止悬垂引用 ----
    // fn dangle() -> &String { let s = String::from("x"); &s } // 报错：返回引用活得比 s 还久
    let s_long = String::from("长长的字符串");
    let s_short = "短";
    let result = longest(&s_long, s_short); // 'a 取两者中较短的作用域
    println!("更长的是：{}", result);

    // 结构体持有引用时也需要标注（示意；教学场景更常用 String 直接持有）：
    // struct Excerpt<'a> { part: &'a str } —— 表示"part 引用不得活过来源"
}
