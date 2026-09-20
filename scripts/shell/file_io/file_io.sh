#!/usr/bin/env bash
# 主题说明：Shell 文件读写——重定向 > 覆盖 / >> 追加 / 2>/dev/null、
#           cat 写文件、here-doc 生成整段文本、read 逐行读取，以及 /dev/null 的用途。
# 运行命令：bash scripts/shell/file_io/file_io.sh
# 预期输出（关键行）：
#   --- notes.txt 的内容（4 行）---
#   读取文件：第 2 行 -> 追加不会覆盖已有内容
#   行数统计 = 4（其中 apple 出现 2 次）

# 所有示例文件都放进 mktemp 建立的临时目录，脚本退出时用 trap 清理，
# 不在仓库里留下任何垃圾文件。
TMPDIR_WORK=$(mktemp -d)
trap 'rm -rf "$TMPDIR_WORK"' EXIT
f="$TMPDIR_WORK/notes.txt"

# ── > 覆盖写：每次都从文件头部重写 ───────────────────────────
echo "第一行：> 每次覆盖整个文件" > "$f"
echo "第二行：又来了" > "$f"           # 覆盖！文件里只剩这一行
echo "--- > 连写两次后，文件只剩 1 行 ---"
cat "$f"

# ── >> 追加写：在文件末尾续行 ────────────────────────────────
echo "追加不会覆盖已有内容" >> "$f"
echo "--- >> 追加一次后 ---"
cat "$f"

# ── here-doc：一次性写入整段文本（分隔符 EOF 加引号可禁止变量展开）──
cat >> "$f" <<'EOF'
here-doc 整段写入：第 1 行
here-doc 整段写入：第 2 行
EOF

echo "--- notes.txt 的内容（$(( $(wc -l < "$f") )) 行）---"
cat "$f"

# ── read 逐行读取：while read 循环是 Shell 处理文件的标准姿势 ──
# -r 禁止反斜杠转义；< "$f" 把文件接到循环的标准输入
n=0
while IFS= read -r line; do
    n=$(( n + 1 ))
    echo "读取文件：第 $n 行 -> $line"
done < "$f"

# read -a 还能把一行按空白拆成数组（类似 cut 的效果）
echo "one two three" > "$TMPDIR_WORK/row.txt"
read -ra fields < "$TMPDIR_WORK/row.txt"
echo "read -a 拆分：字段数 = ${#fields[@]}，第 2 个 = ${fields[1]}"

# ── /dev/null：丢弃输出 / 提供空输入 ─────────────────────────
ls /no/such/path 2>/dev/null            # stderr 进黑洞，报错不再打印
: < /dev/null                           # 读空文件的标准写法
echo "/dev/null 的字节数 = $(wc -c < /dev/null | tr -d ' ')"   # 永远是 0

# ── 综合统计：管道 + 重定向组合 ───────────────────────────────
printf '%s\n' apple banana cherry apple > "$TMPDIR_WORK/fruits.txt"
count=$(grep -c apple < "$TMPDIR_WORK/fruits.txt" | tr -d ' ')   # < 显式重定向输入
lines=$(wc -l < "$TMPDIR_WORK/fruits.txt" | tr -d ' ')           # BSD 的 wc 输出带前导空格，用 tr 清掉
echo "行数统计 = ${lines}（其中 apple 出现 ${count} 次）"

# trap EXIT 已注册清理：此处无需手动 rm
echo "临时目录将由 trap EXIT 自动清理：$TMPDIR_WORK"

exit 0
