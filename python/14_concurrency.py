# 主题说明：Python 并发入门 —— threading + Lock 线程同步、concurrent.futures 线程池、asyncio 协程各一小段。
#           CPython 受 GIL 约束：线程适合 IO 密集任务；CPU 密集可换 ProcessPoolExecutor 进程池。
# 运行命令：python3 python/14_concurrency.py
# 预期输出（关键行）：
#   1) threading+Lock：4 线程各加 10000 次，counter = 40000
#   2) ThreadPoolExecutor.map：['<a 的响应>', '<b 的响应>', '<c 的响应>']
#   3) asyncio.gather：A 醒来；B 醒来

import asyncio
import threading
import time
from concurrent.futures import ThreadPoolExecutor

# 1) threading + Lock：多线程共享可变状态必须加锁，否则会出现竞态条件
counter = 0
lock = threading.Lock()

def add_many(times: int) -> None:
    global counter
    for _ in range(times):
        with lock:                 # with 块自动加锁/释放，比手动 acquire/release 稳妥
            counter += 1

threads = [threading.Thread(target=add_many, args=(10_000,)) for _ in range(4)]
for t in threads:
    t.start()
for t in threads:                  # join 等待全部结束
    t.join()
print(f"1) threading+Lock：4 线程各加 10000 次，counter = {counter}")

# 2) concurrent.futures：线程池并发出结果（适合网络请求等 IO 型任务）
def fetch(url: str) -> str:
    time.sleep(0.01)               # 模拟一次网络往返
    return f"<{url} 的响应>"

with ThreadPoolExecutor(max_workers=4) as pool:
    results = list(pool.map(fetch, ["a", "b", "c"]))   # map 按传入顺序返回结果
print(f"2) ThreadPoolExecutor.map：{results}")

# 3) asyncio：单线程事件循环调度协程；await 处把控制权交还事件循环
async def nap(name: str, seconds: float) -> str:
    await asyncio.sleep(seconds)   # 非阻塞等待（time.sleep 会卡住整个循环）
    return f"{name} 醒来"

async def main() -> None:
    # gather 并发执行多个协程，结果按传入顺序返回
    first, second = await asyncio.gather(nap("A", 0.02), nap("B", 0.01))
    print(f"3) asyncio.gather：{first}；{second}")
    single = await nap("C", 0)     # 单独 await 一个协程
    print(f"   单独 await：{single}")

asyncio.run(main())                # 创建事件循环并运行至结束
print("asyncio 事件循环结束，全部演示完成")
