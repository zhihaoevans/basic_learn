# 主题说明：Python 变量与类型 —— 动态类型、类型标注、多重赋值、常量约定与类型转换。
#           变量本质是"名字绑定到对象"：无需声明类型；类型标注（3.6+）供 IDE/静态检查使用，运行时不强制。
# 运行命令：python3 python/02_variable.py
# 预期输出（关键行）：
#   <class 'int'> 42
#   <class 'str'> hello
#   Alice 18 92.5 True None
#   a=0 b=0 c=0，交换后 x=2 y=1

# 动态类型：同一个名字可先后绑定不同类型的对象（合法但易混淆，慎用）
x = 42
print(type(x), x)
x = "hello"
print(type(x), x)

# 基本类型与类型标注：形式是"名字: 类型 = 值"
age: int = 18
name: str = "Alice"
score: float = 92.5
online: bool = True
nothing: str | None = None          # 3.10+ 联合类型写作 X | Y
print(name, age, score, online, nothing)
print(f"调试写法 {{name=}}：{name=}")   # 3.8+ 的 {name=} 自动带上变量名

# 函数标注：参数类型与返回值类型
def greet(who: str, times: int = 1) -> str:
    return f"你好 {who} x{times}"

print(greet("Bob", 2))

# 多重赋值：链式赋值与元组打包/解包
a = b = c = 0            # 链式赋值：三个名字绑定到同一对象
x, y = 1, 2              # 右侧打包成元组，再解包给左侧
x, y = y, x              # 交换两个变量，不需要临时变量
print(f"a={a} b={b} c={c}，交换后 x={x} y={y}")

# 常量约定：全大写表示"约定上不再修改"，语言层面并不阻止
MAX_RETRY = 3
print(f"常量约定 MAX_RETRY={MAX_RETRY}（全大写，靠约定维护）")

# 类型转换：int/float/str/bool 显式转换
print(int("42"), float("3.14"), str(99), bool(0))
print(f"int(3.99) = {int(3.99)}（截断取整，不是四舍五入）")
print(f"falsy 值判断：bool('')={bool('')}，bool(0)={bool(0)}，bool('x')={bool('x')}")
