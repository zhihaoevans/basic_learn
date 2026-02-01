# C 语言示例

本目录包含 C 语言基础示例与标准库演示，覆盖数组、字符串、数学、输出与标准库头文件。所有示例均使用最新的 C17/C18 标准编写。

## 📁 目录结构

```
c/
├── array/     # 数组示例 (4个完整示例 + README)
│   ├── array_basics.c           # 数组基础：声明、初始化、访问
│   ├── array_operations.c       # 数组操作：排序、搜索、变换
│   ├── multidim_array.c         # 多维数组：矩阵运算
│   ├── array_pointer.c          # 数组与指针关系
│   └── README.md                # 数组章节说明
├── print/     # 输出与格式化示例 (3个完整示例 + README)
│   ├── print_basics.c           # 基础输出函数
│   ├── format_specifiers.c      # 格式说明符完整示例
│   ├── advanced_formatting.c    # 高级格式化技巧
│   └── README.md                # 输出章节说明
├── string/    # 字符串相关示例 (3个完整示例 + README)
│   ├── string_basics.c          # 字符串基础
│   ├── string_operations.c      # 字符串操作函数
│   ├── string_manipulation.c    # 字符串处理技巧
│   └── README.md                # 字符串章节说明
├── math/      # 数学相关示例 (2个完整示例 + README)
│   ├── math_basics.c            # 基础数学运算
│   ├── advanced_math.c          # 高级数学函数
│   └── README.md                # 数学章节说明
├── std/       # C 标准库演示（含完整 README）
│   ├── stdio_demo.c             # stdio.h 演示
│   ├── stdlib_demo.c            # stdlib.h 演示
│   ├── string_demo.c            # string.h 演示
│   ├── math_demo.c              # math.h 演示
│   ├── time_demo.c              # time.h 演示
│   ├── ctype_demo.c             # ctype.h 演示
│   ├── assert_demo.c            # assert.h 演示
│   ├── limits_demo.c            # limits.h 演示
│   ├── stddef_demo.c            # stddef.h 演示
│   ├── stdint_demo.c            # stdint.h 演示
│   ├── stdbool_demo.c           # stdbool.h 演示
│   ├── errno_demo.c             # errno.h 演示
│   ├── signal_demo.c            # signal.h 演示
│   ├── setjmp_demo.c            # setjmp.h 演示
│   ├── stdarg_demo.c            # stdarg.h 演示
│   ├── locale_demo.c            # locale.h 演示
│   └── README.md                # 标准库章节说明
└── tmp/       # 临时/实验代码
```

## 🎯 学习路径建议

### 初学者路径
1. **array/** - 数组基础，理解数据结构
2. **print/** - 输出函数，学习调试技巧
3. **string/** - 字符串操作，掌握文本处理
4. **math/** - 数学运算，理解数值计算

### 进阶路径
5. **std/** - 深入学习C标准库的16个核心头文件

## 🚀 运行方式

### 方式1：使用 Makefile（推荐）

```bash
# 在 c/ 目录下构建所有示例并把可执行文件放到 bin/
make all

# 清理编译产物
make clean

# 运行示例（以数组基础为例）
./bin/array_array_basics

# 运行其他示例
./bin/print_format_specifiers
./bin/string_operations
./bin/math_advanced_math
```

### 方式2：手动编译单个文件

```bash
# 编译数组示例
cc -std=c17 -Wall -Wextra array/array_basics.c -o array_basics
./array_basics

# 编译字符串示例
cc -std=c17 -Wall -Wextra string/string_operations.c -o string_operations
./string_operations

# 编译数学示例（需要链接数学库 -lm）
cc -std=c17 -Wall -Wextra math/math_basics.c -o math_basics -lm
./math_basics
```

## 📚 内容概览

### array/ - 数组示例 ⭐⭐⭐⭐⭐

完整覆盖数组的各个方面：
- **基础**: 声明、初始化、访问、修改、遍历
- **操作**: 排序（冒泡、选择、插入、qsort）、搜索（线性、二分）
- **多维**: 二维数组、矩阵运算、三维数组
- **高级**: 数组与指针、动态数组、指针数组与数组指针

**示例数量**: 4个完整示例 + README  
**代码行数**: ~1,330行  
**难度**: ⭐⭐ ~ ⭐⭐⭐⭐

### print/ - 输出格式化示例 ⭐⭐⭐⭐⭐

涵盖所有输出相关内容：
- **基础**: printf, puts, putchar, fprintf, sprintf, snprintf
- **格式**: 所有格式说明符（%d, %f, %s, %p等）
- **高级**: ANSI颜色、表格输出、进度条、数据可视化

**示例数量**: 3个完整示例 + README  
**代码行数**: ~1,214行  
**难度**: ⭐⭐ ~ ⭐⭐⭐

### string/ - 字符串示例 ⭐⭐⭐⭐⭐

全面的字符串处理：
- **基础**: 字符串概念、声明、初始化、访问
- **操作**: string.h中所有常用函数（strcpy, strcat, strcmp等）
- **技巧**: 安全操作、大小写转换、修剪、替换、反转、回文检查

**示例数量**: 3个完整示例 + README  
**代码行数**: ~1,317行  
**难度**: ⭐⭐ ~ ⭐⭐⭐⭐

### math/ - 数学示例 ⭐⭐⭐⭐⭐

完整的数学计算：
- **基础**: 算术运算、取整、随机数、数学常量
- **高级**: 三角函数、指数对数、幂函数、特殊函数（伽马、误差函数）

**示例数量**: 2个完整示例 + README  
**代码行数**: ~1,036行  
**难度**: ⭐⭐ ~ ⭐⭐⭐⭐

### std/ - 标准库示例 ⭐⭐⭐⭐⭐

16个标准库头文件的完整演示，详见 [std/README.md](std/README.md)

## 📊 统计信息

| 目录 | 示例数 | 代码行数 | README |
|------|--------|----------|---------|
| array/ | 4 | ~1,330 | ✓ |
| print/ | 3 | ~1,214 | ✓ |
| string/ | 3 | ~1,317 | ✓ |
| math/ | 2 | ~1,036 | ✓ |
| std/ | 16 | ~5,000+ | ✓ |
| **总计** | **28+** | **~9,900+** | **5个** |

## 💡 特色亮点

1. **完整性**: 覆盖C语言基础的所有核心主题
2. **实用性**: 每个示例都包含实际应用场景
3. **标准性**: 严格遵循C17/C18标准
4. **注释详细**: 每个示例都有中文注释说明
5. **可运行**: 所有代码都经过测试，可直接运行
6. **文档完善**: 每个目录都有完整的README说明

## ⚠️ 注意事项

1. **编译标准**: 建议使用 `-std=c17` 或 `-std=c11`
2. **数学库**: math/ 目录下的示例需要链接 `-lm`
3. **警告选项**: 推荐使用 `-Wall -Wextra` 捕获潜在问题
4. **平台差异**: 某些示例在不同平台可能有细微差异

## 🔧 编译器要求

- **GCC**: 7.0+ (推荐)
- **Clang**: 6.0+ (推荐)
- **MSVC**: Visual Studio 2019+ (支持C11/C17)

## 📖 参考资源

- C17/C18 标准文档
- 《C Primer Plus》第6版
- 《C程序设计语言》（K&R）第2版
- GNU C Library 文档

## 🤝 贡献指南

欢迎提交问题报告和改进建议！请确保：
- 代码符合C17/C18标准
- 包含详细的中文注释
- 通过编译且无警告
- 示例具有实际意义

---

**创建日期**: 2024年  
**标准**: C17/C18  
**用途**: C语言基础学习和参考
