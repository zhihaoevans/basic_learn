# 主题说明：Python 控制流 —— if/elif、match-case（3.10+）、for/while、break/continue 与 for-else。
# 运行命令：python3 python/05_control.py
# 预期输出（关键行）：
#   score=85 -> B
#   成功 未找到 其他
#   普通点 (3, 4)
#   while 循环结束 count=3

# if / elif / else：按分数定级
score = 85
if score >= 90:
    grade = "A"
elif score >= 80:
    grade = "B"
elif score >= 70:
    grade = "C"
else:
    grade = "D"
print(f"score={score} -> {grade}")

# match-case（3.10+）：结构化模式匹配，比 if-elif 链更清晰
def http_status(code: int) -> str:
    match code:
        case 200 | 201:            # | 表示多个模式取或
            return "成功"
        case 404:
            return "未找到"
        case 500:
            return "服务器错误"
        case _:                    # _ 是通配符，兜底
            return "其他"

print(http_status(200), http_status(404), http_status(403))

# match 解构序列：模式里可以绑定变量
point = (3, 4)
match point:
    case (0, 0):
        print("原点")
    case (x, 0):
        print(f"在 x 轴上，x={x}")
    case (0, y):
        print(f"在 y 轴上，y={y}")
    case (x, y):
        print(f"普通点 ({x}, {y})")

# for + break/continue
for i in range(1, 8):
    if i % 2 == 0:
        continue                   # 跳过偶数
    if i > 6:
        break                      # 提前退出循环
    print(f"奇数 {i}", end=" ")
print()

# for-else：循环没被 break 打断才会走 else（常见于"查找失败"场景）
for n in [2, 3, 5, 7]:
    if n % 2 == 0 and n != 2:
        break
else:
    print("列表里没有除 2 以外的偶数")

# while 循环
count = 0
while count < 3:
    count += 1
print(f"while 循环结束 count={count}")

# range(起, 止, 步长)：左闭右开
print(f"range(10, 0, -3) = {list(range(10, 0, -3))}")
