# Phase 2：五门语言基础语法示例实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为 Java、Rust、JavaScript、TypeScript、SQL 五门语言按 TOPICS.md 统一主题清单落地基础语法示例，每主题一个自包含可运行文件，各自 README 对齐五段式模板，根 README 矩阵同步更新。

**Architecture:** 每门语言一个任务（独立可交付），收尾任务扩展两个既有 workflow 并做全量验证。CI 已就位：java/golang 无需改动即覆盖新文件；javascript.yml、typescript.yml、sql.yml 已预置对应目录的运行逻辑；rust.yml 需增加 examples 运行步骤。

**Tech Stack:** JDK 21（单文件直运行）、Cargo（examples 约定）、Node 20+ ESM、tsx（TypeScript 直运行）、SQLite 3。

## Global Constraints（对所有任务生效）

- 主题与编号严格按 [TOPICS.md](../../TOPICS.md)：01 hello / 02 variable / 03 operator / 04 string / 05 control / 06 function / 07 collection / 08 map / 09 oop / 10 error / 11 file_io / 12 module / 13 stdlib / 14 concurrency / 15 generic（语言不支持标 ➖）/ + 特色主题。
- 每个示例文件头注释三要素：**主题说明（1-2 句）、运行命令、预期输出（关键行）**；注释用中文。
- 每个示例必须独立运行且**退出码 0**；输出用 print 系列展示每个知识点的结果。
- 编号前缀命名（`01_hello`、`02_variable`…）；文件名语言内统一风格。
- 不引入第三方依赖（TypeScript 的 tsx 运行器除外）。
- 每语言 README 按 TOPICS.md 五段式模板重写/新建：简介+官方文档链接 / 环境要求（最低版本）/ 如何运行（一条命令）/ 主题索引表（主题|文件|运行命令|一句话说明）/ 进阶专题链接。
- 完成一个语言后更新根 README.md：语言状态表该行状态改为 ✅ 完整，主题矩阵该行按实际覆盖填 ✅/➖。
- 提交信息：`type(scope): 中文主题`；每任务至少一个提交，示例+README+矩阵行一起提交。
- 示例是教学向：代码优先清晰直白，一个知识点一段、配输出；避免炫技。

---

### Task 1: Java 基础语法（15 题 + 特色）

**Files:**
- Create: `java/01_hello/Hello.java` ~ `java/15_generic/GenericDemo.java`（15 个目录各一个主类文件）+ `java/16_records/RecordsDemo.java`（特色）
- Modify: `java/README.md`（五段式重写）、根 `README.md`（Java 行）
- 既有 `java/HelloWorld.java`、`java/test.java` 保留不动（README 进阶段说明），或移入 `java/legacy/`（择一，实施者定，README 说明即可）

**命名与类名对照：** 01_hello/Hello、02_variable/VariableDemo、03_operator/OperatorDemo、04_string/StringDemo、05_control/ControlFlowDemo、06_function/FunctionDemo、07_collection/CollectionDemo、08_map/MapDemo、09_oop/OopDemo、10_error/ErrorDemo、11_file_io/FileIoDemo、12_module/ModuleDemo、13_stdlib/StdlibDemo、14_concurrency/ConcurrencyDemo、15_generic/GenericDemo、16_records/RecordsDemo

