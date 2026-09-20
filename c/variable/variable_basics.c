/*
 * 主题说明：C 变量、常量与基本类型 —— 基本类型的声明与初始化、sizeof 求类型宽度、
 *           const（运行期只读变量）与 #define（预处理宏）的区别、隐式/显式类型转换与整型溢出。
 * 运行命令：./c/build/bin/variable_variable_basics
 * 预期输出（关键行）：
 *   char=1 short=2 int=4 long=8 "long long"=8 float=4 double=8 bool=1 size_t=8
 *   int 范围: [-2147483648, 2147483647]，UINT_MAX = 4294967295
 *   MAX_BUF=512（#define 宏），max_buf=512（const 变量）
 *   隐式转换: code = 65（char 'A' 提升为 int），i + d = 15.5（int 提升为 double）
 *   显式转换: (double)7 / 2 = 3.50，(int)3.99 = 3（向零截断）
 *   无符号回绕: 4294967295 + 1 = 0（无符号运算是模 2^32，行为有定义）
 */

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* #define：预处理阶段做纯文本替换——无类型、无作用域、不可取地址 */
#define MAX_BUF 512

/* const：运行期只读变量——有类型、遵守作用域、可取地址（更推荐） */
static const int max_buf = 512;

/* 基本类型与 sizeof：sizeof 返回 size_t，必须用 %zu 打印 */
static void demo_types(void) {
    printf("=== 基本类型与 sizeof ===\n");
    printf("char=%zu short=%zu int=%zu long=%zu \"long long\"=%zu float=%zu double=%zu bool=%zu size_t=%zu\n",
           sizeof(char), sizeof(short), sizeof(int), sizeof(long),
           sizeof(long long), sizeof(float), sizeof(double),
           sizeof(bool), sizeof(size_t));

    int big = 2147483647;              /* 即 INT_MAX */
    printf("int 范围: [%d, %d]，UINT_MAX = %u\n", INT_MIN, INT_MAX, UINT_MAX);
    printf("big = %d\n", big);

    bool ok = true;                    /* C99 起 stdbool.h 提供 bool/true/false */
    printf("bool ok = %s（C99 前用 int 0/1 表示真假）\n", ok ? "true" : "false");
}

/* const 与 #define 对比 */
static void demo_const(void) {
    printf("\n=== const 与 #define ===\n");
    printf("MAX_BUF=%d（#define 宏），max_buf=%d（const 变量）\n", MAX_BUF, max_buf);
    printf("const 变量可取地址: &max_buf = %p；宏没有地址\n", (void *)&max_buf);
    /* 常见约定：数组长度这类编译期常量用 #define 或 enum；有类型的只读量用 const */
}

/* 隐式转换（编译器自动进行）与显式转换（程序员写强制类型转换） */
static void demo_conversion(void) {
    printf("\n=== 类型转换 ===\n");
    char c = 'A';
    int code = c;                      /* 隐式转换：char 提升为 int */
    printf("隐式转换: code = %d（char 'A' 提升为 int）\n", code);

    int i = 7;
    double d = 8.5;
    printf("隐式转换: i + d = %.1f（int 提升为 double）\n", i + d);

    printf("显式转换: (double)7 / 2 = %.2f（先转 double 再相除，保留小数）\n",
           (double)i / 2);
    printf("整数相除: 7 / 2 = %d（两个 int 相除直接截断小数）\n", i / 2);
    printf("显式转换: (int)3.99 = %d（浮点转整型向零截断，不是四舍五入）\n",
           (int)3.99);
}

/* 溢出：无符号运算是模运算（有定义）；有符号溢出是未定义行为，只能在注释里说明 */
static void demo_overflow(void) {
    printf("\n=== 整型溢出 ===\n");
    unsigned int u = UINT_MAX;
    printf("无符号回绕: %u + 1 = %u（无符号运算是模 2^32，行为有定义）\n",
           u, u + 1);
    /*
     * 注意：有符号整型溢出（如 INT_MAX + 1）是“未定义行为”——
     * 编译器可以生成任何结果，不能拿来演示，也不可依赖其“回绕”。
     * 用 UBSan 可检测这类问题，见 c/sanitizers/ 目录。
     */
}

int main(void) {
    printf("C 变量、常量与基本类型示例\n");
    printf("==========================================\n\n");

    demo_types();
    demo_const();
    demo_conversion();
    demo_overflow();

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
