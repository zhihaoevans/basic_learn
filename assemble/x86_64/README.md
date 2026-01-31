# x86_64 汇编示例（GNU as / AT&T）

本目录提供 Linux x86_64 平台下的 GNU as（AT&T 语法）示例，按主题分目录组织。

## 目录结构

```
x86_64/
├── 00_toolchain/     # 工具链与约定说明
├── 01_basics/        # 基础指令与退出/输出
├── 02_control_flow/  # 控制流
├── 03_data/          # 数据与内存
├── 04_functions/     # 函数调用
├── 05_stack/         # 栈与栈帧
├── 06_syscalls/      # 系统调用
├── 07_files/         # 文件 I/O
└── 08_misc/          # 其他示例
```

## 构建与运行

```bash
make -C x86_64
./01_basics/hello_write
```

## 示例覆盖

- 系统调用：write/exit/open/read/close
- 控制流：循环与条件分支
- 函数与栈：call/ret、栈帧管理
- 数据：字符串、数组与索引寻址
- 时间戳：rdtsc

## CI 验证

仓库已配置 GitHub Actions，在 Ubuntu 上自动构建与运行基础示例。
