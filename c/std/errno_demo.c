/*
 * errno.h 演示程序
 * 
 * errno.h 定义了错误报告机制，用于指示库函数调用中发生的错误
 * 主要包含：
 * - errno: 全局错误码变量
 * - 各种错误码常量：EDOM, ERANGE, EILSEQ 等
 * - 在某些系统上还包含更多POSIX错误码
 * 
 * errno的使用规则：
 * 1. 调用库函数前应将errno设为0
 * 2. 函数调用后检查返回值，如果表示错误则检查errno
 * 3. errno只在函数返回错误时才有意义
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

// 演示基本的errno使用
void demo_basic_errno(void) {
    printf("=== 基本errno使用演示 ===\n");
    
    // 显示初始errno值
    printf("初始errno值: %d\n", errno);
    
    // 清除errno
    errno = 0;
    printf("清除后errno值: %d\n", errno);
    
    // 故意触发数学错误：对负数开平方根
    errno = 0;  // 清除errno
    double result = sqrt(-1.0);
    
    if (errno != 0) {
        printf("sqrt(-1.0) 产生错误:\n");
        printf("  返回值: %f\n", result);
        printf("  errno: %d\n", errno);
        printf("  错误描述: %s\n", strerror(errno));
        
        // 检查具体的错误类型
        if (errno == EDOM) {
            printf("  错误类型: EDOM (域错误)\n");
        }
    }
    
    printf("\n");
}

// 演示数学函数的错误处理
void demo_math_errors(void) {
    printf("=== 数学函数错误处理演示 ===\n");
    
    // 域错误 (EDOM)
    printf("域错误示例:\n");
    
    errno = 0;
    double result1 = acos(2.0);  // acos的定义域是[-1, 1]
    if (errno == EDOM) {
        printf("  acos(2.0): 域错误, 返回值=%f\n", result1);
    }
    
    errno = 0;
    double result2 = log(-1.0);  // log的定义域是(0, +∞)
    if (errno == EDOM) {
        printf("  log(-1.0): 域错误, 返回值=%f\n", result2);
    }
    
    // 范围错误 (ERANGE)
    printf("\n范围错误示例:\n");
    
    errno = 0;
    double result3 = exp(1000.0);  // 结果太大，溢出
    if (errno == ERANGE) {
        printf("  exp(1000.0): 范围错误(溢出), 返回值=%f\n", result3);
    }
    
    errno = 0;
    double result4 = exp(-1000.0);  // 结果太小，下溢
    if (errno == ERANGE) {
        printf("  exp(-1000.0): 范围错误(下溢), 返回值=%f\n", result4);
    }
    
    errno = 0;
    double result5 = pow(10.0, 400.0);  // 结果溢出
    if (errno == ERANGE) {
        printf("  pow(10.0, 400.0): 范围错误(溢出), 返回值=%f\n", result5);
    }
    
    printf("\n");
}

// 演示字符串转换函数的错误处理
void demo_string_conversion_errors(void) {
    printf("=== 字符串转换错误处理演示 ===\n");
    
    char *endptr;
    long result;
    
    // 正常转换
    errno = 0;
    result = strtol("12345", &endptr, 10);
    printf("strtol(\"12345\"):\n");
    printf("  结果: %ld, errno: %d, 剩余字符: \"%s\"\n", result, errno, endptr);
    
    // 溢出错误
    errno = 0;
    result = strtol("999999999999999999999", &endptr, 10);
    printf("\nstrtol(\"999999999999999999999\"):\n");
    printf("  结果: %ld, errno: %d", result, errno);
    if (errno == ERANGE) {
        printf(" (ERANGE - 溢出)");
        if (result == LONG_MAX) {
            printf(" - 正溢出");
        } else if (result == LONG_MIN) {
            printf(" - 负溢出");
        }
    }
    printf("\n  剩余字符: \"%s\"\n", endptr);
    
    // 下溢错误
    errno = 0;
    result = strtol("-999999999999999999999", &endptr, 10);
    printf("\nstrtol(\"-999999999999999999999\"):\n");
    printf("  结果: %ld, errno: %d", result, errno);
    if (errno == ERANGE) {
        printf(" (ERANGE - 下溢)");
    }
    printf("\n  剩余字符: \"%s\"\n", endptr);
    
    // 无效输入
    errno = 0;
    result = strtol("abc123", &endptr, 10);
    printf("\nstrtol(\"abc123\"):\n");
    printf("  结果: %ld, errno: %d, 剩余字符: \"%s\"\n", result, errno, endptr);
    
    // 部分有效输入
    errno = 0;
    result = strtol("123abc", &endptr, 10);
    printf("\nstrtol(\"123abc\"):\n");
    printf("  结果: %ld, errno: %d, 剩余字符: \"%s\"\n", result, errno, endptr);
    
    printf("\n");
}

// 演示文件操作的错误处理
void demo_file_errors(void) {
    printf("=== 文件操作错误处理演示 ===\n");
    
    FILE *file;
    
    // 尝试打开不存在的文件
    errno = 0;
    file = fopen("nonexistent_file.txt", "r");
    if (file == NULL) {
        printf("打开不存在文件失败:\n");
        printf("  errno: %d\n", errno);
        printf("  错误描述: %s\n", strerror(errno));
        
        // 在POSIX系统上，可能是ENOENT错误
        #ifdef ENOENT
        if (errno == ENOENT) {
            printf("  错误类型: ENOENT (文件或目录不存在)\n");
        }
        #endif
    }
    
    // 创建一个临时文件用于测试
    file = fopen("temp_test.txt", "w");
    if (file != NULL) {
        fprintf(file, "测试内容\n");
        fclose(file);
        printf("\n创建临时文件成功\n");
        
        // 尝试以写模式打开只读文件（在某些系统上可能失败）
        // 这里我们先将文件设为只读（在实际应用中）
        
        // 正常读取文件
        errno = 0;
        file = fopen("temp_test.txt", "r");
        if (file != NULL) {
            char buffer[100];
            if (fgets(buffer, sizeof(buffer), file) != NULL) {
                printf("读取文件内容: %s", buffer);
            }
            fclose(file);
        }
        
        // 清理临时文件
        if (remove("temp_test.txt") == 0) {
            printf("临时文件已删除\n");
        } else {
            printf("删除临时文件失败: %s\n", strerror(errno));
        }
    }
    
    printf("\n");
}

// 演示内存分配错误处理
void demo_memory_errors(void) {
    printf("=== 内存分配错误处理演示 ===\n");
    
    // 正常内存分配
    errno = 0;
    void *ptr = malloc(1024);
    if (ptr != NULL) {
        printf("分配1024字节内存成功\n");
        free(ptr);
    } else {
        printf("内存分配失败: %s\n", strerror(errno));
    }
    
    // 尝试分配大量内存（可能失败）
    errno = 0;
    size_t huge_size = SIZE_MAX / 2;  // 尝试分配很大的内存
    ptr = malloc(huge_size);
    if (ptr != NULL) {
        printf("分配大量内存成功（意外！）\n");
        free(ptr);
    } else {
        printf("分配大量内存失败:\n");
        printf("  请求大小: %zu 字节\n", huge_size);
        printf("  errno: %d\n", errno);
        printf("  错误描述: %s\n", strerror(errno));
        
        #ifdef ENOMEM
        if (errno == ENOMEM) {
            printf("  错误类型: ENOMEM (内存不足)\n");
        }
        #endif
    }
    
    printf("\n");
}

// 安全的错误处理包装函数
double safe_sqrt(double x, int *error_flag) {
    if (error_flag) *error_flag = 0;
    
    errno = 0;
    double result = sqrt(x);
    
    if (errno != 0) {
        if (error_flag) *error_flag = errno;
        printf("警告: sqrt(%.2f) 产生错误: %s\n", x, strerror(errno));
    }
    
    return result;
}

FILE* safe_fopen(const char *filename, const char *mode) {
    errno = 0;
    FILE *file = fopen(filename, mode);
    
    if (file == NULL) {
        printf("错误: 无法打开文件 \"%s\" (模式: %s): %s\n", 
               filename, mode, strerror(errno));
    }
    
    return file;
}

void* safe_malloc(size_t size) {
    errno = 0;
    void *ptr = malloc(size);
    
    if (ptr == NULL && size > 0) {
        printf("错误: 无法分配 %zu 字节内存: %s\n", size, strerror(errno));
    }
    
    return ptr;
}

void demo_safe_wrappers(void) {
    printf("=== 安全包装函数演示 ===\n");
    
    // 使用安全的sqrt函数
    int error;
    double values[] = {4.0, -1.0, 0.0, 16.0};
    size_t count = sizeof(values) / sizeof(values[0]);
    
    printf("安全sqrt函数测试:\n");
    for (size_t i = 0; i < count; i++) {
        double result = safe_sqrt(values[i], &error);
        printf("  sqrt(%.1f) = %.2f", values[i], result);
        if (error != 0) {
            printf(" [错误码: %d]", error);
        }
        printf("\n");
    }
    
    // 使用安全的文件打开函数
    printf("\n安全文件操作测试:\n");
    FILE *file = safe_fopen("nonexistent.txt", "r");
    if (file == NULL) {
        printf("  如预期，文件打开失败\n");
    }
    
    // 使用安全的内存分配函数
    printf("\n安全内存分配测试:\n");
    void *ptr1 = safe_malloc(1024);
    if (ptr1 != NULL) {
        printf("  分配1024字节成功\n");
        free(ptr1);
    }
    
    void *ptr2 = safe_malloc(SIZE_MAX);
    if (ptr2 == NULL) {
        printf("  如预期，大内存分配失败\n");
    }
    
    printf("\n");
}

// 演示错误码的分类和处理策略
void demo_error_categories(void) {
    printf("=== 错误码分类和处理策略演示 ===\n");
    
    printf("标准C错误码:\n");
    printf("  EDOM (%d): 数学函数域错误\n", EDOM);
    printf("  ERANGE (%d): 数学函数范围错误\n", ERANGE);
    printf("  EILSEQ (%d): 非法字节序列\n", EILSEQ);
    
    // 在POSIX系统上可能有更多错误码
    #ifdef ENOENT
    printf("\n常见POSIX错误码:\n");
    printf("  ENOENT (%d): 文件或目录不存在\n", ENOENT);
    #endif
    
    #ifdef EACCES
    printf("  EACCES (%d): 权限被拒绝\n", EACCES);
    #endif
    
    #ifdef ENOMEM
    printf("  ENOMEM (%d): 内存不足\n", ENOMEM);
    #endif
    
    #ifdef EINVAL
    printf("  EINVAL (%d): 无效参数\n", EINVAL);
    #endif
    
    // 错误处理策略示例
    printf("\n错误处理策略:\n");
    printf("1. 可恢复错误 - 重试或使用备选方案\n");
    printf("2. 不可恢复错误 - 清理资源并退出\n");
    printf("3. 用户错误 - 提示用户修正输入\n");
    printf("4. 系统错误 - 记录日志并报告\n");
    
    printf("\n");
}

// 实际应用示例：配置文件读取器
typedef struct {
    char key[64];
    char value[256];
} config_item_t;

int read_config_file(const char *filename, config_item_t *items, size_t max_items) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("错误: 无法打开配置文件 \"%s\": %s\n", filename, strerror(errno));
        return -1;
    }
    
    char line[512];
    size_t count = 0;
    int line_number = 0;
    
    while (fgets(line, sizeof(line), file) != NULL && count < max_items) {
        line_number++;
        
        // 跳过空行和注释
        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }
        
        // 解析键值对
        char *equals = strchr(line, '=');
        if (equals == NULL) {
            printf("警告: 第%d行格式错误，跳过\n", line_number);
            continue;
        }
        
        *equals = '\0';
        char *key = line;
        char *value = equals + 1;
        
        // 移除换行符
        char *newline = strchr(value, '\n');
        if (newline) *newline = '\0';
        
        // 复制到结构体
        strncpy(items[count].key, key, sizeof(items[count].key) - 1);
        strncpy(items[count].value, value, sizeof(items[count].value) - 1);
        items[count].key[sizeof(items[count].key) - 1] = '\0';
        items[count].value[sizeof(items[count].value) - 1] = '\0';
        
        count++;
    }
    
    fclose(file);
    return (int)count;
}

void demo_practical_example(void) {
    printf("=== 实际应用示例：配置文件读取器 ===\n");
    
    // 创建一个示例配置文件
    FILE *config_file = fopen("example.conf", "w");
    if (config_file != NULL) {
        fprintf(config_file, "# 示例配置文件\n");
        fprintf(config_file, "server_port=8080\n");
        fprintf(config_file, "max_connections=100\n");
        fprintf(config_file, "debug_mode=true\n");
        fprintf(config_file, "log_file=/var/log/app.log\n");
        fclose(config_file);
        printf("创建示例配置文件成功\n");
    }
    
    // 读取配置文件
    config_item_t items[10];
    int count = read_config_file("example.conf", items, 10);
    
    if (count > 0) {
        printf("成功读取 %d 个配置项:\n", count);
        for (int i = 0; i < count; i++) {
            printf("  %s = %s\n", items[i].key, items[i].value);
        }
    } else if (count == 0) {
        printf("配置文件为空或没有有效配置项\n");
    }
    // count < 0 的情况已在函数内处理
    
    // 尝试读取不存在的文件
    printf("\n尝试读取不存在的文件:\n");
    read_config_file("nonexistent.conf", items, 10);
    
    // 清理
    if (remove("example.conf") == 0) {
        printf("\n示例配置文件已删除\n");
    }
    
    printf("\n");
}

int main(void) {
    printf("C标准库 errno.h 演示程序\n");
    printf("========================\n\n");
    
    demo_basic_errno();
    demo_math_errors();
    demo_string_conversion_errors();
    demo_file_errors();
    demo_memory_errors();
    demo_safe_wrappers();
    demo_error_categories();
    demo_practical_example();
    
    printf("errno.h 演示完成！\n");
    printf("\n重要提示:\n");
    printf("1. errno是全局变量，多线程环境下需要特别注意\n");
    printf("2. 只有在函数返回错误时，errno才有意义\n");
    printf("3. 调用可能修改errno的函数前，应先清零errno\n");
    printf("4. 使用strerror()获取错误描述字符串\n");
    printf("5. 不同系统可能有不同的错误码，编写可移植代码时需注意\n");
    
    return 0;
}
