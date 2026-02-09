# 工具链与约定

本目录简要说明 x86_64 + GNU as（AT&T 语法）的构建与调用约定。

## 约定

- 目标平台：Linux x86_64
- 语法：GNU as（AT&T）
- 入口：`_start`
- 系统调用：`syscall` 指令
- 寄存器：
  - 参数：`rdi, rsi, rdx, r10, r8, r9`
  - 返回：`rax`

## 构建方式

```bash
as file.s -o file.o
ld file.o -o file
```

或在顶层使用：

```bash
make -C x86_64
```

## 说明

这些示例面向 **Linux x86_64**。在 macOS 上构建会使用 Apple 的 `as/ld`，与 GNU 工具链不兼容。
