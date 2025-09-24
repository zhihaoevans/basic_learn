/*
 * assert.h 标准头文件演示
 * 演示断言宏的用法和调试技巧
 * 
 * 编译选项：
 * - 调试版本：gcc -g assert_demo.c -o assert_demo
 * - 发布版本：gcc -DNDEBUG assert_demo.c -o assert_demo
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// 演示函数：计算数组平均值
double calculate_average(int *array, int size) {
    // 使用断言检查输入参数
    assert(array != NULL);        // 确保数组指针不为空
    assert(size > 0);            // 确保数组大小为正数
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    
    return (double)sum / size;
}

// 演示函数：安全的字符串复制
char* safe_string_copy(const char *source) {
    assert(source != NULL);      // 确保源字符串不为空
    
    int len = strlen(source);
    assert(len >= 0);            // 字符串长度应该非负（实际上strlen返回size_t，总是非负）
    
    char *dest = malloc(len + 1);
    assert(dest != NULL);        // 确保内存分配成功
    
    strcpy(dest, source);
    return dest;
}

// 演示函数：数组边界检查
int get_array_element(int *array, int size, int index) {
    assert(array != NULL);       // 数组指针不为空
    assert(size > 0);           // 数组大小为正
    assert(index >= 0);         // 索引非负
    assert(index < size);       // 索引在有效范围内
    
    return array[index];
}

// 演示函数：除法运算
double safe_divide(double a, double b) {
    assert(b != 0.0);           // 确保除数不为零
    
    return a / b;
}

void demo_basic_assertions() {
    printf("=== 基本断言演示 ===\n");
    
    // 1. 简单的断言测试
    int x = 10;
    assert(x > 0);              // 这个断言会通过
    printf("断言 x > 0 通过，x = %d\n", x);
    
    // 2. 测试数组平均值函数
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    double avg = calculate_average(numbers, size);
    printf("数组平均值: %.2f\n", avg);
    
    // 3. 测试字符串复制函数
    char *original = "Hello, World!";
    char *copy = safe_string_copy(original);
    printf("原字符串: %s\n", original);
    printf("复制字符串: %s\n", copy);
    free(copy);
    
    // 4. 测试数组访问函数
    int element = get_array_element(numbers, size, 2);
    printf("数组第3个元素: %d\n", element);
    
    // 5. 测试除法函数
    double result = safe_divide(10.0, 2.0);
    printf("10.0 / 2.0 = %.2f\n", result);
}

void demo_assertion_failures() {
    printf("\n=== 断言失败演示 ===\n");
    printf("注意：以下代码包含会导致断言失败的情况\n");
    printf("在实际运行时，请注释掉相应代码以避免程序终止\n\n");
    
    // 以下代码会导致断言失败，在演示时应该注释掉
    
    /*
    // 1. 空指针断言失败
    printf("测试空指针断言...\n");
    calculate_average(NULL, 5);  // 这会导致断言失败
    */
    
    /*
    // 2. 无效大小断言失败
    printf("测试无效大小断言...\n");
    int numbers[] = {1, 2, 3};
    calculate_average(numbers, 0);  // 这会导致断言失败
    */
    
    /*
    // 3. 数组越界断言失败
    printf("测试数组越界断言...\n");
    int numbers[] = {1, 2, 3};
    get_array_element(numbers, 3, 5);  // 这会导致断言失败
    */
    
    /*
    // 4. 除零断言失败
    printf("测试除零断言...\n");
    safe_divide(10.0, 0.0);  // 这会导致断言失败
    */
    
    printf("所有可能导致断言失败的代码都已注释\n");
    printf("要测试断言失败，请取消注释相应代码\n");
}

