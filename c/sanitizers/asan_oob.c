#include <stdio.h>
#include <stdlib.h>

// AddressSanitizer (ASan) 示例：堆缓冲区溢出 (Heap Buffer Overflow)
// 编译命令: gcc -fsanitize=address -g asan_oob.c -o asan_oob

int main() {
    printf("ASan Out-of-Bounds Example\n");

    int *array = (int *)malloc(10 * sizeof(int));
    if (array == NULL) {
        return 1;
    }

    // 正常访问
    array[0] = 0;

    // 越界写入：写入第 11 个元素 (索引 10)，这会导致堆缓冲区溢出
    printf("即将执行越界写入...\n");
    array[10] = 100; // BOOM!

    printf("如果看到这句话，说明未检测到错误（或者程序已崩溃）。\n");

    free(array);
    return 0;
}
