// 主题说明：函数与闭包 —— fn 定义、参数与返回值、元组多返回值、闭包三种写法与环境捕获、迭代器链式处理。
// 运行命令：cargo run --example 06_function
// 预期输出（关键行）：
//   add(3, 4) = 7
//   divide(17, 5) = 商 3 余 2
//   偶数平方 = [4, 16, 36, 64, 100]

// 无返回值（单元类型 ()），显式写法是 -> ()
fn greet(name: &str) {
    println!("你好，{}！", name);
}

// 最后一行是表达式（无分号）即返回值；等价于 return a + b;
fn add(a: i32, b: i32) -> i32 {
    a + b
}

// 多返回值：惯用元组，调用方解构
fn divide(a: i32, b: i32) -> (i32, i32) {
    (a / b, a % b)
}

// 高阶函数：接收闭包参数。impl Fn 表示"任何实现了 Fn 的类型"
fn apply_twice(f: impl Fn(i32) -> i32, v: i32) -> i32 {
    f(f(v))
}

fn main() {
    greet("Rust");
    println!("add(3, 4) = {}", add(3, 4));

    // 元组解构接收"多返回值"
    let (quotient, remainder) = divide(17, 5);
    println!("divide(17, 5) = 商 {} 余 {}", quotient, remainder);

    // ---- 闭包三种写法 ----
    let inc = |x: i32| x + 1; // 1) 单表达式体，最简洁
    let adder = |x: i32| {    // 2) 块体，适合多条语句
        let base = 10;
        x + base
    };
    let mut factor = 100;
    let mut with_env = |x: i32| { // 3) 捕获外部环境（此处可变捕获）
        factor += 1; // 修改了环境变量
        x + factor
    };
    println!("inc(41) = {}", inc(41));
    println!("adder(5) = {}", adder(5));
    println!("with_env(0) 第一次 = {}，第二次 = {}", with_env(0), with_env(0));
    println!("闭包修改环境后 factor = {}", factor);

    // move：强制夺取所有权（并发场景常用，见 14_concurrency）
    let title = String::from("闭包");
    let own = move || println!("move 闭包拿走了所有权：{}", title);
    own();

    // 闭包作为参数传给高阶函数
    println!("apply_twice(inc, 10) = {}", apply_twice(inc, 10));

    // ---- 迭代器链：filter 留下偶数，map 求平方，collect 收集 ----
    let squares: Vec<i32> = (1..=10).filter(|x| x % 2 == 0).map(|x| x * x).collect();
    println!("偶数平方 = {:?}", squares);

    // 惰性求值：不 collect 就不执行；sum/fold 等是终结操作
    let total: i32 = (1..=10).map(|x| x * 2).sum();
    println!("1..=10 各乘 2 求和 = {}", total);
    let product = (1..=5).fold(1, |acc, x| acc * x); // fold 手写累积
    println!("5 的阶乘（fold 实现）= {}", product);
}
