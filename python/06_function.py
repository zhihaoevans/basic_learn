# 主题说明：Python 函数 —— def 定义、默认/关键字参数、*args/**kwargs、lambda、闭包与类型标注。
#           函数是一等公民：可以赋值给变量、作参数传递、作返回值。
# 运行命令：python3 python/06_function.py
# 预期输出（关键行）：
#   add(1, 2) = 3，make_greet() = 你好!
#   extremes(3, 1, 4, 1, 5) = (1, 5)
#   可变默认值陷阱：[1] [1, 2]
#   闭包计数：1 2 3

# 基本定义与类型标注（标注供 IDE/静态检查，运行时不强制）
def add(a: int, b: int) -> int:
    """返回 a + b（本行是 docstring，help(add) 可查看）"""
    return a + b

# 默认参数与"仅限关键字参数"（* 之后的参数必须用关键字传）
def make_greet(greeting: str = "你好", *, punct: str = "!") -> str:
    return f"{greeting}{punct}"

# *args 收集多余位置参数为元组；**kwargs 收集多余关键字参数为字典
def extremes(*args: float) -> tuple[float, float]:
    return min(args), max(args)

def show_config(**kwargs: str) -> None:
    for key, value in kwargs.items():
        print(f"配置 {key} = {value}")

print(f"add(1, 2) = {add(1, 2)}，make_greet() = {make_greet()}")
print(f"make_greet('早上好', punct='。') = {make_greet('早上好', punct='。')}")
print(f"extremes(3, 1, 4, 1, 5) = {extremes(3, 1, 4, 1, 5)}")
show_config(host="localhost", mode="fast")

# 可变默认值陷阱：默认值只在定义时求值一次，可变对象会被多次调用共享
def append_bad(item, lst=[]):
    lst.append(item)
    return lst

print(f"可变默认值陷阱：{append_bad(1)} {append_bad(2)}")

# lambda：单表达式匿名函数，常作 sorted/map 的 key
pairs = [("a", 3), ("b", 1), ("c", 2)]
print(f"按值排序：{sorted(pairs, key=lambda kv: kv[1])}")
print(f"map + lambda：{list(map(lambda x: x * x, [1, 2, 3]))}")

# 闭包：内层函数记住外层作用域的变量；nonlocal 声明后可修改它
def make_counter():
    count = 0

    def bump() -> int:
        nonlocal count
        count += 1
        return count

    return bump

counter = make_counter()
print(f"闭包计数：{counter()} {counter()} {counter()}")
