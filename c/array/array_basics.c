/*
 * 数组基础示例
 * 演示C语言中数组的声明、初始化和基本访问
 * C17/C18 标准
 */

#include <stdio.h>
#include <string.h>

// 演示数组声明和初始化
void demo_array_declaration() {
    printf("=== 数组声明和初始化 ===\n");
    
    // 方式1: 声明时完全初始化
    int arr1[5] = {1, 2, 3, 4, 5};
    printf("完全初始化数组: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    
    // 方式2: 部分初始化（剩余元素自动填充0）
    int arr2[5] = {1, 2, 3};
    printf("部分初始化数组: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    
    // 方式3: 全部初始化为0
    int arr3[5] = {0};
    printf("全零初始化数组: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");
    
    // 方式4: 省略大小（由初始化器决定）
    int arr4[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr4) / sizeof(arr4[0]);
    printf("自动大小数组(大小=%d): ", size);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr4[i]);
    }
    printf("\n");
    
    // 方式5: 指定索引初始化（C99特性）
    int arr5[10] = {[0]=1, [3]=4, [9]=10};
    printf("指定索引初始化: ");
    for (int i = 0; i < 10; i++) {
        if (arr5[i] != 0) {
            printf("[%d]=%d ", i, arr5[i]);
        }
    }
    printf("\n");
}

// 演示字符数组和字符串
void demo_char_arrays() {
    printf("\n=== 字符数组和字符串 ===\n");
    
    // 字符数组方式1
    char str1[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    printf("字符数组方式1: %s\n", str1);
    
    // 字符数组方式2（字符串字面量）
    char str2[] = "Hello";
    printf("字符数组方式2: %s\n", str2);
    
    // 指定大小的字符数组
    char str3[20] = "Hello";
    printf("指定大小字符数组(大小=%zu): %s\n", sizeof(str3), str3);
    
    // 字符串复制
    char str4[20];
    strcpy(str4, "World");
    printf("复制后的字符串: %s\n", str4);
}

// 演示数组访问和修改
void demo_array_access() {
    printf("\n=== 数组访问和修改 ===\n");
    
    int numbers[5] = {10, 20, 30, 40, 50};
    
    // 读取元素
    printf("第一个元素: %d\n", numbers[0]);
    printf("最后一个元素: %d\n", numbers[4]);
    
    // 修改元素
    numbers[2] = 99;
    printf("修改后的第三个元素: %d\n", numbers[2]);
    
    // 使用循环访问
    printf("所有元素: ");
    for (size_t i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // 使用sizeof计算数组大小
    size_t array_size = sizeof(numbers) / sizeof(numbers[0]);
    printf("数组元素个数: %zu\n", array_size);
}

// 演示常见的数组操作
void demo_common_operations() {
    printf("\n=== 常见数组操作 ===\n");
    
    int arr[10] = {5, 2, 8, 1, 9, 3, 7, 4, 6, 0};
    
    // 1. 求和
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    printf("数组元素和: %d\n", sum);
    
    // 2. 求平均值
    double average = (double)sum / 10;
    printf("数组平均值: %.2f\n", average);
    
    // 3. 查找最大值和最小值
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < 10; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    printf("最大值: %d, 最小值: %d\n", max, min);
    
    // 4. 查找元素
    int target = 7;
    int found = -1;
    for (int i = 0; i < 10; i++) {
        if (arr[i] == target) {
            found = i;
            break;
        }
    }
    if (found >= 0) {
        printf("找到元素 %d，位置: %d\n", target, found);
    }
    
    // 5. 数组复制
    int copy[10];
    for (int i = 0; i < 10; i++) {
        copy[i] = arr[i];
    }
    printf("复制的数组: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", copy[i]);
    }
    printf("\n");
}

// 演示数组作为函数参数
void print_array(int arr[], size_t size) {
    printf("函数中打印数组: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void modify_array(int arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

void demo_array_as_parameter() {
    printf("\n=== 数组作为函数参数 ===\n");
    
    int data[5] = {1, 2, 3, 4, 5};
    
    printf("原始数组: ");
    print_array(data, 5);
    
    modify_array(data, 5);
    printf("修改后数组: ");
    print_array(data, 5);
    
    // 注意：数组作为参数传递时，实际传递的是指针
    printf("在main中 sizeof(data) = %zu\n", sizeof(data));
    printf("在main中 数组元素个数 = %zu\n", sizeof(data) / sizeof(data[0]));
}

int main(void) {
    printf("C语言数组基础示例\n");
    printf("==========================================\n\n");
    
    demo_array_declaration();
    demo_char_arrays();
    demo_array_access();
    demo_common_operations();
    demo_array_as_parameter();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
