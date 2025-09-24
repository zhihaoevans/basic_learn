/*
 * setjmp.h 演示程序
 * 
 * setjmp.h 提供了非局部跳转功能，允许程序从一个函数跳转到另一个函数
 * 这类似于其他语言中的异常处理机制
 * 
 * 主要功能：
 * - setjmp(): 设置跳转点
 * - longjmp(): 执行非局部跳转
 * - jmp_buf: 存储跳转环境的类型
 * 
 * 编译: gcc -o setjmp_demo setjmp_demo.c
 * 运行: ./setjmp_demo
 */

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

// 全局跳转缓冲区
jmp_buf jump_buffer;
jmp_buf error_buffer;

// 函数声明
void demo_basic_setjmp(void);
void demo_error_handling(void);
void demo_nested_calls(void);
void demo_exception_simulation(void);
void demo_cleanup_with_setjmp(void);
void demo_calculator_with_error_handling(void);

// 辅助函数声明
void deep_function_call(int level);
int divide_with_error_check(int a, int b);
void risky_operation(int value);
void cleanup_resources(void);
double safe_sqrt(double x);
int safe_factorial(int n);

int main(void) {
    printf("=== setjmp.h 演示程序 ===\n\n");
    
    demo_basic_setjmp();
    demo_error_handling();
    demo_nested_calls();
    demo_exception_simulation();
    demo_cleanup_with_setjmp();
    demo_calculator_with_error_handling();
    
    return 0;
}

/*
 * 基本的 setjmp/longjmp 使用
 */
void demo_basic_setjmp(void) {
    printf("1. 基本的 setjmp/longjmp 使用\n");
    printf("================================\n");
    
    int result = setjmp(jump_buffer);
    
    if (result == 0) {
        printf("第一次调用 setjmp，返回值: %d\n", result);
        printf("准备执行 longjmp...\n");
        longjmp(jump_buffer, 42);  // 跳转回 setjmp，返回值为 42
        printf("这行代码不会被执行\n");
    } else {
        printf("从 longjmp 返回，返回值: %d\n", result);
    }
    
    printf("\n");
}

/*
 * 错误处理演示
 */
void demo_error_handling(void) {
    printf("2. 错误处理演示\n");
    printf("================\n");
    
    int error_code = setjmp(error_buffer);
    
    if (error_code == 0) {
        printf("开始执行可能出错的操作...\n");
        
        // 模拟不同的错误情况
        int test_values[] = {10, 0, -5};
        for (int i = 0; i < 3; i++) {
            printf("测试除法: 100 / %d = ", test_values[i]);
            int result = divide_with_error_check(100, test_values[i]);
            printf("%d\n", result);
        }
    } else {
        printf("捕获到错误，错误代码: %d\n", error_code);
        switch (error_code) {
            case 1:
                printf("错误类型: 除零错误\n");
                break;
            case 2:
                printf("错误类型: 负数错误\n");
                break;
            default:
                printf("错误类型: 未知错误\n");
        }
    }
    
    printf("\n");
}

/*
 * 嵌套函数调用中的跳转
 */
void demo_nested_calls(void) {
    printf("3. 嵌套函数调用中的跳转\n");
    printf("========================\n");
    
    jmp_buf nested_buffer;
    int result = setjmp(nested_buffer);
    
    if (result == 0) {
        printf("开始深层函数调用...\n");
        // 将跳转缓冲区传递给深层函数
        memcpy(jump_buffer, nested_buffer, sizeof(jmp_buf));
        deep_function_call(1);
        printf("这行代码不会被执行\n");
    } else {
        printf("从深层函数跳转回来，层级: %d\n", result);
    }
    
    printf("\n");
}

/*
 * 异常模拟演示
 */
void demo_exception_simulation(void) {
    printf("4. 异常模拟演示\n");
    printf("================\n");
    
    jmp_buf exception_buffer;
    int exception_code = setjmp(exception_buffer);
    
    if (exception_code == 0) {
        printf("执行可能抛出异常的操作...\n");
        
        // 将异常缓冲区设置为全局
        memcpy(jump_buffer, exception_buffer, sizeof(jmp_buf));
        
        // 测试不同的风险操作
        int test_cases[] = {5, 0, -3, 100};
        for (int i = 0; i < 4; i++) {
            printf("测试值: %d\n", test_cases[i]);
            risky_operation(test_cases[i]);
        }
        
        printf("所有操作成功完成\n");
    } else {
        printf("捕获到异常，异常代码: %d\n", exception_code);
        switch (exception_code) {
            case 10:
                printf("异常类型: 零值异常\n");
                break;
            case 20:
                printf("异常类型: 负值异常\n");
                break;
            case 30:
                printf("异常类型: 值过大异常\n");
                break;
            default:
                printf("异常类型: 未知异常\n");
        }
    }
    
    printf("\n");
}

