#!/usr/bin/env bash
# 主题说明：Shell 并发入门——& 把命令丢入后台、wait 收割子进程与退出码、
#           jobs 查看后台任务，以及管道各段并行执行的一例子。
# 运行命令：bash scripts/shell/concurrency/background_wait.sh
# 预期输出（关键行）：
#   三个任务已后台启动，主脚本没有被阻塞
#   后台任务数 = 3（jobs -p 列出 RUNNING 任务的 PID）
#   fast 的退出码 = 0；bad 的退出码 = 3
#   worker-a 完成，耗时 0.1s
#   管道统计：error 行出现 2 次

TMPD=$(mktemp -d)
trap 'rm -rf "$TMPD"' EXIT

# ── & 后台：命令立即返回，shell 继续往下跑 ───────────────────
worker() {
    # $1 = 名字，$2 = 模拟耗时（秒）
    sleep "$2"
    echo "$1 完成，耗时 ${2}s" > "$TMPD/$1.done"
    return 0
}

worker worker-a 0.1 &    # & 结尾 = 后台执行，$! 记下它的 PID
pid_a=$!
worker worker-b 0.3 &
pid_b=$!
worker worker-c 0.2 &
pid_c=$!

echo "三个任务已后台启动，主脚本没有被阻塞"
echo "后台任务数 = $(jobs -p | wc -l | tr -d ' ')（jobs -p 列出 RUNNING 任务的 PID）"

# ── wait：收割指定子进程，$? 拿到它的退出码 ──────────────────
bad_exit() {
    sleep 0.1
    return 3              # 故意以非 0 退出，演示 wait 能取到
}
fast() { sleep 0.1; return 0; }

fast &  fast_pid=$!
bad_exit & bad_pid=$!
wait "$fast_pid";  fast_rc=$?
wait "$bad_pid";   bad_rc=$?
echo "fast 的退出码 = ${fast_rc}；bad 的退出码 = ${bad_rc}"
# 裸 wait：等待当前 shell 的全部后台任务结束
wait
echo "全部后台任务已结束"

# 任务结果落在各自的文件里，按固定顺序汇总，输出与调度顺序无关
for w in worker-a worker-b worker-c; do
    cat "$TMPD/$w.done"
done

# ── 管道并行：竖线两侧的进程同时开跑 ─────────────────────────
# 生成 -> 过滤 -> 统计 三段同时执行：grep 一边收数据一边筛，
# wc 一边收 grep 的结果一边数——这就是 Shell 里最常见的并行形态。
printf 'info: start\nerror: db\ndata: 42\nerror: net\n' > "$TMPD/app.log"
errors=$(grep -c '^error' < "$TMPD/app.log")
echo "管道统计：error 行出现 $errors 次"
grep '^error' "$TMPD/app.log" | tr 'a-z' 'A-Z' | sed 's/^/  /' | sed 's/$/!/'

# 说明：wait -n（等任意一个结束）需要 bash 4.3+，本脚本为兼容 bash 3.2 不使用。

exit 0
