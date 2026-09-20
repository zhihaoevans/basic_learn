# Rust 基础语法示例

Rust 是一门静态强类型的系统级语言，以"所有权"机制在无 GC 的前提下实现内存安全，兼具性能与工程性。本目录按 [TOPICS.md](../TOPICS.md) 的统一主题清单组织：一个主题一个自包含的可运行示例（`examples/*.rs`），用 `println!` 逐个知识点演示结果。

- 官方文档：[The Rust Programming Language（"The Book"，中文版）](https://kaisery.github.io/trpl-zh-cn/) ｜ [std 标准库文档](https://doc.rust-lang.org/std/)

## 环境要求

- **Rust stable**（本地 1.98、CI 取最新 stable 均可）：本系列只用稳定版标准库，未引入任何第三方依赖
- 安装：`curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh`，装完 `cargo --version` 确认；升级用 `rustup update`
- 用 rustc/cargo 官方工具链即可，无需 IDE

## 如何运行

先进入本目录，再单条命令运行某个示例（cargo 会自动编译 `examples/` 下的同名文件）：

```bash
cd rust
cargo run --example 01_hello
```

一次性运行全部示例（与 CI 的验证方式相同）：

在仓库根目录执行：

```bash
for ex in rust/examples/*.rs; do n=$(basename "$ex" .rs); echo "== $n"; cargo run -q --manifest-path rust/Cargo.toml --example "$n"; done
```

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [examples/01_hello.rs](examples/01_hello.rs) | `cargo run --example 01_hello` | println! 宏、`{}`/`{:?}` 插值、两种注释 |
| 02 variable | [examples/02_variable.rs](examples/02_variable.rs) | `cargo run --example 02_variable` | let/let mut、shadowing、基本类型、const、as 转换 |
| 03 operator | [examples/03_operator.rs](examples/03_operator.rs) | `cargo run --example 03_operator` | 算术与溢出语义、比较、逻辑短路、位运算、范围 |
| 04 string | [examples/04_string.rs](examples/04_string.rs) | `cargo run --example 04_string` | &str vs String、拼接、len/切片/chars、split/trim/replace |
| 05 control | [examples/05_control.rs](examples/05_control.rs) | `cargo run --example 05_control` | if 表达式、loop/while/for-in、标签、match 入门 |
| 06 function | [examples/06_function.rs](examples/06_function.rs) | `cargo run --example 06_function` | 函数/元组多返回值、闭包三种写法、迭代器链 |
| 07 collection | [examples/07_collection.rs](examples/07_collection.rs) | `cargo run --example 07_collection` | 数组 [T; N]、Vec 增删迭代、切片 &[] |
| 08 map | [examples/08_map.rs](examples/08_map.rs) | `cargo run --example 08_map` | HashMap entry API、get、遍历、BTreeMap 有序 |
| 09 oop | [examples/09_oop.rs](examples/09_oop.rs) | `cargo run --example 09_oop` | struct/impl 方法、枚举带数据、trait、derive |
| 10 error | [examples/10_error.rs](examples/10_error.rs) | `cargo run --example 10_error` | Result/Option、? 运算符、match 错误分支、unwrap/expect/panic! |
| 11 file_io | [examples/11_file_io.rs](examples/11_file_io.rs) | `cargo run --example 11_file_io` | fs 读写、BufReader 逐行、temp_dir 临时文件与清理 |
| 12 module | [examples/12_module.rs](examples/12_module.rs) | `cargo run --example 12_module` | mod 声明、use、pub 可见性（含多文件等价写法） |
| 13 stdlib | [examples/13_stdlib.rs](examples/13_stdlib.rs) | `cargo run --example 13_stdlib` | 方法链、Duration/Instant、env::args、process::exit 说明 |
| 14 concurrency | [examples/14_concurrency.rs](examples/14_concurrency.rs) | `cargo run --example 14_concurrency` | spawn/join、mpsc channel、Arc&lt;Mutex&gt; 共享计数 |
| 15 generic | [examples/15_generic.rs](examples/15_generic.rs) | `cargo run --example 15_generic` | 泛型函数/结构体、trait bound、impl Trait 返回 |
| + 特色 ownership | [examples/16_ownership.rs](examples/16_ownership.rs) | `cargo run --example 16_ownership` | 所有权转移/借用/&mut 规则、生命周期标注、Copy vs Move |

## 进阶说明

- 本目录同时是 Cargo 工程：`rust/Cargo.toml` 定义包 `rust_basics`（无 lib/bin，仅 examples），`cargo build --examples` 一次构建全部
- [hello_world/](hello_world/) 是早期收录的独立 Cargo 子项目（有自己的 `Cargo.toml` 与 `src/main.rs`），保留用于演示标准 src 布局，运行：`cargo run --manifest-path rust/hello_world/Cargo.toml`
- [main.rs](main.rs) 是最早的 rustc 单文件示例（`fn main() { println!("Hello, world!"); }`），CI 用 `rustc` 直接编译运行；标准工程的程序入口都是 `src/main.rs` 或 `examples/*.rs` 里的 `fn main`
- 每个示例文件头部注释都标明了主题说明、运行命令与预期输出，适合按主题顺序阅读
- 之后的进阶方向：智能指针（Box/Rc/RefCell）、错误处理库（thiserror/anyhow）、异步生态（async/await + tokio）、宏（macro_rules! 与过程宏）
