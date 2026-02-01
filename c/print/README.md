# 输出章节示例

本目录包含C语言格式化输出的完整示例代码，从基础到高级，涵盖printf及相关函数的各个方面。

## 📁 文件列表

### 新增示例
- **print_basics.c** - 基础输出函数
  - printf基础用法
  - puts和putchar
  - fprintf和文件输出
  - sprintf和snprintf
  - 宽度和精度控制
  - 不同输出形式
  - 返回值使用
  - 输出缓冲区

- **format_specifiers.c** - 格式说明符完整示例
  - 整数格式说明符（%d, %u, %o, %x等）
  - 浮点数格式说明符（%f, %e, %g, %a等）
  - 字符和字符串格式说明符（%c, %s）
  - 指针格式说明符（%p）
  - 特殊格式说明符（%n, %%）
  - 标志（-, +, 0, #, 空格）
  - 宽度和精度
  - 长度修饰符（hh, h, l, ll, L, z, t）
  - 固定宽度整数类型

- **advanced_formatting.c** - 高级格式化技巧
  - 颜色输出（ANSI转义序列）
  - 表格输出
  - 进度条
  - 数字格式化技巧
  - 时间日期格式化
  - ASCII艺术
  - 对齐和填充技巧
  - 自定义格式化函数
  - 数据可视化
  - 实用输出技巧

### 原有示例
- **test.c** - 简单的十六进制输出测试

## 🎯 学习路径

建议按以下顺序学习：

1. **print_basics.c** - 先掌握基本的输出函数
2. **format_specifiers.c** - 深入理解所有格式说明符
3. **advanced_formatting.c** - 学习高级技巧和实用方法

## 🚀 编译和运行

### 编译单个文件

```bash
# 编译基础示例
cc -std=c17 -Wall -Wextra print_basics.c -o print_basics
./print_basics

# 编译格式说明符示例
cc -std=c17 -Wall -Wextra format_specifiers.c -o format_specifiers
./format_specifiers

# 编译高级格式化示例
cc -std=c17 -Wall -Wextra advanced_formatting.c -o advanced_formatting
./advanced_formatting
```

### 使用父目录的Makefile

```bash
# 在c目录下编译所有示例
cd ..
make all

# 运行编译后的程序
./bin/print_print_basics
./bin/print_format_specifiers
./bin/print_advanced_formatting
```

## 📚 知识点总结

### 1. 基本输出函数

```c
printf("格式字符串", 参数列表);  // 格式化输出
puts("字符串");                  // 输出字符串+换行
putchar('c');                    // 输出单个字符
fprintf(文件指针, "格式", ...); // 输出到文件
sprintf(缓冲区, "格式", ...);   // 输出到字符串
snprintf(缓冲区, 大小, "格式", ...);  // 安全版本
```

### 2. 常用格式说明符

| 说明符 | 类型 | 示例 |
|--------|------|------|
| %d, %i | 有符号十进制整数 | 42, -10 |
| %u | 无符号十进制整数 | 42 |
| %o | 八进制 | 52 |
| %x, %X | 十六进制 | 2a, 2A |
| %f | 浮点数 | 3.14 |
| %e, %E | 科学计数法 | 3.14e+00 |
| %g, %G | 自动选择%f或%e | 3.14 |
| %c | 字符 | 'A' |
| %s | 字符串 | "Hello" |
| %p | 指针 | 0x7fff... |
| %% | 百分号 | % |

### 3. 标志（Flags）

| 标志 | 作用 | 示例 |
|------|------|------|
| - | 左对齐 | %-10d |
| + | 显示正负号 | %+d |
| 空格 | 正数前加空格 | % d |
| 0 | 用0填充 | %05d |
| # | 备用形式 | %#x, %#o |

### 4. 宽度和精度

```c
%10d      // 最小宽度10，右对齐
%-10d     // 最小宽度10，左对齐
%.2f      // 小数点后2位
%10.2f    // 宽度10，精度2
%.5s      // 字符串前5个字符
%*.*f     // 动态指定宽度和精度
```

### 5. 长度修饰符

| 修饰符 | 类型 | 示例 |
|--------|------|------|
| hh | char | %hhd |
| h | short | %hd |
| l | long | %ld |
| ll | long long | %lld |
| L | long double | %Lf |
| z | size_t | %zu |
| t | ptrdiff_t | %td |

## ⚠️ 常见陷阱

1. **缓冲区溢出**
   ```c
   char buf[10];
   sprintf(buf, "很长的字符串");  // 危险！可能溢出
   snprintf(buf, sizeof(buf), "很长的字符串");  // 安全
   ```

2. **类型不匹配**
   ```c
   long l = 100;
   printf("%d", l);   // 错误！应使用 %ld
   ```

3. **精度误用**
   ```c
   printf("%.2d", 5);    // 输出: 05（最少2位数字）
   printf("%.2f", 3.1);  // 输出: 3.10（2位小数）
   ```

4. **忘记刷新缓冲区**
   ```c
   printf("提示：");  // 可能不会立即显示
   fflush(stdout);    // 强制刷新
   ```

5. **NULL字符串**
   ```c
   char *str = NULL;
   printf("%s", str);  // 未定义行为！
   ```

## 💡 最佳实践

1. **使用snprintf而非sprintf**，避免缓冲区溢出
2. **格式说明符与参数类型匹配**，避免未定义行为
3. **检查返回值**，printf返回输出的字符数，-1表示错误
4. **使用const修饰格式字符串**，帮助编译器检查
5. **处理宽字符时使用wprintf**系列函数
6. **输出到stderr用于错误消息**，方便重定向

## 🔗 高级技巧

### 1. ANSI颜色代码

```c
printf("\033[31m红色\033[0m\n");     // 红色文本
printf("\033[42m绿色背景\033[0m\n"); // 绿色背景
printf("\033[1;33m粗体黄色\033[0m\n"); // 粗体黄色
```

### 2. 动态宽度和精度

```c
int width = 10, precision = 2;
printf("%*.*f", width, precision, 3.14159);  // 输出: "      3.14"
```

### 3. 可变参数函数

```c
void my_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
```

### 4. 格式化时间

```c
time_t now = time(NULL);
struct tm *t = localtime(&now);
printf("%04d-%02d-%02d %02d:%02d:%02d\n",
       t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
       t->tm_hour, t->tm_min, t->tm_sec);
```

## 📖 参考资源

- C17/C18 标准文档 - stdio.h
- 《C Primer Plus》第4章 - 格式化输入输出
- 《C程序设计语言》（K&R）第7章 - 输入与输出
- ANSI转义序列参考

---

**标准**: C17/C18  
**编译器**: GCC, Clang, MSVC (支持C99及以上)  
**特别说明**: 某些高级功能（如ANSI颜色）可能在某些终端不支持
