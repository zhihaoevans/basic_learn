/*
 * 主题说明：C 函数 —— 原型（先声明后使用）与定义分离、static 函数仅本文件可见、
 *           值传递与指针传递、递归，以及函数指针入门（赋值、调用、作参数传递）。
 * 运行命令：./c/build/bin/function_function_basics
 * 预期输出（关键行）：
 *   add(3, 4) = 7，mul(6, 7) = 42
 *   值传递：函数内已交换为 a=2, b=1；返回后调用方 x=1, y=2（交换的是副本）
 *   指针传递：交换后调用方 x=2, y=1（通过地址修改了原变量）
 *   递归：5! = 120，fib(10) = 55
 *   函数指针：op(3, 4) = 7，apply(mul, 6, 7) = 42
 */

#include <stdio.h>

/* ---- 原型（prototype）：先声明签名，实现可以放在后面甚至别的文件 ---- */
static int  add(int a, int b);
static int  mul(int a, int b);
static void swap_by_value(int a, int b);
static void swap_by_ptr(int *a, int *b);
static unsigned long factorial(unsigned int n);
static long fib(int n);
static int  apply(int (*op)(int, int), int x, int y);

static void demo_prototype(void) {
    printf("=== 原型与定义 ===\n");
    printf("add(3, 4) = %d，mul(6, 7) = %d\n", add(3, 4), mul(6, 7));
    /*
     * 本文件所有函数都加了 static：仅本编译单元（.c 文件）可见，避免与其他
     * 文件的同名函数冲突。跨文件共享的函数不加 static，并把原型放进头文件
     * （extern 可见性），详见 c/module/ 主题。
     */
}

static void demo_params(void) {
    printf("\n=== 值传递 vs 指针传递 ===\n");
    int x = 1, y = 2;
    swap_by_value(x, y);               /* C 的参数一律按值复制，指针传的是“地址值” */
    printf("返回后调用方 x=%d, y=%d（交换的是副本）\n", x, y);
    swap_by_ptr(&x, &y);
    printf("指针传递：交换后调用方 x=%d, y=%d（通过地址修改了原变量）\n", x, y);
}

static void demo_recursion(void) {
    printf("\n=== 递归 ===\n");
    printf("递归：5! = %lu，fib(10) = %ld\n", factorial(5), fib(10));
    /* 递归必须有终止条件（n <= 1）；无界递归会栈溢出 */
}

static void demo_function_pointer(void) {
    printf("\n=== 函数指针入门 ===\n");
    int (*op)(int, int) = add;         /* 声明并初始化：函数名就是函数地址 */
    printf("函数指针：op(3, 4) = %d，apply(mul, 6, 7) = %d\n",
           op(3, 4), apply(mul, 6, 7));
    op = mul;                          /* 可重新指向同签名的其他函数 */
    printf("改指向后 op(3, 4) = %d\n", op(3, 4));
    /* 函数指针是 C 实现“回调/多态”的基础，struct+函数指针模拟面向对象见 c/oop/ */
}

/* ---- 定义（definition）：函数的实际实现 ---- */

static int add(int a, int b) {
    return a + b;
}

static int mul(int a, int b) {
    return a * b;
}

static void swap_by_value(int a, int b) {
    int t = a;
    a = b;
    b = t;
    printf("值传递：函数内已交换为 a=%d, b=%d；", a, b);
}

static void swap_by_ptr(int *a, int *b) {
    int t = *a;                        /* * 解引用：访问指针指向的变量 */
    *a = *b;
    *b = t;
}

static unsigned long factorial(unsigned int n) {
    if (n <= 1) {
        return 1;                      /* 终止条件 */
    }
    return (unsigned long)n * factorial(n - 1);
}

static long fib(int n) {
    if (n < 2) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

static int apply(int (*op)(int, int), int x, int y) {
    return op(x, y);                   /* 把函数当参数传入：回调的基本形态 */
}

int main(void) {
    printf("C 函数示例\n");
    printf("==========================================\n\n");

    demo_prototype();
    demo_params();
    demo_recursion();
    demo_function_pointer();

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
