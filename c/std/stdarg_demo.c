/*
 * stdarg.h 演示程序
 * 
 * stdarg.h 提供了处理可变参数函数的宏和类型
 * 允许函数接受不定数量的参数
 * 
 * 主要功能：
 * - va_list: 存储可变参数信息的类型
 * - va_start(): 初始化可变参数列表
 * - va_arg(): 获取下一个参数
 * - va_end(): 清理可变参数列表
 * - va_copy(): 复制可变参数列表 (C99)
 * 
 * 编译: gcc -o stdarg_demo stdarg_demo.c
 * 运行: ./stdarg_demo
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 函数声明
void demo_basic_variadic(void);
void demo_printf_like_function(void);
void demo_mathematical_operations(void);
void demo_string_operations(void);
void demo_type_safe_variadic(void);
void demo_va_copy_usage(void);
void demo_practical_logger(void);

// 可变参数函数声明
int sum_integers(int count, ...);
double average(int count, ...);
void my_printf(const char *format, ...);
char* string_concat(int count, ...);
int find_max(int count, ...);
int find_min(int count, ...);
void print_formatted_data(const char *format, ...);
void log_message(int level, const char *format, ...);
void debug_print(const char *file, int line, const char *format, ...);

// 类型安全的可变参数函数
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_END
} arg_type_t;

void print_typed_args(arg_type_t first_type, ...);
double calculate_expression(const char *operation, int count, ...);

int main(void) {
    printf("=== stdarg.h 演示程序 ===\n\n");
    
    demo_basic_variadic();
    demo_printf_like_function();
    demo_mathematical_operations();
    demo_string_operations();
    demo_type_safe_variadic();
    demo_va_copy_usage();
    demo_practical_logger();
    
    return 0;
}

/*
 * 基本可变参数使用
 */
void demo_basic_variadic(void) {
    printf("1. 基本可变参数使用\n");
    printf("====================\n");
    
    // 整数求和
    printf("整数求和演示:\n");
    printf("sum(3, 1, 2, 3) = %d\n", sum_integers(3, 1, 2, 3));
    printf("sum(5, 10, 20, 30, 40, 50) = %d\n", sum_integers(5, 10, 20, 30, 40, 50));
    printf("sum(1, 100) = %d\n", sum_integers(1, 100));
    
    // 平均值计算
    printf("\n平均值计算演示:\n");
    printf("average(3, 1, 2, 3) = %.2f\n", average(3, 1, 2, 3));
    printf("average(4, 85, 90, 78, 92) = %.2f\n", average(4, 85, 90, 78, 92));
    printf("average(2, 100, 200) = %.2f\n", average(2, 100, 200));
    
    printf("\n");
}

/*
 * printf 类似函数演示
 */
void demo_printf_like_function(void) {
    printf("2. printf 类似函数演示\n");
    printf("=======================\n");
    
    printf("使用自定义 my_printf 函数:\n");
    my_printf("Hello, %s! You are %d years old.\n", "Alice", 25);
    my_printf("Pi is approximately %.2f\n", 3.14159);
    my_printf("Character: %c, Integer: %d, String: %s\n", 'A', 42, "World");
    
    printf("\n格式化数据打印:\n");
    print_formatted_data("Student: %s, Age: %d, GPA: %.2f", "Bob", 20, 3.75);
    print_formatted_data("Product: %s, Price: $%.2f, Stock: %d", "Laptop", 999.99, 15);
    
    printf("\n");
}

/*
 * 数学运算演示
 */
