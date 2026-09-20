# 主题说明：Python 异常处理 —— try/except（多类型）、else/finally、raise from 与自定义异常。
# 运行命令：python3 python/10_error.py
# 预期输出（关键行）：
#   parse_int('4x') = 0
#   divide(1, 0) = None
#   业务异常：余额不足：现有 100，需要 150（差额 50）

# 基本形式：try/except 捕获并处理；不捕获则沿调用栈向上抛
def parse_int(text: str) -> int:
    try:
        return int(text)
    except ValueError as e:             # as e 拿到异常对象
        print(f"  无法解析 {text!r}：{e}")
        return 0

print(f"parse_int('42') = {parse_int('42')}")
print(f"parse_int('4x') = {parse_int('4x')}")

# except 多类型 + else（没发生异常才执行）+ finally（无论如何都执行）
def divide(a: float, b: float) -> float | None:
    try:
        result = a / b
    except (ZeroDivisionError, TypeError) as e:      # 一个 except 捕获多种类型
        print(f"  捕获 {type(e).__name__}：{e}")
        return None
    else:
        print("  try 块成功，else 分支执行")           # 放"成功后"的逻辑，避免误捕获
        return result
    finally:
        print("  finally：无论如何都执行（常用于释放资源）")

print(f"divide(10, 4) = {divide(10, 4)}")
print(f"divide(1, 0) = {divide(1, 0)}")

# 自定义异常：继承 Exception，可携带业务字段
class BalanceError(Exception):
    """业务异常：余额不足。"""

    def __init__(self, balance: int, need: int) -> None:
        super().__init__(f"余额不足：现有 {balance}，需要 {need}")
        self.balance = balance
        self.need = need


def withdraw(balance: int, amount: int) -> int:
    if amount > balance:
        raise BalanceError(balance, amount)          # 主动抛出
    return balance - amount

try:
    withdraw(100, 150)
except BalanceError as e:
    print(f"业务异常：{e}（差额 {e.need - e.balance}）")

# raise ... from ...：转译异常时保留原始原因（__cause__），便于排查
def load_setting(data: dict, key: str) -> str:
    try:
        return data[key]
    except KeyError as e:
        raise RuntimeError(f"缺少配置项 {key!r}") from e

try:
    load_setting({"a": 1}, "b")
except RuntimeError as e:
    print(f"外层异常：{e}")
    print(f"原因链 __cause__：{e.__cause__!r}")

# 异常层级与兜底：BaseException <- Exception <- 各种具体异常
try:
    raise TimeoutError("等待超时")
except Exception as e:                # Exception 能兜住绝大多数业务异常
    print(f"Exception 兜底捕获：{type(e).__name__}: {e}")
