# basic_learn 多语言基础语法教学仓库改造设计

- 日期：2026-09-19
- 状态：已与仓库所有者讨论通过

## 背景与目标

basic_learn 是一个编程语言与系统基础学习示例集合。目标是把它打造成**对外教学分享**的多语言基础语法仓库：规范、可复现运行、示例不腐烂。

经讨论确定的三个关键决策：

1. **用途**：对外教学分享（决定：重规范、可复现运行、CI 保障示例不过期）。
2. **语言范围**：主流 10 门——C、C++、Java、Python、Go、Rust、JavaScript、TypeScript、Shell、SQL。
3. **组织方案**：统一主题矩阵驱动（方案 A）。每门语言按同一份主题清单组织，根 README 展示语言 × 主题覆盖矩阵，CI 按语言路径触发。

### 现状要点（2026-09 盘点）

- 覆盖较好：C（主题目录 + CMake）、C++（332 个文件，含进阶专题）、Go（21 个单文件主题示例）。
- 几乎空白：Java、Rust（各只有 Hello World 级文件）、Lua（1 个文件）。
- 有专题无基础：Python（仅 ai/matplotlib/scapy/scrapy 专题）、Swift（仅一个 App 项目）。
- 完全缺失：JavaScript/TypeScript（仅 web/frontend 工程项目）、SQL。
- 已有 CI 先例：`.github/workflows/assemble-x86_64.yml`（按路径触发、构建 + 冒烟运行），本设计将该模式推广到全部 10 门语言。
- 已提交的构建产物需要清理：`java/out`、`java/.idea`、`swift/.build`、`swift/Calculator.app`、`c/bin`、`c/tmp`。

## 1. 统一主题清单（仓库根 `TOPICS.md`）

每门语言按「基础语法 15 题」组织；语言不支持的主题跳过（矩阵中标 ➖），语言独有亮点另列「特色主题」：

| # | 主题 | 内容 |
|---|---|---|
| 01 | hello | Hello World、打印、注释 |
| 02 | variable | 变量、常量与基本类型 |
| 03 | operator | 运算符与表达式 |
| 04 | string | 字符串操作 |
| 05 | control | 控制流：if / switch / 循环 |
| 06 | function | 函数、参数、返回值、闭包/lambda |
| 07 | collection | 数组 / 列表 / 集合 |
| 08 | map | 映射 / 字典 |
| 09 | oop | 类 / 结构体 / 接口 / 继承（按语言范式调整） |
| 10 | error | 错误 / 异常处理 |
| 11 | file_io | 文件读写 |
| 12 | module | 模块 / 包与可见性 |
| 13 | stdlib | 常用标准库速览 |
| 14 | concurrency | 并发入门（goroutine / thread / async / Promise） |
| 15 | generic | 泛型（语言不支持则跳过） |
| +  | 特色主题 | 语言独有亮点，如 Go 的 defer、Rust 的所有权与生命周期 |

适配说明：Shell 按脚本范式取适用子集（变量/字符串/控制流/函数/错误处理等）；SQL 改为自身范式清单：建表与约束、增删改查、聚合与分组、连接、子查询与 CTE、事务、窗口函数、索引与执行计划入门。

## 2. 每语言目录模板与运行方式

原则：**一个主题一个自包含可运行文件**；文件头注释三要素：主题说明、运行命令、预期输出。各语言采用最适合教学的形态：

| 语言 | 目录布局 | 运行方式 |
|---|---|---|
| C / C++ | 沿用现有目录 + CMake，缺主题补源文件 | CMake 构建 + 运行产物 |
| Go | 沿用现有平铺单文件（现状即模板） | `go run <file>.go` |
| Java | `java/01_hello/Hello.java`，一主题一目录一主类 | JDK 11+ 单文件直运行 `java Hello.java`（无构建工具） |
| Rust | 一个 Cargo 工程 + `examples/` 目录 | `cargo run --example 02_variable` |
| JavaScript | 顶层新目录 `javascript/`，平铺 `01_hello.js` | `node 01_hello.js` |
| TypeScript | 顶层新目录 `typescript/`，小 npm 工程 + `tsx` | `npx tsx src/02_variable.ts` |
| Python | `python/` 根下平铺基础主题文件，现有专题目录不动 | `python3 02_variable.py` |
| Shell | 沿用 `scripts/shell/`，按主题清单补齐 | `bash 02_variable.sh` |
| SQL | 新目录 `sql/`：`seed.sql` 造样例库 + 每主题一个 `.sql` | `sqlite3 db.sqlite < 01_select.sql`（SQLite：零服务依赖、CI 友好） |

