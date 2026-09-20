#!/usr/bin/env bash
# 主题说明：Shell 的「模块」机制——source 与直接执行的本质区别、
#           被 source 文件提供函数与变量、(…) 子 shell 的隔离作用、export 的跨进程可见性。
# 运行命令：bash scripts/shell/module/module_source.sh
# 预期输出（关键行）：
#   source 后可直接调用：module_greet(shell) = hello, shell
#   直接执行后 CHILD_ONLY = 未定义
#   source 之后 CHILD_ONLY = set-in-child
#   子进程看到 EXPORTED=visible-to-children；NOT_EXPORTED=看不到

# 定位同目录的模块文件：无论从哪个工作目录启动脚本都能找到
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# ── source 引入模块：函数与变量进入「当前」shell，可直接调用 ──
source "$SCRIPT_DIR/sourced.sh"
echo "source 后可直接调用：module_greet(shell) = $(module_greet shell)"
echo "source 后模块变量可见：MODULE_NAME = $MODULE_NAME"
module_banner

# ── source vs 直接执行：用临时脚本做对照实验 ─────────────────
TMP=$(mktemp)
trap 'rm -f "$TMP"' EXIT
cat > "$TMP" <<'EOF'
CHILD_ONLY="set-in-child"
echo "  （临时脚本自己说：CHILD_ONLY=${CHILD_ONLY}）"
EOF

echo "--- 1) bash 直接执行：新开子进程，赋值不影响本进程 ---"
bash "$TMP"
echo "直接执行后 CHILD_ONLY = ${CHILD_ONLY:-未定义}"

echo "--- 2) source 执行：在当前 shell 逐行跑，变量留了下来 ---"
source "$TMP"
echo "source 之后 CHILD_ONLY = $CHILD_ONLY"

# ── (…) 子 shell 隔离：括号内的赋值/操作一出门就消失 ─────────
(
    ISOLATED=1
    echo "子 shell 内：ISOLATED=$ISOLATED"
)
echo "子 shell 外：ISOLATED=${ISOLATED:-未定义}"

# ── export 可见性：导出后才传给子进程 ────────────────────────
NOT_EXPORTED="only-here"       # 普通 Shell 变量：只属于当前进程
EXPORTED="visible-to-children" # export 后进入环境，子进程可见
export EXPORTED
bash -c 'echo "子进程看到 EXPORTED=${EXPORTED}；NOT_EXPORTED=${NOT_EXPORTED:-看不到}"'

# 结论：Shell 变量天生是全局的，可见性靠三层控制——
#   函数内 local（函数级）、(…) 子 shell（进程内隔离）、export（跨进程传递）。

exit 0
