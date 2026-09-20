# 主题说明：Python 特色 —— 装饰器（含带参数装饰器）与生成器（yield、生成器表达式）。
#           装饰器是"接收函数返回新函数"的语法糖；生成器惰性产出值，适合大序列与流式处理。
# 运行命令：python3 python/16_decorator_generator.py
# 预期输出（关键行）：
#   -> 调用 add(2, 3)
#   <- 返回 5
#   hello py
#   逐个 next：3 2 1
#   sum(平方生成器) = 285

import time
from functools import wraps

# 1) 基础装饰器：@trace 等价于 add = trace(add)
def trace(func):
    @wraps(func)                     # wraps 保留原函数名与 docstring
    def wrapper(*args, **kwargs):
        print(f"-> 调用 {func.__name__}{args}")
        result = func(*args, **kwargs)
        print(f"<- 返回 {result}")
        return result
    return wrapper

@trace
def add(a, b):
    return a + b

add(2, 3)

# 2) 带参数的装饰器：三层嵌套，最外层接收参数，返回真正的装饰器
def repeat(times: int):
    def deco(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            for i in range(times):
                result = func(*args, **kwargs)
                print(f"  第 {i + 1}/{times} 次执行完毕")
            return result
        return wrapper
    return deco

@repeat(times=3)                     # 先调用 repeat(3) 拿到装饰器，再装饰 hello
def hello(name: str) -> str:
    return f"hello {name}"

print(hello("py"))

# 3) 装饰器实战：计时（毫秒数随机器/负载变化）
def timed(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        t0 = time.perf_counter()
        result = func(*args, **kwargs)
        ms = (time.perf_counter() - t0) * 1000
        print(f"{func.__name__} 耗时 {ms:.2f} ms")
        return result
    return wrapper

@timed
def slow_add(a: int, b: int) -> int:
    time.sleep(0.01)                 # 模拟耗时操作
    return a + b

print(f"slow_add(1, 2) = {slow_add(1, 2)}")

# 4) 生成器函数：yield 逐个产出，函数在 yield 处暂停，next() 时从暂停点继续
def countdown(n: int):
    while n > 0:
        yield n
        n -= 1

gen = countdown(3)
print(f"逐个 next：{next(gen)} {next(gen)} {next(gen)}")
print(f"整体消费：{list(countdown(5))}")

# 5) yield 生成斐波那契数列：无需预先构造整个列表
def fib(limit: int):
    a, b = 0, 1
    while a < limit:
        yield a
        a, b = b, a + b

print(f"fib(100) = {list(fib(100))}")

# 6) 生成器表达式：类似列表推导式，但用圆括号、按需产出，省内存
squares = (i * i for i in range(10))
print(f"sum(平方生成器) = {sum(squares)}")        # sum 消费生成器，全程未建列表
print(f"函数调用可省外层括号：{sum(x * x for x in range(4))}")

# 7) 惰性流水线：itertools.count 无限流 + islice 截取，配合生成器表达式
import itertools

evens = (n * 2 for n in itertools.count())        # 无限偶数流，不占内存
print(f"无限流取前 5 个偶数：{list(itertools.islice(evens, 5))}")
