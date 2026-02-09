#include <stdio.h>

void original_function() {
    printf("This is the original function.\n");
}

void __attribute__((alias("original_function"))) alias_function();

int main() {
    original_function(); // 调用原始函数
    alias_function();    // 调用别名函数

    return 0;
}
