#!/usr/bin/env bash
# 主题说明：Shell 的第一个程序——shebang 行的作用、echo 与 printf 的区别、
#           三种注释写法，以及脚本的几种运行方式。
# 运行命令：bash scripts/shell/hello/hello.sh
# 预期输出（关键行）：
#   hello, world
#   printf 不自动换行|接着上一行
#   编号：a 值：1
#   编号：b 值：2

# shebang（#!）写在这里只对「./hello.sh 直接执行」生效：内核据此选择解释器；
# 用「bash hello.sh」运行时 shebang 只是被当作注释跳过，解释器由命令本身决定。
# 本行是单行注释：Shell 里注释以 # 开头，没有独立的多行注释语法。

# echo：自动换行、参数原样拼接，适合打印简单信息
echo "hello, world"

# printf：格式化输出，不自动换行（行尾的 | 用来展示光标停在原处）
printf "printf 不自动换行|"
printf "接着上一行\n"

# printf 的格式串会被循环利用：参数多于占位符时按组重复格式
printf "编号：%s 值：%d\n" a 1 b 2

# 多行内容也可以用 here-doc + cat 当作「块注释」输出或丢弃：
: <<'NOTE'
这一段位于 here-doc 中，: 是什么都不做的内建命令，
因此整段文字不会被执行，也不会输出（常用于临时禁用一段代码）。
NOTE

echo "--- 脚本的三种运行方式（注释说明，见头注释预期输出）---"
echo "运行方式 1：bash hello.sh（新开 bash 进程执行，最常用）"
echo "运行方式 2：chmod +x hello.sh && ./hello.sh（靠 shebang 找解释器）"
echo "运行方式 3：source hello.sh（在当前 shell 中执行，变量会留下来）"

exit 0
