/*
 * 主题说明：C 模块与可见性 —— util.h 只放声明（接口），util.c 放定义（实现）：
 *           extern 计数器跨文件共享、static 函数对其他编译单元隐藏、include guard 防重复包含。
 * 运行命令：./c/build/bin/module_module_demo（实现文件的独立自测另见 ./c/build/bin/module_util）
 * 预期输出（关键行）：
 *   max(-3, 7) = 7
 *   pow(2, 10) = 1024
 *   util_call_count = 2（extern 变量在模块内部共享，外部经 util.h 声明读取）
 */

#include <stdio.h>

#include "util.h"                      /* 模块接口：原型与 extern 声明都在这里 */

/*
 * 构建说明：真实项目中，本文件与 util.c 由构建系统一起编译链接
 * （gcc module_demo.c util.c）。本仓库 CMake 按“每个 .c 一个可执行 target”组织，
 * module_demo.c 单独编译时拿不到 util.o，故此处先屏蔽 util.c 的自测 main、
 * 再包含实现文件，等价模拟“两文件链接”的效果。
 */
#define UTIL_NO_MAIN
#include "util.c"

int main(void) {
    printf("C 模块与可见性示例（module_demo.c + util.h + util.c）\n");
    printf("==========================================\n\n");

    /* 使用方只认 util.h 声明的接口，不关心实现细节 */
    printf("max(-3, 7) = %d\n", util_max(-3, 7));
    printf("pow(2, 10) = %ld\n", util_pow(2, 10));

    /* extern 变量：定义在 util.c，这里经 util.h 的声明直接读同一份存储 */
    printf("util_call_count = %d（extern 变量在模块内部共享，外部经 util.h 声明读取）\n",
           util_call_count);

    /*
     * util.c 里的 static 函数 mul_add 是文件私有的：util.h 没有声明它，
     * 在本文件写 mul_add(1, 2, 3) 会直接编译失败——尝试前请注释取消。
     * 这就是 C 的“模块内部实现对外不可见”。
     */

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
