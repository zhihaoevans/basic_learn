#!/usr/bin/env bash
# 主题说明：Shell 函数——定义与调用的两种写法、函数内位置参数（$1/$#/$@）、
#           local 局部变量，以及「return 返回状态码」与「echo 输出数据」两条通道的区别。
# 运行命令：bash scripts/shell/function/function_basics.sh
# 预期输出（关键行）：
#   3 + 4 = 7
#   greet(Haskell) = hello, Haskell
#   两数相加：5 + 6 = 11

# 定义方式一：function 关键字（函数体花括号可省略 body 部分，但推荐完整写）
function add {
    # $1 $2 是「调用函数时」传进来的位置参数，与脚本级的 $1 互不影响
    echo "$1 + $2 = $(( $1 + $2 ))"
}

# 定义方式二：C 风格括号（两种完全等价，同一个仓库里统一用一种即可）
sub() {
    echo "$1 - $2 = $(( $1 - $2 ))"
}

# 调用函数不需要括号：空格分隔传参
add 3 4
sub 10 4

# return 只返回 0-255 的「退出状态码」（0 表示成功），用来表达成败而不是数据
is_even() {
    if (( $1 % 2 == 0 )); then
        return 0        # 0 = 真/成功
    else
        return 1        # 非 0 = 假/失败
    fi
}

if is_even 10; then
    echo "10 是偶数（return 0 被当真）"
fi

# $? 保存「上一条命令/函数」的退出状态码
is_even 7
echo "is_even 7 的退出码 \$? = $?"

# 要「返回数据」就往 stdout echo，调用方用命令替换 $() 接住
greet() {
    echo "hello, $1"
}
msg=$(greet "Haskell")
echo "greet(Haskell) = $msg"

# local：让变量只在函数内可见，避免覆盖同名的全局变量（不用 local 就是全局赋值）
counter_demo() {
    local inner=99      # 函数局部，函数返回后消失
    outer=7             # 未用 local，会修改/创建全局变量
    echo "函数内：inner=$inner outer=$outer"
}
counter_demo
echo "函数外：outer=${outer}（泄漏成全局）；inner=${inner:-未定义}"

# 综合练习：函数接两个参数、echo 返回结果、调用方检查 $? 判断成功与否
sum2() {
    if [ "$#" -ne 2 ]; then
        echo "参数数量错误" >&2   # 错误信息走 stderr
        return 1
    fi
    echo $(( $1 + $2 ))
    return 0
}

if result=$(sum2 5 6); then
    echo "两数相加：5 + 6 = $result"
fi

# 函数同样支持 "$@" 逐个遍历参数
show_args() {
    for a in "$@"; do
        echo "参数：$a"
    done
}
show_args x y z

exit 0
