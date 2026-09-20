# 主题说明：Python 字符串操作 —— 索引/切片、f-string 与 format、join/split/strip/replace、不可变性、encode 与 bytes。
# 运行命令：python3 python/04_string.py
# 预期输出（关键行）：
#   s[7:13] = Python
#   反转 s[::-1] = !nohtyP ,olleH
#   go-rust-python
#   [hello python]

s = "Hello, Python!"

# 索引（正/负下标）与切片 [start:stop:step]（左闭右开）
print(f"s[0] = {s[0]}，s[-1] = {s[-1]}")
print(f"s[7:13] = {s[7:13]}")
print(f"s[:5] = {s[:5]}，s[7:] = {s[7:]}")
print(f"反转 s[::-1] = {s[::-1]}")
print(f"每隔一个取 s[::2] = {s[::2]}")

# f-string 与 str.format 的对齐与填充（两种插值写法效果一致）
name, price = "苹果", 4.5
print(f"商品 [{name:>4}] 价格 {price:06.2f} 元")            # >4 右对齐补空格，06.2f 补零
print("商品 [{}] 价格 {:.2f} 元".format(name, price))       # str.format 位置占位

# join / split：列表 <-> 字符串互转
words = ["go", "rust", "python"]
print("-".join(words))
print(f"按逗号切分：{'a,b,,c'.split(',')}")                  # 保留空串
whitespace_line = "  one two\tthree "                       # 正则串等含反斜杠的字面量建议写在 f-string 外
print(f"无参切分：{whitespace_line.split()}")                # 按任意空白切并去掉空项

# strip / replace：清理与替换
raw = "   hello python   "
print(f"[{raw.strip()}]")                       # strip 去两端空白
print(f"[{'xxhixx'.strip('x')}]")               # 去两端指定字符
print(f"替换前 2 处：{'py-py-py'.replace('py', 'go', 2)}")

# 不可变性：字符串方法都返回新字符串，原串不会被修改
old = "abc"
print(old.upper(), old)

# 查找与判断：find / in / startswith / count
print(f"'Py' in s 为 {'Py' in s}，s.find('Java') = {s.find('Java')}（找不到返回 -1）")
print(f"s.startswith('Hello') 为 {s.startswith('Hello')}，'o' 出现 {s.count('o')} 次")

# encode/decode：str 是 Unicode 文本，bytes 是字节序列；读写文件/网络时需按编码转换
b = "你好".encode("utf-8")
print(f"utf-8 字节：{b}，字节数 {len(b)}，字符数 {len('你好')}")
print(f"decode 回文本：{b.decode('utf-8')}")
