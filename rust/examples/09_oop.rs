// 主题说明：结构化编程 —— struct 与 impl 方法/关联函数、携带数据的枚举、trait 定义与实现、
//           trait bound 约束泛型，以及 derive(Debug/PartialEq) 派生宏。
//           Rust 没有类与继承，用"数据 + 行为 + 接口"组合出同样的表达力。
// 运行命令：cargo run --example 09_oop
// 预期输出（关键行）：
//   Rect { width: 3.0, height: 4.0 }，面积 = 12
//   r1 == r3 = true
//   枚举变体：圆，面积 = 78.5398

// derive：编译器自动实现 Debug（调试打印）与 PartialEq（== 比较）
#[derive(Debug, PartialEq)]
struct Rect {
    width: f64,
    height: f64,
}

impl Rect {
    // 关联函数：第一个参数不是 self，类似其他语言的"静态方法"，常用作构造器
    fn new(width: f64, height: f64) -> Self {
        Self { width, height } // Self 是 impl 类型的别名；字段名简写
    }

    fn square(size: f64) -> Self {
        Rect { width: size, height: size }
    }

    // 方法：&self 只读借用（另有 &mut self 可变借用、self 夺取所有权）
    fn area(&self) -> f64 {
        self.width * self.height
    }

    fn is_wider_than(&self, other: &Rect) -> bool {
        self.width > other.width
    }
}

// 枚举可携带数据：一个类型的每个变体装不同的载荷——Rust 没有"类继承"，
// "多形态数据"用枚举表达，配合 match 使用（Option/Result 正是这样定义的）
enum Shape {
    Circle(f64),       // 变体携带一个 f64（半径）
    Rect(Rect),        // 变体携带一个结构体
    Unit,              // 无载荷变体
}

// trait：定义共享行为的接口（类似 interface）
trait Describe {
    fn area(&self) -> f64; // 必须实现的方法

    fn kind(&self) -> String {
        String::from("图形") // 默认实现，实现者可覆盖
    }
}

impl Describe for Rect {
    fn area(&self) -> f64 {
        self.width * self.height // 覆盖：沿用字段计算
    }
}

impl Describe for Shape {
    fn area(&self) -> f64 {
        match self {
            Shape::Circle(r) => std::f64::consts::PI * r * r, // 解构出半径
            Shape::Rect(r) => r.area(), // 委托给 Rect 的实现
            Shape::Unit => 0.0,
        }
    }

    fn kind(&self) -> String {
        String::from(match self {
            Shape::Circle(_) => "圆",
            Shape::Rect(_) => "矩形",
            Shape::Unit => "单位",
        })
    }
}

// trait bound：T 必须实现 Describe 才能传入——静态分发、零开销
fn report<T: Describe>(name: &str, item: &T) {
    println!("{}（{}）：面积 = {:.4}", name, item.kind(), item.area());
}

fn main() {
    // ---- 结构体与 impl ----
    let r1 = Rect::new(3.0, 4.0);
    let r2 = Rect::square(5.0);
    println!("{:?}，面积 = {:.0}", r1, r1.area());
    println!("r2 更宽？{}", r2.is_wider_than(&r1));

    // derive 的能力：Debug 调试打印、PartialEq 相等比较
    let r3 = Rect::new(3.0, 4.0);
    println!("r1 == r3 = {}", r1 == r3);

    // 更新语法：..base 复制未提到的字段
    let r4 = Rect { height: 9.0, ..r1 };
    println!("结构体更新语法：{:?}", r4);

    // ---- 枚举携带数据 + match 分派 ----
    let shapes = [Shape::Circle(5.0), Shape::Rect(Rect::new(2.0, 6.0)), Shape::Unit];
    for s in &shapes {
        println!("枚举变体：{}，面积 = {:.4}", s.kind(), s.area());
    }

    // ---- trait 与 trait bound ----
    report("矩形 r1", &r1); // Rect 没覆盖 kind()，用的是 trait 默认实现"图形"
    report("半径 5 的圆", &shapes[0]);
}
