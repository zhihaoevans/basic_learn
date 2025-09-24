/*
 * stdlib.h 标准头文件演示
 * 演示标准库的各种函数用法：内存管理、类型转换、随机数、程序控制等
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void demo_memory_management() {
    printf("=== 内存管理演示 ===\n");
    
    // malloc - 分配内存
    int *ptr = (int*)malloc(5 * sizeof(int));
    if (ptr == NULL) {
        printf("内存分配失败\n");
        return;
    }
    
    printf("使用malloc分配了5个int的内存\n");
    
    // 初始化分配的内存
    for (int i = 0; i < 5; i++) {
        ptr[i] = (i + 1) * 10;
    }
    
    printf("初始化数据: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // realloc - 重新分配内存
    ptr = (int*)realloc(ptr, 8 * sizeof(int));
    if (ptr == NULL) {
        printf("内存重新分配失败\n");
        return;
    }
    
    printf("使用realloc扩展到8个int\n");
    
    // 初始化新增的内存
    for (int i = 5; i < 8; i++) {
        ptr[i] = (i + 1) * 10;
    }
    
    printf("扩展后数据: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // free - 释放内存
    free(ptr);
    printf("内存已释放\n");
    
    // calloc - 分配并初始化为0的内存
    int *zero_ptr = (int*)calloc(5, sizeof(int));
    if (zero_ptr != NULL) {
        printf("calloc分配的内存（自动初始化为0）: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", zero_ptr[i]);
        }
        printf("\n");
        free(zero_ptr);
    }
}

void demo_string_conversion() {
    printf("\n=== 字符串转换演示 ===\n");
    
    // atoi - 字符串转整数
    char str_int[] = "12345";
    int num = atoi(str_int);
    printf("atoi('%s') = %d\n", str_int, num);
    
    // atof - 字符串转浮点数
    char str_float[] = "123.456";
    double fnum = atof(str_float);
    printf("atof('%s') = %.3f\n", str_float, fnum);
    
    // atol - 字符串转长整数
    char str_long[] = "1234567890";
    long lnum = atol(str_long);
    printf("atol('%s') = %ld\n", str_long, lnum);
    
    // strtol - 更强大的字符串转长整数
    char str_hex[] = "1A2B";
    char *endptr;
    long hex_num = strtol(str_hex, &endptr, 16);  // 16进制
    printf("strtol('%s', base 16) = %ld\n", str_hex, hex_num);
    
    char str_bin[] = "1010";
    long bin_num = strtol(str_bin, &endptr, 2);   // 2进制
    printf("strtol('%s', base 2) = %ld\n", str_bin, bin_num);
    
    // strtod - 字符串转双精度浮点数
    char str_double[] = "3.14159265";
    double dnum = strtod(str_double, &endptr);
    printf("strtod('%s') = %.8f\n", str_double, dnum);
}

void demo_random_numbers() {
    printf("\n=== 随机数演示 ===\n");
    
    // 设置随机数种子
    srand((unsigned int)time(NULL));
    
    printf("生成10个0-99的随机数: ");
    for (int i = 0; i < 10; i++) {
        int random_num = rand() % 100;
        printf("%d ", random_num);
    }
    printf("\n");
    
    // 生成指定范围的随机数 [min, max]
    int min = 10, max = 50;
    printf("生成5个%d-%d范围的随机数: ", min, max);
    for (int i = 0; i < 5; i++) {
        int random_num = min + rand() % (max - min + 1);
        printf("%d ", random_num);
    }
    printf("\n");
    
    // 生成随机浮点数 [0, 1)
    printf("生成5个0-1的随机浮点数: ");
    for (int i = 0; i < 5; i++) {
        double random_float = (double)rand() / RAND_MAX;
        printf("%.3f ", random_float);
    }
    printf("\n");
    
    printf("RAND_MAX = %d\n", RAND_MAX);
}

// 比较函数用于qsort和bsearch
int compare_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void demo_sorting_searching(void) {
    printf("\n=== 排序和搜索演示 ===\n");
    
    // 准备测试数据
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("原始数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // qsort - 快速排序
    qsort(arr, n, sizeof(int), compare_int);
    
    printf("qsort排序后: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // bsearch - 二分搜索
    int key = 25;
    int *result = (int*)bsearch(&key, arr, n, sizeof(int), compare_int);
    
    if (result != NULL) {
        printf("bsearch找到 %d，位置: %ld\n", key, result - arr);
    } else {
        printf("bsearch未找到 %d\n", key);
    }
    
    // 搜索不存在的元素
    key = 99;
    result = (int*)bsearch(&key, arr, n, sizeof(int), compare_int);
    if (result == NULL) {
        printf("bsearch未找到 %d（预期结果）\n", key);
    }
}

void demo_math_functions(void) {
    printf("\n=== 数学函数演示 ===\n");
    
    // abs - 绝对值
    int negative = -42;
    printf("abs(%d) = %d\n", negative, abs(negative));
    
    // labs - 长整数绝对值
    long long_negative = -1234567890L;
    printf("labs(%ld) = %ld\n", long_negative, labs(long_negative));
    
    // div - 整数除法
    div_t result = div(17, 5);
    printf("div(17, 5): 商 = %d, 余数 = %d\n", result.quot, result.rem);
    
    // ldiv - 长整数除法
    ldiv_t long_result = ldiv(1000000L, 7L);
    printf("ldiv(1000000, 7): 商 = %ld, 余数 = %ld\n", long_result.quot, long_result.rem);
}

void demo_environment(void) {
    printf("\n=== 环境变量演示 ===\n");
    
    // getenv - 获取环境变量
    char *path = getenv("PATH");
    if (path != NULL) {
        printf("PATH环境变量长度: %zu\n", strlen(path));
        printf("PATH前50个字符: %.50s...\n", path);
    }
    
    char *home = getenv("HOME");
    if (home != NULL) {
        printf("HOME = %s\n", home);
    }
    
    char *user = getenv("USER");
    if (user != NULL) {
        printf("USER = %s\n", user);
    }
    
    // 尝试获取不存在的环境变量
    char *nonexistent = getenv("NONEXISTENT_VAR");
    if (nonexistent == NULL) {
        printf("NONEXISTENT_VAR 不存在（预期结果）\n");
    }
}

// 清理函数声明
void cleanup_function(void) {
    printf("程序退出时的清理函数被调用\n");
}

void demo_program_control(void) {
    printf("\n=== 程序控制演示 ===\n");
    
    // system - 执行系统命令
    printf("执行系统命令 'echo Hello from system()':\n");
    int ret = system("echo Hello from system()");
    printf("system() 返回值: %d\n", ret);
    
    printf("执行系统命令 'date':\n");
    system("date");
    
    // 注意：exit() 会终止程序，所以这里只演示不调用
    printf("注意: exit() 函数会终止程序，这里不演示调用\n");
    printf("atexit() 可以注册程序退出时的清理函数\n");
    
    // 演示atexit（注册退出函数）
    if (atexit(cleanup_function) == 0) {
        printf("成功注册了退出清理函数\n");
    }
}

int main(void) {
    printf("C语言 stdlib.h 标准头文件演示\n");
    printf("=================================\n");
    
    demo_memory_management();
    demo_string_conversion();
    demo_random_numbers();
    demo_sorting_searching();
    demo_math_functions();
    demo_environment();
    demo_program_control();
    
    printf("\n演示完成！\n");
    return 0;
}