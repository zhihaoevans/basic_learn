// 主题说明：字符串操作 —— &str（切片引用）与 String（堆上可增长）两种类型、
//           拼接与 format!、len/切片/chars、split/trim/replace，以及字节与字符遍历的区别。
// 运行命令：cargo run --example 04_string
// 预期输出（关键行）：
//   format! 拼接 = hello world! 它可增长
//   "你好" len = 6 字节，chars = 2 个字符
//   拆分结果 = ["a", "b", "c"]

fn main() {
    // ---- 两种字符串类型 ----
    let s1: &str = "hello"; // &str：字符串切片，指向静态数据或 String 的一段，只读
    let mut s2 = String::from("world"); // String：堆分配、可增长、拥有所有权
    s2.push('!'); // push 追加单个 char
    s2.push_str(" 它可增长"); // push_str 追加 &str
    println!("s1 = {}，s2 = {}", s1, s2);

    // ---- 拼接 ----
    let joined = format!("{} {}", s1, s2); // 推荐：format! 不夺取任何一方所有权
    println!("format! 拼接 = {}", joined);
    let owned = String::from("rust") + " is " + "fast"; // + 运算符：第一个参数必须是 String，后面接 &str
    println!("+ 拼接 = {}", owned);

    // ---- 长度与切片 ----
    let zh = "你好";
    println!("\"你好\" len = {} 字节，chars = {} 个字符", zh.len(), zh.chars().count());
    let s = String::from("Hello, Rust");
    let hello = &s[0..5]; // 切片按【字节】索引，必须落在 UTF-8 字符边界上
    println!("切片 [0..5] = {}", hello);
    // let bad = &zh[0..1]; // 取消注释会 panic：中文占 3 字节，1 不是字符边界

    // ---- 常用处理：split / trim / replace / to_uppercase ----
    let raw = "  a,b,c  ";
    let parts: Vec<&str> = raw.trim().split(',').collect();
    println!("拆分结果 = {:?}", parts);
    println!("trim 后 = \"{}\"", raw.trim());
    println!("replace 后 = {}", raw.trim().replace('a', "A").to_uppercase());
    println!("包含判断：包含 \"rust\" = {}", s.to_lowercase().contains("rust"));

    // ---- 遍历：字节 vs 字符 ----
    for (i, b) in zh.bytes().enumerate() {
        println!("第 {} 个字节 = 0x{:02X}", i, b); // 6 个字节
    }
    for (i, c) in zh.chars().enumerate() {
        println!("第 {} 个字符 = {}", i, c); // 2 个字符
    }
    // chars() 支持链式处理：过滤出中文字符
    let mixed = "Rust 好 strong";
    let cjk: String = mixed.chars().filter(|c| *c > '\u{4E00}' && *c < '\u{9FFF}').collect();
    println!("从中英混排里抽出中文：{}", cjk);
}
