/*
 * 主题说明：C 模块的“实现文件”—— util.c 定义 util.h 声明的函数与 extern 变量，
 *           并用 static 把辅助函数限制在本文件内（对外不可见）。
 * 运行命令：./c/build/bin/module_util
 * 预期输出（关键行）：
 *   util.c 自测: max(-3, 7) = 7
 *   util.c 自测: pow(2, 10) = 1024
 *   util.c 自测: util_call_count = 2（每次调用公共函数各计 1 次）
 */

#include <stdio.h>

#include "util.h"

/* extern 可见变量的定义（全程序仅此一份）：其他编译单元经 util.h 的声明访问它 */
int util_call_count = 0;

/*
 * static 函数：文件私有。头文件里没有它的声明，
 * 其他编译单元既看不到也无法调用——这就是 C 的“隐藏实现细节”。
 */
static long mul_add(long acc, int m, int addend) {
    return acc * m + addend;
}

int util_max(int a, int b) {
    util_call_count++;                 /* 记录模块被使用的次数 */
    return a > b ? a : b;
}

long util_pow(int base, unsigned int exp) {
    util_call_count++;
    long result = 1;
    for (unsigned int i = 0; i < exp; i++) {
        result = mul_add(result, base, 0);  /* 内部使用私有函数 */
    }
    return result;
}

/*
 * 自测 main：本仓库 CMake 把每个 .c 编成独立可执行文件（目录_文件 命名），
 * util.c 单独成 target 时必须自带 main 才能构建、运行并以退出码 0 通过 CI。
 * module_demo.c 会先定义 UTIL_NO_MAIN 再包含本文件，屏蔽这里的 main，
 * 避免两个 main 冲突——真实项目里 util.c 不需要 main，由构建系统与使用方链接。
 */
#ifndef UTIL_NO_MAIN
int main(void) {
    printf("util.c 自测: max(-3, 7) = %d\n", util_max(-3, 7));
    printf("util.c 自测: pow(2, 10) = %ld\n", util_pow(2, 10));
    printf("util.c 自测: util_call_count = %d（每次调用公共函数各计 1 次）\n",
           util_call_count);
    return 0;
}
#endif /* UTIL_NO_MAIN */
