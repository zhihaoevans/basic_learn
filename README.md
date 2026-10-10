# basic_learn

> **快速导航 / Quick navigation**： [选择语言](#语言目录与状态) · [主题覆盖矩阵](#主题覆盖矩阵) · [统一主题清单](TOPICS.md) · [调试笔记](docs/gdb) · [Web 示例](web/frontend)

## 从这里开始

这是一个按**相同主题对照不同编程语言**的可运行示例库，适合学习新语言、复习基础语法和比较语言设计差异。

1. **选语言**：从下方「语言目录与状态」进入对应语言的 README。
2. **选主题**：打开 [TOPICS.md](TOPICS.md)，从变量、函数、集合、错误处理等主题中选择一个。
3. **看示例并运行**：进入语言目录，参考示例文件中的运行命令和预期输出，在本地验证。
4. **横向比较**：用同一个主题对比 C++、Go、Rust、Python、TypeScript 等语言的实现方式。

> 不同语言需要各自的编译器或运行时；具体环境和运行方式请以对应目录及示例说明为准。

常用编程语言基础语法示例集合，面向教学分享：每门语言按统一主题清单组织，一个主题一个可运行示例，CI 保障所有示例可构建、可运行、不腐烂。

- 主题清单见 [TOPICS.md](TOPICS.md)
- 每个示例文件头注释包含：主题说明、运行命令、预期输出
- 想贡献新示例？按 TOPICS.md 的主题编号放入对应语言目录，CI 会自动验证

## 语言目录与状态

| 语言 | 目录 | 基础语法状态 | CI |
|---|---|---|---|
| C | [c](c/README.md) | ✅ 完整 | ✅ |
| C++ | [cpp](cpp/README.md) | ✅ 完整 | ✅ |
| Go | [golang](golang/README.md) | ✅ 完整 | ✅ |
| Java | [java](java/README.md) | ✅ 完整 | ✅ |
| Python | [python](python/README.md) | ✅ 完整 | ✅ |
| Rust | [rust](rust/README.md) | ✅ 完整 | ✅ |
| JavaScript | [javascript](javascript/README.md) | ✅ 完整 | ✅ |
| TypeScript | [typescript](typescript/README.md) | ✅ 完整 | ✅ |
| Shell | [scripts/shell](scripts/shell/README.md) | ✅ 完整 | ✅ |
| SQL | [sql](sql/README.md) | ✅ 完整 | ✅ |

## 主题覆盖矩阵

图例：✅ 已覆盖　➖ 不适用　— 待补（清单定义见 [TOPICS.md](TOPICS.md)）

| 语言 | 01 hello | 02 variable | 03 operator | 04 string | 05 control | 06 function | 07 collection | 08 map | 09 oop | 10 error | 11 file_io | 12 module | 13 stdlib | 14 concurrency | 15 generic | 特色 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| C | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ➖ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ➖ | — |
| C++ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Go | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Java | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Python | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Rust | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| JavaScript | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ➖ | ✅ |
| TypeScript | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Shell | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ➖ | ✅ | ✅ | ✅ | ✅ | ✅ | ➖ | ✅ |
| SQL | ➖ | ✅ | ✅ | ✅ | ✅ | ➖ | ✅ | ➖ | ➖ | ✅ | ➖ | ➖ | ✅ | ➖ | ➖ | ✅ |

> 矩阵为手动维护：完成一个主题就更新对应单元格。
>
> *SQL 行说明：SQL 为声明式范式，不按 15 题清单组织，本行 ✅ 为近似映射 —— 02 建表与类型（seed.sql）、03 运算符与函数（01）、04 字符串函数（01）、05 CASE/流程（02）、07 结果集操作（04 的 UNION/INTERSECT/EXCEPT）、10 约束与错误处理（seed + 06）、13 内置函数速览（01/02/04）、特色为窗口函数/递归 CTE/执行计划（04/07/08）；➖ 为无对应主题。SQL 自身的 8 个范式主题清单见 [sql/README.md](sql/README.md)。*

## 其他语言与工具示例

- [assembly](assembly/README.md) - 汇编语言示例
- [swift](swift/) - Swift 示例项目（运行方式以目录内容为准）
- [lua](lua/learnlua.lua) - Lua 示例
- [scripts/sed](scripts/sed/README.md) - sed 示例
- [build_systems/makefile](build_systems/makefile/README.md) - Makefile 模板
- [c/preprocessor](c/preprocessor/README.md) - C 宏示例
- [cpp/protobuf](cpp/protobuf/README.md) - Protobuf 示例
- languages/ - 早期多语言章节式练习与测试（旧结构，待后续计划迁移合并）

## 文档与图示

- [docs/markdown](docs/markdown) - Markdown 示例
- [docs/drawio](docs/drawio) - Drawio 绘图
- [docs/plantuml](docs/plantuml) - PlantUML 图示
- [docs/mermaid](docs/mermaid) - Mermaid 图示
- [docs/gdb](docs/gdb) - GDB 学习与笔记
- [docs/intel](docs/intel) - Intel 架构相关资料

## Web

- [web/frontend](web/frontend) - 前端示例与练习（Vue3 工程）

## 最小运行示例

先克隆仓库，再按语言目录安装对应工具；本仓库没有涵盖所有语言的统一运行环境。

```bash
git clone https://github.com/zhihaoevans/basic_learn.git
cd basic_learn
cmake -S cpp/basics -B build/cpp-basics
cmake --build build/cpp-basics
./build/cpp-basics/01_hello
```

此示例需要 CMake 3.16+ 与支持 C++17 的编译器；上面的可执行文件路径对应 Linux/macOS 的常见单配置构建。其他语言的命令见各目录 README。

## 按工程目标选择入口

| 目标 | 入口 |
| --- | --- |
| 对照学习语言基础 | [TOPICS.md](TOPICS.md) · [C++](cpp/README.md) · [Python](python/README.md) · [Go](golang/README.md) |
| 学习内存错误定位 | [C Sanitizers](c/sanitizers/README.md) |
| 学习调试与底层 | [GDB 笔记](docs/gdb/) · [汇编示例](assembly/README.md) |
| 参考构建工具 | [Makefile 模板](build_systems/makefile/README.md) |
| Web 练习 | [Web 前端](web/frontend/) |

## 新增示例

按 [主题清单](TOPICS.md)选择主题，在对应语言目录补充最小可运行例子，并注明环境、命令和预期输出。涉及新依赖时同步更新相关 [CI 工作流](.github/workflows/)。表格与 CI 状态是文档中的维护记录，实际运行结果以当前提交的检查为准。
