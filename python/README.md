# Python 基础语法示例

Python 是一门动态强类型的解释型语言，以语法简洁、生态丰富著称，广泛用于脚本、数据处理、Web 与 AI。本目录按 [TOPICS.md](../TOPICS.md) 的统一主题清单组织：一个主题一个自包含的可运行示例（`NN_*.py`），用 `print` 逐个知识点演示结果。

- 官方文档：[Python 官方教程（中文）](https://docs.python.org/zh-cn/3/tutorial/) ｜ [标准库参考](https://docs.python.org/zh-cn/3/library/index.html)

## 环境要求

- **Python 3.10+**（本系列使用 match-case 结构化匹配与 `X | Y` 类型标注，均为 3.10 起可用；本地 3.13、CI 取最新 3.x 均可）
- 安装：macOS/Linux 一般自带 `python3`，`python3 --version` 确认版本；也可用 [uv](https://docs.astral.sh/uv/) 或 [pyenv](https://github.com/pyenv/pyenv) 管理多版本
- 全部示例仅用标准库，无需安装任何第三方依赖

## 如何运行

在仓库根目录执行（与 CI 的验证方式相同）：

```bash
python3 python/01_hello.py
```

一次性运行全部基础示例：

```bash
for f in python/[0-9]*.py; do echo "== $f =="; python3 "$f"; done
```

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [01_hello.py](01_hello.py) | `python3 python/01_hello.py` | print、f-string 插值、两种注释 |
| 02 variable | [02_variable.py](02_variable.py) | `python3 python/02_variable.py` | 动态类型、类型标注、多重赋值、常量约定、类型转换 |
| 03 operator | [03_operator.py](03_operator.py) | `python3 python/03_operator.py` | 算术（** 与 //）、is vs ==、海象运算符、% 与 format |
| 04 string | [04_string.py](04_string.py) | `python3 python/04_string.py` | 切片、join/split/strip/replace、不可变性、encode |
| 05 control | [05_control.py](05_control.py) | `python3 python/05_control.py` | if-elif、match-case、for-else、while、break/continue |
| 06 function | [06_function.py](06_function.py) | `python3 python/06_function.py` | 默认/关键字参数、*args/**kwargs、lambda、闭包 |
| 07 collection | [07_collection.py](07_collection.py) | `python3 python/07_collection.py` | list/tuple/set、推导式、sort vs sorted、解包 |
| 08 map | [08_map.py](08_map.py) | `python3 python/08_map.py` | dict 增删改查、get/defaultdict、遍历、\| 合并 |
| 09 oop | [09_oop.py](09_oop.py) | `python3 python/09_oop.py` | class、继承与 super、property、__repr__、dataclass |
| 10 error | [10_error.py](10_error.py) | `python3 python/10_error.py` | try/except 多类型、else/finally、raise from、自定义异常 |
| 11 file_io | [11_file_io.py](11_file_io.py) | `python3 python/11_file_io.py` | with open 读/写/逐行、json.dump/load、pathlib |
| 12 module | [12_module.py](12_module.py) | `python3 python/12_module.py` | import/from-import 双文件演示（配合 [mymath.py](mymath.py)）、包结构说明 |
| 13 stdlib | [13_stdlib.py](13_stdlib.py) | `python3 python/13_stdlib.py` | collections/itertools/datetime/re/os/sys 速览 |
| 14 concurrency | [14_concurrency.py](14_concurrency.py) | `python3 python/14_concurrency.py` | threading+Lock、ThreadPoolExecutor、asyncio 各一小段 |
| 15 generic | [15_generic.py](15_generic.py) | `python3 python/15_generic.py` | TypeVar 泛型函数/泛型类、带约束 TypeVar、Protocol |
| + 特色 | [16_decorator_generator.py](16_decorator_generator.py) | `python3 python/16_decorator_generator.py` | 装饰器（含带参）、生成器与 yield、生成器表达式 |

> 12_module.py 依赖同级的 [mymath.py](mymath.py)：运行 12_module.py 时它作为模块被导入（`__name__ == "mymath"`）；单独运行 mymath.py 则走 `__name__ == "__main__"` 自测段，同样退出码 0。

## 进阶说明

- 每个示例文件头部注释都标明了主题说明、运行命令与预期输出，适合按主题顺序阅读
- 之后的进阶方向：虚拟环境与打包（venv/pip/uv）、类型检查（mypy）、测试（pytest）、异步 Web（FastAPI）
- 仓库内已有的 Python 专题目录（依赖第三方库，不随基础示例进 CI）：
  - [chapters/](chapters/) - 早期章节式基础练习
  - [ai/](ai/) - AI/机器学习示例
  - [matplotlib/](matplotlib/) - Matplotlib 可视化示例（含 README）
  - [scapy/](scapy/) - Scapy 网络分析示例（含 README）
  - [scrapy/](scrapy/) - Scrapy 爬虫示例（含 README）
- 早期多语言章节式练习与测试见 [languages/python](../languages/python/)（旧结构，后续计划迁移合并）
