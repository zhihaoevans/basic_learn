// 主题说明：变量与常量 —— let 默认不可变、let mut 可变、shadowing 遮蔽、基本类型与 as 转换。
//           Rust 是静态强类型，整数字面量默认 i32、小数默认 f64。
// 运行命令：cargo run --example 02_variable
// 预期输出（关键行）：
//   x = 5, y = 11
//   shadowing 后 x = "6"（长度 1）
//   常量 MAX_SCORE = 100

// const 常量：编译期求值，必须显式标注类型，命名惯例全大写
const MAX_SCORE: i32 = 100;

fn main() {
    // let 声明的变量默认不可变（immutable）
    let x = 5;
    // x = 6; // 取消注释会报错：cannot assign twice to immutable variable

    // let mut 才允许修改
    let mut y = 10;
    y += 1;
    println!("x = {}, y = {}", x, y);

    // shadowing：用 let 重新声明同名变量，可以改变类型——这与 mut 完全不同
    let x = x + 1; // 新的 x，值为 6
    let x = x.to_string(); // 再遮蔽成 String 类型
    println!("shadowing 后 x = \"{}\"（长度 {}）", x, x.len());

    // 基本类型一览
    let a: i32 = -42; // 有符号 32 位整数（整数字面量默认类型）
    let b: u8 = 255; // 无符号 8 位，取值 0~255
    let c: f64 = 3.14159; // 双精度浮点（小数字面量默认类型）
    let flag: bool = true;
    let ch: char = '中'; // char 是 4 字节 Unicode 标量，可存中文与 emoji
    let size: usize = 8; // 与平台指针同宽的无符号类型，常用于长度/索引
    println!(
        "i32={} u8={} f64={} bool={} char={} usize={}",
        a, b, c, flag, ch, size
    );

    // 类型推断：由后续用法推断出具体类型
    let guess = "42".parse::<i32>().expect("不是数字"); // turbofish ::<> 指明目标类型
    println!("字符串解析结果 = {}", guess + 1);

    // as 显式转换（有截断风险，需自己负责）
    let sum = a as i64 + b as i64; // i32/u8 -> i64，避免溢出
    let ratio = b as f64 / 256.0; // 整数转浮点
    let truncated = c as i32; // f64 -> i32 直接舍去小数
    println!("转换求和 = {}，比例 = {:.3}，截断 = {}", sum, ratio, truncated);

    // 静态变量（补充）：static 生命周期贯穿整个程序，修改需要 unsafe，本例只读
    static LANG: &str = "Rust";
    println!("常量 MAX_SCORE = {}，静态 LANG = {}", MAX_SCORE, LANG);
}
