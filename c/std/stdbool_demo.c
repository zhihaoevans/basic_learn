/*
 * stdbool.h 演示程序
 * 
 * stdbool.h 定义了布尔类型和相关的宏，在C99标准中引入
 * 主要包含：
 * - bool: 布尔类型（实际上是 _Bool 的别名）
 * - true: 真值常量（值为1）
 * - false: 假值常量（值为0）
 * - __bool_true_false_are_defined: 指示宏已定义的标志
 * 
 * 注意：在C23标准中，bool、true、false成为关键字，不再需要包含stdbool.h
 */

#include <stdio.h>
#include <stdbool.h>

// 有副作用的函数，用于演示短路求值
static bool increment_counter(int *counter) {
    (*counter)++;
    printf("  increment_counter被调用，counter = %d\n", *counter);
    return true;
}

// 演示基本布尔类型使用
void demo_basic_bool(void) {
    printf("=== 基本布尔类型演示 ===\n");
    
    // 布尔变量声明和初始化
    bool is_valid = true;
    bool is_empty = false;
    bool result;
    
    printf("bool类型大小: %zu 字节\n", sizeof(bool));
    printf("is_valid = %s (值: %d)\n", is_valid ? "true" : "false", is_valid);
    printf("is_empty = %s (值: %d)\n", is_empty ? "true" : "false", is_empty);
    
    // 布尔运算
    result = is_valid && !is_empty;
    printf("is_valid && !is_empty = %s\n", result ? "true" : "false");
    
    result = is_valid || is_empty;
    printf("is_valid || is_empty = %s\n", result ? "true" : "false");
    
    // 检查宏是否已定义
    #ifdef __bool_true_false_are_defined
    printf("布尔宏已正确定义 (__bool_true_false_are_defined = %d)\n", 
           __bool_true_false_are_defined);
    #endif
    
    printf("\n");
}

// 演示布尔值的转换
void demo_bool_conversion(void) {
    printf("=== 布尔值转换演示 ===\n");
    
    // 整数到布尔的转换
    int numbers[] = {0, 1, -1, 42, 100};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("整数到布尔的转换:\n");
    for (size_t i = 0; i < count; i++) {
        bool b = numbers[i];  // 隐式转换
        printf("  %d -> %s\n", numbers[i], b ? "true" : "false");
    }
    
    // 指针到布尔的转换
    int value = 42;
    int *ptr = &value;
    int *null_ptr = NULL;
    
    printf("\n指针到布尔的转换:\n");
    printf("  有效指针 -> %s\n", ptr ? "true" : "false");
    printf("  NULL指针 -> %s\n", null_ptr ? "true" : "false");
    
    // 浮点数到布尔的转换
    double floats[] = {0.0, 0.1, -0.1, 3.14, -2.71};
    size_t float_count = sizeof(floats) / sizeof(floats[0]);
    
    printf("\n浮点数到布尔的转换:\n");
    for (size_t i = 0; i < float_count; i++) {
        bool b = floats[i];
        printf("  %.2f -> %s\n", floats[i], b ? "true" : "false");
    }
    
    printf("\n");
}

// 演示布尔函数
bool is_even(int n) {
    return n % 2 == 0;
}

bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