/*
 * 带资源清理的 setjmp 使用
 */
void demo_cleanup_with_setjmp(void) {
    printf("5. 带资源清理的 setjmp 使用\n");
    printf("============================\n");
    
    jmp_buf cleanup_buffer;
    int cleanup_code = setjmp(cleanup_buffer);
    
    if (cleanup_code == 0) {
        printf("分配资源...\n");
        char *buffer = malloc(1024);
        FILE *file = fopen("temp.txt", "w");
        
        if (!buffer || !file) {
            printf("资源分配失败\n");
            cleanup_resources();
            return;
        }
        
        printf("使用资源进行操作...\n");
        fprintf(file, "测试数据\n");
        strcpy(buffer, "临时数据");
        
        // 模拟可能的错误
        if (rand() % 2) {
            printf("模拟操作失败，准备清理...\n");
            fclose(file);
            free(buffer);
            longjmp(cleanup_buffer, 1);
        }
        
        printf("操作成功完成\n");
        fclose(file);
        free(buffer);
        remove("temp.txt");
    } else {
        printf("从错误处理返回，已执行清理操作\n");
    }
    
    printf("\n");
}

/*
 * 实用示例：带错误处理的计算器
 */
void demo_calculator_with_error_handling(void) {
    printf("6. 实用示例：带错误处理的计算器\n");
    printf("================================\n");
    
    jmp_buf calc_buffer;
    int error_type = setjmp(calc_buffer);
    
    if (error_type == 0) {
        // 将计算器缓冲区设置为全局
        memcpy(jump_buffer, calc_buffer, sizeof(jmp_buf));
        
        printf("执行数学计算...\n");
        
        // 测试平方根计算
        double sqrt_values[] = {16.0, 25.0, -4.0, 0.0};
        for (int i = 0; i < 4; i++) {
            printf("sqrt(%.1f) = %.2f\n", sqrt_values[i], safe_sqrt(sqrt_values[i]));
        }
        
        // 测试阶乘计算
        int fact_values[] = {5, 0, -3, 15};
        for (int i = 0; i < 4; i++) {
            printf("%d! = %d\n", fact_values[i], safe_factorial(fact_values[i]));
        }
        
        printf("所有计算完成\n");
    } else {
        printf("计算错误，错误类型: %d\n", error_type);
        switch (error_type) {
            case 100:
                printf("数学错误: 负数开平方根\n");
                break;
            case 200:
                printf("数学错误: 负数阶乘\n");
                break;
            case 300:
                printf("数学错误: 阶乘溢出\n");
                break;
            default:
                printf("未知数学错误\n");
        }
    }
    
    printf("\n");
}

// 辅助函数实现

/*
 * 深层函数调用
 */
void deep_function_call(int level) {
    printf("进入函数层级: %d\n", level);
    
    if (level < 5) {
        deep_function_call(level + 1);
    } else {
        printf("到达最深层级，准备跳转...\n");
        longjmp(jump_buffer, level);
    }
    
    printf("从层级 %d 返回\n", level);
}

/*
 * 带错误检查的除法
 */
int divide_with_error_check(int a, int b) {
    if (b == 0) {
        longjmp(error_buffer, 1);  // 除零错误
    }
    if (b < 0) {
        longjmp(error_buffer, 2);  // 负数错误
    }
    return a / b;
}

/*
 * 风险操作模拟
 */
void risky_operation(int value) {
    if (value == 0) {
        longjmp(jump_buffer, 10);  // 零值异常
    }
    if (value < 0) {
        longjmp(jump_buffer, 20);  // 负值异常
    }
    if (value > 50) {
        longjmp(jump_buffer, 30);  // 值过大异常
    }
    
    printf("  操作成功，值: %d\n", value);
}

/*
 * 资源清理函数
 */
void cleanup_resources(void) {
    printf("执行资源清理...\n");
    // 这里可以添加实际的清理代码
}

/*
 * 安全的平方根计算
 */
double safe_sqrt(double x) {
    if (x < 0) {
        longjmp(jump_buffer, 100);  // 负数开平方根错误
    }
    
    // 简单的平方根计算（牛顿法）
    if (x == 0) return 0;
    
    double guess = x / 2.0;
    double prev_guess;
    
    do {
        prev_guess = guess;
        guess = (guess + x / guess) / 2.0;
    } while (guess != prev_guess && guess - prev_guess > 0.000001);
    
    return guess;
}

/*
 * 安全的阶乘计算
 */
int safe_factorial(int n) {
    if (n < 0) {
        longjmp(jump_buffer, 200);  // 负数阶乘错误
    }
    
    if (n > 12) {  // 防止整数溢出
        longjmp(jump_buffer, 300);  // 阶乘溢出错误
    }
    
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    
    return result;
}
