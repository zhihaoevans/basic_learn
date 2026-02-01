/*
 * 格式说明符完整示例
 * 演示printf中所有常用的格式说明符
 * C17/C18 标准
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// 演示整数格式说明符
void demo_integer_specifiers() {
    printf("=== 整数格式说明符 ===\n");
    
    int num = 42;
    int negative = -42;
    
    // %d 或 %i - 有符号十进制整数
    printf("%%d: %d\n", num);
    printf("%%i: %i\n", num);
    printf("负数 %%d: %d\n", negative);
    
    // %u - 无符号十进制整数
    unsigned int unum = 42;
    printf("%%u: %u\n", unum);
    
    // %o - 八进制
    printf("%%o: %o\n", num);
    printf("%%#o: %#o (带前缀)\n", num);
    
    // %x, %X - 十六进制
    printf("%%x: %x\n", num);
    printf("%%X: %X\n", num);
    printf("%%#x: %#x (带前缀)\n", num);
    printf("%%#X: %#X (带前缀)\n", num);
    
    // 不同大小的整数
    short s = 100;
    long l = 100000L;
    long long ll = 100000000000LL;
    
    printf("%%hd (short): %hd\n", s);
    printf("%%ld (long): %ld\n", l);
    printf("%%lld (long long): %lld\n", ll);
    
    printf("\n");
}

// 演示浮点数格式说明符
void demo_float_specifiers() {
    printf("=== 浮点数格式说明符 ===\n");
    
    double num = 3.14159265358979;
    double large = 123456.789;
    double small = 0.000123456;
    
    // %f - 十进制浮点数
    printf("%%f: %f\n", num);
    printf("%%.2f: %.2f\n", num);
    printf("%%.6f: %.6f\n", num);
    
    // %e, %E - 科学计数法
    printf("%%e: %e\n", large);
    printf("%%E: %E\n", large);
    printf("%%.2e: %.2e\n", large);
    
    // %g, %G - 自动选择%f或%e
    printf("%%g (大数): %g\n", large);
    printf("%%g (小数): %g\n", small);
    printf("%%G: %G\n", large);
    
    // %a, %A - 十六进制浮点数（C99）
    printf("%%a: %a\n", num);
    printf("%%A: %A\n", num);
    
    // 特殊值
    double inf = 1.0 / 0.0;
    double nan = 0.0 / 0.0;
    printf("无穷大: %f\n", inf);
    printf("NaN: %f\n", nan);
    
    printf("\n");
}

// 演示字符和字符串格式说明符
void demo_char_string_specifiers() {
    printf("=== 字符和字符串格式说明符 ===\n");
    
    // %c - 字符
    char ch = 'A';
    printf("%%c: %c\n", ch);
    printf("%%c (数字): %c\n", 65);  // ASCII码
    
    // %s - 字符串
    char str[] = "Hello, World!";
    printf("%%s: %s\n", str);
    printf("%%.5s: %.5s (精度限制)\n", str);
    printf("%%20s: %20s (右对齐)\n", str);
    printf("%%-20s: %-20s (左对齐)\n", str);
    
    // 空字符串和NULL
    printf("空字符串: '%s'\n", "");
    // printf("NULL: '%s'\n", NULL);  // 未定义行为，不要这样做
    
    printf("\n");
}

// 演示指针格式说明符
void demo_pointer_specifiers() {
    printf("=== 指针格式说明符 ===\n");
    
    int num = 42;
    int *ptr = &num;
    
    // %p - 指针地址
    printf("%%p: %p\n", (void*)ptr);
    printf("数组地址: %p\n", (void*)&num);
    
    // NULL指针
    printf("NULL指针: %p\n", (void*)NULL);
    
    printf("\n");
}

// 演示特殊格式说明符
void demo_special_specifiers() {
    printf("=== 特殊格式说明符 ===\n");
    
    // %n - 存储已输出的字符数
    int count;
    printf("Hello %nWorld\n", &count);
    printf("在%%n之前输出了 %d 个字符\n", count);
    
    // %% - 输出百分号
    printf("百分号: %%\n");
    printf("完成度: 75%%\n");
    
    printf("\n");
}

// 演示标志（Flags）
void demo_flags() {
    printf("=== 标志演示 ===\n");
    
    int num = 42;
    int negative = -42;
    
    // - : 左对齐
    printf("左对齐: '%-10d'\n", num);
    printf("右对齐: '%10d'\n", num);
    
    // + : 显示正负号
    printf("%%+d: %+d\n", num);
    printf("%%+d: %+d\n", negative);
    
    // 空格 : 正数前加空格
    printf("%% d: % d\n", num);
    printf("%% d: % d\n", negative);
    
    // 0 : 用0填充
    printf("%%05d: %05d\n", num);
    printf("%%08d: %08d\n", num);
    
    // # : 备用形式
    printf("%%#o: %#o\n", num);
    printf("%%#x: %#x\n", num);
    printf("%%#X: %#X\n", num);
    printf("%%#f: %#f\n", 3.0);  // 总是显示小数点
    
    printf("\n");
}

// 演示宽度和精度
void demo_width_and_precision() {
    printf("=== 宽度和精度 ===\n");
    
    // 整数宽度
    printf("宽度5: '%5d'\n", 42);
    printf("宽度5: '%5d'\n", 12345);
    printf("宽度5: '%5d'\n", 1);
    
    // 整数精度（最小位数）
    printf("精度5: '%.5d'\n", 42);
    printf("精度5: '%.5d'\n", 12345);
    
    // 浮点数宽度和精度
    double pi = 3.14159;
    printf("宽度10精度2: '%10.2f'\n", pi);
    printf("宽度10精度4: '%10.4f'\n", pi);
    
    // 字符串宽度和精度
    char *str = "Hello, World!";
    printf("宽度20: '%20s'\n", str);
    printf("精度5: '%.5s'\n", str);
    printf("宽度20精度5: '%20.5s'\n", str);
    
    // 使用*动态指定宽度和精度
    int width = 10;
    int precision = 3;
    printf("动态宽度和精度: '%*.*f'\n", width, precision, pi);
    
    printf("\n");
}

// 演示长度修饰符
void demo_length_modifiers() {
    printf("=== 长度修饰符 ===\n");
    
    // hh - char
    signed char sc = -128;
    unsigned char uc = 255;
    printf("%%hhd (signed char): %hhd\n", sc);
    printf("%%hhu (unsigned char): %hhu\n", uc);
    
    // h - short
    short sh = -32768;
    unsigned short us = 65535;
    printf("%%hd (short): %hd\n", sh);
    printf("%%hu (unsigned short): %hu\n", us);
    
    // l - long
    long l = -2147483648L;
    unsigned long ul = 4294967295UL;
    printf("%%ld (long): %ld\n", l);
    printf("%%lu (unsigned long): %lu\n", ul);
    
    // ll - long long
    long long ll = -9223372036854775807LL;
    unsigned long long ull = 18446744073709551615ULL;
    printf("%%lld (long long): %lld\n", ll);
    printf("%%llu (unsigned long long): %llu\n", ull);
    
    // L - long double
    long double ld = 3.14159265358979L;
    printf("%%Lf (long double): %Lf\n", ld);
    
    // z - size_t
    size_t sz = sizeof(int);
    printf("%%zu (size_t): %zu\n", sz);
    
    // t - ptrdiff_t
    int arr[10];
    printf("%%td (ptrdiff_t): %td\n", &arr[9] - &arr[0]);
    
    printf("\n");
}

// 演示固定宽度整数类型（C99/C11）
void demo_fixed_width_types() {
    printf("=== 固定宽度整数类型 ===\n");
    
    int8_t i8 = -128;
    uint8_t u8 = 255;
    int16_t i16 = -32768;
    uint16_t u16 = 65535;
    int32_t i32 = -2147483648;
    uint32_t u32 = 4294967295;
    int64_t i64 = -9223372036854775807LL;
    uint64_t u64 = 18446744073709551615ULL;
    
    printf("int8_t: %" PRId8 "\n", i8);
    printf("uint8_t: %" PRIu8 "\n", u8);
    printf("int16_t: %" PRId16 "\n", i16);
    printf("uint16_t: %" PRIu16 "\n", u16);
    printf("int32_t: %" PRId32 "\n", i32);
    printf("uint32_t: %" PRIu32 "\n", u32);
    printf("int64_t: %" PRId64 "\n", i64);
    printf("uint64_t: %" PRIu64 "\n", u64);
    
    // 十六进制输出
    printf("int32_t (hex): %#" PRIx32 "\n", (uint32_t)255);
    printf("int64_t (hex): %#" PRIx64 "\n", (uint64_t)255);
    
    printf("\n");
}

// 演示综合示例
void demo_comprehensive() {
    printf("=== 综合示例 ===\n");
    
    // 格式化表格
    printf("%-15s %10s %10s %15s\n", "类型", "十进制", "十六进制", "八进制");
    printf("%-15s %10d %10x %15o\n", "整数", 255, 255, 255);
    printf("%-15s %10d %#10x %#15o\n", "带前缀", 255, 255, 255);
    printf("\n");
    
    // 格式化数值
    double values[] = {1.23, 123.456, 0.00123, 123456.789};
    printf("%-15s %12s %12s %12s\n", "值", "%%f", "%%e", "%%g");
    for (int i = 0; i < 4; i++) {
        printf("%-15.6f %12f %12e %12g\n", values[i], values[i], values[i], values[i]);
    }
    printf("\n");
    
    // 对齐示例
    printf("%-20s %10s\n", "项目", "值");
    printf("%-20s %10d\n", "整数", 42);
    printf("%-20s %10.2f\n", "浮点数", 3.14);
    printf("%-20s %10s\n", "字符串", "Hello");
}

int main(void) {
    printf("C语言格式说明符完整示例\n");
    printf("==========================================\n\n");
    
    demo_integer_specifiers();
    demo_float_specifiers();
    demo_char_string_specifiers();
    demo_pointer_specifiers();
    demo_special_specifiers();
    demo_flags();
    demo_width_and_precision();
    demo_length_modifiers();
    demo_fixed_width_types();
    demo_comprehensive();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
