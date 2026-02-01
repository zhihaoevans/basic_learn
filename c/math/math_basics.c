/*
 * 基础数学运算示例
 * 演示C语言中的基本数学运算和操作符
 * C17/C18 标准
 */

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

#ifndef M_E
#define M_E 2.71828182845904523536
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif
#ifndef M_LN2
#define M_LN2 0.69314718055994530942
#endif
#ifndef M_LN10
#define M_LN10 2.30258509299404568402
#endif
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <float.h>

// 演示基本算术运算
void demo_basic_arithmetic() {
    printf("=== 基本算术运算 ===\n");
    
    int a = 10, b = 3;
    
    printf("a = %d, b = %d\n", a, b);
    printf("加法: a + b = %d\n", a + b);
    printf("减法: a - b = %d\n", a - b);
    printf("乘法: a * b = %d\n", a * b);
    printf("除法: a / b = %d (整数除法)\n", a / b);
    printf("取模: a %% b = %d\n", a % b);
    
    // 浮点数运算
    double x = 10.0, y = 3.0;
    printf("\nx = %.1f, y = %.1f\n", x, y);
    printf("浮点除法: x / y = %.4f\n", x / y);
    
    printf("\n");
}

// 演示复合赋值运算符
void demo_compound_assignment() {
    printf("=== 复合赋值运算符 ===\n");
    
    int num = 10;
    printf("初始值: num = %d\n", num);
    
    num += 5;  // num = num + 5
    printf("num += 5: num = %d\n", num);
    
    num -= 3;  // num = num - 3
    printf("num -= 3: num = %d\n", num);
    
    num *= 2;  // num = num * 2
    printf("num *= 2: num = %d\n", num);
    
    num /= 4;  // num = num / 4
    printf("num /= 4: num = %d\n", num);
    
    num %= 3;  // num = num % 3
    printf("num %%= 3: num = %d\n", num);
    
    printf("\n");
}

// 演示自增自减运算符
void demo_increment_decrement() {
    printf("=== 自增自减运算符 ===\n");
    
    int i = 5;
    printf("初始值: i = %d\n", i);
    
    printf("i++ (后缀): %d (使用后再加1)\n", i++);
    printf("当前 i = %d\n", i);
    
    printf("++i (前缀): %d (先加1再使用)\n", ++i);
    printf("当前 i = %d\n", i);
    
    printf("i-- (后缀): %d (使用后再减1)\n", i--);
    printf("当前 i = %d\n", i);
    
    printf("--i (前缀): %d (先减1再使用)\n", --i);
    printf("当前 i = %d\n", i);
    
    printf("\n");
}

// 演示基本数学函数
void demo_basic_math_functions() {
    printf("=== 基本数学函数 ===\n");
    
    double num = -5.7;
    
    // 绝对值
    printf("abs(-10) = %d\n", abs(-10));
    printf("fabs(%.1f) = %.1f\n", num, fabs(num));
    
    // 幂运算
    printf("pow(2, 3) = %.0f (2的3次方)\n", pow(2, 3));
    printf("pow(10, 2) = %.0f\n", pow(10, 2));
    
    // 平方根
    printf("sqrt(16) = %.0f\n", sqrt(16));
    printf("sqrt(2) = %.6f\n", sqrt(2));
    
    // 立方根
    printf("cbrt(27) = %.0f\n", cbrt(27));
    printf("cbrt(8) = %.0f\n", cbrt(8));
    
    // 对数
    printf("log(e) = %.6f (自然对数)\n", log(M_E));
    printf("log10(100) = %.0f (常用对数)\n", log10(100));
    printf("log2(8) = %.0f (以2为底)\n", log2(8));
    
    // 指数
    printf("exp(1) = %.6f (e的1次方)\n", exp(1));
    printf("exp(2) = %.6f\n", exp(2));
    
    printf("\n");
}

// 演示取整函数
void demo_rounding_functions() {
    printf("=== 取整函数 ===\n");
    
    double values[] = {3.2, 3.5, 3.8, -3.2, -3.5, -3.8};
    
    for (int i = 0; i < 6; i++) {
        double val = values[i];
        printf("值: %.1f\n", val);
        printf("  ceil(%.1f)  = %.0f (向上取整)\n", val, ceil(val));
        printf("  floor(%.1f) = %.0f (向下取整)\n", val, floor(val));
        printf("  round(%.1f) = %.0f (四舍五入)\n", val, round(val));
        printf("  trunc(%.1f) = %.0f (截断小数)\n", val, trunc(val));
        printf("\n");
    }
}

