/*
 * 主题说明：C 运算符与表达式 —— 算术（整数相除向零截断）、位运算、自增自减（前置/后置）、
 *           条件（三目）表达式、逻辑短路、复合赋值与运算符优先级陷阱。
 * 运行命令：./c/build/bin/operator_operator_basics
 * 预期输出（关键行）：
 *   7 + 3 * 2 = 13（* 高于 +）
 *   7 / 2 = 3，7 % 2 = 1，-7 / 2 = -3（C99 起整数除法向零截断）
 *   0x0F & 0x3C = 0xc(12)，0x0F | 0x3C = 0x3f(63)，0x0F ^ 0x3C = 0x33(51)
 *   ~0x0F = 0xfffffff0(4294967280)，0x0F << 2 = 60，0x3C >> 2 = 15
 *   i++ 表达式取旧值 5，之后 i = 6；++i 表达式取新值 7
 *   最大值: 9（a > b ? a : b）
 *   短路: check(0) && check(1) = false 后 check 调用次数 = 1（右侧未求值）
 *   1 << 2 + 1 = 8（+ 高于 <<，等价 1<<(2+1)）
 *   陷阱: x & 3 == 3 解析为 x & (3 == 3)，x=5 时得 1；(x & 3) == 3 才得 0
 */

#include <stdio.h>

/* 供短路演示：带副作用的检查函数，统计自己被调用的次数 */
static int call_count = 0;

static int check(int v) {
    call_count = call_count + 1;
    return v != 0;
}

static void demo_arithmetic(void) {
    printf("=== 算术运算 ===\n");
    printf("7 + 3 * 2 = %d（* 高于 +）\n", 7 + 3 * 2);
    printf("7 / 2 = %d，7 %% 2 = %d，-7 / 2 = %d（C99 起整数除法向零截断）\n",
           7 / 2, 7 % 2, -7 / 2);
    printf("7.0 / 2 = %.2f（任一操作数为浮点则按浮点除）\n", 7.0 / 2);

    int x = 10;
    x += 5;                            /* 复合赋值：等价 x = x + 5 */
    printf("复合赋值: 10 += 5 → %d\n", x);
}

static void demo_bitwise(void) {
    printf("\n=== 位运算（按 unsigned int 演示） ===\n");
    unsigned int a = 0x0F;             /* 0000 1111 */
    unsigned int b = 0x3C;             /* 0011 1100 */
    printf("0x0F & 0x3C = 0x%x(%u)，0x0F | 0x3C = 0x%x(%u)，0x0F ^ 0x3C = 0x%x(%u)\n",
           a & b, a & b, a | b, a | b, a ^ b, a ^ b);
    printf("~0x0F = 0x%x(%u)（按位取反，无符号回绕后为“最大值-a”）\n",
           ~a, ~a);
    printf("0x0F << 2 = %u（左移一位相当于 ×2），0x3C >> 2 = %u（右移一位相当于 ÷2）\n",
           a << 2, b >> 2);
}

static void demo_increment(void) {
    printf("\n=== 自增自减 ===\n");
    int i = 5;
    int old = i++;                     /* 后置：表达式返回旧值，i 再加 1 */
    printf("i++ 表达式取旧值 %d，之后 i = %d\n", old, i);
    printf("++i 表达式取新值 %d\n", ++i);
}

static void demo_conditional(void) {
    printf("\n=== 条件（三目）表达式 ===\n");
    int a = 5, b = 9;
    printf("最大值: %d（a > b ? a : b）\n", a > b ? a : b);
    int score = 72;
    char grade = score >= 90 ? 'A' : (score >= 60 ? 'C' : 'F');  /* 右结合，可嵌套 */
    printf("score=%d → grade=%c（嵌套三目模拟简单分级）\n", score, grade);
}

static void demo_short_circuit(void) {
    printf("\n=== 逻辑与短路 ===\n");
    call_count = 0;
    int r1 = check(0) && check(1);     /* check(0) 为假，右侧不再求值 */
    printf("短路: check(0) && check(1) = %s 后 check 调用次数 = %d（右侧未求值）\n",
           r1 ? "true" : "false", call_count);
    call_count = 0;
    int r2 = check(2) || check(0);     /* check(2) 为真，右侧不再求值 */
    printf("短路: check(2) || check(0) = %s 后 check 调用次数 = %d\n",
           r2 ? "true" : "false", call_count);
}

static void demo_precedence(void) {
    printf("\n=== 优先级陷阱 ===\n");
    printf("1 << (2 + 1) = %d（+ 高于 <<，故 1 << 2 + 1 等价 1<<(2+1)）\n",
           1 << (2 + 1));
    printf("(1 << 2) + 1 = %d（加括号才能表达“先移位再加”）\n", (1 << 2) + 1);

    int x = 5;                         /* 二进制 0101：x & 3 = 1，不等于 3 */
    printf("陷阱: x & 3 == 3 实际按 x & (3 == 3) 解析，x=5 时得 %d；(x & 3) == 3 才得 %d\n",
           x & (3 == 3), (x & 3) == 3);
    /* 经验：位运算与比较运算混用时，永远给位运算加括号 */
}

int main(void) {
    printf("C 运算符与表达式示例\n");
    printf("==========================================\n\n");

    demo_arithmetic();
    demo_bitwise();
    demo_increment();
    demo_conditional();
    demo_short_circuit();
    demo_precedence();

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
