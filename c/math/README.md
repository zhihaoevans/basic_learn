# 数学章节示例

本目录包含C语言数学运算和函数的完整示例代码，从基础到高级，涵盖math.h库的各个方面。

## 📁 文件列表

### 新增示例
- **math_basics.c** - 基础数学运算
  - 基本算术运算（+, -, *, /, %）
  - 复合赋值运算符（+=, -=, *=, /=, %=）
  - 自增自减运算符（++, --）
  - 基本数学函数（abs, pow, sqrt, log, exp）
  - 取整函数（ceil, floor, round, trunc）
  - 最大值和最小值
  - 随机数生成
  - 整数除法和取模
  - 数值范围和精度
  - 类型转换
  - 溢出问题
  - 数学常量

- **advanced_math.c** - 高级数学函数
  - 三角函数（sin, cos, tan）
  - 反三角函数（asin, acos, atan, atan2）
  - 双曲函数（sinh, cosh, tanh）
  - 指数和对数函数（exp, log, log10, log2）
  - 幂和根函数（pow, sqrt, cbrt, hypot）
  - 余数和取模函数（fmod, remainder）
  - 浮点数分解（modf, frexp, ldexp）
  - 特殊值处理（isfinite, isinf, isnan）
  - 比较函数（fmax, fmin, fdim, fma）
  - 错误函数和伽马函数（erf, tgamma）
  - 实用计算示例

### 原有示例
- **test.c** - 简单的数学测试

## 🎯 学习路径

建议按以下顺序学习：

1. **math_basics.c** - 掌握基本运算和常用函数
2. **advanced_math.c** - 学习高级数学函数

## 🚀 编译和运行

### 编译单个文件

```bash
# 编译基础示例（需要链接数学库 -lm）
cc -std=c17 -Wall -Wextra math_basics.c -o math_basics -lm
./math_basics

# 编译高级示例
cc -std=c17 -Wall -Wextra advanced_math.c -o advanced_math -lm
./advanced_math
```

### 使用父目录的Makefile

```bash
# 在c目录下编译所有示例
cd ..
make all

# 运行编译后的程序
./bin/math_math_basics
./bin/math_advanced_math
```

**重要**: 数学函数需要链接数学库 `-lm`

## 📚 知识点总结

### 1. 基本算术运算符

| 运算符 | 说明 | 示例 |
|--------|------|------|
| `+` | 加法 | `a + b` |
| `-` | 减法 | `a - b` |
| `*` | 乘法 | `a * b` |
| `/` | 除法 | `a / b` |
| `%` | 取模（整数） | `a % b` |

### 2. 复合赋值运算符

```c
a += 5;  // 等价于 a = a + 5
a -= 3;  // 等价于 a = a - 3
a *= 2;  // 等价于 a = a * 2
a /= 4;  // 等价于 a = a / 4
a %= 3;  // 等价于 a = a % 3
```

### 3. 基本数学函数

| 函数 | 说明 | 示例 |
|------|------|------|
| `abs(x)` | 整数绝对值 | `abs(-5)` → 5 |
| `fabs(x)` | 浮点绝对值 | `fabs(-3.5)` → 3.5 |
| `pow(x, y)` | x的y次方 | `pow(2, 3)` → 8.0 |
| `sqrt(x)` | 平方根 | `sqrt(16)` → 4.0 |
| `cbrt(x)` | 立方根 | `cbrt(27)` → 3.0 |
| `exp(x)` | e的x次方 | `exp(1)` → 2.718... |
| `log(x)` | 自然对数 | `log(e)` → 1.0 |
| `log10(x)` | 常用对数 | `log10(100)` → 2.0 |
| `log2(x)` | 以2为底的对数 | `log2(8)` → 3.0 |

### 4. 取整函数

| 函数 | 说明 | 示例 |
|------|------|------|
| `ceil(x)` | 向上取整 | `ceil(3.2)` → 4.0 |
| `floor(x)` | 向下取整 | `floor(3.8)` → 3.0 |
| `round(x)` | 四舍五入 | `round(3.5)` → 4.0 |
| `trunc(x)` | 截断小数 | `trunc(3.8)` → 3.0 |

### 5. 三角函数

| 函数 | 说明 | 输入 |
|------|------|------|
| `sin(x)` | 正弦 | 弧度 |
| `cos(x)` | 余弦 | 弧度 |
| `tan(x)` | 正切 | 弧度 |
| `asin(x)` | 反正弦 | [-1, 1] |
| `acos(x)` | 反余弦 | [-1, 1] |
| `atan(x)` | 反正切 | 任意值 |
| `atan2(y, x)` | 反正切（考虑象限） | 任意值 |

