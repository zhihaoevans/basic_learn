# C标准库演示程序集合

这个项目包含了C语言标准库主要头文件的完整使用演示，每个演示文件都展示了相应头文件中函数和宏的实际用法。

## 📁 项目结构

```
c_stdlib_demos/
├── stdio_demo.c      # stdio.h 演示 - 输入输出函数
├── stdlib_demo.c     # stdlib.h 演示 - 内存管理、转换、随机数等
├── string_demo.c     # string.h 演示 - 字符串操作函数
├── math_demo.c       # math.h 演示 - 数学函数
├── time_demo.c       # time.h 演示 - 时间日期函数
├── ctype_demo.c      # ctype.h 演示 - 字符分类函数
├── assert_demo.c     # assert.h 演示 - 断言宏
├── limits_demo.c     # limits.h 演示 - 数据类型限制
├── stddef_demo.c     # stddef.h 演示 - 标准定义
├── stdint_demo.c     # stdint.h 演示 - 固定宽度整数类型
├── stdbool_demo.c    # stdbool.h 演示 - 布尔类型
├── errno_demo.c      # errno.h 演示 - 错误码处理
├── signal_demo.c     # signal.h 演示 - 信号处理
├── setjmp_demo.c     # setjmp.h 演示 - 非局部跳转
├── stdarg_demo.c     # stdarg.h 演示 - 可变参数
├── locale_demo.c     # locale.h 演示 - 本地化支持
├── Makefile          # 编译脚本
└── README.md         # 项目说明文档
```

## 🚀 快速开始

### 编译所有演示程序
```bash
make all
```

### 运行所有演示程序
```bash
make run
```

### 编译并运行单个演示程序
```bash
# 编译单个程序
make stdio_demo

# 运行单个程序
make run-stdio
```

## 📚 演示内容详解

### 1. stdio_demo.c - 标准输入输出
- **基本I/O**: `printf`, `putchar`, `puts`
- **文件I/O**: `fopen`, `fprintf`, `fputs`, `fputc`, `fgets`, `fgetc`, `fclose`
- **格式化I/O**: `sprintf`, `snprintf`, `sscanf`
- **文件操作**: `ftell`, `rewind`, `fseek`, `remove`
- **错误处理**: `perror`, `ferror`, `feof`

### 2. stdlib_demo.c - 标准库函数
- **内存管理**: `malloc`, `realloc`, `free`, `calloc`
- **字符串转换**: `atoi`, `atof`, `atol`, `strtol`, `strtod`
- **随机数生成**: `srand`, `rand`
- **排序和搜索**: `qsort`, `bsearch`
- **数学函数**: `abs`, `labs`, `div`, `ldiv`
- **环境变量**: `getenv`
- **程序控制**: `system`, `atexit`

### 3. string_demo.c - 字符串操作
- **字符串长度**: `strlen`
- **字符串复制**: `strcpy`, `strncpy`
- **字符串连接**: `strcat`, `strncat`
- **字符串比较**: `strcmp`, `strncmp`
- **字符串搜索**: `strchr`, `strrchr`, `strstr`, `strspn`, `strcspn`, `strpbrk`
- **字符串分割**: `strtok`
- **内存操作**: `memset`, `memcpy`, `memmove`, `memcmp`, `memchr`
- **错误信息**: `strerror`

### 4. math_demo.c - 数学函数
- **基本数学**: `sqrt`, `pow`, `fabs`, `ceil`, `floor`, `round`
- **三角函数**: `sin`, `cos`, `tan`, `asin`, `acos`, `atan`, `atan2`
- **双曲函数**: `sinh`, `cosh`, `tanh`
- **指数对数**: `exp`, `exp2`, `expm1`, `log`, `log10`, `log2`, `log1p`
- **特殊函数**: `fmod`, `remainder`, `modf`, `frexp`, `ldexp`
- **比较分类**: `isfinite`, `isnormal`, `isinf`, `isnan`, `signbit`, `fmax`, `fmin`, `fdim`
- **误差伽马**: `erf`, `erfc`, `tgamma`, `lgamma`

### 5. time_demo.c - 时间日期
- **基本时间**: `time`, `ctime`, `difftime`
- **时间结构**: `localtime`, `gmtime`, `mktime`
- **时间格式化**: `strftime`
- **时间解析**: `strptime` (POSIX)
- **CPU时间**: `clock`
- **时间计算**: 时间差、未来日期、月份边界
- **性能计时**: `clock()` vs `time()`

