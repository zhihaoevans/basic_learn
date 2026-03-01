# 编程语言基础学习仓库

- 目标：以统一章节结构，逐步构建多语言的“基础语法与核心概念”示例、练习与测试。
- 支持语言（首批）：Python、JavaScript、Go、Rust（后续扩展：Java、C/C++、Shell）。
- 要求：示例与测试本地通过，CI 通过后再推送远程。

## 快速开始
- 查看总体方案：[plan-programming-basics.md](file:///Volumes/DATA/code/learn/basic_learn/.trae/documents/plan-programming-basics.md)
- 目录说明：
  - /languages：各语言代码与测试
  - /scripts：统一运行与工具脚本
  - /docs：通用文档与章节索引
  - /.github/workflows：CI 工作流

## 运行测试（首批）
- Python：
  - 进入仓库根目录，执行：
    ```bash
    python -m unittest discover -s languages/python/tests
    ```
- 统一入口（创建后）：
  ```bash
  bash scripts/run_all_tests.sh
  ```

## 约定
- 涉及 Python 的脚本与文档使用 `python` 命令（不使用 `python3`）。
- 章节目录统一为 ch01-basics、ch02-control、ch03-functions 等。
