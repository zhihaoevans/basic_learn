# 主题说明：Python 常用标准库速览 —— collections / itertools / datetime / re / os / sys，全部开箱即用无需安装。
# 运行命令：python3 python/13_stdlib.py
# 预期输出（关键行）：
#   Counter 最常见 2 词：[('the', 3), ('quick', 1)]
#   日期运算：2026-01-01 + 40 天 = 2026-02-10，相差 40 天
#   sys.version_info >= (3, 10)：True（本系列按 3.10+ 编写）

import datetime
import itertools
import os
import re
import sys
from collections import Counter, deque

# collections.Counter：对哈希对象计数
words = "the quick brown fox jumps over the lazy dog the end".split()
word_counts = Counter(words)
print(f"Counter 最常见 2 词：{word_counts.most_common(2)}")
print(f"Counter 数量相加：{Counter('aab') + Counter('abb')}")

# collections.deque：双端队列，两端进出都是 O(1)
dq = deque([2, 3])
dq.appendleft(1)
dq.append(4)
dq.popleft()
print(f"deque 操作后：{list(dq)}")

# itertools：迭代器工具箱
print(f"chain 拼接：{list(itertools.chain([1, 2], [3, 4]))}")
print(f"combinations 组合：{list(itertools.combinations('abc', 2))}")
print(f"count+islice 取无限流前 3 个：{list(itertools.islice(itertools.count(10), 3))}")

# datetime：日期运算与解析/格式化
d1 = datetime.date(2026, 1, 1)
d2 = d1 + datetime.timedelta(days=40)
print(f"日期运算：{d1} + 40 天 = {d2}，相差 {(d2 - d1).days} 天")
dt = datetime.datetime.strptime("2026-09-19 08:30", "%Y-%m-%d %H:%M")   # 解析
print(f"strftime 格式化：{dt.strftime('%Y/%m/%d %H:%M')}，ISO 星期 {dt.isoweekday()}")

# re：正则表达式（正则字符串建议写在外面，避免 f-string 表达式里出现反斜杠）
text = "订单A: 3件, 订单B: 12件"
pattern = r"(\w+)[:：]\s*(\d+)件"
print(f"findall 提取：{re.findall(pattern, text)}")
m = re.search(r"\d+", "abc42def")
print(f"search 首个匹配：{m.group()}（位置 {m.start()}）")

# os：与操作系统交互（路径、目录、环境变量）
here = os.path.dirname(os.path.abspath(__file__))
py_files = sorted(f for f in os.listdir(here) if f[0].isdigit() and f.endswith(".py"))
print(f"os.listdir 本目录数字开头的 .py 前 3 个：{py_files[:3]}")
print(f"os.environ 取缺失键给默认值：{os.environ.get('BASIC_LEARN_DEMO', '默认值')}")

# sys：解释器与脚本自身（argv / 模块缓存 / 版本判断）
print(f"sys.argv[0] 的 basename：{os.path.basename(sys.argv[0])}")
print(f"sys.version_info >= (3, 10)：{sys.version_info >= (3, 10)}（本系列按 3.10+ 编写）")
print(f"'os' 已被导入（sys.modules 缓存）：{'os' in sys.modules}")