**各文件必须演示的知识点：**
- 01：System.out.println、单行/多行/Javadoc 注释
- 02：var 局部推断、8 种基本类型、String、final 常量、类型转换（隐式+显式 cast）
- 03：算术（含整数除法、%）、自增前后缀、比较、逻辑短路、位运算、三元
- 04：拼接、length/charAt/substring/indexOf/equals vs ==、StringBuilder、String.format、转文本块（"""）
- 05：if/else、switch（传统+箭头语法）、for、增强 for、while、do-while、break/continue、带标签循环
- 06：方法定义与重载、可变参数、返回值、Lambda（函数式接口 Function/Predicate）、方法引用
- 07：数组声明/遍历/Arrays 工具、ArrayList、LinkedList、HashSet、遍历方式对比
- 08：HashMap 增删改查遍历、getOrDefault、TreeMap 排序、LinkedHashMap 顺序
- 09：class/字段/构造器/this、getter/setter、继承 super/@Override、抽象类、接口 default 方法、多态、instanceof 模式匹配
- 10：try/catch/finally、多 catch、异常层级、throw/throws、自定义异常、try-with-resources
- 11：Files.writeString/readString（写读临时文件）、BufferedReader 逐行、File 遍历目录；临时文件用 Files.createTempFile 并清理
- 12：包声明+跨类访问（本目录两个文件：ModuleDemo.java + 同包工具类 Util.java 演示 public/private/protected）、import 静态导入；说明单文件运行约束
- 13：Optional、Arrays.asList/sort/stream 简用、LocalDate/LocalDateTime、Objects 工具、String.join
- 14：Thread 创建两种方式、ExecutorService+Future、synchronized 计数器对比、join
- 15：泛型方法 <T>、泛型类 Box<T>、有界类型参数 <T extends Comparable>、通配符简述
- 16（特色）：record 定义与解构、紧凑构造器、switch 表达式模式匹配（JDK 21）

**验证：** `find java -name '*.java' -exec java {} \;` 全部退出 0（12_module 双文件用 `java java/12_module/ModuleDemo.java`——单文件模式只跑入口文件）。

### Task 2: Rust 基础语法（15 题 + 特色）

**Files:**
- Create: `rust/Cargo.toml`（package `rust_basics`，无 lib，bin 仅 examples 用）+ `rust/examples/01_hello.rs` ~ `rust/examples/15_generic.rs` + `rust/examples/16_ownership.rs`（特色）
- Keep: `rust/hello_world/`（既有包）、`rust/main.rs`（rust.yml 仍单独 rustc 运行）
- Modify: `rust/README.md`、根 `README.md`（Rust 行）

**知识点：**
- 01：println!、变量插值 {} 与 {:?}、注释
- 02：let/let mut、shadowing、基本类型（i32/u8/f64/bool/char/usize）、const、as 转换
- 03：算术（含溢出语义说明）、比较、逻辑、位运算、范围
- 04：&str vs String、拼接 format!/push_str、len/切片/chars、split/trim/replace、遍历字节 vs 字符
- 05：if 表达式（赋值）、loop/break 值、while、for-in range/迭代器、match 基础
- 06：fn、参数/返回、多返回值元组、闭包三种写法、迭代器链（map/filter/collect）
- 07：数组 [T; N]、Vec 增删/迭代、切片 &[]
- 08：HashMap entry API、get、遍历、BTreeMap 有序
- 09：struct、impl 方法/关联函数、枚举带数据、trait 定义与实现、trait bound、derive(Debug/PartialEq)
- 10：Result/Option、? 运算符、match 错误分支、unwrap/expect 使用场景说明、panic! 说明
- 11：fs::write/read_to_string、逐行读 BufReader、临时文件（tempfile 不引入——用固定 std::env::temp_dir().join() 路径并清理）
- 12：mod 声明与 use、pub 可见性、模块内函数组织（单文件内 mod 块，说明多文件等价写法）
- 13：std 常用速览：collections/iter/str 方法链、Duration/Instant 计时、env::args、process::exit 说明
- 14：thread::spawn/join、channel mpsc、Arc<Mutex> 共享计数
- 15：泛型函数/结构体、trait bound、impl Trait 返回
- 16（特色）：所有权转移/借用/&mut 规则、生命周期标注一例、Copy vs Move

**验证：** `cargo run -q --example 01_hello` … 逐个 examples 运行退出 0；`cargo build -q` 无 warning（示例内允许少量必要的 allow 注解）。

### Task 3: JavaScript 基础语法（15 题 + 特色，15 generic ➖）

**Files:**
- Create: `javascript/package.json`（仅 `{"type":"module"}` + name/private）+ `javascript/01_hello.js` ~ `javascript/14_concurrency.js` + `javascript/15_destructuring.js`（特色：解构与展开）
- Create: `javascript/README.md`；Modify: 根 `README.md`（JavaScript 行 → ✅，15 generic 标 ➖）

**知识点：**
- 01：console.log、模板字符串、注释、node 运行方式
- 02：let/const/var 区别、动态类型、typeof、基本类型与引用类型
- 03：算术（含 0.1+0.2 精度）、比较 == vs ===、逻辑与短路、?? 与 ?.、位运算
- 04：字符串方法（slice/replaceAll/includes/padStart/split/join）、模板多行、编码 charCodeAt
- 05：if/switch（含 fallthrough 说明）、for/for-of/for-in 区别、while、break/continue、标签
- 06：函数声明/表达式/箭头函数、默认参数/剩余参数、闭包计数器、回调、高阶函数
- 07：数组方法（map/filter/reduce/find/some/every/sort/slice/splice）、Set、解构遍历
- 08：Map vs 普通对象、set/get/has/size、遍历 for-of entries、Object.keys/values/entries
- 09：class/constructor/extends/super、静态方法、私有字段 #、getter/setter、instanceof
- 10：Error 子类型、throw/try/catch/finally、自定义 Error 类、异步错误 catch
- 11：fs/promises writeFile/readFile/appendFile、同步版对比、逐行读取（readline/promises）
- 12：ESM export/import（本目录两个文件：12_module.js + lib/math_utils.js 命名/默认导出双演示）
- 13：内置常用：JSON 处理、Math、Date/Intl、URL、structuredClone
- 14：Promise 链、async/await、Promise.all/allSettled、串行 vs 并行计时演示
- 15（特色）：对象/数组解构、默认值、换名、展开与收集、函数参数解构

**验证：** `for f in javascript/*.js; do node "$f"; done` 全部退出 0（临时文件写到 os.tmpdir 并清理）。

### Task 4: TypeScript 基础语法（15 题 + 特色，含 generic）

**Files:**
- Create: `typescript/package.json`（tsx 依赖）+ `typescript/tsconfig.json`（strict）+ `typescript/package-lock.json`（npm install 生成）
- Create: `typescript/src/01_hello.ts` ~ `typescript/src/15_generic.ts` + `typescript/src/16_type_utils.ts`（特色：类型工具与联合类型）
- Create: `typescript/README.md`；Modify: 根 `README.md`（TypeScript 行 → ✅）

**知识点：** 与 JavaScript 任务同构（01-14），差异点：
- 02：类型标注、类型推断、any/unknown/never、类型收窄（typeof/instanceof）
- 04：字符串字面量类型、模板字面量类型一例
- 05：可辨识联合 + switch never 穷尽检查
- 06：函数类型签名、可选/默认参数、重载
- 07：泛型数组 readonly、元组、Array<T> 方法
- 08：Record/索引签名、Partial 应用一例
- 09：implements 接口、抽象类、访问修饰符 public/private/protected、readonly
- 10：自定义错误类、unknown 收窄、类型守卫 is
- 11：fs/promises 泛型返回标注
- 12：export/import 类型与值、type-only import（import type）
- 13：内置工具类型速览（Partial/Pick/Omit/Readonly/Record）基础用法并入 13 或 16
- 15：泛型函数/接口/约束 extends、泛型默认值
- 16（特色）：联合/交叉类型、字面量联合、Pick/Omit/Record 实战、as const

**验证：** `cd typescript && npm install`；`npx tsc --noEmit`（严格检查通过）；`for f in src/*.ts; do npx tsx "$f"; done` 全部退出 0。typescript.yml 已预置 `npm ci`+tsx 逻辑，lock 文件入册即生效。

### Task 5: SQL 基础语法（SQLite，8 个范式主题）

**Files:**
- Create: `sql/seed.sql`（建库脚本：students/courses/scores 三表+约束+样例数据，幂等 DROP TABLE IF EXISTS）
- Create: `sql/01_select.sql`、`sql/02_aggregate.sql`、`sql/03_join.sql`、`sql/04_subquery_cte.sql`、`sql/05_dml.sql`、`sql/06_transaction.sql`、`sql/07_window.sql`、`sql/08_index_explain.sql`
- Create: `sql/README.md`；Modify: 根 `README.md`（SQL 行 → ✅，矩阵 SQL 行替换为范式清单列）

**各文件要点：** 01 WHERE/ORDER BY/LIMIT/DISTINCT/模糊与范围；02 COUNT/SUM/AVG/MAX/MIN/GROUP BY+HAVING；03 INNER/LEFT/自连接/多表；04 标量与 IN 子查询、WITH CTE、递归 CTE 一例；05 INSERT/UPDATE/DELETE/UPSERT(ON CONFLICT)/RETURNING；06 BEGIN/COMMIT/ROLLBACK 演示（成功提交+失败回滚各一段，SELECT 验证）；07 ROW_NUMBER/RANK/OVER(PARTITION BY)；08 CREATE INDEX 前后 EXPLAIN QUERY PLAN 对比。
每个 .sql 头部注释含主题说明+运行命令+预期结果描述；文件末尾 SELECT 展示结果。

**验证：** `rm -f sql/db.sqlite && sqlite3 sql/db.sqlite < sql/seed.sql && for f in sql/[0-9]*.sql; do sqlite3 sql/db.sqlite < "$f" || echo "FAIL: $f"; done` 全部退出 0；05/06 的增删改在 db 上可重复执行（脚本自身保证幂等或使用事务回滚）。

### Task 6: 收尾——CI 扩展与全量验证

**Files:**
- Modify: `.github/workflows/rust.yml`（增加逐 example 运行步骤）
- Modify: `.github/workflows/javascript.yml`（增加运行 javascript/*.js 基础示例步骤）
- 复核根 README 全部行与矩阵

**rust.yml 新增步骤**（置于 Test languages/rust 之后）：
```yaml
      - name: Run rust/examples basics
        run: |
          for ex in rust/examples/*.rs; do
            name=$(basename "$ex" .rs)
            echo "== $name =="
            cargo run -q --manifest-path rust/Cargo.toml --example "$name"
          done
```
**javascript.yml 新增步骤**（置于 node --test 之后）：
```yaml
      - name: Run javascript basics examples
        run: |
          for f in javascript/*.js; do
            echo "== $f =="
            node "$f"
          done
```

**验证：** 本地重放两个新步骤的循环体；全部 workflow YAML `ruby -ryaml` 解析通过；根 README 相对链接检查脚本通过。

### 收尾（控制器执行）

1. 整体分支审查（requesting-code-review 模板 + 全部任务 Minor 清单）
2. 修复 Important+ 发现
3. 合回 main（--no-ff）并推送
4. `gh run list` 确认触发的工作流全绿