### 6. ctype_demo.c - 字符分类
- **字符分类**: `isalpha`, `isdigit`, `isalnum`, `islower`, `isupper`, `isspace`, `ispunct`, `isprint`, `iscntrl`, `isgraph`, `isxdigit`
- **字符转换**: `toupper`, `tolower`
- **字符串处理**: 去空格、字符计数、提取数字/字母
- **输入验证**: 验证用户输入
- **大小写转换**: 标题格式、句子格式、交替格式、反转格式

### 7. assert_demo.c - 断言调试
- **基本断言**: `assert` 宏的使用
- **断言失败**: 演示断言失败的情况
- **条件断言**: 根据条件使用断言
- **调试vs发布**: `NDEBUG` 宏的影响
- **最佳实践**: 前置条件、后置条件、不变量检查
- **断言替代**: 用户输入和可恢复错误的处理

### 8. limits_demo.c - 数据类型限制
- **字符类型**: `CHAR_BIT`, `CHAR_MIN`, `CHAR_MAX`, `SCHAR_MIN`, `SCHAR_MAX`, `UCHAR_MAX`
- **短整型**: `SHRT_MIN`, `SHRT_MAX`, `USHRT_MAX`
- **整型**: `INT_MIN`, `INT_MAX`, `UINT_MAX`
- **长整型**: `LONG_MIN`, `LONG_MAX`, `ULONG_MAX`
- **长长整型**: `LLONG_MIN`, `LLONG_MAX`, `ULLONG_MAX`
- **实际应用**: 数值范围检查、数据类型选择、溢出检测
- **位计算**: 存储大小、二进制表示、存储效率

### 9. stddef_demo.c - 标准定义
- **NULL指针**: `NULL` 宏的使用和安全检查
- **size_t类型**: 内存大小和数组索引
- **ptrdiff_t类型**: 指针差值计算
- **wchar_t类型**: 宽字符支持
- **offsetof宏**: 结构体成员偏移量
- **内存对齐**: 结构体对齐和填充
- **安全编程**: 指针操作最佳实践

### 10. stdint_demo.c - 固定宽度整数类型
- **精确宽度类型**: `int8_t`, `int16_t`, `int32_t`, `int64_t`
- **最小宽度类型**: `int_least8_t`, `int_least16_t` 等
- **最快类型**: `int_fast8_t`, `int_fast16_t` 等
- **指针大小类型**: `intptr_t`, `uintptr_t`
- **最大整数类型**: `intmax_t`, `uintmax_t`
- **常量宏**: `INT8_C`, `UINT32_C` 等
- **位操作**: 位掩码、位字段、哈希表

### 11. stdbool_demo.c - 布尔类型
- **布尔类型**: `bool`, `true`, `false`
- **类型转换**: 整数与布尔值转换
- **布尔函数**: 判断函数（偶数、质数、回文）
- **布尔数组**: 筛法算法、标志管理
- **条件表达式**: 短路求值、三元操作符
- **控制结构**: 布尔值在循环和条件中的使用
- **配置管理**: 布尔标志的实际应用

### 12. errno_demo.c - 错误码处理
- **errno变量**: 全局错误码的使用
- **数学错误**: `sqrt`, `acos`, `log` 等函数的错误处理
- **字符串转换错误**: `strtol` 转换错误检测
- **文件操作错误**: 文件打开、删除错误处理
- **内存分配错误**: `malloc` 失败处理
- **安全包装函数**: 带错误检查的函数封装
- **错误分类**: 不同类型错误的处理策略

### 13. signal_demo.c - 信号处理
- **信号处理器**: 自定义信号处理函数
- **信号发送**: `raise` 函数使用
- **信号常量**: `SIGINT`, `SIGFPE`, `SIGILL` 等
- **特殊处理器**: `SIG_IGN`, `SIG_DFL`
- **原子操作**: `sig_atomic_t` 类型
- **信号安全**: 信号处理最佳实践
- **服务器应用**: 优雅关闭和信号管理

### 14. setjmp_demo.c - 非局部跳转
- **跳转设置**: `setjmp` 设置跳转点
- **非局部跳转**: `longjmp` 执行跳转
- **错误处理**: 异常模拟和错误恢复
- **嵌套调用**: 深层函数调用中的跳转
- **资源清理**: 跳转时的资源管理
- **异常模拟**: 类似异常处理的机制
- **计算器示例**: 带错误处理的实用应用

