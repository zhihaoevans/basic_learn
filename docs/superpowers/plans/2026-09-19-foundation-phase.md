# basic_learn 地基改造（Phase 0+1）实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 落地设计文档（docs/superpowers/specs/2026-09-19-multi-language-syntax-repo-design.md）的 Phase 0+1：清理构建产物、定稿主题清单 TOPICS.md、重写根 README（含覆盖矩阵）、为已有可运行语言（Go/C/Shell）添加按路径触发的 CI。

**Architecture:** 本计划是系列计划的第一份（地基），只做仓库级基础设施，不新建任何语言示例。后续计划按「Java → Rust → JavaScript+TypeScript → SQL → 已有语言对齐」逐份编写，每份引用本计划产出的 TOPICS.md 编号约定。CI 采用仓库现有 assemble-x86_64.yml 的模式：每语言一个 workflow、按路径触发、逐个运行示例确认退出码为 0。

**Tech Stack:** git、GitHub Actions、CMake（C）、Go 工具链、bash。

## Global Constraints

- 语言范围固定 10 门：C、C++、Java、Python、Go、Rust、JavaScript、TypeScript、Shell、SQL。
- 主题编号固定 01-15（见 Task 2 的 TOPICS.md），后续所有语言计划必须引用这套编号。
- 新建语言目录用编号前缀（`01_`、`02_`…）；已有语言（Go/C/C++/Shell）保留现有命名，不重命名。
- 每个示例文件必须可独立运行且退出码为 0；文件头注释三要素：主题说明、运行命令、预期输出。
- 提交信息风格沿用仓库惯例：`type(scope): 中文主题` + 空行 + 中文要点列表。
- 不动以下未跟踪的用户 WIP 与本地配置：`c/sanitizers/`、`c/std/Makefile`、`.vscode/c_cpp_properties.json`。
- C++ 的 CI job 不在本计划内：cpp/ 无统一构建入口（无顶层 CMakeLists），其 CI 策略归入后续「已有语言对齐」计划。

---

### Task 1: 清理构建产物与 IDE 文件，补全 .gitignore

**Files:**
- Modify: `.gitignore`
- Delete (git rm): `java/.idea/`（4 个文件）、`java/basic_learn.iml`、`c/tmp/test.c`
- Delete (仅磁盘，未被 git 跟踪): `java/out/`、`swift/.build/`、`swift/Calculator.app`、`c/bin/`、`c/build/`、`c/tmp/`

**Interfaces:**
- Consumes: 无
- Produces: 干净的 git 索引与 .gitignore 规则，后续任务提交不再混入产物

- [ ] **Step 1: 确认当前被跟踪的产物清单**

Run: `git ls-files | grep -E '^java/\.idea/|\.iml$|^c/tmp/|\.DS_Store'`
Expected: 列出 `java/.idea/.gitignore`、`java/.idea/misc.xml`、`java/.idea/modules.xml`、`java/.idea/vcs.xml`、`java/basic_learn.iml`、`c/tmp/test.c` 及 6 个 `.DS_Store`（若与预期不符，以实际输出为准继续）。

- [ ] **Step 2: 从 git 索引移除产物并删除磁盘文件**

```bash
git ls-files | grep '\.DS_Store' | xargs git rm --cached
git rm -r java/.idea
git rm java/basic_learn.iml
git rm c/tmp/test.c
rm -rf java/out swift/.build swift/Calculator.app c/bin c/build c/tmp
```

Expected: 各命令无报错；`git status` 显示上述文件为 deleted（staged）。

- [ ] **Step 3: 补全 .gitignore**

在 `.gitignore` 末尾追加：

```gitignore
# IDE
**/.idea/
*.iml
# Swift / macOS 构建产物
**/.build/
*.app/
# C 临时目录
c/tmp/
```

- [ ] **Step 4: 验证清理结果**

```bash
git ls-files | grep -E '^java/\.idea/|\.iml$|^c/tmp/|\.DS_Store'; echo "exit=$?"
git check-ignore -v swift/.build java/.idea x.app 2>/dev/null | head -3
git status --short
```

Expected: 第一条无输出且 `exit=1`（已无跟踪产物）；`check-ignore` 显示新规则命中；status 中仅剩本任务的 staged 删除与 `.gitignore` 修改（`.vscode/` 与 `c/sanitizers/` 等不在其中）。

- [ ] **Step 5: Commit**

```bash
git add .gitignore
git commit -m "chore: 清理已提交的构建产物与 IDE 配置

- 移除 java/.idea、java/basic_learn.iml、c/tmp、已跟踪的 .DS_Store
- 删除本地未跟踪产物 java/out、swift/.build、swift/Calculator.app、c/bin
- .gitignore 补充 .idea/*.iml/.build/*.app/c/tmp 规则"
```