void demo_mathematical_operations(void) {
    printf("3. 数学运算演示\n");
    printf("================\n");
    
    // 查找最大值和最小值
    printf("查找最大值:\n");
    printf("max(5, 3, 7, 1, 9, 2) = %d\n", find_max(6, 3, 7, 1, 9, 2, 5));
    printf("max(3, 100, 50, 75) = %d\n", find_max(3, 100, 50, 75));
    
    printf("\n查找最小值:\n");
    printf("min(5, 3, 7, 1, 9, 2) = %d\n", find_min(6, 3, 7, 1, 9, 2, 5));
    printf("min(3, 100, 50, 75) = %d\n", find_min(3, 100, 50, 75));
    
    // 表达式计算
    printf("\n表达式计算:\n");
    printf("add(3, 10, 20, 30) = %.2f\n", calculate_expression("add", 3, 10.0, 20.0, 30.0));
    printf("multiply(4, 2, 3, 4, 5) = %.2f\n", calculate_expression("multiply", 4, 2.0, 3.0, 4.0, 5.0));
    printf("average(5, 1, 2, 3, 4, 5) = %.2f\n", calculate_expression("average", 5, 1.0, 2.0, 3.0, 4.0, 5.0));
    
    printf("\n");
}

/*
 * 字符串操作演示
 */
void demo_string_operations(void) {
    printf("4. 字符串操作演示\n");
    printf("==================\n");
    
    // 字符串连接
    printf("字符串连接演示:\n");
    char *result1 = string_concat(3, "Hello", " ", "World!");
    printf("concat(\"Hello\", \" \", \"World!\") = \"%s\"\n", result1);
    free(result1);
    
    char *result2 = string_concat(5, "C", " is", " a", " great", " language");
    printf("concat(5 strings) = \"%s\"\n", result2);
    free(result2);
    
    char *result3 = string_concat(1, "Single string");
    printf("concat(1 string) = \"%s\"\n", result3);
    free(result3);
    
    printf("\n");
}

/*
 * 类型安全的可变参数演示
 */
void demo_type_safe_variadic(void) {
    printf("5. 类型安全的可变参数演示\n");
    printf("==========================\n");
    
    printf("类型安全的参数打印:\n");
    print_typed_args(TYPE_INT, 42, 
                     TYPE_DOUBLE, 3.14159, 
                     TYPE_STRING, "Hello World", 
                     TYPE_INT, 100, 
                     TYPE_END);
    
    print_typed_args(TYPE_STRING, "Name: Alice", 
                     TYPE_INT, 25, 
                     TYPE_DOUBLE, 98.6, 
                     TYPE_STRING, "Status: Active", 
                     TYPE_END);
    
    printf("\n");
}

/*
 * va_copy 使用演示
 */
void demo_va_copy_usage(void) {
    printf("6. va_copy 使用演示\n");
    printf("===================\n");
    
    // 这个演示需要一个使用 va_copy 的函数
    printf("va_copy 允许复制可变参数列表，用于多次遍历参数\n");
    printf("在实际应用中，这对于需要多次处理相同参数列表的函数很有用\n");
    
    printf("\n");
}

/*
 * 实用日志系统演示
 */
void demo_practical_logger(void) {
    printf("7. 实用日志系统演示\n");
    printf("====================\n");
    
    printf("日志系统演示:\n");
    log_message(1, "System started successfully");
    log_message(2, "User %s logged in from IP %s", "admin", "192.168.1.100");
    log_message(3, "Warning: Memory usage at %.1f%%", 85.5);
    log_message(4, "Error: Failed to connect to database after %d attempts", 3);
    
    printf("\n调试信息演示:\n");
    debug_print(__FILE__, __LINE__, "Debug: Variable x = %d, y = %.2f", 42, 3.14);
    debug_print(__FILE__, __LINE__, "Debug: Processing user %s with ID %d", "user123", 456);
    
    printf("\n");
}

// 可变参数函数实现

/*
 * 整数求和函数
 */
int sum_integers(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);
    }
    
    va_end(args);
    return sum;
}

/*
 * 平均值计算函数
 */
double average(int count, ...) {
    if (count <= 0) return 0.0;
    
    va_list args;
    va_start(args, count);
    
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);  // 注意：小于int的类型会被提升为int
    }
    
    va_end(args);
    return sum / count;
}

/*
 * 简化的 printf 实现
 */
