#include <stdio.h>
#include <stdlib.h>

// LeakSanitizer (LSan) 示例：内存泄漏
// 通常作为 AddressSanitizer 的一部分运行
// 编译命令: gcc -fsanitize=address -g lsan_leak.c -o lsan_leak
// 或者专门指定: gcc -fsanitize=leak -g lsan_leak.c -o lsan_leak

void leak_memory() {
    int *ptr = (int *)malloc(100 * sizeof(int));
    ptr[0] = 1;
    printf("分配了内存但没有释放\n");
    // 忘记 free(ptr);
}

int main() {
    printf("LeakSanitizer Example\n");
    leak_memory();
    printf("程序结束，LSan 应该报告内存泄漏\n");
    return 0;
}
