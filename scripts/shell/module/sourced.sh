#!/usr/bin/env bash
# 主题说明：被 source 的「模块」文件——只定义函数与变量，不主动执行任务；
#           被 source 时不运行自测，被直接执行时跑一段自测并退出 0。
# 运行命令：bash scripts/shell/module/sourced.sh   （直接运行 = 执行自测）
#           在其他脚本中：source "$(dirname ...)/sourced.sh"（引入定义）
# 预期输出（关键行）：
#   [sourced.sh 自测] module_greet(shell) = hello, shell
#   [sourced.sh 自测] add3(1, 2, 3) = 6
#   [sourced.sh 自测] MODULE_NAME = shell-module

# ── 模块对外提供的变量（source 后即可直接使用）────────────────
MODULE_NAME="shell-module"
MODULE_VERSION="1.0"

# ── 模块对外提供的函数 ────────────────────────────────────────
module_greet() {
    # 取第一个参数，未传则用参数扩展给默认值
    echo "hello, ${1:-world}"
}

add3() {
    echo $(( $1 + $2 + $3 ))
}

# 模块内部细节：调用方看不到也无需关心的辅助约定（Shell 没有真正的
# private，靠命名约定 _ 前缀表示「内部函数，请勿外部调用」）
_format_version() {
    echo "v${MODULE_VERSION}"
}

module_banner() {
    echo "[$MODULE_NAME $(_format_version)]"
}

# ── 自测段：只有被「直接执行」时才运行 ────────────────────────
# BASH_SOURCE[0] 是本文件路径；等于 $0 说明是被直接执行的，
# 否则说明是被 source 的——此时应保持沉默，只留下定义。
if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
    echo "[sourced.sh 自测] module_greet(shell) = $(module_greet shell)"
    echo "[sourced.sh 自测] add3(1, 2, 3) = $(add3 1 2 3)"
    echo "[sourced.sh 自测] MODULE_NAME = $MODULE_NAME"
    echo "[sourced.sh 自测] banner = $(module_banner)"
    exit 0                       # 只有直接执行时才 exit；source 时 exit 会连累引入方
fi

# 被 source 的执行路径到这里就结束：只留下定义，不做任何其他事。