void demo_conditional_assertions() {
    printf("\n=== 条件断言演示 ===\n");
    
    // 演示复杂的断言条件
    int array[] = {5, 2, 8, 1, 9};
    int n = sizeof(array) / sizeof(array[0]);
    
    // 检查数组是否已排序（升序）
    int is_sorted = 1;
    for (int i = 1; i < n; i++) {
        if (array[i] < array[i-1]) {
            is_sorted = 0;
            break;
        }
    }
    
    printf("数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    printf("数组是否已排序: %s\n", is_sorted ? "是" : "否");
    
    // 注意：这个断言在当前数组下会失败，所以注释掉
    // assert(is_sorted);  // 断言数组已排序
    
    // 演示范围检查断言
    int value = 50;
    int min_val = 0, max_val = 100;
    
    assert(value >= min_val && value <= max_val);  // 检查值在有效范围内
    printf("值 %d 在范围 [%d, %d] 内\n", value, min_val, max_val);
}

void demo_debug_vs_release() {
    printf("\n=== 调试版本 vs 发布版本演示 ===\n");
    
    #ifdef NDEBUG
    printf("当前编译为发布版本 (NDEBUG已定义)\n");
    printf("所有assert宏都被禁用\n");
    #else
    printf("当前编译为调试版本 (NDEBUG未定义)\n");
    printf("所有assert宏都处于活动状态\n");
    #endif
    
    // 这个断言在调试版本中会检查，在发布版本中会被忽略
    int debug_value = 42;
    assert(debug_value == 42);
    
    printf("断言检查完成（如果是发布版本，此检查被跳过）\n");
    
    // 演示性能敏感的断言
    printf("执行性能测试...\n");
    
    for (int i = 0; i < 1000000; i++) {
        // 在调试版本中，这个断言会被执行100万次
        // 在发布版本中，这个断言会被完全忽略
        assert(i >= 0);
        
        // 一些实际工作
        volatile int temp = i * 2;  // volatile防止编译器优化
    }
    
    printf("性能测试完成\n");
}

// 辅助函数声明
void process_positive_number(int n);
int multiply_by_two(int x);
void array_invariant_example(void);

// 检查前置条件
void process_positive_number(int n) {
    assert(n > 0);  // 前置条件：n必须为正数
    // 函数实现...
    printf("处理正数: %d\n", n);
}

// 检查后置条件
int multiply_by_two(int x) {
    int result = x * 2;
    assert(result == x * 2);  // 后置条件：结果应该是输入的两倍
    return result;
}

// 检查不变量
void array_invariant_example(void) {
    int sorted_array[] = {1, 3, 5, 7, 9};
    int size = 5;
    
    // 不变量：数组应该保持排序状态
    for (int i = 1; i < size; i++) {
        assert(sorted_array[i] >= sorted_array[i-1]);
    }
    
    printf("数组不变量检查通过\n");
}

void demo_assertion_best_practices(void) {
    printf("\n=== 断言最佳实践演示 ===\n");
    
    printf("断言的最佳实践：\n");
    printf("1. 断言应该检查程序的逻辑错误，而不是用户错误\n");
    printf("2. 断言中不应该包含有副作用的代码\n");
    printf("3. 断言应该检查函数的前置条件和后置条件\n");
    printf("4. 断言应该用于检查不变量\n");
    printf("5. 在发布版本中，断言会被完全移除\n\n");
    
    // 好的断言使用示例
    
    // 调用示例函数
    process_positive_number(5);
    int doubled = multiply_by_two(21);
    printf("21 * 2 = %d\n", doubled);
    array_invariant_example();
}

void demo_assertion_alternatives(void) {
    printf("\n=== 断言替代方案演示 ===\n");
    
    printf("对于用户输入验证，应该使用错误处理而不是断言：\n");
    
    // 错误的做法（不要这样做）：
    // assert(user_input > 0);  // 用户输入可能为负数，这不是程序错误
    
    // 正确的做法：
    int user_input = -5;  // 模拟用户输入
    
    if (user_input <= 0) {
        printf("错误：输入值必须为正数，当前输入: %d\n", user_input);
        // 返回错误码或采取其他错误处理措施
        return;
    }
    
    printf("对于可恢复的错误，使用错误码或异常处理：\n");
    
    // 文件操作示例
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        printf("警告：无法打开文件，使用默认配置\n");
        // 使用默认配置继续执行
    } else {
        printf("文件打开成功\n");
        fclose(file);
    }
    
    printf("断言 vs 错误处理的选择原则：\n");
    printf("- 程序逻辑错误 → 使用断言\n");
    printf("- 用户输入错误 → 使用错误处理\n");
    printf("- 系统资源问题 → 使用错误处理\n");
    printf("- 网络/IO错误 → 使用错误处理\n");
}

int main(void) {
    printf("C语言 assert.h 标准头文件演示\n");
    printf("================================\n");
    
    #ifdef NDEBUG
    printf("警告：当前编译为发布版本，断言已被禁用\n");
    printf("要查看断言效果，请使用：gcc -g assert_demo.c\n\n");
    #else
    printf("当前编译为调试版本，断言处于活动状态\n");
    printf("要编译发布版本，请使用：gcc -DNDEBUG assert_demo.c\n\n");
    #endif
    
    demo_basic_assertions();
    demo_assertion_failures();
    demo_conditional_assertions();
    demo_debug_vs_release();
    demo_assertion_best_practices();
    demo_assertion_alternatives();
    
    printf("\n演示完成！\n");
    printf("\n重要提示：\n");
    printf("1. 断言是调试工具，在发布版本中会被完全移除\n");
    printf("2. 不要在断言中放置有副作用的代码\n");
    printf("3. 断言失败会导致程序终止，适合捕获程序逻辑错误\n");
    printf("4. 对于用户输入验证，使用正常的错误处理机制\n");
    
    return 0;
}