bool is_palindrome(const char *str) {
    if (str == NULL) return false;
    
    int len = 0;
    while (str[len] != '\0') len++;  // 计算长度
    
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

void demo_bool_functions(void) {
    printf("=== 布尔函数演示 ===\n");
    
    // 测试偶数判断
    int test_numbers[] = {1, 2, 3, 4, 15, 16, 100, 101};
    size_t count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    printf("偶数判断:\n");
    for (size_t i = 0; i < count; i++) {
        printf("  %d 是偶数: %s\n", test_numbers[i], 
               is_even(test_numbers[i]) ? "是" : "否");
    }
    
    // 测试质数判断
    printf("\n质数判断:\n");
    for (size_t i = 0; i < count; i++) {
        printf("  %d 是质数: %s\n", test_numbers[i], 
               is_prime(test_numbers[i]) ? "是" : "否");
    }
    
    // 测试回文判断
    const char *test_strings[] = {"", "a", "aa", "aba", "abc", "racecar", "hello"};
    size_t str_count = sizeof(test_strings) / sizeof(test_strings[0]);
    
    printf("\n回文判断:\n");
    for (size_t i = 0; i < str_count; i++) {
        printf("  \"%s\" 是回文: %s\n", test_strings[i], 
               is_palindrome(test_strings[i]) ? "是" : "否");
    }
    
    printf("\n");
}

// 演示布尔数组和标志位
void demo_bool_arrays_and_flags(void) {
    printf("=== 布尔数组和标志位演示 ===\n");
    
    // 布尔数组：埃拉托斯特尼筛法找质数
    const int MAX_NUM = 30;
    bool is_prime_arr[MAX_NUM + 1];
    
    // 初始化：假设所有数都是质数
    for (int i = 0; i <= MAX_NUM; i++) {
        is_prime_arr[i] = true;
    }
    
    // 0和1不是质数
    is_prime_arr[0] = is_prime_arr[1] = false;
    
    // 埃拉托斯特尼筛法
    for (int i = 2; i * i <= MAX_NUM; i++) {
        if (is_prime_arr[i]) {
            for (int j = i * i; j <= MAX_NUM; j += i) {
                is_prime_arr[j] = false;
            }
        }
    }
    
    printf("使用埃拉托斯特尼筛法找到的质数 (2-%d):\n", MAX_NUM);
    for (int i = 2; i <= MAX_NUM; i++) {
        if (is_prime_arr[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    // 状态标志示例
    typedef struct {
        bool is_initialized;
        bool is_connected;
        bool has_error;
        bool is_readonly;
        bool is_cached;
    } system_flags_t;
    
    system_flags_t system = {false, false, false, false, false};
    
    printf("\n系统状态标志演示:\n");
    printf("初始状态: 初始化=%s, 连接=%s, 错误=%s, 只读=%s, 缓存=%s\n",
           system.is_initialized ? "是" : "否",
           system.is_connected ? "是" : "否",
           system.has_error ? "是" : "否",
           system.is_readonly ? "是" : "否",
           system.is_cached ? "是" : "否");
    
    // 模拟系统初始化
    system.is_initialized = true;
    system.is_connected = true;
    system.is_cached = true;
    
    printf("初始化后: 初始化=%s, 连接=%s, 错误=%s, 只读=%s, 缓存=%s\n",
           system.is_initialized ? "是" : "否",
           system.is_connected ? "是" : "否",
           system.has_error ? "是" : "否",
           system.is_readonly ? "是" : "否",
           system.is_cached ? "是" : "否");
    
    printf("\n");
}

// 演示条件表达式和短路求值
void demo_conditional_and_short_circuit(void) {
    printf("=== 条件表达式和短路求值演示 ===\n");
    
    // 短路求值演示
    bool a = true, b = false;
    int counter = 0;
    
    printf("短路求值测试:\n");
    
    // AND短路：如果第一个操作数为false，不会计算第二个
    counter = 0;
    printf("false && increment_counter(): ");
    bool result1 = false && increment_counter(&counter);
    printf("结果=%s, counter=%d\n", result1 ? "true" : "false", counter);
    
    // AND不短路：第一个操作数为true，会计算第二个
    counter = 0;
    printf("true && increment_counter(): ");
    bool result2 = true && increment_counter(&counter);
    printf("结果=%s, counter=%d\n", result2 ? "true" : "false", counter);
    
    // OR短路：如果第一个操作数为true，不会计算第二个
    counter = 0;
    printf("true || increment_counter(): ");
    bool result3 = true || increment_counter(&counter);
    printf("结果=%s, counter=%d\n", result3 ? "true" : "false", counter);
    
    // OR不短路：第一个操作数为false，会计算第二个
    counter = 0;
    printf("false || increment_counter(): ");
    bool result4 = false || increment_counter(&counter);
    printf("结果=%s, counter=%d\n", result4 ? "true" : "false", counter);
    
    // 三元运算符
    int x = 10, y = 20;
    int max_val = (x > y) ? x : y;
    printf("\n三元运算符: max(%d, %d) = %d\n", x, y, max_val);
    
    // 复杂条件表达式
    bool is_weekend = true;
    bool is_holiday = false;
    bool can_sleep_in = is_weekend || is_holiday;
    printf("可以睡懒觉: %s (周末=%s, 假期=%s)\n", 
           can_sleep_in ? "是" : "否",
           is_weekend ? "是" : "否",
           is_holiday ? "是" : "否");
    
    printf("\n");
}

// 演示布尔值在控制结构中的使用
void demo_control_structures(void) {
    printf("=== 控制结构中的布尔值演示 ===\n");
    
    // if语句
    bool user_logged_in = true;
    bool has_permission = false;
    
    if (user_logged_in) {
        printf("用户已登录\n");
        if (has_permission) {
            printf("  用户有权限执行操作\n");
        } else {
            printf("  用户没有权限\n");
        }
    } else {
        printf("用户未登录\n");
    }
    
    // while循环
    printf("\n使用布尔值控制循环:\n");
    bool continue_processing = true;
    int iteration = 0;
    
    while (continue_processing && iteration < 5) {
        printf("  处理迭代 %d\n", iteration + 1);
        iteration++;
        
        // 模拟某种条件下停止
        if (iteration >= 3) {
            continue_processing = false;
            printf("  条件满足，停止处理\n");
        }
    }
    
    // for循环中的布尔条件
    printf("\n查找数组中的第一个偶数:\n");
    int numbers[] = {1, 3, 5, 8, 9, 12, 15};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    bool found = false;
    
    for (size_t i = 0; i < count && !found; i++) {
        printf("  检查 %d: ", numbers[i]);
        if (is_even(numbers[i])) {
            printf("找到偶数！\n");
            found = true;
        } else {
            printf("不是偶数\n");
        }
    }
    
    if (!found) {
        printf("  没有找到偶数\n");
    }
    
    printf("\n");
}

// 实际应用示例：简单的配置管理
typedef struct {
    bool debug_mode;
    bool verbose_logging;
    bool auto_save;
    bool network_enabled;
    bool encryption_enabled;
} config_t;

void print_config(const config_t *config) {
    printf("当前配置:\n");
    printf("  调试模式: %s\n", config->debug_mode ? "开启" : "关闭");
    printf("  详细日志: %s\n", config->verbose_logging ? "开启" : "关闭");
    printf("  自动保存: %s\n", config->auto_save ? "开启" : "关闭");
    printf("  网络功能: %s\n", config->network_enabled ? "开启" : "关闭");
    printf("  加密功能: %s\n", config->encryption_enabled ? "开启" : "关闭");
}

bool validate_config(const config_t *config) {
    // 如果启用网络但没有加密，发出警告
    if (config->network_enabled && !config->encryption_enabled) {
        printf("警告: 网络功能已启用但加密功能未启用，存在安全风险\n");
        return false;
    }
    
    // 如果启用详细日志但没有调试模式，可能不合理
    if (config->verbose_logging && !config->debug_mode) {
        printf("提示: 详细日志已启用但调试模式未启用\n");
    }
    
    return true;
}

void demo_practical_example(void) {
    printf("=== 实际应用示例：配置管理 ===\n");
    
    // 默认配置
    config_t config = {
        .debug_mode = false,
        .verbose_logging = false,
        .auto_save = true,
        .network_enabled = true,
        .encryption_enabled = false
    };
    
    printf("默认配置:\n");
    print_config(&config);
    
    printf("\n配置验证: %s\n", validate_config(&config) ? "通过" : "失败");
    
    // 修改配置
    printf("\n启用加密功能...\n");
    config.encryption_enabled = true;
    config.debug_mode = true;
    config.verbose_logging = true;
    
    printf("修改后配置:\n");
    print_config(&config);
    
    printf("\n配置验证: %s\n", validate_config(&config) ? "通过" : "失败");
    
    printf("\n");
}

int main(void) {
    printf("C标准库 stdbool.h 演示程序\n");
    printf("==========================\n\n");
    
    demo_basic_bool();
    demo_bool_conversion();
    demo_bool_functions();
    demo_bool_arrays_and_flags();
    demo_conditional_and_short_circuit();
    demo_control_structures();
    demo_practical_example();
    
    printf("stdbool.h 演示完成！\n");
    printf("\n重要提示:\n");
    printf("1. bool类型实际上是_Bool的别名，大小通常为1字节\n");
    printf("2. true和false是宏，分别定义为1和0\n");
    printf("3. 任何非零值转换为bool都是true，只有0是false\n");
    printf("4. 布尔运算支持短路求值，可以提高效率\n");
    printf("5. 在C23标准中，bool、true、false成为关键字\n");
    
    return 0;
}
