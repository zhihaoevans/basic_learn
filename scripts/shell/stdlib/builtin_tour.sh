#!/usr/bin/env bash
# 主题说明：Shell 常用内建命令速览——test 与 [[ ]] 的写法差异、
#           参数扩展默认值 ${var:-default} 系列、cd 与 pushd/popd 目录切换、getopts 解析选项。
# 运行命令：bash scripts/shell/stdlib/builtin_tour.sh
# 预期输出（关键行）：
#   [ ] 与 [[ ]] 判定一致：两个字符串相等
#   正则捕获年份：2024
#   未设置时取默认值：EDITOR = vi
#   目录栈当前有 3 个条目（dirs -v 可查看）
#   getopts 解析：name = Alice，verbose = on

TMPD=$(mktemp -d)
trap 'rm -rf "$TMPD"' EXIT

# ── test（即 [ ]）与 [[ ]]：同一件事的两种写法 ────────────────
a="hello"
b="hello"
# 传统写法：[ ] 是普通命令，变量必须加引号防止分词/通配
if [ "$a" = "$b" ] && [ -n "$a" ]; then
    echo "[ ] 判定：a 与 b 相等且非空"
fi
# 现代写法：[[ ]] 是 shell 语法关键字，不加引号也安全，还支持 && || 和正则
if [[ $a == "$b" && -n $a ]]; then
    echo "[ ] 与 [[ ]] 判定一致：两个字符串相等"
fi
# [[ ]] 的 =~ 正则匹配（匹配结果存入 BASH_REMATCH）
if [[ "release-2024.09" =~ ^release-([0-9]{4}) ]]; then
    echo "正则捕获年份：${BASH_REMATCH[1]}"
fi

# ── 参数扩展：不碰外部命令就能加工变量 ───────────────────────
unset EDITOR
echo "未设置时取默认值：EDITOR = ${EDITOR:-vi}"    # :- 只读取，不赋值
echo "取默认并赋值：EDITOR = ${EDITOR:=nano}"       # := 会顺带把值赋回去
echo "已设置时输出替代标记：EDITOR = ${EDITOR:+（已设置为 nano）}"
echo "字符串长度：'hello' = ${#a}"
path="/usr/local/bin/bash"
echo "去最短前缀：${path#*/}"                       # usr/local/bin/bash
echo "去最短后缀：${path##*/}"                      # bash
echo "替换一次：${path/local/opt}"                  # /usr/opt/bin/bash
echo "替换全部：${path//\//_}"                      # _usr_local_bin_bash... 前导 / 也会被替换
file="report.tar.gz"
echo "去扩展名：${file%.*}"                         # report.tar（% 只去最后一段）

# ── cd 与 pushd/popd：目录切换的两种姿态 ──────────────────────
echo "起始目录：$PWD"
pushd "$TMPD" >/dev/null            # pushd 会打印目录栈，重定向到黑洞保持输出干净
echo "pushd 切到临时目录后：PWD = $PWD"
pushd /tmp >/dev/null               # 再压一层
echo "目录栈当前有 $(dirs -p | wc -l | tr -d ' ') 个条目（dirs -v 可查看）"
popd >/dev/null                     # 弹回上一层
echo "popd 回到：$PWD"
popd >/dev/null
echo "再 popd 回到出发点：$PWD"

# cd 系：cd - 表示「回到上一个目录」，它自己会打印目标路径（这里静音处理）
cd /tmp
echo "cd /tmp 后：$PWD"
cd - >/dev/null
echo "cd - 回到上一个目录：$PWD"

# ── getopts：解析 -n 名字 / -v 开关 这类短选项 ───────────────
parse_args() {
    local opt
    OPTIND=1                        # 复位：防止函数被多次调用时残留状态
    NAME="anonymous"
    VERBOSE=off
    while getopts ":n:vh" opt; do   # 首个冒号 = 静默错误模式；n: 表示 n 带参数
        case $opt in
            n) NAME="$OPTARG" ;;
            v) VERBOSE=on ;;
            h) echo "用法：$0 [-n 名字] [-v]"; return 0 ;;
            \?) echo "未知选项：-$OPTARG" >&2; return 1 ;;
            :)  echo "选项 -$OPTARG 缺少参数" >&2; return 1 ;;
        esac
    done
}
parse_args -n Alice -v
echo "getopts 解析：name = ${NAME}，verbose = ${VERBOSE}"

# ── 其他高频内建一句话示范 ───────────────────────────────────
echo "type 揭穿命令真身：type 类型 = $(type -t type)"
echo "basename：$(basename /a/b/c.txt)　dirname：$(dirname /a/b/c.txt)"
printf 'seq 风格计数：'; for i in 1 2 3; do printf ' %s' "$i"; done; echo

exit 0
