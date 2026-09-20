# 主题说明：Python 面向对象 —— class 定义、继承与 super、property、魔术方法 __repr__ 与 dataclass。
# 运行命令：python3 python/09_oop.py
# 预期输出（关键行）：
#   Animal(name='通用')
#   Dog(name='旺财')
#   自动生成 __repr__：Point(x=3, y=4)
#
# 说明：Dog 未重写 __repr__ 时，打印 dog 用的是从 Animal 继承来的版本。

class Animal:
    """基类：演示 __init__、实例方法与 __repr__ 魔术方法。"""

    def __init__(self, name: str) -> None:
        self.name = name                # 实例属性

    def speak(self) -> str:             # 实例方法
        return "……"

    def __repr__(self) -> str:          # repr()/调试展示时调用的魔术方法
        return f"{type(self).__name__}(name={self.name!r})"


class Dog(Animal):                      # 继承：Dog 是一种 Animal
    def __init__(self, name: str, breed: str) -> None:
        super().__init__(name)          # super() 调用父类方法
        self.breed = breed

    def speak(self) -> str:             # 方法重写（多态的基础）
        return "汪！"

    def fetch(self) -> str:             # 子类新增方法
        return f"{self.name} 去捡球"


generic, dog = Animal("通用"), Dog("旺财", "柴犬")
print(generic)                          # 触发 __repr__
print(dog)
print(f"多态调用：{generic.speak()} / {dog.speak()}，{dog.fetch()}")
print(f"isinstance(dog, Animal) = {isinstance(dog, Animal)}，isinstance(generic, Dog) = {isinstance(generic, Dog)}")
print(f"dog 的方法解析顺序 MRO：{[c.__name__ for c in type(dog).__mro__]}")

# property：像属性一样访问，背后走 getter/setter，setter 里可做校验
class Account:
    def __init__(self, owner: str) -> None:
        self.owner = owner
        self._balance = 0               # 约定：_ 前缀表示"内部使用"

    @property
    def balance(self) -> int:           # getter：acct.balance
        return self._balance

    @balance.setter
    def balance(self, value: int) -> None:
        if value < 0:
            raise ValueError("余额不能为负")
        self._balance = value

acct = Account("Alice")
acct.balance = 100                      # 走 setter 赋值
print(f"acct.balance = {acct.balance}") # 走 getter 读取
try:
    acct.balance = -1
except ValueError as e:
    print(f"setter 校验生效：{e}")

# dataclass（3.7+）：按类型标注自动生成 __init__/__repr__/__eq__
from dataclasses import dataclass

@dataclass
class Point:
    x: float
    y: float = 0.0                      # 带默认值的字段放在后面

    def dist_to_origin(self) -> float:
        return (self.x ** 2 + self.y ** 2) ** 0.5

p1, p2 = Point(3, 4), Point(3, 4)
print(f"自动生成 __repr__：{p1}")
print(f"自动生成 __eq__：p1 == p2 为 {p1 == p2}，p1.dist_to_origin() = {p1.dist_to_origin()}")
print(f"Point(5) 用默认值：{Point(5)}")

# 其他常用魔术方法速览（不逐一展开）：
# __str__（print/str）、__len__（len）、__eq__（==）、__add__（+）、__iter__（for 迭代）
