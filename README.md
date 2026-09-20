# basic_learn

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
| Shell | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ➖ | ✅ | ✅ | ✅ | ✅ | ✅ | ➖ | — |
| SQL | ➖ | ✅ | ✅ | ✅ | ✅ | ➖ | ✅ | ➖ | ➖ | ✅ | ➖ | ➖ | ✅ | ➖ | ➖ | ✅ |

> 矩阵为手动维护：完成一个主题就更新对应单元格。
>
> *SQL 行说明：SQL 为声明式范式，不按 15 题清单组织，本行 ✅ 为近似映射 —— 02 建表与类型（seed.sql）、03 运算符与函数（01）、04 字符串函数（01）、05 CASE/流程（02）、07 结果集操作（04 的 UNION/INTERSECT/EXCEPT）、10 约束与错误处理（seed + 06）、13 内置函数速览（01/02/04）、特色为窗口函数/递归 CTE/执行计划（04/07/08）；➖ 为无对应主题。SQL 自身的 8 个范式主题清单见 [sql/README.md](sql/README.md)。*

## 其他语言与工具示例

- [assembly](assembly/README.md) - 汇编语言示例
- swift/ - Swift 示例项目（本地项目，未纳入版本管理）
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
