/*
 * 数组操作示例
 * 演示数组的常见操作：排序、搜索、反转等
 * C17/C18 标准
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 打印数组
void print_array(const int arr[], size_t size, const char *label) {
    printf("%s: ", label);
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 冒泡排序
void bubble_sort(int arr[], size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (size_t j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // 如果没有发生交换，说明已经排序完成
        if (!swapped) break;
    }
}

// 选择排序
void selection_sort(int arr[], size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // 交换
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// 插入排序
void insertion_sort(int arr[], size_t size) {
    for (size_t i = 1; i < size; i++) {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

// qsort比较函数
int compare_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// 演示排序算法
void demo_sorting() {
    printf("=== 数组排序演示 ===\n");
    
    // 冒泡排序
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    print_array(arr1, size1, "冒泡排序前");
    bubble_sort(arr1, size1);
    print_array(arr1, size1, "冒泡排序后");
    printf("\n");
    
    // 选择排序
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    print_array(arr2, size2, "选择排序前");
    selection_sort(arr2, size2);
    print_array(arr2, size2, "选择排序后");
    printf("\n");
    
    // 插入排序
    int arr3[] = {64, 34, 25, 12, 22, 11, 90};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    print_array(arr3, size3, "插入排序前");
    insertion_sort(arr3, size3);
    print_array(arr3, size3, "插入排序后");
    printf("\n");
    
    // 使用标准库qsort
    int arr4[] = {64, 34, 25, 12, 22, 11, 90};
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    print_array(arr4, size4, "qsort排序前");
    qsort(arr4, size4, sizeof(int), compare_int);
    print_array(arr4, size4, "qsort排序后");
}

// 线性搜索
int linear_search(const int arr[], size_t size, int target) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == target) {
            return (int)i;
        }
    }
    return -1;
}

// 二分搜索（数组必须已排序）
int binary_search(const int arr[], size_t size, int target) {
    int left = 0;
    int right = (int)size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// 演示搜索算法
void demo_searching() {
    printf("\n=== 数组搜索演示 ===\n");
    
    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    // 线性搜索
    int target1 = 7;
    int pos1 = linear_search(arr, size, target1);
    if (pos1 >= 0) {
        printf("线性搜索: 找到 %d 在位置 %d\n", target1, pos1);
    } else {
        printf("线性搜索: 未找到 %d\n", target1);
    }
    
    int target2 = 15;
    int pos2 = linear_search(arr, size, target2);
    if (pos2 >= 0) {
        printf("线性搜索: 找到 %d 在位置 %d\n", target2, pos2);
    } else {
        printf("线性搜索: 未找到 %d\n", target2);
    }
    
    // 二分搜索（需要先排序）
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t sorted_size = sizeof(sorted_arr) / sizeof(sorted_arr[0]);
    
    int target3 = 5;
    int pos3 = binary_search(sorted_arr, sorted_size, target3);
    if (pos3 >= 0) {
        printf("二分搜索: 找到 %d 在位置 %d\n", target3, pos3);
    } else {
        printf("二分搜索: 未找到 %d\n", target3);
    }
}

// 数组反转
void reverse_array(int arr[], size_t size) {
    for (size_t i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

// 数组旋转（向左旋转n个位置）
void rotate_left(int arr[], size_t size, size_t n) {
    n = n % size;  // 处理n大于size的情况
    
    // 反转前n个元素
    reverse_array(arr, n);
    // 反转剩余元素
    reverse_array(arr + n, size - n);
    // 反转整个数组
    reverse_array(arr, size);
}

// 演示数组变换
void demo_transformations() {
    printf("\n=== 数组变换演示 ===\n");
    
    // 反转
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    print_array(arr1, size1, "反转前");
    reverse_array(arr1, size1);
    print_array(arr1, size1, "反转后");
    printf("\n");
    
    // 旋转
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    print_array(arr2, size2, "旋转前");
    rotate_left(arr2, size2, 3);
    print_array(arr2, size2, "向左旋转3位后");
}

// 删除重复元素（原地修改，返回新大小）
size_t remove_duplicates(int arr[], size_t size) {
    if (size == 0) return 0;
    
    size_t write_pos = 1;
    for (size_t read_pos = 1; read_pos < size; read_pos++) {
        bool is_duplicate = false;
        for (size_t j = 0; j < write_pos; j++) {
            if (arr[read_pos] == arr[j]) {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate) {
            arr[write_pos++] = arr[read_pos];
        }
    }
    return write_pos;
}

// 演示数组去重
void demo_remove_duplicates() {
    printf("\n=== 数组去重演示 ===\n");
    
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    print_array(arr, size, "去重前");
    size_t new_size = remove_duplicates(arr, size);
    print_array(arr, new_size, "去重后");
}

// 合并两个有序数组
void merge_sorted_arrays(const int arr1[], size_t size1, const int arr2[], size_t size2, int result[]) {
    size_t i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    
    while (i < size1) {
        result[k++] = arr1[i++];
    }
    
    while (j < size2) {
        result[k++] = arr2[j++];
    }
}

// 演示数组合并
void demo_merge_arrays() {
    printf("\n=== 数组合并演示 ===\n");
    
    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 10};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result[10];
    
    print_array(arr1, size1, "数组1");
    print_array(arr2, size2, "数组2");
    
    merge_sorted_arrays(arr1, size1, arr2, size2, result);
    print_array(result, size1 + size2, "合并后");
}

int main(void) {
    printf("C语言数组操作示例\n");
    printf("==========================================\n\n");
    
    demo_sorting();
    demo_searching();
    demo_transformations();
    demo_remove_duplicates();
    demo_merge_arrays();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
