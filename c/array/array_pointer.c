/*
 * 数组与指针关系示例
 * 演示数组名与指针的关系、指针数组、数组指针等
 * C17/C18 标准
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// 演示数组名与指针的关系
void demo_array_name_as_pointer() {
    printf("=== 数组名与指针的关系 ===\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // 数组名可以转换为指针
    
    printf("数组元素:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    printf("\n");
    
    // 使用指针访问数组
    printf("通过指针访问数组:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(ptr + %d) = %d\n", i, *(ptr + i));
    }
    printf("\n");
    
    // 数组名和指针的区别
    printf("数组名和指针的区别:\n");
    printf("arr = %p\n", (void*)arr);
    printf("ptr = %p\n", (void*)ptr);
    printf("sizeof(arr) = %zu (整个数组的大小)\n", sizeof(arr));
    printf("sizeof(ptr) = %zu (指针的大小)\n", sizeof(ptr));
    printf("\n");
    
    // 指针可以改变指向，但数组名不能
    int arr2[3] = {1, 2, 3};
    ptr = arr2;  // OK: 指针可以重新赋值
    // arr = arr2;  // ERROR: 数组名不能重新赋值
    printf("指针重新赋值后指向新数组:\n");
    printf("*ptr = %d\n\n", *ptr);
}

// 演示指针算术
void demo_pointer_arithmetic() {
    printf("=== 指针算术演示 ===\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    
    printf("原始位置: *ptr = %d\n", *ptr);
    
    ptr++;  // 指向下一个元素
    printf("ptr++后: *ptr = %d\n", *ptr);
    
    ptr += 2;  // 向前移动2个元素
    printf("ptr+=2后: *ptr = %d\n", *ptr);
    
    ptr--;  // 指向前一个元素
    printf("ptr--后: *ptr = %d\n", *ptr);
    
    // 指针相减
    int *ptr1 = &arr[4];
    int *ptr2 = &arr[1];
    ptrdiff_t diff = ptr1 - ptr2;
    printf("指针相减: ptr1 - ptr2 = %td\n\n", diff);
}

// 演示使用指针遍历数组
void demo_pointer_traversal() {
    printf("=== 使用指针遍历数组 ===\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr;
    
    // 方法1: 使用指针和索引
    printf("方法1 - 指针+索引:\n");
    ptr = arr;
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // 方法2: 使用指针递增
    printf("方法2 - 指针递增:\n");
    ptr = arr;
    for (int i = 0; i < 5; i++) {
        printf("%d ", *ptr++);
    }
    printf("\n");
    
    // 方法3: 使用指针比较
    printf("方法3 - 指针比较:\n");
    int *end = arr + 5;
    for (ptr = arr; ptr < end; ptr++) {
        printf("%d ", *ptr);
    }
    printf("\n\n");
}

// 演示指针数组（数组的元素是指针）
void demo_array_of_pointers() {
    printf("=== 指针数组 ===\n");
    
    // 字符串数组实际上是指针数组
    const char *names[] = {
        "Alice",
        "Bob",
        "Charlie",
        "David",
        "Eve"
    };
    
    int count = sizeof(names) / sizeof(names[0]);
    printf("字符串指针数组:\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, names[i]);
    }
    printf("\n");
    
    // 整数指针数组
    int a = 10, b = 20, c = 30, d = 40;
    int *int_ptrs[] = {&a, &b, &c, &d};
    
    printf("整数指针数组:\n");
    for (size_t i = 0; i < sizeof(int_ptrs) / sizeof(int_ptrs[0]); i++) {
        printf("*int_ptrs[%zu] = %d\n", i, *int_ptrs[i]);
    }
    printf("\n");
}

// 演示数组指针（指向整个数组的指针）
void demo_pointer_to_array() {
    printf("=== 数组指针 ===\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    
    // 指向数组的指针
    int (*ptr_to_array)[5] = &arr;
    
    printf("通过数组指针访问元素:\n");
    for (int i = 0; i < 5; i++) {
        printf("(*ptr_to_array)[%d] = %d\n", i, (*ptr_to_array)[i]);
    }
    printf("\n");
    
    // 二维数组指针
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    int (*row_ptr)[4] = matrix;  // 指向第一行
    
    printf("通过行指针访问二维数组:\n");
    for (int i = 0; i < 3; i++) {
        printf("行 %d: ", i);
        for (int j = 0; j < 4; j++) {
            printf("%d ", row_ptr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 使用指针作为函数参数修改数组
void modify_array_via_pointer(int *arr, size_t size, int increment) {
    for (size_t i = 0; i < size; i++) {
        arr[i] += increment;
    }
}

// 使用数组指针作为函数参数
void print_matrix_via_pointer(int (*matrix)[4], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 演示指针作为函数参数
void demo_pointer_as_parameter() {
    printf("=== 指针作为函数参数 ===\n");
    
    int arr[5] = {1, 2, 3, 4, 5};
    
    printf("修改前: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    modify_array_via_pointer(arr, 5, 10);
    
    printf("修改后: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    
    // 二维数组作为参数
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("二维数组:\n");
    print_matrix_via_pointer(matrix, 3);
    printf("\n");
}

// 返回指针的函数
int* find_max_element(int *arr, size_t size) {
    if (size == 0) return NULL;
    
    int *max_ptr = arr;
    for (size_t i = 1; i < size; i++) {
        if (arr[i] > *max_ptr) {
            max_ptr = &arr[i];
        }
    }
    return max_ptr;
}

// 演示返回指针的函数
void demo_function_returning_pointer() {
    printf("=== 返回指针的函数 ===\n");
    
    int arr[8] = {23, 45, 12, 67, 89, 34, 56, 78};
    
    int *max_ptr = find_max_element(arr, 8);
    if (max_ptr != NULL) {
        printf("数组中的最大值: %d\n", *max_ptr);
        printf("最大值的地址: %p\n", (void*)max_ptr);
        printf("最大值在数组中的索引: %td\n", max_ptr - arr);
    }
    printf("\n");
}

// 演示动态数组
void demo_dynamic_array() {
    printf("=== 动态数组 ===\n");
    
    size_t size = 5;
    
    // 使用malloc分配数组
    int *dynamic_arr = (int*)malloc(size * sizeof(int));
    if (dynamic_arr == NULL) {
        printf("内存分配失败\n");
        return;
    }
    
    // 初始化数组
    for (size_t i = 0; i < size; i++) {
        dynamic_arr[i] = (int)((i + 1) * 10);
    }
    
    printf("动态数组: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", dynamic_arr[i]);
    }
    printf("\n");
    
    // 使用realloc调整大小
    size_t new_size = 8;
    int *temp = (int*)realloc(dynamic_arr, new_size * sizeof(int));
    if (temp == NULL) {
        printf("内存重新分配失败\n");
        free(dynamic_arr);
        return;
    }
    dynamic_arr = temp;
    
    // 初始化新元素
    for (size_t i = size; i < new_size; i++) {
        dynamic_arr[i] = (int)((i + 1) * 10);
    }
    
    printf("扩展后的动态数组: ");
    for (size_t i = 0; i < new_size; i++) {
        printf("%d ", dynamic_arr[i]);
    }
    printf("\n");
    
    // 释放内存
    free(dynamic_arr);
    printf("内存已释放\n\n");
}

// 演示指针数组与二维数组的区别
void demo_pointer_array_vs_2d_array() {
    printf("=== 指针数组 vs 二维数组 ===\n");
    
    // 真正的二维数组（连续内存）
    int real_2d[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("二维数组（连续内存）:\n");
    printf("sizeof(real_2d) = %zu bytes\n", sizeof(real_2d));
    printf("地址: real_2d[0] = %p\n", (void*)real_2d[0]);
    printf("地址: real_2d[1] = %p\n", (void*)real_2d[1]);
    printf("地址: real_2d[2] = %p\n\n", (void*)real_2d[2]);
    
    // 指针数组（不连续内存）
    int row0[] = {1, 2, 3, 4};
    int row1[] = {5, 6, 7, 8};
    int row2[] = {9, 10, 11, 12};
    int *ptr_array[3] = {row0, row1, row2};
    
    printf("指针数组（可能不连续）:\n");
    printf("sizeof(ptr_array) = %zu bytes\n", sizeof(ptr_array));
    printf("地址: ptr_array[0] = %p\n", (void*)ptr_array[0]);
    printf("地址: ptr_array[1] = %p\n", (void*)ptr_array[1]);
    printf("地址: ptr_array[2] = %p\n", (void*)ptr_array[2]);
}

int main(void) {
    printf("C语言数组与指针关系示例\n");
    printf("==========================================\n\n");
    
    demo_array_name_as_pointer();
    demo_pointer_arithmetic();
    demo_pointer_traversal();
    demo_array_of_pointers();
    demo_pointer_to_array();
    demo_pointer_as_parameter();
    demo_function_returning_pointer();
    demo_dynamic_array();
    demo_pointer_array_vs_2d_array();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
