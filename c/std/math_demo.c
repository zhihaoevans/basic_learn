/*
 * math.h 标准头文件演示
 * 演示数学库的各种函数用法
 * 编译时需要链接数学库：gcc -lm math_demo.c
 */

#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void demo_basic_math() {
    printf("=== 基本数学函数演示 ===\n");
    
    double x = 16.0;
    double y = -25.0;
    double z = 2.7;
    
    // 平方根
    printf("sqrt(%.1f) = %.6f\n", x, sqrt(x));
    printf("sqrt(%.1f) = %.6f\n", z, sqrt(z));
    
    // 幂函数
    printf("pow(2, 3) = %.1f\n", pow(2, 3));
    printf("pow(%.1f, 0.5) = %.6f (等同于sqrt)\n", x, pow(x, 0.5));
    printf("pow(%.1f, 2) = %.1f\n", z, pow(z, 2));
    
    // 绝对值
    printf("fabs(%.1f) = %.1f\n", y, fabs(y));
    printf("fabs(%.1f) = %.1f\n", z, fabs(z));
    
    // 向上取整
    printf("ceil(%.1f) = %.1f\n", z, ceil(z));
    printf("ceil(-%.1f) = %.1f\n", z, ceil(-z));
    
    // 向下取整
    printf("floor(%.1f) = %.1f\n", z, floor(z));
    printf("floor(-%.1f) = %.1f\n", z, floor(-z));
    
    // 四舍五入（C99标准）
    printf("round(%.1f) = %.1f\n", z, round(z));
    printf("round(2.5) = %.1f\n", round(2.5));
    printf("round(3.5) = %.1f\n", round(3.5));
}

void demo_trigonometric() {
    printf("\n=== 三角函数演示 ===\n");
    
    double angles[] = {0, M_PI/6, M_PI/4, M_PI/3, M_PI/2, M_PI};
    char *angle_names[] = {"0°", "30°", "45°", "60°", "90°", "180°"};
    int num_angles = sizeof(angles) / sizeof(angles[0]);
    
    printf("角度\t弧度\t\tsin\t\tcos\t\ttan\n");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < num_angles; i++) {
        double angle = angles[i];
        printf("%s\t%.6f\t%.6f\t%.6f\t", 
               angle_names[i], angle, sin(angle), cos(angle));
        
        if (fabs(cos(angle)) < 1e-10) {
            printf("undefined\n");
        } else {
            printf("%.6f\n", tan(angle));
        }
    }
    
    // 反三角函数
    printf("\n反三角函数演示:\n");
    double values[] = {0, 0.5, 0.707107, 0.866025, 1.0};
    
    for (int i = 0; i < 5; i++) {
        double val = values[i];
        printf("asin(%.6f) = %.6f 弧度 = %.1f°\n", 
               val, asin(val), asin(val) * 180 / M_PI);
        printf("acos(%.6f) = %.6f 弧度 = %.1f°\n", 
               val, acos(val), acos(val) * 180 / M_PI);
        if (i < 4) {  // tan的定义域更大
            printf("atan(%.6f) = %.6f 弧度 = %.1f°\n", 
                   val, atan(val), atan(val) * 180 / M_PI);
        }
        printf("\n");
    }
    
    // atan2函数
    printf("atan2函数演示（处理象限）:\n");
    double x_coords[] = {1, -1, -1, 1};
    double y_coords[] = {1, 1, -1, -1};
    char *quadrants[] = {"第一象限", "第二象限", "第三象限", "第四象限"};
    
    for (int i = 0; i < 4; i++) {
        double angle = atan2(y_coords[i], x_coords[i]);
        printf("atan2(%.1f, %.1f) = %.6f 弧度 = %.1f° (%s)\n",
               y_coords[i], x_coords[i], angle, angle * 180 / M_PI, quadrants[i]);
    }
}

