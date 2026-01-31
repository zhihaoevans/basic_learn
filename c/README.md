# C 语言示例

本目录包含 C 语言基础示例与标准库演示，覆盖数组、字符串、数学、输出与标准库头文件。

## 目录结构

```
c/
├── array/     # 数组与初始化示例
├── math/      # 数学相关示例
├── print/     # 输出与格式化示例
├── string/    # 字符串相关示例
├── std/       # C 标准库演示（含完整 README）
└── tmp/       # 临时/实验代码
```

## 学习路径建议

1. array → print → string → math
2. 进入 std/ 学习 C 标准库头文件及其示例

## 运行方式

```bash
# 使用 Makefile 在 c/ 目录下构建所有示例并把可执行文件放到 bin/
make -C c
# 或构建单个示例（在 c/ 目录）
make -C c all
# 以单文件为例（不使用 make）
cc array/test.c -o array_test
./array_test
```
