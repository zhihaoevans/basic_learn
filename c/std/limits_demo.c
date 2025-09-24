/*
 * limits_demo.c - C标准库 limits.h 头文件演示
 * 
 * limits.h 定义了各种整数类型的最大值和最小值常量
 * 这些常量在编写可移植代码时非常有用
 */

#include <stdio.h>
#include <limits.h>

// 演示函数声明
void demonstrate_char_limits(void);
void demonstrate_short_limits(void);
void demonstrate_int_limits(void);
void demonstrate_long_limits(void);
void demonstrate_long_long_limits(void);
void demonstrate_practical_usage(void);
void check_overflow_conditions(void);
void demonstrate_bit_calculations(void);

int main(void) {
    printf("=== C标准库 limits.h 演示 ===\n\n");
    
    demonstrate_char_limits();
    demonstrate_short_limits();
    demonstrate_int_limits();
    demonstrate_long_limits();
    demonstrate_long_long_limits();
    demonstrate_practical_usage();
    check_overflow_conditions();
    demonstrate_bit_calculations();
    
    return 0;
}

void demonstrate_char_limits(void) {
    printf("1. 字符类型限制 (char limits):\n");
    printf("   CHAR_BIT (每个字符的位数): %d\n", CHAR_BIT);
    printf("   CHAR_MIN (char最小值): %d\n", CHAR_MIN);
    printf("   CHAR_MAX (char最大值): %d\n", CHAR_MAX);
    printf("   SCHAR_MIN (signed char最小值): %d\n", SCHAR_MIN);
    printf("   SCHAR_MAX (signed char最大值): %d\n", SCHAR_MAX);
    printf("   UCHAR_MAX (unsigned char最大值): %u\n", UCHAR_MAX);
    
    // 演示字符类型的使用
    char c = CHAR_MAX;
    unsigned char uc = UCHAR_MAX;
    printf("   char变量存储最大值: %d\n", c);
    printf("   unsigned char变量存储最大值: %u\n", uc);
    printf("\n");
}

void demonstrate_short_limits(void) {
    printf("2. 短整型限制 (short limits):\n");
    printf("   SHRT_MIN (short最小值): %d\n", SHRT_MIN);
    printf("   SHRT_MAX (short最大值): %d\n", SHRT_MAX);
    printf("   USHRT_MAX (unsigned short最大值): %u\n", USHRT_MAX);
    
    // 演示短整型的使用
    short s = SHRT_MAX;
    unsigned short us = USHRT_MAX;
    printf("   short变量存储最大值: %d\n", s);
    printf("   unsigned short变量存储最大值: %u\n", us);
    printf("\n");
}

void demonstrate_int_limits(void) {
    printf("3. 整型限制 (int limits):\n");
    printf("   INT_MIN (int最小值): %d\n", INT_MIN);
    printf("   INT_MAX (int最大值): %d\n", INT_MAX);
    printf("   UINT_MAX (unsigned int最大值): %u\n", UINT_MAX);
    
    // 演示整型的使用
    int i = INT_MAX;
    unsigned int ui = UINT_MAX;
    printf("   int变量存储最大值: %d\n", i);
    printf("   unsigned int变量存储最大值: %u\n", ui);
    printf("\n");
}

void demonstrate_long_limits(void) {
    printf("4. 长整型限制 (long limits):\n");
    printf("   LONG_MIN (long最小值): %ld\n", LONG_MIN);
    printf("   LONG_MAX (long最大值): %ld\n", LONG_MAX);
    printf("   ULONG_MAX (unsigned long最大值): %lu\n", ULONG_MAX);
    
    // 演示长整型的使用
    long l = LONG_MAX;
    unsigned long ul = ULONG_MAX;
    printf("   long变量存储最大值: %ld\n", l);
    printf("   unsigned long变量存储最大值: %lu\n", ul);
    printf("\n");
}

void demonstrate_long_long_limits(void) {
    printf("5. 长长整型限制 (long long limits):\n");
    printf("   LLONG_MIN (long long最小值): %lld\n", LLONG_MIN);
    printf("   LLONG_MAX (long long最大值): %lld\n", LLONG_MAX);
    printf("   ULLONG_MAX (unsigned long long最大值): %llu\n", ULLONG_MAX);
    
    // 演示长长整型的使用
    long long ll = LLONG_MAX;
    unsigned long long ull = ULLONG_MAX;
    printf("   long long变量存储最大值: %lld\n", ll);
    printf("   unsigned long long变量存储最大值: %llu\n", ull);
    printf("\n");
}