void demo_hyperbolic() {
    printf("\n=== 双曲函数演示 ===\n");
    
    double x_values[] = {0, 0.5, 1.0, 1.5, 2.0};
    int num_values = sizeof(x_values) / sizeof(x_values[0]);
    
    printf("x\tsinh(x)\t\tcosh(x)\t\ttanh(x)\n");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < num_values; i++) {
        double x = x_values[i];
        printf("%.1f\t%.6f\t%.6f\t%.6f\n", 
               x, sinh(x), cosh(x), tanh(x));
    }
    
    // 验证双曲函数恒等式: cosh²(x) - sinh²(x) = 1
    printf("\n验证恒等式 cosh²(x) - sinh²(x) = 1:\n");
    for (int i = 0; i < num_values; i++) {
        double x = x_values[i];
        double cosh_x = cosh(x);
        double sinh_x = sinh(x);
        double identity = cosh_x * cosh_x - sinh_x * sinh_x;
        printf("x=%.1f: cosh²(x) - sinh²(x) = %.10f\n", x, identity);
    }
}

void demo_exponential_logarithmic() {
    printf("\n=== 指数和对数函数演示 ===\n");
    
    double values[] = {1, 2, 5, 10, 100};
    int num_values = sizeof(values) / sizeof(values[0]);
    
    // 指数函数
    printf("指数函数:\n");
    for (int i = 0; i < num_values; i++) {
        double x = values[i];
        printf("exp(%.1f) = %.6f\n", x, exp(x));
        if (x <= 10) {  // 避免exp2结果过大
            printf("exp2(%.1f) = %.6f (2^x)\n", x, exp2(x));
        }
        printf("expm1(%.1f) = %.6f (exp(x)-1，高精度)\n", x, expm1(x));
        printf("\n");
    }
    
    // 对数函数
    printf("对数函数:\n");
    for (int i = 0; i < num_values; i++) {
        double x = values[i];
        printf("log(%.1f) = %.6f (自然对数)\n", x, log(x));
        printf("log10(%.1f) = %.6f (常用对数)\n", x, log10(x));
        printf("log2(%.1f) = %.6f (以2为底)\n", x, log2(x));
        printf("log1p(%.1f) = %.6f (log(1+x)，高精度)\n", x, log1p(x));
        printf("\n");
    }
    
    // 验证对数和指数的逆运算关系
    printf("验证 log(exp(x)) = x:\n");
    double test_values[] = {0.5, 1.0, 2.0, 3.0};
    for (int i = 0; i < 4; i++) {
        double x = test_values[i];
        double result = log(exp(x));
        printf("log(exp(%.1f)) = %.10f (误差: %.2e)\n", 
               x, result, fabs(result - x));
    }
}

void demo_special_functions() {
    printf("\n=== 特殊函数演示 ===\n");
    
    // 取模运算
    printf("fmod函数（浮点取模）:\n");
    double dividend[] = {7.5, -7.5, 7.5, -7.5};
    double divisor[] = {2.3, 2.3, -2.3, -2.3};
    
    for (int i = 0; i < 4; i++) {
        double result = fmod(dividend[i], divisor[i]);
        printf("fmod(%.1f, %.1f) = %.6f\n", dividend[i], divisor[i], result);
    }
    
    // remainder函数（IEEE余数）
    printf("\nremainder函数（IEEE余数）:\n");
    for (int i = 0; i < 4; i++) {
        double result = remainder(dividend[i], divisor[i]);
        printf("remainder(%.1f, %.1f) = %.6f\n", dividend[i], divisor[i], result);
    }
    
    // 分解浮点数
    printf("\n浮点数分解:\n");
    double test_nums[] = {123.456, -67.89, 0.0625};
    
    for (int i = 0; i < 3; i++) {
        double num = test_nums[i];
        double integer_part, fractional_part;
        int exponent;
        
        // modf - 分解为整数和小数部分
        fractional_part = modf(num, &integer_part);
        printf("modf(%.6f): 整数部分=%.1f, 小数部分=%.6f\n", 
               num, integer_part, fractional_part);
        
        // frexp - 分解为尾数和指数
        double mantissa = frexp(num, &exponent);
        printf("frexp(%.6f): 尾数=%.6f, 指数=%d (%.6f = %.6f * 2^%d)\n",
               num, mantissa, exponent, num, mantissa, exponent);
        
        // ldexp - 从尾数和指数构造数值
        double reconstructed = ldexp(mantissa, exponent);
        printf("ldexp(%.6f, %d) = %.6f (重构验证)\n", 
               mantissa, exponent, reconstructed);
        printf("\n");
    }
}

