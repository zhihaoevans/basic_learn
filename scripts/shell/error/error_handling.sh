#!/usr/bin/env bash
# 主题说明：Shell 错误处理——退出码约定（0 成功 / 非 0 失败）、$? 判断、
#           2>/dev/null 丢弃 stderr、|| 提供兜底值、trap ERR 捕获失败点，以及 set -e 的行为说明。
# 运行命令：bash scripts/shell/error/error_handling.sh
# 预期输出（关键行）：
#   /no/such/file 的退出码 = 1（stderr 已被 2>/dev/null 吞掉）
#   兜底值 = (文件不存在，用默认值)
#   trap ERR 捕获：第 39 行附近的命令失败，退出码 1
#   子 shell 内 set -e：false 之后的内容不会执行

# ── 约定：0 = 成功，非 0 = 失败 ────────────────────────────────
# 常见约定：1 通用错误，2 用法错误，126 无执行权限，127 命令找不到；
# 自己的脚本尽量用 1-125，且「最后一条命令决定整个脚本的退出码」。
true
echo "true 的退出码 = $?"
false
echo "false 的退出码 = $?"

# ── 2>/dev/null：把标准错误扔进「黑洞」 ───────────────────────
# 命令仍会失败（退出码非 0），只是不再向终端打印报错
if cat /no/such/file 2>/dev/null; then
    echo "不会走到这里"
else
    echo "/no/such/file 的退出码 = $?（stderr 已被 2>/dev/null 吞掉）"
fi

# ── || 兜底：失败时给默认值 ───────────────────────────────────
content=$(cat /no/such/file 2>/dev/null) || content="(文件不存在，用默认值)"
echo "兜底值 = $content"
value=$(grep -c '^root:' /etc/passwd 2>/dev/null) || value=0
echo "/etc/passwd 中 root 行数 = $value"

# ── trap ERR：命令失败时自动执行处理函数 ──────────────────────
err_report() {
    echo "trap ERR 捕获：第 ${1} 行附近的命令失败，退出码 ${2}" >&2
}
trap 'err_report "$LINENO" "$?"' ERR

cat /no/such/file 2>/dev/null    # 故意失败一次，触发上面的 ERR trap

trap - ERR                       # 演示完就摘掉，避免后续干扰

# ── set -e：遇错即退（在子 shell 里演示，不影响本脚本继续运行）──
# set -e 让任何非条件位置上的失败命令直接终止脚本；但它不作用于
# if/while 条件、&& || 右侧、管道非末尾段，因此仍要显式检查关键步骤。
(
    set -e
    echo "子 shell 内 set -e：false 之后的内容不会执行"
    false
    echo "这一行永远到不了"
)
echo "子 shell 的退出码 = $?（set -e 使其在 false 处提前退出）"

# ── 实战形态：检查关键步骤，失败则带明确退出码终止 ─────────────
need_file() {
    if [ ! -f "$1" ]; then
        echo "错误：文件不存在：$1" >&2
        return 2              # 用法/输入错误约定为 2
    fi
    return 0
}
if need_file /etc/hosts; then
    echo "/etc/hosts 存在，继续处理"
fi

exit 0                         # 脚本主动声明成功退出
