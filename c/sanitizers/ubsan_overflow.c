#include <stdio.h>
#include <limits.h>

// UndefinedBehaviorSanitizer (UBSan) 示例：有符号整数溢出
// 编译命令: gcc -fsanitize=undefined -g ubsan_overflow.c -o ubsan_overflow

int main() {
    printf("UBSan Integer Overflow Example\n");

    int k = INT_MAX;
    printf("INT_MAX = %d\n", k);

    printf("即将执行整数溢出操作...\n");
    k += 1; // 有符号整数溢出是未定义行为

    printf("Result: %d\n", k);
    return 0;
}
