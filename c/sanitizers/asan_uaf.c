#include <stdio.h>
#include <stdlib.h>

// AddressSanitizer (ASan) 示例：释放后使用 (Use-After-Free)
// 编译命令: gcc -fsanitize=address -g asan_uaf.c -o asan_uaf

int main() {
    printf("ASan Use-After-Free Example\n");

    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;

    printf("释放内存...\n");
    free(ptr);

    // 释放后使用：尝试读取已释放的内存
    printf("即将访问已释放的内存...\n");
    printf("Value: %d\n", *ptr); // BOOM!

    return 0;
}
