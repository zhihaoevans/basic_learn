/*
 * 高级数学函数示例
 * 演示math.h中的三角函数、双曲函数等高级数学函数
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

#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0)
#define RAD_TO_DEG(rad) ((rad) * 180.0 / M_PI)

// 演示三角函数
void demo_trigonometric_functions() {
    printf("=== 三角函数 ===\n");
    
    // 常见角度的三角函数值
    double angles[] = {0, 30, 45, 60, 90, 180, 270, 360};
    
    printf("%-8s %-12s %-12s %-12s\n", "角度", "sin", "cos", "tan");
    printf("-----------------------------------------------\n");
    
    for (int i = 0; i < 8; i++) {
        double deg = angles[i];
        double rad = DEG_TO_RAD(deg);
        
        printf("%-8.0f %-12.6f %-12.6f ", deg, sin(rad), cos(rad));
        
        // tan(90°) 和 tan(270°) 是无穷大
        if (deg == 90.0 || deg == 270.0) {
            printf("undefined\n");
        } else {
            printf("%-12.6f\n", tan(rad));
        }
    }
    
    printf("\n");
}

// 演示反三角函数
void demo_inverse_trigonometric() {
    printf("=== 反三角函数 ===\n");
    
    double values[] = {-1.0, -0.5, 0.0, 0.5, 1.0};
    
    printf("%-8s %-12s %-12s %-12s\n", "值", "asin(弧度)", "acos(弧度)", "atan(弧度)");
    printf("-------------------------------------------------------\n");
    
    for (int i = 0; i < 5; i++) {
        double val = values[i];
        printf("%-8.1f %-12.6f %-12.6f %-12.6f\n", 
               val, asin(val), acos(val), atan(val));
    }
    
    // atan2 - 考虑象限的反正切
    printf("\natan2(y, x) - 考虑象限:\n");
    printf("atan2(1, 1) = %.6f rad = %.2f° (第一象限)\n", 
           atan2(1, 1), RAD_TO_DEG(atan2(1, 1)));
    printf("atan2(1, -1) = %.6f rad = %.2f° (第二象限)\n", 
           atan2(1, -1), RAD_TO_DEG(atan2(1, -1)));
    printf("atan2(-1, -1) = %.6f rad = %.2f° (第三象限)\n", 
           atan2(-1, -1), RAD_TO_DEG(atan2(-1, -1)));
    printf("atan2(-1, 1) = %.6f rad = %.2f° (第四象限)\n", 
           atan2(-1, 1), RAD_TO_DEG(atan2(-1, 1)));
    
    printf("\n");
}

// 演示双曲函数
void demo_hyperbolic_functions() {
    printf("=== 双曲函数 ===\n");
    
    double values[] = {-2.0, -1.0, 0.0, 1.0, 2.0};
    
    printf("%-8s %-12s %-12s %-12s\n", "x", "sinh(x)", "cosh(x)", "tanh(x)");
    printf("-------------------------------------------------------\n");
    
    for (int i = 0; i < 5; i++) {
        double x = values[i];
        printf("%-8.1f %-12.6f %-12.6f %-12.6f\n", 
               x, sinh(x), cosh(x), tanh(x));
    }
    
    // 反双曲函数
    printf("\n反双曲函数:\n");
    printf("asinh(1.0) = %.6f\n", asinh(1.0));
    printf("acosh(2.0) = %.6f\n", acosh(2.0));
    printf("atanh(0.5) = %.6f\n", atanh(0.5));
    
    printf("\n");
}

// 演示指数和对数函数
void demo_exp_log_functions() {
    printf("=== 指数和对数函数 ===\n");
    
    // 指数函数
    printf("指数函数:\n");
    for (int i = 0; i <= 5; i++) {
        printf("  exp(%d) = %.6f\n", i, exp(i));
    }
    
    printf("\nexp2 (2的幂次):\n");
    for (int i = 0; i <= 10; i++) {
        printf("  2^%d = %.0f\n", i, exp2(i));
    }
    
    printf("\nexpm1 (exp(x)-1, 对小x更精确):\n");
    printf("  expm1(0.001) = %.10f\n", expm1(0.001));
    printf("  exp(0.001)-1 = %.10f\n", exp(0.001) - 1);
    
    // 对数函数
    printf("\n对数函数:\n");
    double values[] = {1.0, 2.0, 10.0, 100.0, M_E};
    for (int i = 0; i < 5; i++) {
        double x = values[i];
        printf("  log(%.2f)=%.4f, log10(%.2f)=%.4f, log2(%.2f)=%.4f\n",
               x, log(x), x, log10(x), x, log2(x));
    }
    
    printf("\nlog1p (log(1+x), 对小x更精确):\n");
    printf("  log1p(0.001) = %.10f\n", log1p(0.001));
    printf("  log(1+0.001) = %.10f\n", log(1 + 0.001));
    
    printf("\n");
}

// 演示幂和根函数
void demo_power_root_functions() {
    printf("=== 幂和根函数 ===\n");
    
    // pow - 通用幂函数
    printf("幂函数 pow(x, y):\n");
    printf("  2^3 = %.0f\n", pow(2, 3));
    printf("  3^2 = %.0f\n", pow(3, 2));
    printf("  10^-2 = %.4f\n", pow(10, -2));
    printf("  2^0.5 = %.6f (平方根)\n", pow(2, 0.5));
    
    // sqrt - 平方根
    printf("\n平方根 sqrt(x):\n");
    for (int i = 1; i <= 5; i++) {
        printf("  √%d = %.6f\n", i, sqrt(i));
    }
    
    // cbrt - 立方根
    printf("\n立方根 cbrt(x):\n");
    for (int i = 1; i <= 5; i++) {
        printf("  ∛%d = %.6f\n", i, cbrt(i));
    }
    
    // hypot - 斜边长度
    printf("\n斜边 hypot(x, y) = √(x²+y²):\n");
    printf("  hypot(3, 4) = %.0f\n", hypot(3, 4));
    printf("  hypot(5, 12) = %.0f\n", hypot(5, 12));
    
    printf("\n");
}

// 演示余数和取模函数
void demo_remainder_functions() {
    printf("=== 余数和取模函数 ===\n");
    
    double x = 7.5, y = 2.3;
    
    printf("x = %.1f, y = %.1f\n\n", x, y);
    
    // fmod - 浮点取模
    printf("fmod(x, y) = %.6f (C语言风格)\n", fmod(x, y));
    
    // remainder - IEEE余数
    printf("remainder(x, y) = %.6f (IEEE风格)\n", remainder(x, y));
    
    // remquo - 余数和商
    int quo;
    double rem = remquo(x, y, &quo);
    printf("remquo(x, y): 余数=%.6f, 商=%d\n", rem, quo);
    
    printf("\n");
}

// 演示浮点数分解函数
void demo_float_decomposition() {
    printf("=== 浮点数分解 ===\n");
    
    double x = 123.456;
    
    // modf - 分解整数和小数部分
    double intpart, fracpart;
    fracpart = modf(x, &intpart);
    printf("modf(%.3f): 整数部分=%.0f, 小数部分=%.3f\n", 
           x, intpart, fracpart);
    
    // frexp - 分解为尾数和指数
    int exp;
    double mantissa = frexp(x, &exp);
    printf("frexp(%.3f): 尾数=%.6f, 指数=%d\n", x, mantissa, exp);
    printf("验证: %.6f * 2^%d = %.3f\n", mantissa, exp, mantissa * pow(2, exp));
    
    // ldexp - 从尾数和指数构建
    double result = ldexp(mantissa, exp);
    printf("ldexp(%.6f, %d) = %.3f\n", mantissa, exp, result);
    
    printf("\n");
}

// 演示特殊值处理
void demo_special_values() {
    printf("=== 特殊值处理 ===\n");
    
    double inf = INFINITY;
    double neg_inf = -INFINITY;
    double nan = NAN;
    double zero = 0.0;
    double neg_zero = -0.0;
    double normal = 42.0;
    
    printf("%-15s %-10s %-10s %-10s %-10s\n", 
           "值", "isfinite", "isinf", "isnan", "isnormal");
    printf("----------------------------------------------------------------\n");
    
    printf("%-15s %-10d %-10d %-10d %-10d\n", 
           "INFINITY", isfinite(inf), isinf(inf), isnan(inf), isnormal(inf));
    printf("%-15s %-10d %-10d %-10d %-10d\n", 
           "-INFINITY", isfinite(neg_inf), isinf(neg_inf), isnan(neg_inf), isnormal(neg_inf));
    printf("%-15s %-10d %-10d %-10d %-10d\n", 
           "NAN", isfinite(nan), isinf(nan), isnan(nan), isnormal(nan));
    printf("%-15s %-10d %-10d %-10d %-10d\n", 
           "0.0", isfinite(zero), isinf(zero), isnan(zero), isnormal(zero));
    printf("%-15s %-10d %-10d %-10d %-10d\n", 
           "-0.0", isfinite(neg_zero), isinf(neg_zero), isnan(neg_zero), isnormal(neg_zero));
    printf("%-15s %-10d %-10d %-10d %-10d\n", 
           "42.0", isfinite(normal), isinf(normal), isnan(normal), isnormal(normal));
    
    // signbit - 符号位
    printf("\nsignbit (符号位):\n");
    printf("  signbit(42.0) = %d\n", signbit(42.0));
    printf("  signbit(-42.0) = %d\n", signbit(-42.0));
    printf("  signbit(0.0) = %d\n", signbit(0.0));
    printf("  signbit(-0.0) = %d\n", signbit(-0.0));
    
    // copysign - 复制符号
    printf("\ncopysign (复制符号):\n");
    printf("  copysign(10.0, -1.0) = %.1f\n", copysign(10.0, -1.0));
    printf("  copysign(-10.0, 1.0) = %.1f\n", copysign(-10.0, 1.0));
    
    printf("\n");
}

// 演示比较函数
void demo_comparison_functions() {
    printf("=== 比较函数 ===\n");
    
    double a = 3.5, b = 2.1, c = 3.5;
    
    printf("a = %.1f, b = %.1f, c = %.1f\n\n", a, b, c);
    
    // fmax, fmin
    printf("fmax(a, b) = %.1f\n", fmax(a, b));
    printf("fmin(a, b) = %.1f\n", fmin(a, b));
    
    // fdim - 正差值
    printf("fdim(a, b) = %.1f (a-b, 如果a>b)\n", fdim(a, b));
    printf("fdim(b, a) = %.1f (b-a, 如果b>a)\n", fdim(b, a));
    
    // fma - 融合乘加
    printf("fma(2, 3, 4) = %.0f (2*3+4)\n", fma(2, 3, 4));
    
    printf("\n");
}

// 演示错误函数和伽马函数
void demo_error_gamma_functions() {
    printf("=== 错误函数和伽马函数 ===\n");
    
    // 错误函数
    printf("错误函数 erf(x):\n");
    for (int i = 0; i <= 3; i++) {
        double x = i * 0.5;
        printf("  erf(%.1f) = %.6f\n", x, erf(x));
    }
    
    // 互补错误函数
    printf("\n互补错误函数 erfc(x) = 1 - erf(x):\n");
    for (int i = 0; i <= 3; i++) {
        double x = i * 0.5;
        printf("  erfc(%.1f) = %.6f\n", x, erfc(x));
    }
    
    // 伽马函数
    printf("\n伽马函数 tgamma(x) (阶乘的推广):\n");
    for (int i = 1; i <= 6; i++) {
        printf("  tgamma(%d) = %.0f ((n-1)! = %.0f)\n", 
               i, tgamma(i), tgamma(i));
    }
    
    // 对数伽马函数
    printf("\n对数伽马函数 lgamma(x):\n");
    printf("  lgamma(10) = %.6f\n", lgamma(10));
    printf("  验证: exp(lgamma(10)) = %.0f = 9! = %.0f\n", 
           exp(lgamma(10)), tgamma(10));
    
    printf("\n");
}

// 演示实用计算
void demo_practical_calculations() {
    printf("=== 实用计算示例 ===\n");
    
    // 计算两点间距离
    double x1 = 1.0, y1 = 2.0;
    double x2 = 4.0, y2 = 6.0;
    double distance = hypot(x2 - x1, y2 - y1);
    printf("点(%.0f,%.0f)到点(%.0f,%.0f)的距离: %.2f\n", 
           x1, y1, x2, y2, distance);
    
    // 计算圆的面积和周长
    double radius = 5.0;
    double area = M_PI * pow(radius, 2);
    double circumference = 2 * M_PI * radius;
    printf("\n半径%.0f的圆:\n", radius);
    printf("  面积: %.2f\n", area);
    printf("  周长: %.2f\n", circumference);
    
    // 计算复合利息
    double principal = 1000.0;  // 本金
    double rate = 0.05;         // 年利率 5%
    int years = 10;
    double amount = principal * pow(1 + rate, years);
    printf("\n复合利息计算:\n");
    printf("  本金: %.2f\n", principal);
    printf("  年利率: %.1f%%\n", rate * 100);
    printf("  期限: %d年\n", years);
    printf("  最终金额: %.2f\n", amount);
    
    printf("\n");
}

int main(void) {
    printf("C语言高级数学函数示例\n");
    printf("==========================================\n\n");
    
    demo_trigonometric_functions();
    demo_inverse_trigonometric();
    demo_hyperbolic_functions();
    demo_exp_log_functions();
    demo_power_root_functions();
    demo_remainder_functions();
    demo_float_decomposition();
    demo_special_values();
    demo_comparison_functions();
    demo_error_gamma_functions();
    demo_practical_calculations();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
