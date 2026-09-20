// 主题说明：运算符与表达式 —— 算术（含整数溢出语义）、比较、逻辑短路、位运算与范围。
//           注意：debug 构建下整数溢出会 panic，release 下回绕；需要可控溢出请用 wrapping_* 系列。
// 运行命令：cargo run --example 03_operator
// 预期输出（关键行）：
//   7 / 2 = 3，7 % 2 = 1
//   u8 回绕：250 + 10 = 4
//   1..=5 收集 = [1, 2, 3, 4, 5]

fn main() {
    // ---- 算术运算 ----
    println!("7 / 2 = {}，7 % 2 = {}", 7 / 2, 7 % 2); // 整数除法向零截断
    println!("浮点除法 = {:.4}", 7.0 / 2.0);

    // 溢出语义：cargo run 是 debug 模式，250u8 + 10 会直接 panic（演示用注释说明）
    // println!("{}", 250u8 + 10); // 取消注释：attempt to add with overflow
    let x: u8 = 250;
    println!("u8 回绕：250 + 10 = {}", x.wrapping_add(10)); // 260 % 256 = 4
    println!("饱和加法：250 + 10 = {}", x.saturating_add(10)); // 封顶 255
    println!("带检查加法：250 + 10 = {:?}", 250u8.checked_add(10)); // None 表示溢出

    // ---- 比较运算 ----
    println!("1 < 2 = {}，2 >= 2 = {}", 1 < 2, 2 >= 2);
    println!("字符串也能比较：\"abc\" < \"abd\" = {}", "abc" < "abd"); // 按字典序

    // ---- 逻辑运算：&& || ! 短路求值 ----
    fn check(n: i32) -> bool {
        println!("  （check({}) 被调用）", n);
        n > 0
    }
    println!("短路示例：");
    let r = check(-1) && check(999); // 第一个为 false，第二个不再执行
    println!("false && ... = {}", r);
    let r = check(1) || check(999); // 第一个为 true，第二个不再执行
    println!("true || ... = {}", r);

    // ---- 位运算：& | ^ ! << >> ----
    let m = 0b1100;
    let n = 0b1010;
    println!("1100 & 1010 = {:04b}", m & n);
    println!("1100 | 1010 = {:04b}", m | n);
    println!("1100 ^ 1010 = {:04b}", m ^ n);
    println!("!1100(u8) = {:08b}", !m as u8);
    println!("1 << 4 = {}，32 >> 2 = {}", 1u32 << 4, 32u32 >> 2);

    // ---- 范围：a..b 左闭右开，a..=b 两端都含 ----
    let half_open: Vec<i32> = (0..5).collect(); // 0,1,2,3,4
    let closed: Vec<i32> = (1..=5).collect(); // 1,2,3,4,5
    println!("0..5  收集 = {:?}", half_open);
    println!("1..=5 收集 = {:?}", closed);
    println!("范围也能判断包含：(1..=5).contains(&3) = {}", (1..=5).contains(&3));
}
