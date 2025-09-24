/*
 * stddef.h 演示程序
 * 
 * stddef.h 定义了一些标准的类型和宏，这些是C语言中最基础的定义
 * 主要包含：
 * - NULL: 空指针常量
 * - size_t: 无符号整数类型，用于表示对象大小
 * - ptrdiff_t: 有符号整数类型，用于表示指针差值
 * - wchar_t: 宽字符类型
 * - offsetof: 获取结构体成员偏移量的宏
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>
#include <string.h>

// 演示结构体，用于offsetof演示
struct example_struct {
    char a;
    int b;
    double c;
    char d[10];
};

// 演示NULL指针的使用
void demo_null_pointer(void) {
    printf("=== NULL 指针演示 ===\n");
    
    // NULL的基本使用
    int *ptr = NULL;
    printf("NULL指针的值: %p\n", (void*)ptr);
    printf("NULL的数值: %d\n", (ptr == NULL) ? 1 : 0);
    
    // 检查指针是否为NULL
    if (ptr == NULL) {
        printf("指针为空，安全检查通过\n");
    }
    
    // 分配内存后检查
    ptr = malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        printf("分配内存成功，值: %d\n", *ptr);
        free(ptr);
        ptr = NULL; // 释放后置为NULL，避免悬空指针
    }
    
    printf("\n");
}

// 演示size_t类型的使用
void demo_size_t(void) {
    printf("=== size_t 类型演示 ===\n");
    
    // size_t的基本信息
    printf("size_t的大小: %zu 字节\n", sizeof(size_t));
    printf("size_t的最大值: %zu\n", (size_t)SIZE_MAX);
    
    // 常见的size_t使用场景
    char str[] = "Hello, World!";
    size_t len = strlen(str);
    printf("字符串长度: %zu\n", len);
    
    // 数组大小计算
    int arr[] = {1, 2, 3, 4, 5};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    printf("数组元素个数: %zu\n", arr_size);
    
    // 内存分配
    size_t num_elements = 10;
    int *dynamic_arr = malloc(num_elements * sizeof(int));
    if (dynamic_arr != NULL) {
        printf("成功分配 %zu 个整数的内存\n", num_elements);
        
        // 初始化数组
        for (size_t i = 0; i < num_elements; i++) {
            dynamic_arr[i] = (int)(i * i);
        }
        
        // 打印数组
        printf("动态数组内容: ");
        for (size_t i = 0; i < num_elements; i++) {
            printf("%d ", dynamic_arr[i]);
        }
        printf("\n");
        
        free(dynamic_arr);
    }
    
    printf("\n");
}

// 演示ptrdiff_t类型的使用
void demo_ptrdiff_t(void) {
    printf("=== ptrdiff_t 类型演示 ===\n");
    
    // ptrdiff_t的基本信息
    printf("ptrdiff_t的大小: %zu 字节\n", sizeof(ptrdiff_t));
    
    // 指针算术运算
    int arr[] = {10, 20, 30, 40, 50};
    int *start = arr;
    int *end = arr + 4; // 指向最后一个元素
    
    ptrdiff_t diff = end - start;
    printf("指针差值: %td (元素个数)\n", diff);
    printf("字节差值: %td 字节\n", diff * (ptrdiff_t)sizeof(int));
    
    // 在数组中查找元素
    int target = 30;
    int *found = NULL;
    
    for (int *p = start; p <= end; p++) {
        if (*p == target) {
            found = p;
            break;
        }
    }
    
    if (found != NULL) {
        ptrdiff_t index = found - start;
        printf("找到元素 %d，索引: %td\n", target, index);
    }
    
    printf("\n");
}

// 演示wchar_t类型的使用
void demo_wchar_t(void) {
    printf("=== wchar_t 类型演示 ===\n");
    
    // wchar_t的基本信息
    printf("wchar_t的大小: %zu 字节\n", sizeof(wchar_t));
    
    // 宽字符常量
    wchar_t wide_char = L'A';
    printf("宽字符 'A' 的值: %d\n", (int)wide_char);
    
    // 宽字符串
    wchar_t wide_string[] = L"Hello, 世界!";
    printf("宽字符串长度: %zu\n", wcslen(wide_string));
    
    // 注意：在某些系统上可能需要设置locale才能正确显示宽字符
    printf("宽字符串内容: ");
    for (size_t i = 0; wide_string[i] != L'\0'; i++) {
        if (wide_string[i] < 128) {
            printf("%c", (char)wide_string[i]);
        } else {
            printf("[U+%04X]", (unsigned int)wide_string[i]);
        }
    }
    printf("\n");
    
    printf("\n");
}

// 演示offsetof宏的使用
void demo_offsetof(void) {
    printf("=== offsetof 宏演示 ===\n");
    
    // 显示结构体信息
    printf("struct example_struct 的大小: %zu 字节\n", sizeof(struct example_struct));
    
    // 显示各成员的偏移量
    printf("成员偏移量:\n");
    printf("  char a:      偏移 %zu 字节\n", offsetof(struct example_struct, a));
    printf("  int b:       偏移 %zu 字节\n", offsetof(struct example_struct, b));
    printf("  double c:    偏移 %zu 字节\n", offsetof(struct example_struct, c));
    printf("  char d[10]:  偏移 %zu 字节\n", offsetof(struct example_struct, d));
    
    // 实际验证偏移量
    struct example_struct s;
    char *base = (char*)&s;
    
    printf("\n实际地址验证:\n");
    printf("  结构体基址: %p\n", (void*)&s);
    printf("  成员a地址:  %p (偏移: %td)\n", (void*)&s.a, (char*)&s.a - base);
    printf("  成员b地址:  %p (偏移: %td)\n", (void*)&s.b, (char*)&s.b - base);
    printf("  成员c地址:  %p (偏移: %td)\n", (void*)&s.c, (char*)&s.c - base);
    printf("  成员d地址:  %p (偏移: %td)\n", (void*)&s.d, (char*)&s.d - base);
    
    printf("\n");
}

// 演示内存对齐和填充
void demo_memory_alignment(void) {
    printf("=== 内存对齐演示 ===\n");
    
    // 不同结构体的大小比较
    struct packed {
        char a;
        char b;
        char c;
    };
    
    struct aligned {
        char a;
        int b;
        char c;
    };
    
    struct reordered {
        char a;
        char c;
        int b;
    };
    
    printf("结构体大小比较:\n");
    printf("  struct packed (3个char):   %zu 字节\n", sizeof(struct packed));
    printf("  struct aligned (char,int,char): %zu 字节\n", sizeof(struct aligned));
    printf("  struct reordered (char,char,int): %zu 字节\n", sizeof(struct reordered));
    
    printf("\n对齐分析:\n");
    printf("  char对齐要求: %zu 字节\n", _Alignof(char));
    printf("  int对齐要求:  %zu 字节\n", _Alignof(int));
    printf("  double对齐要求: %zu 字节\n", _Alignof(double));
    
    printf("\n");
}

// 实用工具函数：安全的指针操作
void demo_safe_pointer_operations(void) {
    printf("=== 安全指针操作演示 ===\n");
    
    // 安全的内存分配和释放
    size_t count = 5;
    int *arr = malloc(count * sizeof(int));
    
    if (arr != NULL) {
        printf("成功分配内存\n");
        
        // 初始化
        for (size_t i = 0; i < count; i++) {
            arr[i] = (int)(i + 1);
        }
        
        // 使用指针算术
        int *current = arr;
        int *end = arr + count;
        
        printf("数组内容: ");
        while (current < end) {
            printf("%d ", *current);
            current++;
        }
        printf("\n");
        
        // 计算已处理的元素数量
        ptrdiff_t processed = current - arr;
        printf("已处理元素数量: %td\n", processed);
        
        // 安全释放
        free(arr);
        arr = NULL; // 避免悬空指针
        printf("内存已安全释放\n");
    } else {
        printf("内存分配失败\n");
    }
    
    printf("\n");
}

int main(void) {
    printf("C标准库 stddef.h 演示程序\n");
    printf("========================\n\n");
    
    demo_null_pointer();
    demo_size_t();
    demo_ptrdiff_t();
    demo_wchar_t();
    demo_offsetof();
    demo_memory_alignment();
    demo_safe_pointer_operations();
    
    printf("stddef.h 演示完成！\n");
    printf("\n重要提示:\n");
    printf("1. NULL是空指针常量，用于初始化指针\n");
    printf("2. size_t用于表示大小，总是无符号类型\n");
    printf("3. ptrdiff_t用于指针差值，是有符号类型\n");
    printf("4. offsetof可以获取结构体成员的偏移量\n");
    printf("5. 注意内存对齐对结构体大小的影响\n");
    
    return 0;
}