命名规则：**新建语言目录**（Java、Rust、JavaScript、TypeScript、SQL）采用编号前缀（`01_`、`02_`…）排序并与矩阵对应；**已有语言**（Go、C、C++、Shell）保留现有命名不做重命名，主题顺序由各自 README 索引表承担。文件命名在语言内保持统一。

## 3. 每语言 README 模板

统一五段式：

1. 一句语言简介 + 官方文档链接
2. 环境要求（最低版本）与安装提示
3. 如何运行示例（一条命令）
4. 主题索引表：主题｜示例文件｜运行命令｜一句话说明
5. 进阶专题链接（现有 scrapy、design_mode、protobuf 等归入此段，不删除）

## 4. 根 README 与覆盖矩阵

根 README 重写为：仓库定位、快速上手、语言目录索引、**语言 × 主题覆盖矩阵**（✅ 已覆盖 / ➖ 不适用 / — 待补）。规模 10 门 × 15 题，手动维护，随提交更新。

不在 10 门清单内的现有语言（Swift、Lua、Assembly、sed）保留现状，在根 README 标注「其他语言示例」，不投入建设。

## 5. CI 防腐

推广现有 assembly workflow 的模式：每门语言一个独立 job，按路径触发（改哪门跑哪门），动作为「构建/语法检查 + 逐个运行示例并确认退出码为 0」：

- C/C++：CMake 构建 + 运行全部产物
- Go：`go vet` + 逐个 `go run`
- Java：逐个 `java <file>.java`（单文件模式）
- Rust：`cargo build --examples` + 逐个运行
- Python：逐个 `python3`（需跳过依赖第三方库的进阶专题）
- JavaScript：逐个 `node`
- TypeScript：`npm ci` 后逐个 `npx tsx`
- Shell：逐个 `bash`
- SQL：`sqlite3` 建库后逐个执行 `.sql`

示例失效即红灯，保障仓库不腐烂。

## 6. 现有内容处置与仓库清理

- **不动**：C++ 全部现有文件（仅在 README 标「进阶」并补索引）；Swift / Lua / Assembly / sed 现状保留。
- **清理**：删除已提交的构建产物 `java/out`、`java/.idea`、`swift/.build`、`swift/Calculator.app`、`c/bin`、`c/tmp`；`.gitignore` 补充对应规则与 `.DS_Store`。
- **web/frontend**：保留为前端工程专题；JS/TS 基础语法放顶层新目录 `javascript/`、`typescript/`，与「按语言组织」的顶层结构一致。

## 实施顺序

1. **Phase 0 模板与清理**：定稿 `TOPICS.md`、README 模板；清理构建产物、补 `.gitignore`。
2. **Phase 1 基础设施**：重写根 README（含覆盖矩阵）；搭建按语言触发的 CI 骨架。
3. **Phase 2 补空白语言**：Java → Rust → JavaScript → TypeScript → SQL（每门：示例文件 + README + CI job）。
4. **Phase 3 对齐已有语言**：Python 补基础主题；Go/C/C++ 对照清单补缺主题、README 对齐模板；Shell 补齐。

## 范围外（明确不做）

- 不为 10 门之外的新语言（Kotlin、Ruby、PHP 等）铺目录。
- 不重写 C++ 现有进阶内容，不做教材式练习题体系（方案 C 已否决）。
- 不引入每语言的测试框架（示例以可运行 + 退出码为准）。
