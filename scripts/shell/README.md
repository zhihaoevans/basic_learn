# Shell 脚本示例

Shell（本目录以 Bash 方言为准）是 Unix 世界最常用的命令行解释语言，擅长粘合命令、批量处理与自动化。本目录按 [TOPICS.md](../../TOPICS.md) 的统一主题清单组织基础语法示例：一个主题一个自包含可运行文件，每个文件头注释含主题说明、运行命令与预期输出。

- 权威参考：[GNU Bash 官方手册](https://www.gnu.org/software/bash/manual/)
- 进阶阅读：[Bash FAQ（greg's wiki）](https://mywiki.wooledge.org/BashFAQ)、[ShellCheck  lint 工具](https://www.shellcheck.net/)

## 环境要求

- **Bash 4+**（`bash --version` 查看；`variable/dict_var.sh` 的关联数组 `declare -A` 需要 4+）
- macOS 自带的 `/bin/bash` 为 3.2：本目录其余示例均兼容 3.2，关联数组示例请 `brew install bash` 后用新版运行
- Linux 发行版自带版本一般满足要求

## 如何运行

在仓库根目录执行（所有示例不依赖工作目录，随处可跑）：

```bash
bash scripts/shell/hello/hello.sh          # 运行任意示例
# CI 同款全量门禁：逐个运行全部脚本，退出码非 0 即 FAIL
find scripts/shell -name '*.sh' | sort | while read -r f; do bash "$f" >/dev/null 2>&1 || echo "FAIL: $f"; done
```

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [hello/hello.sh](hello/hello.sh) | `bash scripts/shell/hello/hello.sh` | shebang、echo vs printf、注释、三种运行方式 |
| 02 variable | [variable/parameter.sh](variable/parameter.sh) | `bash scripts/shell/variable/parameter.sh` | 变量赋值与位置参数（另有 string_var/array_var/dict_var） |
| 03 operator | [operator/digit_op.sh](operator/digit_op.sh) | `bash scripts/shell/operator/digit_op.sh` | 算术/逻辑/字符串运算（digit_op、logic_op、string_op） |
| 04 string | [variable/string_var.sh](variable/string_var.sh) | `bash scripts/shell/variable/string_var.sh` | 字符串长度、子串截取 |
| 05 control | [proc_ctrl/for_loop.sh](proc_ctrl/for_loop.sh) | `bash scripts/shell/proc_ctrl/for_loop.sh` | for/while 循环与分支（proc_ctrl 目录） |
| 06 function | [function/function_basics.sh](function/function_basics.sh) | `bash scripts/shell/function/function_basics.sh` | 函数定义、位置参数、local、return vs echo 两条返回通道 |
| 07 collection | [variable/array_var.sh](variable/array_var.sh) | `bash scripts/shell/variable/array_var.sh` | 数组声明、遍历、长度 |
| 08 map | [variable/dict_var.sh](variable/dict_var.sh) | `bash scripts/shell/variable/dict_var.sh` | 关联数组 declare -A（需 bash 4+） |
| 09 oop | — | — | ➖ Shell 无类/继承等面向对象机制（靠函数+命名约定模拟，见 module/） |
| 10 error | [error/error_handling.sh](error/error_handling.sh) | `bash scripts/shell/error/error_handling.sh` | 退出码约定、2>/dev/null、&#124;&#124; 兜底、trap ERR、set -e 说明 |
| 11 file_io | [file_io/file_io.sh](file_io/file_io.sh) | `bash scripts/shell/file_io/file_io.sh` | > 覆盖/>> 追加、here-doc、read 逐行、/dev/null |
| 12 module | [module/module_source.sh](module/module_source.sh)（+ sourced.sh） | `bash scripts/shell/module/module_source.sh` | source vs 直接执行、模块提供函数、(…) 隔离、export 可见性 |
| 13 stdlib | [stdlib/builtin_tour.sh](stdlib/builtin_tour.sh) | `bash scripts/shell/stdlib/builtin_tour.sh` | test 与 [[ ]]、参数扩展默认值、pushd/popd、getopts |
| 14 concurrency | [concurrency/background_wait.sh](concurrency/background_wait.sh) | `bash scripts/shell/concurrency/background_wait.sh` | & 后台、wait 收割退出码、jobs、管道并行 |
| 15 generic | — | — | ➖ Shell 无泛型概念 |
| + 特色 | [test_file/test_file.sh](test_file/test_file.sh) | `bash scripts/shell/test_file/test_file.sh` | 文件测试内建（-e/-f/-d/-r 等判定） |

> 目录内另有早期示例：`test.sh`（入门综合脚本），以及 `variable/`、`operator/`、`proc_ctrl/` 下的多个补充文件，均随 CI 门禁一起运行。

## 进阶专题

- [../sed/](../sed/README.md) —— sed 流编辑器专题：与管道、正则配合做文本处理，是 Shell 文本流水线的进阶形态
