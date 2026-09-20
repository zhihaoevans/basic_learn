// 主题说明：错误处理 —— Result<T, E> 与 Option<T>、? 运算符传播错误、match 错误分支、
//           unwrap/expect 的适用场景与 panic! 的定位说明。
//           Rust 没有 try/catch：可恢复错误走 Result，不可恢复走 panic!。
// 运行命令：cargo run --example 10_error
// 预期输出（关键行）：
//   解析成功：3 + 14 = 17
//   错误分支：ParseIntError 报告——invalid digit found in string
//   兜底默认值 = 0

use std::num::ParseIntError;

// ? 运算符：遇到 Err 立即返回错误、遇到 Ok 解包继续——是 Rust 错误传播的核心语法
// 缺项时 next() 返回 None，用 unwrap_or("") 变成空串，空串解析自然得到 ParseIntError
fn parse_pair(text: &str) -> Result<(i32, i32), ParseIntError> {
    let mut parts = text.split(',');
    let a = parts.next().unwrap_or("").parse::<i32>()?;
    let b = parts.next().unwrap_or("").parse::<i32>()?;
    Ok((a, b))
}

fn main() {
    // ---- Result：Ok / Err 两个分支 ----
    let ok = "3,14".parse::<i32>();
    match ok {
        Ok(n) => println!("解析 \"3,14\" 成功：{}", n),
        Err(e) => println!("解析失败：{}", e),
    }

    // ---- match 错误分支：对错误精细分派 ----
    let bad = "abc".parse::<i32>();
    match bad {
        Ok(n) => println!("ok: {}", n),
        Err(e) => println!("错误分支：ParseIntError 报告——{}", e),
    }

    // ---- ? 传播：parse_pair 内部任一步失败，错误原样传出 ----
    match parse_pair("3,14") {
        Ok((a, b)) => println!("解析成功：{} + {} = {}", a, b, a + b),
        Err(e) => println!("解析失败：{}", e),
    }
    match parse_pair("只有一项") {
        Ok((a, b)) => println!("不应走到这：{} {}", a, b),
        Err(e) => println!("缺项被 ? 传播出来：{}", e),
    }

    // ---- Option：表达"可能没有值"，替代 null ----
    let maybe: Option<i32> = None;
    println!("兜底默认值 = {}", maybe.unwrap_or(0)); // 没有 0 时给默认值
    println!("映射继续链 = {:?}", maybe.map(|x| x * 2)); // None 穿透 map
    let some: Option<i32> = Some(21);
    println!("有值时 unwrap_or = {}，map 后 = {:?}", some.unwrap_or(0), some.map(|x| x * 2));
    if let Some(v) = some {
        println!("if let 拿到值：{}", v);
    }

    // ---- unwrap / expect：便捷但有风险 ----
    // unwrap()：Err/None 时直接 panic；expect("说明")：panic 时附带上下文信息。
    // 适用场景：原型/测试/示例代码，或"此处失败即程序 bug、无法恢复"的场合；
    // 生产库代码对外输入请返回 Result，而不是 unwrap。
    let pinned = "42".parse::<i32>().expect("字面量必然合法，失败即 bug");
    println!("expect 演示 = {}", pinned);

    // ---- panic!：不可恢复错误 ----
    // 数组越界、算术溢出（debug 下）、显式 panic! 宏都会中止线程并展开栈打印调用位置。
    // 它不是异常，不能被捕获；本示例要保持退出码 0，因此只演示概念不真正触发：
    // panic!("boom"); // 取消注释会看到：thread 'main' panicked at ...
    // std::panic::catch_unwind 只用于 FFI 边界等特殊场景，不是常规错误处理手段。
    println!("示例正常结束（退出码 0）");
}
