# 主题说明：Python 的第一个程序 —— print 输出、f-string 插值与注释写法。
#           print 是内置函数（可变参数、sep/end 选项）；f-string（3.6+）是如今最推荐的字符串插值方式。
# 运行命令：python3 python/01_hello.py
# 预期输出（关键行）：
#   Hello, Python!
#   你好，Python！第 1 个示例
#   表达式插值：1 + 1 = 2
#   a-b-c

# 单行注释：以 # 开头，最常用

"""模块文档字符串（docstring）：三引号字符串的惯例用法，
   用于说明模块/函数的用途，也算一种"注释"。"""

print("Hello, Python!")

# f-string：f 前缀 + {} 表达式插值，{} 里可以写任意表达式
name = "Python"
no = 1
print(f"你好，{name}！第 {no} 个示例")
print(f"表达式插值：1 + 1 = {1 + 1}")

# print 的常用选项：sep 指定分隔符（默认空格），end 指定结尾（默认换行）
print("a", "b", "c", sep="-")
print("不换行", end="")
print(" <- 紧跟在上一行")

# f-string 的格式化：精度、宽度与对齐
pi = 3.14159
print(f"pi ≈ {pi:.2f}")
print(f"右对齐宽度 8：[{pi:>8.2f}]，左对齐：[{pi:<8.2f}]")