---

### Task 2: 新增 TOPICS.md（统一主题清单 + README 模板）

**Files:**
- Create: `TOPICS.md`

**Interfaces:**
- Consumes: 无
- Produces: 主题编号 01-15 及各语言适配说明、每语言 README 五段式模板。后续所有语言计划与 README 重写（Task 3、Phase 2/3 各计划）必须按此编号与模板执行。

- [ ] **Step 1: 写入 TOPICS.md 完整内容**

```markdown
# 统一主题清单

每门语言的基础语法部分按同一份主题清单组织：**一个主题一个自包含可运行文件**。
示例文件头注释三要素：主题说明、运行命令、预期输出。

图例：✅ 已覆盖　➖ 语言不适用　— 待补

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
| 15 | generic | 泛型（语言不支持则标 ➖） |
| +  | 特色主题 | 语言独有亮点，如 Go 的 defer/select、Rust 的所有权与生命周期 |

## 范式适配

- **Shell**：取适用子集（02/03/04/05/06/07/08/10/11），oop/generic 标 ➖。
- **SQL**：改为自身范式清单——建表与约束、增删改查、聚合与分组、连接、子查询与 CTE、事务、窗口函数、索引与执行计划入门。

## 每语言 README 五段式模板

1. 一句语言简介 + 官方文档链接
2. 环境要求（最低版本）与安装提示
3. 如何运行示例（一条命令）
4. 主题索引表：主题 | 示例文件 | 运行命令 | 一句话说明
5. 进阶专题链接（仓库内已有的专题目录归入此段，不删除）
```

- [ ] **Step 2: 验证**

Run: `head -30 TOPICS.md && git status --short TOPICS.md`
Expected: 内容完整显示，文件为新增未跟踪状态。

- [ ] **Step 3: Commit**

```bash
git add TOPICS.md
git commit -m "docs: 新增统一主题清单 TOPICS.md

- 基础语法 15 题编号 01-15，另设语言特色主题
- Shell/SQL 范式适配说明
- 每语言 README 五段式模板"
```

---

### Task 3: 重写根 README（定位 + 覆盖矩阵）

**Files:**
- Modify: `README.md`（全文替换）

**Interfaces:**
- Consumes: TOPICS.md 的主题编号（Task 2）
- Produces: 覆盖矩阵。后续语言计划完成时必须同步更新矩阵对应单元格。

- [ ] **Step 1: 用以下完整内容替换 README.md**

```markdown
# basic_learn

常用编程语言基础语法示例集合，面向教学分享：每门语言按统一主题清单组织，一个主题一个可运行示例，CI 保障所有示例可构建、可运行、不腐烂。

- 主题清单见 [TOPICS.md](TOPICS.md)
- 每个示例文件头注释包含：主题说明、运行命令、预期输出
- 想贡献新示例？按 TOPICS.md 的主题编号放入对应语言目录，CI 会自动验证

## 语言目录与状态

| 语言 | 目录 | 基础语法状态 | CI |
|---|---|---|---|
| C | [c](c/README.md) | 🚧 部分主题 | ✅ |
| C++ | [cpp](cpp/README.md) | 🚧 进阶丰富，基础待对齐 | — |
| Go | [golang](golang/README.md) | 🚧 部分主题 | ✅ |
| Java | [java](java/README.md) | ❌ 待建 | — |
| Python | [python](python/README.md) | ❌ 基础待建（专题已有） | — |
| Rust | [rust](rust/README.md) | ❌ 待建 | — |
| JavaScript | javascript/ | ❌ 待建 | — |
| TypeScript | typescript/ | ❌ 待建 | — |
| Shell | [scripts/shell](scripts/shell/README.md) | 🚧 部分主题 | ✅ |
| SQL | sql/ | ❌ 待建 | — |

## 主题覆盖矩阵

图例：✅ 已覆盖　➖ 不适用　— 待补（清单定义见 [TOPICS.md](TOPICS.md)）

| 语言 | 01 hello | 02 variable | 03 operator | 04 string | 05 control | 06 function | 07 collection | 08 map | 09 oop | 10 error | 11 file_io | 12 module | 13 stdlib | 14 concurrency | 15 generic | 特色 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| C | ✅ | — | — | ✅ | — | — | ✅ | — | — | — | — | — | ✅ | — | ➖ | — |
| C++ | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — |
| Go | ✅ | ✅ | — | — | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | — | ✅ | — | ✅ | — | ✅ |
| Java | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — |
| Python | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — |
| Rust | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — |
| JavaScript | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — |
| TypeScript | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — |
| Shell | — | ✅ | ✅ | ✅ | ✅ | — | ✅ | ✅ | ➖ | — | — | — | — | — | ➖ | — |
| SQL | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — | — |

> 矩阵为手动维护：完成一个主题就更新对应单元格；SQL 行在落地时替换为其范式清单。

## 其他语言与工具示例

- [assembly](assembly/README.md) - 汇编语言示例
- [swift](swift) - Swift 示例项目
- [lua](lua/learnlua.lua) - Lua 示例
- [scripts/sed](scripts/sed/README.md) - sed 示例
- [build_systems/makefile](build_systems/makefile/README.md) - Makefile 模板
- [c/preprocessor](c/preprocessor/README.md) - C 宏示例
- [cpp/protobuf](cpp/protobuf/README.md) - Protobuf 示例

## 文档与图示

- [docs/markdown](docs/markdown) - Markdown 示例
- [docs/drawio](docs/drawio) - Drawio 绘图
- [docs/plantuml](docs/plantuml) - PlantUML 图示
- [docs/mermaid](docs/mermaid) - Mermaid 图示
- [docs/gdb](docs/gdb) - GDB 学习与笔记
- [docs/intel](docs/intel) - Intel 架构相关资料

## Web

- [web/frontend](web/frontend) - 前端示例与练习（Vue3 工程）
```

