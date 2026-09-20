# C 语言示例

C 是静态类型的编译型系统语言，以贴近硬件、零运行时开销和可移植著称。本目录按 [TOPICS.md](../TOPICS.md) 的统一主题清单组织基础语法示例：一个主题一个自包含可运行文件，每个文件头注释含主题说明、运行命令与预期输出。

- 权威参考：[cppreference C（含 C17 标准）](https://en.cppreference.com/w/c)
- 语言标准与提案：[WG14 / ISO C 委员会](https://www.open-std.org/jtc1/sc22/wg14/)

## 环境要求

- **C17** 标准（gcc 7+ 或 clang 6+，CMake 配置里已固定 `CMAKE_C_STANDARD 17`）
- **CMake ≥ 3.16**
- **pthread**（POSIX 线程，Linux/macOS 系统自带；`concurrency/` 示例由 CMake 自动链接）

## 如何运行

统一用 CMake 构建产物名按「目录_文件」前缀规则生成（如 `variable/variable_basics.c` → `variable_variable_basics`），全部输出到 `c/build/bin/`：

```bash
# 在仓库根目录执行
cmake -S c -B c/build         # 配置
cmake --build c/build -j8     # 构建（零错误零警告）
./c/build/bin/variable_variable_basics   # 运行任意示例
for b in c/build/bin/*; do "$b" >/dev/null 2>&1 || echo "FAIL: $b"; done  # CI 同款全量门禁
```

> 旧版 README 推荐 `make all`（Makefile）：Makefile 已不再是本目录的主要构建方式，请统一使用上述 CMake 流程（与 CI 的 c.yml 门禁一致）。

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [print/print_basics.c](print/print_basics.c) | `./c/build/bin/print_print_basics` | printf/puts/putchar 基础输出 |
| 02 variable | [variable/variable_basics.c](variable/variable_basics.c) | `./c/build/bin/variable_variable_basics` | 基本类型、sizeof、const vs #define、类型转换与整型溢出 |
| 03 operator | [operator/operator_basics.c](operator/operator_basics.c) | `./c/build/bin/operator_operator_basics` | 算术/位运算/自增自减/三目/短路/优先级陷阱 |
| 04 string | [string/string_basics.c](string/string_basics.c) | `./c/build/bin/string_string_basics` | 字符串声明与 string.h 常用函数 |
| 05 control | [control/control_flow.c](control/control_flow.c) | `./c/build/bin/control_control_flow` | if/switch（fallthrough）/三种循环/break-continue/goto |
| 06 function | [function/function_basics.c](function/function_basics.c) | `./c/build/bin/function_function_basics` | 原型/定义/static/递归/函数指针入门 |
| 07 collection | [array/array_basics.c](array/array_basics.c) | `./c/build/bin/array_array_basics` | 数组声明、初始化、遍历与传参 |
| 08 map | — | — | ➖ C 标准库无映射/字典类型（只能数组+查找函数或第三方库模拟） |
| 09 oop | [oop/struct_polymorphism.c](oop/struct_polymorphism.c) | `./c/build/bin/oop_struct_polymorphism` | struct 封装+函数指针字段模拟方法与多态 |
| 10 error | [error/error_handling.c](error/error_handling.c) | `./c/build/bin/error_error_handling` | 返回码约定/errno/perror/strerror/EXIT_FAILURE |
| 11 file_io | [file_io/file_io.c](file_io/file_io.c) | `./c/build/bin/file_io_file_io` | fopen 模式/文本与二进制读写/错误检查 |
| 12 module | [module/module_demo.c](module/module_demo.c)（+ util.h/util.c） | `./c/build/bin/module_module_demo` | 头文件声明+实现文件定义、extern/static 可见性、include guard |
| 13 stdlib | [std/](std/README.md)（16 个头文件逐一演示） | 如 `./c/build/bin/std_stdio_demo` | C 标准库头文件速览 |
| 14 concurrency | [concurrency/pthread_basics.c](concurrency/pthread_basics.c) | `./c/build/bin/concurrency_pthread_basics` | pthread_create/join、mutex 互斥计数 |
| 15 generic | — | — | ➖ C 无语言级泛型（宏可粗略模拟，见 preprocessor/） |

各主题目录还有更多进展示例（array/ 的排序搜索多维、print/ 的格式化技巧、string/ 的处理技巧、math/ 的数学函数等），详见各目录 README。

## 进阶专题

- [gcc/](gcc/) —— 编译器特性专题（如 attribute 用法）
- [preprocessor/](preprocessor/README.md) —— 宏与预处理：#define、宏函数、条件编译、预定义宏
- [sanitizers/](sanitizers/README.md) —— ASan/LSan/UBSan/TSan 内存错误与未定义行为检测
- [../linux/](../linux/) —— 更进一步的 Linux 系统编程（系统调用、进程线程、IPC、网络等）
