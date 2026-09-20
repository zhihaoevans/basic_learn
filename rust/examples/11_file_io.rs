// 主题说明：文件读写 —— fs::write 整写、read_to_string 整读、BufReader 逐行读、
//           追加写，以及用 std::env::temp_dir() 做临时文件并清理（不引入第三方 tempfile）。
// 运行命令：cargo run --example 11_file_io
// 预期输出（关键行）：
//   整读共 47 字节 / 27 字符
//   第 1 行：Hello, file IO!
//   临时文件已清理：.../rust_basics_11_file_io_demo.txt

use std::env;
use std::fs::{self, File};
use std::io::{BufRead, BufReader, Write};

fn main() -> std::io::Result<()> {
    // 固定路径的临时文件：不引入 tempfile 依赖，用系统临时目录 + 明确文件名
    let path = env::temp_dir().join("rust_basics_11_file_io_demo.txt");
    println!("临时文件路径：{}", path.display());

    // ---- 一次性写入 ----
    fs::write(&path, "Hello, file IO!\n第二行：逐行读取演示\n")?;

    // ---- 一次性读出 ----
    let content = fs::read_to_string(&path)?;
    println!("整读共 {} 字节 / {} 字符", content.len(), content.chars().count());

    // ---- 逐行读：BufReader 带缓冲，read_to_string 不适合大文件时用它 ----
    let file = File::open(&path)?;
    let reader = BufReader::new(file);
    for (i, line) in reader.lines().enumerate() {
        let line = line?; // lines() 里每行也是 io::Result，? 传播
        println!("第 {} 行：{}", i + 1, line);
    }

    // ---- 追加写：File::options() 链式配置打开方式 ----
    {
        let mut appender = File::options().append(true).open(&path)?;
        writeln!(appender, "第三行：追加写入")?;
    } // 块结束时自动关闭文件（RAII，无需 close）

    // 追加后再核对
    let content = fs::read_to_string(&path)?;
    let count = content.lines().count();
    println!("追加后共 {} 行，末行 = {:?}", count, content.lines().last());

    // ---- 元数据与存在性 ----
    let meta = fs::metadata(&path)?;
    println!("文件大小 = {} 字节，是文件？{}", meta.len(), meta.is_file());

    // ---- 清理临时文件 ----
    fs::remove_file(&path)?;
    println!("临时文件已清理：{}", path.display());
    println!("还存在吗？{}", path.exists());

    Ok(()) // main 返回 Result：Ok 对应进程退出码 0
}