// 演示最大值和最小值
void demo_max_min() {
    printf("=== 最大值和最小值 ===\n");
    
    int a = 10, b = 20, c = 15;
    
    printf("a = %d, b = %d, c = %d\n", a, b, c);
    
    // 两数比较
    int max2 = (a > b) ? a : b;
    int min2 = (a < b) ? a : b;
    printf("max(a, b) = %d\n", max2);
    printf("min(a, b) = %d\n", min2);
    
    // 三数比较
    int max3 = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    int min3 = (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
    printf("max(a, b, c) = %d\n", max3);
    printf("min(a, b, c) = %d\n", min3);
    
    // 使用fmax/fmin
    printf("fmax(3.5, 2.1) = %.1f\n", fmax(3.5, 2.1));
    printf("fmin(3.5, 2.1) = %.1f\n", fmin(3.5, 2.1));
    
    printf("\n");
}

// 演示随机数生成
void demo_random_numbers() {
    printf("=== 随机数生成 ===\n");
    
    // 设置随机数种子
    srand((unsigned int)time(NULL));
    
    // 生成随机整数
    printf("随机整数 (0-RAND_MAX):\n");
    for (int i = 0; i < 5; i++) {
        printf("  %d\n", rand());
    }
    
    // 生成指定范围的随机数 [0, n)
    printf("\n随机数 [0, 10):\n");
    for (int i = 0; i < 5; i++) {
        printf("  %d\n", rand() % 10);
    }
    
    // 生成指定范围的随机数 [min, max]
    int min = 1, max = 100;
    printf("\n随机数 [%d, %d]:\n", min, max);
    for (int i = 0; i < 5; i++) {
        int r = min + rand() % (max - min + 1);
        printf("  %d\n", r);
    }
    
    // 生成随机浮点数 [0.0, 1.0)
    printf("\n随机浮点数 [0.0, 1.0):\n");
    for (int i = 0; i < 5; i++) {
        double r = (double)rand() / RAND_MAX;
        printf("  %.6f\n", r);
    }
    
    printf("\n");
}

// 演示整数除法和取模
void demo_division_modulo() {
    printf("=== 整数除法和取模 ===\n");
    
    int dividend, divisor;
    
    // 正数除法
    dividend = 17;
    divisor = 5;
    printf("%d / %d = %d, %d %% %d = %d\n", 
           dividend, divisor, dividend / divisor,
           dividend, divisor, dividend % divisor);
    
    // 负数除法
    dividend = -17;
    divisor = 5;
    printf("%d / %d = %d, %d %% %d = %d\n", 
           dividend, divisor, dividend / divisor,
           dividend, divisor, dividend % divisor);
    
    dividend = 17;
    divisor = -5;
    printf("%d / %d = %d, %d %% %d = %d\n", 
           dividend, divisor, dividend / divisor,
           dividend, divisor, dividend % divisor);
    
    // 使用div函数
    div_t result = div(17, 5);
    printf("\ndiv(17, 5): 商=%d, 余数=%d\n", result.quot, result.rem);
    
    printf("\n");
}

// 演示数值范围和精度
void demo_numeric_limits() {
    printf("=== 数值范围和精度 ===\n");
    
    printf("整数类型范围:\n");
    printf("  INT_MIN  = %d\n", INT_MIN);
    printf("  INT_MAX  = %d\n", INT_MAX);
    printf("  UINT_MAX = %u\n", UINT_MAX);
    
    printf("\n浮点类型范围:\n");
    printf("  FLT_MIN  = %e\n", FLT_MIN);
    printf("  FLT_MAX  = %e\n", FLT_MAX);
    printf("  DBL_MIN  = %e\n", DBL_MIN);
    printf("  DBL_MAX  = %e\n", DBL_MAX);
    
    printf("\n浮点精度:\n");
    printf("  FLT_DIG  = %d (有效数字位数)\n", FLT_DIG);
    printf("  DBL_DIG  = %d (有效数字位数)\n", DBL_DIG);
    printf("  FLT_EPSILON = %e\n", FLT_EPSILON);
    printf("  DBL_EPSILON = %e\n", DBL_EPSILON);
    
    printf("\n");
}

// 演示类型转换
void demo_type_conversion() {
    printf("=== 类型转换 ===\n");
    
    // 整数除法 vs 浮点数除法
    int a = 7, b = 2;
    printf("整数除法: %d / %d = %d\n", a, b, a / b);
    printf("浮点除法: %d / %d = %.2f\n", a, b, (double)a / b);
    printf("浮点除法: %d / %d = %.2f\n", a, b, a / (double)b);
    
    // 隐式类型转换
    double x = 3.7;
    int y = x;  // 截断小数部分
    printf("\ndouble %.1f -> int %d (截断)\n", x, y);
    
    // 显式类型转换
    double pi = 3.14159;
    printf("(int)%.5f = %d\n", pi, (int)pi);
    printf("(int)(%.5f + 0.5) = %d (四舍五入)\n", pi, (int)(pi + 0.5));
    
    printf("\n");
}

// 演示溢出问题
void demo_overflow() {
    printf("=== 溢出问题 ===\n");
    
    // 整数溢出
    int max = INT_MAX;
    printf("INT_MAX = %d\n", max);
    printf("INT_MAX + 1 = %d (溢出)\n", max + 1);
    
    unsigned int u_max = UINT_MAX;
    printf("\nUINT_MAX = %u\n", u_max);
    printf("UINT_MAX + 1 = %u (回绕到0)\n", u_max + 1);
    
    // 防止溢出
    long long big_product = (long long)max * 2;
    printf("\n使用long long避免溢出: %lld\n", big_product);
    
    printf("\n");
}

// 演示常用数学常量
void demo_math_constants() {
    printf("=== 数学常量 ===\n");
    
    printf("M_E  (自然对数底) = %.15f\n", M_E);
    printf("M_PI (圆周率)     = %.15f\n", M_PI);
    printf("M_SQRT2 (√2)      = %.15f\n", M_SQRT2);
    printf("M_LN2 (ln 2)      = %.15f\n", M_LN2);
    printf("M_LN10 (ln 10)    = %.15f\n", M_LN10);
    
    printf("\n");
}

int main(void) {
    printf("C语言基础数学运算示例\n");
    printf("==========================================\n\n");
    
    demo_basic_arithmetic();
    demo_compound_assignment();
    demo_increment_decrement();
    demo_basic_math_functions();
    demo_rounding_functions();
    demo_max_min();
    demo_random_numbers();
    demo_division_modulo();
    demo_numeric_limits();
    demo_type_conversion();
    demo_overflow();
    demo_math_constants();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
