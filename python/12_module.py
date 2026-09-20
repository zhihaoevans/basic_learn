# 主题说明：Python 模块与包 —— import / from-import / as 别名的用法；双文件演示"入口脚本"与"被导入模块"的关系。
#           mymath.py 与本文件同级：运行本文件时 mymath 被导入，其 __name__ 为 "mymath" 而非 "__main__"。
# 运行命令：python3 python/12_module.py
# 预期输出（关键行）：
#   mymath 模块已加载，__name__ = mymath
#   mymath.add(2, 3) = 5
#   mm.factorial(5) = 120
#   直接运行 12_module.py：__name__ = __main__

# import 整个模块，之后用"模块名.属性"访问
import mymath

# from-import：只引入需要的名字；import ... as ... 起短别名
from mymath import PI, circle_area
import mymath as mm

print(f"mymath 模块已加载，__name__ = {mymath.__name__}")
print(f"mymath.__file__ 以 mymath.py 结尾：{mymath.__file__.endswith('mymath.py')}")

print(f"mymath.add(2, 3) = {mymath.add(2, 3)}")
print(f"PI = {PI:.4f}")
print(f"circle_area(1) = {circle_area(1):.4f}")
print(f"mm.factorial(5) = {mm.factorial(5)}")
print(f"mymath.__all__ = {mymath.__all__}")

# 模块只被导入一次：sys.modules 缓存，再次 import 不会重新执行模块代码
import sys

print(f"'mymath' in sys.modules：{'mymath' in sys.modules}")

# 包结构说明（注释演示）：带 __init__.py 的目录就是包，例如
#   mypkg/
#   ├── __init__.py
#   └── sub/
#       ├── __init__.py
#       └── mod.py
#   from mypkg.sub import mod     # 绝对导入
#   from . import sibling         # 包内相对导入
#
# 直接运行本文件时 __name__ == "__main__"，被导入时则是模块名 ——
# 这就是"导入时只初始化、运行时才执行"惯用法的关键（见 mymath.py 的自测段）。

if __name__ == "__main__":
    # 这段只在直接运行本文件时执行；若本文件被别处 import 则跳过
    print(f"直接运行 12_module.py：__name__ = {__name__}")