void demonstrate_practical_usage(void) {
    printf("6. 实际应用示例:\n");
    
    // 检查数值是否在有效范围内
    int user_input = 1000000;
    if (user_input >= INT_MIN && user_input <= INT_MAX) {
        printf("   用户输入 %d 在int范围内\n", user_input);
    }
    
    // 选择合适的数据类型
    printf("   根据数值范围选择数据类型:\n");
    printf("   - 0到255: 使用unsigned char (最大值: %u)\n", UCHAR_MAX);
    printf("   - -128到127: 使用signed char (范围: %d到%d)\n", SCHAR_MIN, SCHAR_MAX);
    printf("   - 0到65535: 使用unsigned short (最大值: %u)\n", USHRT_MAX);
    printf("   - 大数值: 使用long或long long\n");
    
    // 数组大小限制
    printf("   数组索引应该小于 INT_MAX: %d\n", INT_MAX);
    printf("\n");
}

void check_overflow_conditions(void) {
    printf("7. 溢出检查示例:\n");
    
    // 检查加法溢出
    int a = INT_MAX - 10;
    int b = 20;
    
    printf("   检查 %d + %d 是否会溢出:\n", a, b);
    if (a > INT_MAX - b) {
        printf("   警告: 加法会导致溢出!\n");
    } else {
        printf("   安全: 结果 = %d\n", a + b);
    }
    
    // 检查乘法溢出
    int x = 50000;
    int y = 50000;
    printf("   检查 %d * %d 是否会溢出:\n", x, y);
    if (x != 0 && y > INT_MAX / x) {
        printf("   警告: 乘法会导致溢出!\n");
    } else {
        printf("   安全: 结果 = %d\n", x * y);
    }
    
    // 演示溢出行为（注释掉以避免未定义行为）
    /*
    int overflow_demo = INT_MAX;
    printf("   INT_MAX = %d\n", overflow_demo);
    overflow_demo++; // 这会导致溢出
    printf("   INT_MAX + 1 = %d (溢出结果)\n", overflow_demo);
    */
    
    printf("\n");
}

void demonstrate_bit_calculations(void) {
    printf("8. 位计算和存储大小:\n");
    
    // 计算各类型的位数
    printf("   各数据类型的位数:\n");
    printf("   - char: %d 位\n", CHAR_BIT);
    printf("   - short: 至少 %d 位\n", 16);
    printf("   - int: 至少 %d 位\n", 16);
    printf("   - long: 至少 %d 位\n", 32);
    printf("   - long long: 至少 %d 位\n", 64);
    
    // 计算可表示的不同值的数量
    printf("   各类型可表示的不同值数量:\n");
    printf("   - unsigned char: %u 个不同值\n", UCHAR_MAX + 1U);
    printf("   - unsigned short: %u 个不同值\n", USHRT_MAX + 1U);
    
    // 二进制表示
    printf("   最大值的二进制模式:\n");
    printf("   - CHAR_MAX (%d) 的位模式包含 %d 个1\n", CHAR_MAX, CHAR_BIT - 1);
    printf("   - UCHAR_MAX (%u) 的位模式包含 %d 个1\n", UCHAR_MAX, CHAR_BIT);
    
    // 存储效率考虑
    printf("   存储效率建议:\n");
    printf("   - 布尔值: 使用 unsigned char (0或1)\n");
    printf("   - 小整数: 使用 short 或 int\n");
    printf("   - 大整数: 使用 long 或 long long\n");
    printf("   - 数组索引: 使用 size_t 或 int\n");
    
    printf("\n");
}

/*
编译说明:
gcc -o limits_demo limits_demo.c

运行说明:
./limits_demo

注意事项:
1. limits.h 中的常量在编译时确定，不同平台可能有不同值
2. 这些限制值对于编写可移植代码非常重要
3. 在进行数值计算时应该检查溢出条件
4. 选择合适的数据类型可以节省内存并避免溢出
5. CHAR_BIT 通常是8，但标准只保证至少为8

实际应用:
- 输入验证: 确保用户输入在有效范围内
- 数据类型选择: 根据数值范围选择最合适的类型
- 溢出检测: 在关键计算前检查是否会溢出
- 跨平台兼容性: 使用这些常量而不是硬编码数值
- 内存优化: 选择最小的合适数据类型
*/