### 15. stdarg_demo.c - 可变参数
- **可变参数宏**: `va_list`, `va_start`, `va_arg`, `va_end`
- **参数复制**: `va_copy` 的使用
- **printf类函数**: 自定义格式化输出
- **数学运算**: 可变参数的数学函数
- **字符串操作**: 可变参数字符串连接
- **类型安全**: 类型安全的可变参数处理
- **日志系统**: 实用的日志记录应用

### 16. locale_demo.c - 本地化支持
- **本地化设置**: `setlocale` 函数使用
- **数字格式化**: 不同地区的数字格式
- **货币格式化**: 货币符号和格式
- **时间格式化**: 本地化的日期时间显示
- **字符分类**: 本地化的字符处理
- **字符串排序**: `strcoll` 本地化比较
- **多语言应用**: 国际化程序示例

## 🛠️ 编译要求

- **编译器**: GCC 或任何支持C99标准的编译器
- **标准**: C99 或更高版本
- **系统**: Linux, macOS, Windows (使用MinGW或类似环境)

## 📋 Makefile 使用指南

### 基本命令
```bash
make all          # 编译所有程序
make clean        # 清理生成的文件
make run          # 运行所有演示程序
make test         # 测试编译
make help         # 显示帮助信息
```

### 单个程序操作
```bash
make stdio_demo   # 编译stdio演示
make run-stdio    # 运行stdio演示
make run-math     # 运行math演示
make run-stddef   # 运行stddef演示
make run-errno    # 运行errno演示
make run-signal   # 运行signal演示
# ... 其他程序类似
```

### 高级功能
```bash
make debug        # 编译调试版本
make release      # 编译发布版本
make memcheck     # 内存检查（需要valgrind）
make stylecheck   # 代码风格检查（需要cppcheck）
make archive      # 创建源代码压缩包
```

## ⚠️ 注意事项

1. **数学库链接**: `math_demo.c` 需要链接数学库 (`-lm`)
2. **断言宏**: `assert_demo.c` 在发布版本中断言会被禁用
3. **平台差异**: 某些函数可能在不同平台上有不同的行为
4. **编译警告**: 使用 `-Wall -Wextra` 编译选项来捕获潜在问题
5. **内存管理**: 注意动态内存的分配和释放

## 🎯 学习建议

1. **按顺序学习**: 建议按照以下顺序学习：
   - **基础**: stdio → stdlib → string → math → time → ctype → assert → limits
   - **进阶**: stddef → stdint → stdbool → errno → signal → setjmp → stdarg → locale
2. **动手实践**: 运行每个演示程序，观察输出结果
3. **修改实验**: 尝试修改代码参数，观察行为变化
4. **阅读注释**: 每个文件都有详细的中文注释说明
5. **查阅文档**: 结合C标准库文档深入理解每个函数

## 🔧 故障排除

### 编译错误
- 确保使用支持C99的编译器
- 检查是否正确链接了数学库（math_demo）
- 验证所有源文件都在当前目录

### 运行时错误
- 检查文件权限
- 确保有足够的内存空间
- 验证输入数据的有效性

### 平台兼容性
- Windows用户可能需要使用MinGW或MSYS2
- 某些POSIX特定的函数在Windows上可能不可用

## 📖 扩展学习

这些演示程序现在涵盖了C标准库的主要功能，包括：

**基础库** (8个):
- `stdio.h` - 输入输出
- `stdlib.h` - 标准库函数  
- `string.h` - 字符串操作
- `math.h` - 数学函数
- `time.h` - 时间日期
- `ctype.h` - 字符分类
- `assert.h` - 断言调试
- `limits.h` - 数据类型限制

**进阶库** (8个):
- `stddef.h` - 标准定义
- `stdint.h` - 固定宽度整数类型
- `stdbool.h` - 布尔类型
- `errno.h` - 错误码处理
- `signal.h` - 信号处理
- `setjmp.h` - 非局部跳转
- `stdarg.h` - 可变参数
- `locale.h` - 本地化支持

这16个头文件构成了C标准库的核心，涵盖了日常C编程中最常用的功能。

## 📄 许可证

本项目仅用于教育目的，代码可自由使用和修改。

## 🤝 贡献

欢迎提交问题报告和改进建议！

---

**作者**: AI Assistant  
**创建日期**: 2024年  
**用途**: C语言标准库学习和参考