**重要**: C语言的三角函数使用弧度制，不是角度制！

```c
// 角度转弧度
double deg_to_rad(double deg) {
    return deg * M_PI / 180.0;
}

// 弧度转角度
double rad_to_deg(double rad) {
    return rad * 180.0 / M_PI;
}
```

### 6. 数学常量（需要定义 `_USE_MATH_DEFINES` 或使用 `-D_GNU_SOURCE`）

| 常量 | 值 | 说明 |
|------|-----|------|
| `M_E` | 2.718... | 自然对数底 |
| `M_PI` | 3.141... | 圆周率 |
| `M_SQRT2` | 1.414... | √2 |
| `M_LN2` | 0.693... | ln(2) |
| `M_LN10` | 2.302... | ln(10) |

## ⚠️ 常见陷阱

1. **整数除法**
   ```c
   int a = 7, b = 2;
   int result = a / b;      // 结果是 3，不是 3.5
   double result2 = a / b;  // 还是 3.0，因为a/b是整数除法
   double result3 = (double)a / b;  // 正确：3.5
   ```

2. **忘记链接数学库**
   ```bash
   cc math_program.c -lm  # 正确：链接 libm
   ```

3. **角度和弧度混淆**
   ```c
   sin(90);     // 错误！应该用弧度
   sin(M_PI/2); // 正确：90度 = π/2 弧度
   ```

4. **浮点数精度问题**
   ```c
   double a = 0.1 + 0.2;
   if (a == 0.3) { ... }  // 可能为假！
   
   // 正确做法：使用误差范围
   if (fabs(a - 0.3) < 1e-10) { ... }
   ```

5. **整数溢出**
   ```c
   int big = INT_MAX;
   int overflow = big + 1;  // 溢出！
   
   // 使用更大的类型
   long long safe = (long long)big + 1;
   ```

6. **除以零**
   ```c
   double result = 1.0 / 0.0;  // 结果是无穷大
   int x = 1 / 0;              // 运行时错误！
   ```

## 💡 最佳实践

1. **检查定义域**
   ```c
   // sqrt需要非负数
   if (x >= 0) {
       double result = sqrt(x);
   }
   
   // asin和acos需要[-1, 1]
   if (x >= -1 && x <= 1) {
       double result = asin(x);
   }
   ```

2. **处理特殊值**
   ```c
   if (isnan(result)) {
       // 处理NaN
   }
   if (isinf(result)) {
       // 处理无穷大
   }
   ```

3. **使用合适的类型**
   ```c
   // 整数运算
   int a = 5, b = 2;
   int quot = a / b;     // 商
   int rem = a % b;      // 余数
   
   // 浮点运算
   double x = 5.0, y = 2.0;
   double result = x / y;  // 2.5
   ```

4. **避免重复计算**
   ```c
   // 不好
   for (int i = 0; i < n; i++) {
       result += pow(x, 2);  // 每次都计算
   }
   
   // 好
   double x_squared = pow(x, 2);
   for (int i = 0; i < n; i++) {
       result += x_squared;
   }
   ```

5. **使用标准常量**
   ```c
   // 不好
   double pi = 3.14;
   
   // 好
   double pi = M_PI;
   ```

## 🔗 高级技巧

### 1. 快速平方根倒数（游戏开发常用）

```c
float fast_inverse_sqrt(float x) {
    // 仅用于演示，实际应用需要更多优化
    return 1.0f / sqrtf(x);
}
```

### 2. 计算两点间距离

```c
double distance(double x1, double y1, double x2, double y2) {
    return hypot(x2 - x1, y2 - y1);
}
```

### 3. 角度归一化到 [0, 360)

```c
double normalize_angle(double angle) {
    angle = fmod(angle, 360.0);
    if (angle < 0) angle += 360.0;
    return angle;
}
```

### 4. 线性插值

```c
double lerp(double a, double b, double t) {
    return a + t * (b - a);
}
```

### 5. 计算阶乘

```c
double factorial(int n) {
    return tgamma(n + 1);
}
```

## 📖 参考资源

- C17/C18 标准文档 - math.h
- 《C Primer Plus》第6章 - 运算符、表达式和语句
- IEEE 754 浮点数标准
- 数值分析教材

## 🔍 相关主题

- **浮点数表示** - IEEE 754标准
- **数值精度** - 浮点运算的误差
- **性能优化** - 数学运算的优化技巧
- **科学计算** - 更高级的数值计算库

---

**标准**: C17/C18  
**编译器**: GCC, Clang, MSVC (支持C99及以上)  
**重要**: 编译时必须链接数学库 `-lm`
