// 主题说明：模块系统 —— mod 声明模块、use 引入路径、pub 可见性控制，以及单文件内组织模块的方式；
//           文末注释给出等价的多文件写法。Rust 用"模块 + 可见性"而非"目录即包"来组织代码。
// 运行命令：cargo run --example 12_module
// 预期输出（关键行）：
//   math::add(1, 2) = 3
//   nested::VERSION = 1.0
//   square.side = 3，square.area() = 9

// ---- 方式一（本文件采用）：单文件内的 mod 块 ----
mod math {
    // pub：模块外可见；不加 pub 则仅模块内可见
    pub fn add(a: i32, b: i32) -> i32 {
        a + b
    }

    // 私有函数：模块的实现细节，外部无法调用
    fn normalize(v: f64) -> f64 {
        if v < 0.0 { -v } else { v }
    }

    // 公开函数内部可以使用私有项
    pub fn distance(x: f64, y: f64) -> f64 {
        normalize((x * x + y * y).sqrt())
    }

    // 嵌套模块：路径 math::nested::VERSION
    pub mod nested {
        pub const VERSION: &str = "1.0";

        pub fn describe() -> String {
            format!("math 模块 v{}", VERSION)
        }
    }
}

// ---- 另一个模块：含结构体与可见性细节 ----
mod shapes {
    pub struct Square {
        pub side: f64,      // pub 字段：模块外可读写
        _secret_id: u32,    // 私有字段：模块外不可构造/访问（下用关联函数构造）
    }

    impl Square {
        // 因为有私有字段，外部无法字面量构造，必须走这个"构造器"
        pub fn new(side: f64) -> Self {
            Square { side, _secret_id: 1 }
        }

        pub fn area(&self) -> f64 {
            self.side * self.side // 可访问本模块私有字段
        }
    }
}

// ---- use：把路径引入当前作用域，避免每次写全路径 ----
use math::nested; // 之后直接写 nested::VERSION
use shapes::Square;

fn main() {
    // 全路径调用
    println!("math::add(1, 2) = {}", math::add(1, 2));
    println!("math::distance(3.0, -4.0) = {}", math::distance(3.0, -4.0)); // 内部用了私有函数

    // use 引入后短路径调用
    println!("nested::VERSION = {}", nested::VERSION);
    println!("{}", nested::describe());

    // 私有性演示：私有字段只能通过关联函数构造
    let square = Square::new(3.0);
    println!("square.side = {}，square.area() = {:.0}", square.side, square.area());

    // 分支语句说明：以下写法都无法通过编译（可见性/私有性拦截）——
    // math::normalize(1.0);        // error: function `normalize` is private
    // let s = Square { side: 1.0, _secret_id: 0 }; // error: field `_secret_id` is private
}

// ---- 方式二（等价多文件写法，供对照）----
// 目录结构：
//   src/main.rs          → 内容 = 本文件去掉 mod 块，改写两行声明：
//                            mod math;      // 编译器找 src/math.rs
//                            mod shapes;    // 编译器找 src/shapes.rs
//   src/math.rs          → 原 mod math { ... } 的花括号体（去掉一层缩进）
//   src/math/nested.rs   → 嵌套模块放子文件（或在 math.rs 里写 `pub mod nested;`）
// 模块路径、pub 规则与单文件版完全一致——mod 块只是把"文件"内联进了当前文件。
// 另：本目录是 examples/ 下的单文件示例，故采用方式一；真实工程建议按方式二拆分。
