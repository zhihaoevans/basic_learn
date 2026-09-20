# SQL 基础语法示例（SQLite 方言）

SQL 是声明式语言：你不描述"怎么一步步算"，只描述"要什么结果"，由数据库的查询优化器决定执行路径。本目录以 SQLite 为载体，按 SQL 自身的范式清单组织（见 [TOPICS.md](../TOPICS.md) 的范式适配一节）：一个主题一个自包含的可运行 `.sql` 文件，全部基于 `seed.sql` 建出的同一份样例库（students / courses / scores 三表）。

- 官方文档：[SQLite 文档首页](https://sqlite.org/docs.html) ｜ [SQL 语法索引](https://sqlite.org/lang.html) ｜ [命令行工具 CLI](https://sqlite.org/cli.html) ｜ [内置函数](https://sqlite.org/lang_corefunc.html)

## 环境要求

- **sqlite3 ≥ 3.35**：示例用到 `RETURNING`（3.35 引入）；窗口函数需 ≥ 3.25、`ON CONFLICT`（UPSERT）需 ≥ 3.24，Ubuntu 22.04+/macOS 12+ 自带或一行命令即满足（本地以 3.45 验证，CI 用 ubuntu-latest 自带版本）
- 安装：macOS `brew install sqlite3`（系统自带版本一般也够）；Ubuntu `sudo apt install sqlite3`；Windows 从 [sqlite.org/download](https://sqlite.org/download.html) 下载命令行工具
- 无需任何第三方依赖：每台机器上的 sqlite3 就能跑全部示例

## 如何运行示例

先在仓库根目录建出样例库（生成 `sql/db.sqlite`，该文件是运行产物，不入库）：

```bash
sqlite3 sql/db.sqlite < sql/seed.sql
```

单条命令运行某个主题：

```bash
sqlite3 sql/db.sqlite < sql/01_select.sql
```

一次性运行全部主题（与 CI 的验证方式相同；05/06 可重复执行，连跑多遍结果一致）：

```bash
for f in sql/[0-9]*.sql; do echo "== $f"; sqlite3 sql/db.sqlite < "$f"; done
```

想恢复数据的初始状态，随时重跑一遍 `seed.sql` 即可（DROP 后重建）。

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 建表与约束（seed） | [seed.sql](seed.sql) | `sqlite3 sql/db.sqlite < sql/seed.sql` | 三表建表：主键/非空/唯一/CHECK/DEFAULT/联合主键/外键 + 样例数据 |
| 01 查询 | [01_select.sql](01_select.sql) | `sqlite3 sql/db.sqlite < sql/01_select.sql` | 投影、WHERE、LIKE 模糊、BETWEEN/IN、NULL 判断、ORDER BY、LIMIT/OFFSET、DISTINCT、字符串与日期函数 |
| 02 聚合 | [02_aggregate.sql](02_aggregate.sql) | `sqlite3 sql/db.sqlite < sql/02_aggregate.sql` | COUNT/SUM/AVG/MAX/MIN、GROUP BY、HAVING 与 WHERE 的分工、CASE WHEN 分支与透视 |
| 03 连接 | [03_join.sql](03_join.sql) | `sqlite3 sql/db.sqlite < sql/03_join.sql` | INNER/LEFT JOIN、三表连接、自连接（组织树）、连接 + 聚合、反连接找"没有成绩"的学生 |
| 04 子查询与 CTE | [04_subquery_cte.sql](04_subquery_cte.sql) | `sqlite3 sql/db.sqlite < sql/04_subquery_cte.sql` | 标量/IN/相关子查询、WITH 与多 CTE、WITH RECURSIVE 递归、UNION/INTERSECT/EXCEPT |
| 05 增删改 | [05_dml.sql](05_dml.sql) | `sqlite3 sql/db.sqlite < sql/05_dml.sql` | INSERT/UPDATE/DELETE、UPSERT（ON CONFLICT DO UPDATE/NOTHING）、RETURNING |
| 06 事务 | [06_transaction.sql](06_transaction.sql) | `sqlite3 sql/db.sqlite < sql/06_transaction.sql` | 自动提交模式、BEGIN/COMMIT 成功路径、ROLLBACK 回滚路径、原子性验证 |
| 07 窗口函数 | [07_window.sql](07_window.sql) | `sqlite3 sql/db.sqlite < sql/07_window.sql` | ROW_NUMBER/RANK/DENSE_RANK 三种口径、PARTITION BY 分区、窗口聚合、取每组第一名 |
| 08 索引与计划 | [08_index_explain.sql](08_index_explain.sql) | `sqlite3 sql/db.sqlite < sql/08_index_explain.sql` | EXPLAIN QUERY PLAN、SCAN→SEARCH 对比、自动索引、覆盖索引、最左前缀 |

## 进阶说明

- 每个示例文件头部注释都标明了主题说明、运行命令与预期结果，适合按编号顺序阅读；示例使用 sqlite3 命令行的点命令（`.headers on` / `.mode column` / `.print`）来让输出带表头、更可读
- 仅 SQLite 方言特性均以【SQLite 方言】标注：如 `RETURNING`、`ON CONFLICT`（UPSERT）、`GLOB`、外键需 `PRAGMA foreign_keys = ON` 才强制、TEXT 存日期的配套函数（`date`/`julianday`）等；换成 MySQL/PostgreSQL 时这些点需要对照调整
- 05/06 的增删改与事务都落在脚本自建、每次重建的演示表上（或整体 ROLLBACK），因此整个目录可以反复连跑，`seed.sql` 重跑即恢复初始数据
- 之后的进阶方向：视图（VIEW）与触发器（TRIGGER）、全文检索 FTS5、JSON 函数（`json_extract`）、生成列、`PRAGMA` 调优（WAL、`analyze`）、以及在各语言中嵌入 SQLite（Python 内置 `sqlite3` 模块、Go 的 `modernc.org/sqlite` 等）
