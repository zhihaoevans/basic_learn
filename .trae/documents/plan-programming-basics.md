# 编程语言基础学习仓库整体方案（Plan）

## 目标与范围
- 构建一个可持续扩展的多语言“基础语法与核心概念”学习仓库
- 每个语言按统一章节目录组织：示例代码、习题、测试、讲解文档
- 本地与 CI 测试均需通过后再推送远程仓库
- 执行脚本中涉及 Python 时统一使用 `python` 命令

## 仓库总体结构（顶层）
- README.md：项目介绍与使用指南
- /languages/<lang>：各语言根目录（lang 例：python、javascript、go、rust、java、c、cpp、shell）
- /scripts：统一脚本（运行全部测试、格式化、初始化）
- /docs：通用文档（章节索引、学习路线）
- /.github/workflows：GitHub Actions 流水线
- /tools：辅助工具（如代码检查配置模板等）

## 章节清单（统一模板）
- ch01-basics：变量、基本类型、表达式与语句
- ch02-control：条件、循环、跳转
- ch03-functions：函数/方法、参数、返回值、作用域
- ch04-ds：常用数据结构（数组/列表、字典/映射、集合、字符串）
- ch05-io：文件与标准 I/O、简单网络 I/O（按语言能力取舍）
- ch06-error：错误/异常处理、断言
- ch07-oop-generics：面向对象/泛型与类型系统（按语言能力取舍）
- ch08-concurrency：并发/协程/线程（按语言能力取舍）
- ch09-modules：模块/包管理与依赖
- ch10-testing：测试约定与示例

## 每个语言的目录模板
```
/languages/<lang>/
  README.md
  src/
    ch01-basics/
    ch02-control/
    ...
  tests/
    ch01-basics/
    ch02-control/
    ...
  docs/
    overview.md
```
- 示例代码与测试按章节对应，测试必须覆盖示例的关键点

## 语言与测试框架映射（初始建议）
- Python：pytest；格式化 black/ruff（后续可选）
- JavaScript：vitest（或 jest）；格式化 eslint/prettier
- Go：内置 testing；格式化 gofmt/golangci-lint（后续可选）
- Rust：cargo test；格式化 rustfmt/clippy（后续可选）
- Java：JUnit（后续里程碑）；格式化 google-java-format（后续可选）
- C/C++：CMake + CTest 或 Unity/CppUTest（后续里程碑）
- Shell：bats-core（后续里程碑）

## 脚本与统一入口
- /scripts/run_all_tests.sh：串行/并行运行各语言测试
  - 调用 python 相关脚本时使用 `python`
- /scripts/format_all.sh：统一执行各语言格式化（按需）
- /scripts/init_lang.sh <lang>：生成语言骨架与首章示例

## CI/CD 流水线方案
- GitHub Actions 工作流：`/.github/workflows/learn.yml`
  - 触发：push、pull_request
  - 矩阵或分阶段运行：python、javascript、go、rust（首批）
  - 步骤：检出 → 安装依赖 → 运行各语言测试 → 汇总结果
- 要求：所有 Job 通过才允许合并与推送

## 提交与版本策略
- 提交流程（本地）：
  1) 编写示例与测试
  2) 本地运行 `/scripts/run_all_tests.sh`，全部通过
  3) 更新章节文档与 README
  4) 提交变更并推送远程（CI 通过）
- 分支策略：main（稳定）+ feature/<lang>-<chapter>
- 版本节点：完成一个语言的一个章节即打 Tag（如 v-python-ch01）

## 首轮实施里程碑（迭代 0 → 迭代 2）
- 迭代 0：基础骨架
  - 建立顶层目录与通用 README
  - 初始化 /languages/python、/languages/javascript、/languages/go、/languages/rust
  - 创建 /scripts/run_all_tests.sh（含 python 调用）
  - 基础 learn.yml 工作流跑通“空项目”或最小用例
- 迭代 1：ch01-basics
  - 为四种语言实现 ch01-basics 示例与对应测试
  - 本地与 CI 均通过
- 迭代 2：ch02-control
  - 四种语言实现控制流示例与测试
  - 完善文档、格式化与静态检查（按需开启）

## 验收标准
- 本地与 CI 测试全部通过（含脚本统一入口）
- 章节文档可读、示例与测试一一对应
- 目录规范统一、可复用模板清晰
- 推送远程后工作流绿灯

## 风险与权衡
- 依赖与工具链差异：优先选择官方/主流工具，尽量最小化初始依赖
- 并发与 I/O 章节按语言特性逐步深化，先覆盖基础可验证内容
- C/C++、Java、Shell 等放在后续里程碑，避免首期复杂度过高

## 下一步（待实施）
- 创建脚本与四种语言骨架
- 配置最小 CI 以验证结构
- 编写 ch01-basics 示例与测试并通过
