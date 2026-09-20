# 主题说明：Python 字典 dict —— 增删改查、get/setdefault/defaultdict、遍历、推导式与 | 合并运算符。
# 运行命令：python3 python/08_map.py
# 预期输出（关键行）：
#   删：user = {'name': 'Alice'}，pop('age') = 19，'name' in user = True
#   config.get('port', 8080) = 8080
#   defaults | override = {'host': '0.0.0.0', 'port': 9000}

from collections import defaultdict

# 增删改查
user = {"name": "Alice", "age": 18}
user["city"] = "Beijing"       # 新增键值对
user["age"] = 19               # 修改已有键
print(f"查：user = {user}，user['name'] = {user['name']}")
del user["city"]               # 删除指定键
age = user.pop("age")          # 弹出并返回值
print(f"删：user = {user}，pop('age') = {age}，'name' in user = {'name' in user}")

# get：键不存在时返回默认值而不抛 KeyError（[] 访问缺失键会抛 KeyError）
config = {"host": "localhost"}
print(f"config.get('port') = {config.get('port')}")
print(f"config.get('port', 8080) = {config.get('port', 8080)}")

# setdefault 与 collections.defaultdict：自动初始化缺失键
groups = {}
for w in ["py", "rust", "python"]:
    groups.setdefault(w[0], []).append(w)     # 缺失则先放入空列表
dd = defaultdict(int)                         # 缺失键自动取 int() 即 0
for ch in "banana":
    dd[ch] += 1
print(f"setdefault 分组：{groups}")
print(f"defaultdict(int) 计数：{dict(dd)}")

# 遍历：默认遍历键；keys()/values()/items() 三种视图（3.7+ 字典保持插入序）
scores = {"alice": 90, "bob": 85, "carol": 95}
print(f"键：{list(scores)}")
print(f"值：{list(scores.values())}")
for name, score in scores.items():            # 最常用的键值遍历
    print(f"  {name} -> {score}")

# 字典推导式
bonus = {name: score + 5 for name, score in scores.items()}
even_sq = {i: i * i for i in range(4) if i % 2 == 0}
print(f"每人加 5 分：{bonus}")
print(f"带条件的推导：{even_sq}")

# 合并：| 运算符（3.9+）生成新字典，同键右侧优先；{**a, **b} 是等价老写法
defaults = {"host": "0.0.0.0", "port": 8000}
override = {"port": 9000}
print(f"defaults | override = {defaults | override}")
unpacked = {**defaults, **override}     # 解包合并的老写法（先算好再插入，f-string 表达式里不能写 **）
print(f"{{**defaults, **override}} = {unpacked}")

# 排序遍历：items() + sorted 按值排序
ranking = sorted(scores.items(), key=lambda kv: kv[1], reverse=True)
print(f"按分数降序：{ranking}")
