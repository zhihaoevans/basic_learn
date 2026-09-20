// 主题说明：控制流 —— if 是表达式可直接赋值、loop 可 break 出值、while、for-in 遍历范围与迭代器、match 模式匹配入门。
// 运行命令：cargo run --example 05_control
// 预期输出（关键行）：
//   6 是偶数
//   loop 跳出值 = 30
//   1 到 100 求和 = 5050
//   match 结果 = 六

fn main() {
    let n = 6;

    // ---- if 是表达式：分支有值，可直接用于赋值（Rust 没有三元运算符 ?:）----
    let parity = if n % 2 == 0 { "偶数" } else { "奇数" };
    println!("{} 是{}", n, parity);

    // 普通多分支
    if n < 0 {
        println!("负数");
    } else if n == 0 {
        println!("零");
    } else {
        println!("正数");
    }

    // ---- loop：无限循环，break 可以带返回值 ----
    let mut count = 0;
    let result = loop {
        count += 1;
        if count == 3 {
            break count * 10; // break 的值成为 loop 表达式的值
        }
    };
    println!("loop 跳出值 = {}（count = {}）", result, count);

    // 循环标签：break/continue 可指定跳出哪一层
    'outer: for i in 1..=3 {
        for j in 1..=3 {
            if i * j > 4 {
                break 'outer; // 直接跳出外层
            }
            print!("{}x{}={} ", i, j, i * j);
        }
    }
    println!();

    // ---- while ----
    let mut down = 3;
    while down > 0 {
        print!("{} ", down);
        down -= 1;
    }
    println!("发射！");

    // ---- for-in：Rust 最常用的循环 ----
    for i in 1..=5 {
        print!("{} ", i); // 闭区间范围
    }
    println!();
    let sum: i32 = (1..=100).sum(); // 范围本身是迭代器，配合迭代器方法免写循环
    println!("1 到 100 求和 = {}", sum);

    let langs = ["Rust", "Go", "Java"];
    for (idx, lang) in langs.iter().enumerate() {
        println!("[{}] {}", idx, lang); // enumerate 带下标遍历
    }

    // ---- match：多模式匹配，分支必须穷尽 ----
    let msg = match n {
        1 => "一",
        6 => "六",
        2 | 3 => "二或三", // 多值模式
        4..=5 => "四五之间", // 范围模式
        _ => "其他", // _ 兜底，保证穷尽
    };
    println!("match 结果 = {}", msg);

    // match 同样是表达式，也能解构元组
    let point = (3, -4);
    let quadrant = match point {
        (0, 0) => "原点",
        (_x, 0) => "在 x 轴上",
        (0, y) if y != 0 => "在 y 轴上", // match 守卫：附加条件
        (x, y) if x > 0 && y > 0 => "第一象限",
        _ => "其他位置",
    };
    println!("点 {:?} —— {}", point, quadrant);

    // if let：只关心一种模式时的语法糖
    if let Some(v) = Option::Some(42) {
        println!("if let 捕获到 Some({})", v);
    }
}