- [ ] **Step 2: 验证所有相对链接可达**

```bash
grep -oE '\]\(([^)h][^)]*)\)' README.md | sed 's/](\(.*\))/\1/' | while read -r p; do
  [ -e "$p" ] || echo "BROKEN: $p"
done; echo "link check done"
```

Expected: 只输出 `link check done`，无 BROKEN。`javascript`、`typescript`、`sql` 三行在状态表中刻意用纯文本（目录尚未创建），Phase 2 各语言落地时再改为链接。若链接检查输出其他 BROKEN，修正后重跑。

- [ ] **Step 3: Commit**

```bash
git add README.md
git commit -m "docs: 重写根 README 为教学仓库门面

- 新增语言状态表与主题覆盖矩阵（10 门 × 15 题）
- 保留其他语言、文档图示、Web 分区索引
- 矩阵图例与 TOPICS.md 对齐"
```

---

### Task 4: CI workflow — golang

**Files:**
- Create: `.github/workflows/golang.yml`

**Interfaces:**
- Consumes: 仓库现有 assemble-x86_64.yml 的按路径触发模式
- Produces: `golang` workflow。Phase 3 对齐 Go 缺失主题时本 job 自动覆盖新文件（`golang/**` 路径触发，无需改 workflow）。

- [ ] **Step 1: 写入 workflow 文件**

```yaml
name: golang

on:
  push:
    paths:
      - 'golang/**'
      - '.github/workflows/golang.yml'
  pull_request:
    paths:
      - 'golang/**'
      - '.github/workflows/golang.yml'
  workflow_dispatch:

jobs:
  verify:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Show Go version
        run: go version

      - name: Vet and run every example
        run: |
          cd golang
          for f in *.go; do
            echo "== $f =="
            go vet "$f"
            go run "$f"
          done
```

- [ ] **Step 2: 本地预演 CI 脚本逻辑**

```bash
cd golang && for f in *.go; do go vet "$f" && go run "$f" >/dev/null || echo "FAIL: $f"; done; echo done
```

Expected: 仅输出 `done`，无 FAIL（2026-09-19 已验证 21 个文件全部通过；执行时若出现 FAIL，先修复示例再提交）。

- [ ] **Step 3: YAML 语法检查**

```bash
ruby -ryaml -e 'YAML.load_file(".github/workflows/golang.yml"); puts "yaml ok"'
```

Expected: `yaml ok`

- [ ] **Step 4: Commit**

```bash
git add .github/workflows/golang.yml
git commit -m "ci: 新增 golang 基础语法验证

- 按路径触发，逐文件 go vet + go run
- 沿用 assemble-x86_64 的触发模式"
```

---

### Task 5: CI workflow — c（CMake 构建 + 运行）

**Files:**
- Create: `.github/workflows/c.yml`

**Interfaces:**
- Consumes: `c/CMakeLists.txt` 现有构建（排除 gcc/preprocessor 子目录）
- Produces: `c` workflow。产物输出至 `c/build/bin`（由 CMakeLists 的 `BIN_DIR` 决定）。

- [ ] **Step 1: 写入 workflow 文件**

