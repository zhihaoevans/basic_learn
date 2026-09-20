# 主题说明：演示用的被导入模块 —— 由 python/12_module.py 通过 import mymath 使用。
#           定义常量、函数与 __all__ 导出清单；含 __name__ == "__main__" 自测段，直接运行也能自测。
# 运行命令：python3 python/mymath.py（自测）；通常由 python3 python/12_module.py 导入使用
# 预期输出（关键行）：
#   mymath 自测：__name__ = __main__
#   mymath 自测：add(2, 3) = 5
#   mymath 自测：factorial(5) = 120

PI = 3.14159                          # 模块级常量


def add(a: float, b: float) -> float:
    """加法：被导入时通过 mymath.add(2, 3) 调用。"""
    return a + b


def factorial(n: int) -> int:
    """阶乘：演示模块内的循环与累乘。"""
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result


def circle_area(radius: float) -> float:
    """圆面积：使用模块常量 PI。"""
    return PI * radius * radius


# __all__：from mymath import * 时只导出这些名字
__all__ = ["PI", "add", "factorial", "circle_area"]

if __name__ == "__main__":
    # 只有直接运行本文件时才执行；被 import 时 __name__ 是 "mymath"，这段不会运行。
    # 这就是 12_module.py 里"被导入不执行自测"的原因。
    print(f"mymath 自测：__name__ = {__name__}")
    print(f"mymath 自测：add(2, 3) = {add(2, 3)}")
    print(f"mymath 自测：factorial(5) = {factorial(5)}")
    print(f"mymath 自测：circle_area(2) = {circle_area(2):.4f}")
