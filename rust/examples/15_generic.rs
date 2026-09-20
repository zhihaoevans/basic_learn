// 主题说明：泛型 —— 泛型函数、泛型结构体与方法、trait bound 约束，以及 impl Trait 返回类型。
//           Rust 泛型是编译期单态化（monomorphization）：每个具体类型生成一份代码，零运行时开销。
// 运行命令：cargo run --example 15_generic
// 预期输出（关键行）：
//   最大数 = 9，最大单词 = pear
//   前 5 个平方 = [0, 1, 4, 9, 16]
//   Pair { first: 1.5, second: 1.5 } 相等 = true

use std::fmt::Debug;

// ---- 泛型结构体 ----
#[derive(Debug)]
struct Pair<T> {
    first: T,
    second: T,
}

// impl<T: ...>：方法也可以比结构体要求更多约束
impl<T: PartialEq + Debug> Pair<T> {
    fn same(&self) -> bool {
        self.first == self.second // 需要 PartialEq
    }

    fn show(&self) {
        println!("{:?}", self); // 需要 Debug
    }
}

// ---- 泛型函数 + trait bound：T 必须可比较 ----
fn largest<T: PartialOrd>(items: &[T]) -> &T {
    let mut max = &items[0];
    for item in items {
        if item > max {
            max = item;
        }
    }
    max
}

// 多重约束用 + 连接；where 从句适合复杂签名（两种写法等价）
fn dump<T>(item: &T)
where
    T: Debug + Clone,
{
    let cloned = item.clone();
    println!("克隆后调试打印：{:?}", cloned);
}

// ---- impl Trait：返回"某个实现了该 trait 的具体类型"，常用于迭代器 ----
fn squares(n: u32) -> impl Iterator<Item = u32> {
    (0..n).map(|i| i * i) // 不写死具体类型，调用方当迭代器用
}

// impl Trait 也能放在参数位置（等价于泛型 + bound 的语法糖）
fn shout(s: impl AsRef<str>) -> String {
    s.as_ref().to_uppercase()
}

// ---- 泛型枚举的"内置代表"：Option<T> / Result<T, E> 本身就是泛型 ----
fn first_or_default<T: Copy>(slice: &[T], default: T) -> T {
    match slice.first() {
        Some(v) => *v,
        None => default,
    }
}

fn main() {
    // 泛型函数：同一份代码服务多种类型
    let nums = [3, 7, 2, 9, 4];
    let words = ["apple", "pear", "fig"];
    println!("最大数 = {}，最大单词 = {}", largest(&nums), largest(&words));

    // 泛型结构体
    let p1 = Pair { first: 1, second: 2 };
    let p2 = Pair { first: 1.5, second: 1.5 };
    p1.show();
    println!("Pair {{ first: 1.5, second: 1.5 }} 相等 = {}", p2.same());

    // where 从句与 impl Trait 参数
    dump(&String::from("泛型字符串"));
    println!("shout(impl AsRef<str>) = {}", shout("rust"));

    // impl Trait 返回迭代器
    let sq: Vec<u32> = squares(5).collect();
    println!("前 5 个平方 = {:?}", sq);
    println!("前 5 个平方求和 = {}", squares(5).sum::<u32>());

    // 泛型 + 默认值
    let empty: [i32; 0] = [];
    println!("first_or_default 空数组取默认 = {}，非空取首元素 = {}",
        first_or_default(&empty, -1),
        first_or_default(&nums, 0));
}
