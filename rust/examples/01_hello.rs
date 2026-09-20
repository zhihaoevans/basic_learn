// 主题说明：Rust 的第一个程序 —— println! 宏、变量插值与两种注释写法。
//           println! 是宏而非函数，编译期检查格式串；{} 通用显示，{:?} 调试输出。
// 运行命令：cargo run --example 01_hello
// 预期输出（关键行）：
//   Hello, Rust!
//   你好，Rust！第 1 个示例
//   1 + 1 = 2

fn main() {
    // 单行注释：以 // 开头，最常用

    /*
     块注释：可跨多行，常用于临时屏蔽一段代码
    */

    println!("Hello, Rust!");

    // {} 按顺序插值，可加编号 {0}/{1} 复用参数
    let name = "Rust";
    let no = 1;
    println!("你好，{}！第 {} 个示例", name, no);
    println!("编号复用：{0} 对 {0}，胜者是 {0}", name);

    // {:?} 调试格式：元组、数组等没有 Display 的类型用它打印
    let pair = (2024, "stable");
    let list = [1, 2, 3];
    println!("元组用调试打印：{:?}", pair);
    println!("数组用调试打印：{:?}", list);

    // {:#?} 是带缩进的美化调试输出
    println!("美化调试输出：{:#?}", pair);

    println!("1 + 1 = {}", 1 + 1);

    // print! 不换行，println! 换行
    print!("print! 不换行，");
    print!("接着这一行\n");
    println!("换行转义与制表符：a\tb");
}