void demo_comparison_functions() {
    printf("\n=== 比较和分类函数演示 ===\n");
    
    double values[] = {-INFINITY, -1.0, -0.0, 0.0, 1.0, INFINITY, NAN};
    char *names[] = {"-INF", "-1.0", "-0.0", "0.0", "1.0", "+INF", "NaN"};
    int num_values = sizeof(values) / sizeof(values[0]);
    
    printf("值\t有限\t正常\t无穷\tNaN\t符号位\n");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < num_values; i++) {
        double val = values[i];
        printf("%s\t%s\t%s\t%s\t%s\t%s\n",
               names[i],
               isfinite(val) ? "是" : "否",
               isnormal(val) ? "是" : "否",
               isinf(val) ? "是" : "否",
               isnan(val) ? "是" : "否",
               signbit(val) ? "负" : "正");
    }
    
    // 比较函数
    printf("\n比较函数演示:\n");
    double a = 3.14, b = 2.71, c = NAN;
    
    printf("fmax(%.2f, %.2f) = %.2f\n", a, b, fmax(a, b));
    printf("fmin(%.2f, %.2f) = %.2f\n", a, b, fmin(a, b));
    printf("fmax(%.2f, NaN) = %.2f (NaN被忽略)\n", a, fmax(a, c));
    printf("fmin(%.2f, NaN) = %.2f (NaN被忽略)\n", a, fmin(a, c));
    
    // fdim - 正差值
    printf("fdim(%.2f, %.2f) = %.2f (正差值)\n", a, b, fdim(a, b));
    printf("fdim(%.2f, %.2f) = %.2f (正差值)\n", b, a, fdim(b, a));
}

void demo_error_functions() {
    printf("\n=== 错误和伽马函数演示 ===\n");
    
    double x_values[] = {0.0, 0.5, 1.0, 1.5, 2.0};
    int num_values = sizeof(x_values) / sizeof(x_values[0]);
    
    printf("x\terf(x)\t\terfc(x)\t\ttgamma(x)\tlgamma(x)\n");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < num_values; i++) {
        double x = x_values[i];
        if (x > 0 || i == 0) {  // tgamma在x<=0时未定义（除了正整数）
            printf("%.1f\t%.6f\t%.6f\t%.6f\t%.6f\n",
                   x, erf(x), erfc(x), 
                   (x > 0) ? tgamma(x) : 1.0,  // tgamma(0)未定义，这里用1代替
                   (x > 0) ? lgamma(x) : 0.0); // lgamma(0)未定义，这里用0代替
        }
    }
    
    // 验证 erf(x) + erfc(x) = 1
    printf("\n验证 erf(x) + erfc(x) = 1:\n");
    for (int i = 0; i < num_values; i++) {
        double x = x_values[i];
        double sum = erf(x) + erfc(x);
        printf("x=%.1f: erf(x) + erfc(x) = %.10f (误差: %.2e)\n",
               x, sum, fabs(sum - 1.0));
    }
}

int main() {
    printf("C语言 math.h 标准头文件演示\n");
    printf("===============================\n");
    printf("注意：编译时需要链接数学库：gcc -lm math_demo.c\n\n");
    
    demo_basic_math();
    demo_trigonometric();
    demo_hyperbolic();
    demo_exponential_logarithmic();
    demo_special_functions();
    demo_comparison_functions();
    demo_error_functions();
    
    printf("\n演示完成！\n");
    return 0;
}