# 主题说明：Python 运算符与表达式 —— 算术（** 幂、// 整除）、比较与逻辑、is vs ==、海象运算符、% 与 format 格式化。
# 运行命令：python3 python/03_operator.py
# 预期输出（关键行）：
#   17 / 5 = 3.4
#   17 // 5 = 3
#   2 ** 10 = 1024
#   -7 // 2 = -4（整除向负无穷取整）

a, b = 17, 5
print(f"{a} + {b} = {a + b}")
print(f"{a} - {b} = {a - b}")
print(f"{a} * {b} = {a * b}")
print(f"{a} / {b} = {a / b}")          # 真除法：结果总是 float
print(f"{a} // {b} = {a // b}")        # 整除：向下取整
print(f"{a} % {b} = {a % b}")          # 取模（余数）
print(f"2 ** 10 = {2 ** 10}")          # 幂运算
print(f"-7 // 2 = {-7 // 2}（整除向负无穷取整）")
print(f"-7 % 2 = {-7 % 2}（余数符号跟除数一致）")
print(f"divmod(17, 5) = {divmod(17, 5)}")   # (商, 余数) 一次拿到

# 复合赋值运算符：+= -= *= //= %= **=
n = 10
n += 5
print(f"n += 5 后 n = {n}")

# 比较与逻辑运算；Python 支持链式比较
print(f"1 < 2 < 3 为 {1 < 2 < 3}（等价于 1 < 2 and 2 < 3）")
print(f"and/or 的短路求值：{3 > 1 and 'yes' or 'no'}")

# is vs ==：== 比较值是否相等，is 比较是否为同一对象（身份）
lst1 = [1, 2, 3]
lst2 = [1, 2, 3]
print(f"lst1 == lst2 为 {lst1 == lst2}")
print(f"lst1 is lst2 为 {lst1 is lst2}")
x = None
print(f"x is None 为 {x is None}（判 None 的惯用法，不用 ==）")

# 海象运算符 :=（3.8+）：在表达式内部完成赋值并取回该值
data = [3, 1, 4, 1, 5]
if (n := len(data)) > 3:
    print(f"海象运算符：len(data) = {n}，> 3 成立进入分支")

# 字符串格式化表达式：% 风格与 str.format 方法
name, score = "Alice", 91.567
print("%% 风格：%s 得分 %.1f" % (name, score))
print("format 风格：{} 得分 {:.1f}".format(name, score))
