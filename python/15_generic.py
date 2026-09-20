# 主题说明：Python 泛型入门 —— TypeVar 泛型函数/泛型类、带约束的 TypeVar 与 Protocol 结构化类型（静态鸭子类型）。
#           Python 是"渐进式类型"：标注供 mypy/IDE 检查，运行时不强制。
# 运行命令：python3 python/15_generic.py
# 预期输出（关键行）：
#   first([1, 2, 3]) + 1 = 2
#   Box[str]：get().upper() = PY
#   make_sound：汪 喵

from typing import Generic, Protocol, TypeVar

T = TypeVar("T")                       # 类型变量：占位符，调用时才确定具体类型
Number = TypeVar("Number", int, float) # 带约束：只允许 int 或 float

# 泛型函数：入参与返回值共用同一个 T，保证"进什么类型、出什么类型"
def first(items: list[T]) -> T:
    return items[0]

print(f"first([1, 2, 3]) + 1 = {first([1, 2, 3]) + 1}")             # T 推导为 int
print(f"first(['a', 'b']).upper() = {first(['a', 'b']).upper()}")   # T 推导为 str

# 带约束的泛型：限定允许的类型集合，编辑器可据此提示 + 运算
def total(values: list[Number]) -> Number:
    result: Number = values[0]
    for v in values[1:]:
        result = result + v
    return result

print(f"total([1, 2, 3]) = {total([1, 2, 3])}，total([1.5, 2.5]) = {total([1.5, 2.5])}")

# 泛型类：继承 Generic[T]，实例在整个生命周期里固定 T
class Box(Generic[T]):
    def __init__(self, item: T) -> None:
        self._item = item

    def get(self) -> T:
        return self._item

    def replace(self, new_item: T) -> T:      # 参数与属性保持同一类型
        old, self._item = self._item, new_item
        return old

int_box: Box[int] = Box(42)                   # 标注让 IDE 知道 get() 返回 int
old = int_box.replace(7)
print(f"Box[int]：换掉 {old} 后 get() = {int_box.get()}")
str_box = Box("py")
print(f"Box[str]：get().upper() = {str_box.get().upper()}")

# Protocol（结构化类型 / 静态鸭子类型）：方法签名匹配即算实现，无需继承
class Speaker(Protocol):
    def speak(self) -> str: ...

class Dog:
    def speak(self) -> str:                   # 没继承 Speaker，但结构满足
        return "汪"

class Cat:
    def speak(self) -> str:
        return "喵"

def make_sound(s: Speaker) -> str:            # 静态检查器能验证传入者"长得像"Speaker
    return s.speak()

print(f"make_sound：{make_sound(Dog())} {make_sound(Cat())}")
print(f"运行时标注不强制：first 只是普通 {type(first).__name__}，不检查类型参数")