```yaml
name: c

on:
  push:
    paths:
      - 'c/**'
      - '.github/workflows/c.yml'
  pull_request:
    paths:
      - 'c/**'
      - '.github/workflows/c.yml'
  workflow_dispatch:

jobs:
  verify:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Configure
        run: cmake -S c -B c/build

      - name: Build
        run: cmake --build c/build

      - name: Run every example
        run: |
          for b in c/build/bin/*; do
            echo "== $b =="
            "$b"
          done
```

- [ ] **Step 2: 本地预演 CI 脚本逻辑**

```bash
cmake -S c -B c/build >/dev/null && cmake --build c/build >/dev/null 2>&1 && \
for b in c/build/bin/*; do "$b" >/dev/null 2>&1 || echo "NONZERO: $b"; done; echo done
```

Expected: 仅输出 `done`（2026-09-19 已验证 19 个产物全部退出码 0）。注意：`c/sanitizers/` 是用户未跟踪的 WIP，若其并入构建且含故意崩溃的示例，需在 Run 步骤加显式排除清单——本计划不处理。

- [ ] **Step 3: YAML 语法检查**

```bash
ruby -ryaml -e 'YAML.load_file(".github/workflows/c.yml"); puts "yaml ok"'
```

Expected: `yaml ok`

- [ ] **Step 4: Commit**

```bash
git add .github/workflows/c.yml
git commit -m "ci: 新增 c 基础语法验证

- CMake 构建 c/ 全部示例并逐个运行
- gcc/preprocessor 子目录沿用现有 CMake 排除规则"
```

---

### Task 6: CI workflow — shell

**Files:**
- Create: `.github/workflows/shell.yml`

**Interfaces:**
- Consumes: `scripts/shell/` 现有脚本
- Produces: `shell` workflow。Phase 3 补齐 Shell 主题时自动覆盖（`scripts/shell/**` 触发）。

- [ ] **Step 1: 写入 workflow 文件**

```yaml
name: shell

on:
  push:
    paths:
      - 'scripts/shell/**'
      - '.github/workflows/shell.yml'
  pull_request:
    paths:
      - 'scripts/shell/**'
      - '.github/workflows/shell.yml'
  workflow_dispatch:

jobs:
  verify:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Run every script
        run: |
          find scripts/shell -name '*.sh' | sort | while read -r f; do
            echo "== $f =="
            bash "$f"
          done
```

- [ ] **Step 2: 本地预演 CI 脚本逻辑**

```bash
find scripts/shell -name '*.sh' | sort | while read -r f; do bash "$f" >/dev/null 2>&1 || echo "FAIL: $f"; done; echo done
```

Expected: 仅输出 `done`（2026-09-19 已验证 13 个脚本全部退出码 0）。

- [ ] **Step 3: YAML 语法检查**

```bash
ruby -ryaml -e 'YAML.load_file(".github/workflows/shell.yml"); puts "yaml ok"'
```

Expected: `yaml ok`

- [ ] **Step 4: Commit**

```bash
git add .github/workflows/shell.yml
git commit -m "ci: 新增 shell 基础语法验证

- 按路径触发，逐脚本 bash 运行确认退出码 0"
```

---

### Task 7: 推送并确认 CI 绿灯（需用户确认推送）

**Files:**
- 无新文件

**Interfaces:**
- Consumes: Task 1-6 的全部提交
- Produces: GitHub 上 golang/c/shell/assemble-x86_64 四个 workflow 全绿的地基仓库

- [ ] **Step 1: 确认提交序列完整**

Run: `git log --oneline -7 && git status --short`
Expected: 7 个新提交（1 个设计文档 + Task 1-6 各 1 个）；工作区除用户 WIP（c/sanitizers、.vscode）外干净。

- [ ] **Step 2: 征得用户同意后推送**

推送属对外动作，执行前向用户确认：

```bash
git push origin main
```

- [ ] **Step 3: 确认 CI 结果**

Run: `gh run list --limit 5`（或访问仓库 Actions 页）
Expected: golang、c、shell 三个 workflow 均为 success（push 同时改动多语言目录时多个 workflow 并行触发）。若有红灯，读 `gh run view <id> --log-failed` 修复后追加提交再推。

---

## 后续计划（不在本计划内）

按设计文档实施顺序，本计划落地后逐份编写：

1. Java 基础语法（Phase 2，一主题一目录 + JDK 11+ 单文件运行 + java.yml）
2. Rust 基础语法（Phase 2，Cargo 工程 examples/ + rust.yml）
3. JavaScript + TypeScript 基础语法（Phase 2，javascript/ 平铺 + typescript/ npm+tsx + 各自 workflow）
4. SQL 基础语法（Phase 2，sql/ + sqlite3 + sql.yml）
5. 已有语言对齐（Phase 3：Python 补基础、Go/C/C++/Shell 对照清单补缺、各 README 对齐五段式、cpp CI 策略）
