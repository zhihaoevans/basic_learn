# 主题说明：Python 内置集合类型 —— list/tuple/set、推导式、sort vs sorted 与解包。
# 运行命令：python3 python/07_collection.py
# 预期输出（关键行）：
#   增：[2, 3, 1, 4, 1, 5, 9]，长度 7，包含 4：True
#   并 {1, 2, 3, 4}，交 {3}，差 {1, 2}，对称差 {1, 2, 4}
#   sorted(data) = [1, 1, 3, 4, 5]（新列表）
#   data.sort(reverse=True) 后 data = [5, 4, 3, 1, 1]（原地修改）

# list：有序、可变、允许重复
nums = [3, 1, 4]
nums.append(1)               # 尾部追加
nums.extend([5, 9])          # 追加另一个可迭代对象
nums.insert(0, 2)            # 指定位置插入
print(f"增：{nums}，长度 {len(nums)}，包含 4：{4 in nums}")
nums.remove(1)               # 按值删除第一个匹配元素
tail = nums.pop()            # 按位弹出末尾元素
print(f"删：{nums}，弹出了 {tail}")

# tuple：有序、不可变；常用于固定长度的异构结构
point = (3, 4)
x, y = point                          # 解包
first, *middle, last = [1, 2, 3, 4]   # 星号解包：收集中间一段
print(f"point={point}，解包 x={x} y={y}")
print(f"星号解包：first={first} middle={middle} last={last}")

# set：无序、元素唯一，支持集合运算
s = {1, 2, 2, 3}
print(f"{{1, 2, 2, 3}} 长度为 {len(s)}（自动去重）")
a, b = {1, 2, 3}, {3, 4}
print(f"并 {a | b}，交 {a & b}，差 {a - b}，对称差 {a ^ b}")
empty = set()                # 注意：{} 是空字典，不是空集合
print(f"空集合要写 set()：{empty}，类型 {type(empty).__name__}")

# 推导式：list / set / dict 三种
squares = [i * i for i in range(5)]
evens = [i for i in range(10) if i % 2 == 0]
grid = [(i, j) for i in range(2) for j in range(2)]    # 双重循环
lengths = {len(w) for w in ["a", "bb", "cc"]}
word_len = {w: len(w) for w in ["py", "rust"]}
print(f"列表推导：{squares} / {evens}")
print(f"双重循环推导：{grid}")
print(f"集合推导：{lengths}，字典推导：{word_len}")

# sort vs sorted：sorted 返回新列表；list.sort 原地排序并返回 None
data = [3, 1, 4, 1, 5]
new_sorted = sorted(data)
data.sort(reverse=True)
print(f"sorted(data) = {new_sorted}（新列表）")
print(f"data.sort(reverse=True) 后 data = {data}（原地修改）")
words = ["banana", "fig", "apple"]
print(f"按长度排序：{sorted(words, key=len)}")