void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // 使用 vprintf 处理可变参数
    vprintf(format, args);
    
    va_end(args);
}

/*
 * 字符串连接函数
 */
char* string_concat(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // 首先计算总长度
    size_t total_length = 0;
    va_list args_copy;
    va_copy(args_copy, args);  // 复制参数列表
    
    for (int i = 0; i < count; i++) {
        const char *str = va_arg(args_copy, const char*);
        total_length += strlen(str);
    }
    va_end(args_copy);
    
    // 分配内存
    char *result = malloc(total_length + 1);
    if (!result) {
        va_end(args);
        return NULL;
    }
    
    // 连接字符串
    result[0] = '\0';
    for (int i = 0; i < count; i++) {
        const char *str = va_arg(args, const char*);
        strcat(result, str);
    }
    
    va_end(args);
    return result;
}

/*
 * 查找最大值函数
 */
int find_max(int count, ...) {
    if (count <= 0) return 0;
    
    va_list args;
    va_start(args, count);
    
    int max = va_arg(args, int);
    for (int i = 1; i < count; i++) {
        int current = va_arg(args, int);
        if (current > max) {
            max = current;
        }
    }
    
    va_end(args);
    return max;
}

/*
 * 查找最小值函数
 */
int find_min(int count, ...) {
    if (count <= 0) return 0;
    
    va_list args;
    va_start(args, count);
    
    int min = va_arg(args, int);
    for (int i = 1; i < count; i++) {
        int current = va_arg(args, int);
        if (current < min) {
            min = current;
        }
    }
    
    va_end(args);
    return min;
}

/*
 * 格式化数据打印函数
 */
void print_formatted_data(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    printf("Formatted: ");
    vprintf(format, args);
    printf("\n");
    
    va_end(args);
}

/*
 * 类型安全的参数打印函数
 */
void print_typed_args(arg_type_t first_type, ...) {
    va_list args;
    va_start(args, first_type);
    
    arg_type_t type = first_type;
    printf("Typed arguments: ");
    
    while (type != TYPE_END) {
        switch (type) {
            case TYPE_INT: {
                int value = va_arg(args, int);
                printf("[INT: %d] ", value);
                break;
            }
            case TYPE_DOUBLE: {
                double value = va_arg(args, double);
                printf("[DOUBLE: %.2f] ", value);
                break;
            }
            case TYPE_STRING: {
                const char *value = va_arg(args, const char*);
                printf("[STRING: %s] ", value);
                break;
            }
            default:
                printf("[UNKNOWN] ");
                break;
        }
        type = va_arg(args, arg_type_t);
    }
    
    printf("\n");
    va_end(args);
}

/*
 * 表达式计算函数
 */
double calculate_expression(const char *operation, int count, ...) {
    if (count <= 0) return 0.0;
    
    va_list args;
    va_start(args, count);
    
    double result = va_arg(args, double);
    
    if (strcmp(operation, "add") == 0) {
        for (int i = 1; i < count; i++) {
            result += va_arg(args, double);
        }
    } else if (strcmp(operation, "multiply") == 0) {
        for (int i = 1; i < count; i++) {
            result *= va_arg(args, double);
        }
    } else if (strcmp(operation, "average") == 0) {
        for (int i = 1; i < count; i++) {
            result += va_arg(args, double);
        }
        result /= count;
    } else {
        // 未知操作，返回第一个参数
        for (int i = 1; i < count; i++) {
            va_arg(args, double);  // 消费剩余参数
        }
    }
    
    va_end(args);
    return result;
}

/*
 * 日志消息函数
 */
void log_message(int level, const char *format, ...) {
    const char *level_names[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    const char *level_name = (level >= 1 && level <= 4) ? level_names[level-1] : "UNKNOWN";
    
    printf("[%s] ", level_name);
    
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    printf("\n");
}

/*
 * 调试打印函数
 */
void debug_print(const char *file, int line, const char *format, ...) {
    printf("[DEBUG %s:%d] ", file, line);
    
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    printf("\n");
}
