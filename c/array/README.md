# 数组章节示例

本目录包含C语言数组的完整示例代码，从基础到进阶，覆盖数组的各个方面。

## 📁 文件列表

### 基础示例
- **array_basics.c** - 数组基础知识
  - 数组声明和初始化的多种方式
  - 字符数组和字符串
  - 数组访问和修改
  - 常见数组操作（求和、平均值、查找等）
  - 数组作为函数参数

- **array_operations.c** - 数组操作算法
  - 排序算法（冒泡、选择、插入、qsort）
  - 搜索算法（线性搜索、二分搜索）
  - 数组变换（反转、旋转）
  - 去重操作
  - 合并有序数组

- **multidim_array.c** - 多维数组
  - 二维数组的声明和初始化
  - 矩阵运算（加法、乘法、转置）
  - 二维数组常见操作
  - 三维数组示例
  - 字符串数组

- **array_pointer.c** - 数组与指针
  - 数组名与指针的关系
  - 指针算术
  - 使用指针遍历数组
  - 指针数组与数组指针
  - 指针作为函数参数
  - 返回指针的函数
  - 动态数组

### 原有示例
- **init_arr.c** - 数组初始化示例
- **test.c** - 数组和结构体大小测试
- **test1.c** - 简单数组测试

## 🎯 学习路径

建议按以下顺序学习：

1. **array_basics.c** - 先掌握数组的基本概念和操作
2. **multidim_array.c** - 然后学习多维数组
3. **array_pointer.c** - 理解数组与指针的关系
4. **array_operations.c** - 最后学习常见算法

## 🚀 编译和运行

### 编译单个文件

```bash
# 编译基础示例
cc -std=c17 -Wall -Wextra array_basics.c -o array_basics
./array_basics

# 编译操作示例
cc -std=c17 -Wall -Wextra array_operations.c -o array_operations
./array_operations

# 编译多维数组示例
cc -std=c17 -Wall -Wextra multidim_array.c -o multidim_array
./multidim_array

# 编译指针示例
cc -std=c17 -Wall -Wextra array_pointer.c -o array_pointer
./array_pointer
```

### 使用父目录的Makefile

```bash
# 在c目录下编译所有示例
cd ..
make all

# 运行编译后的程序
./bin/array_array_basics
./bin/array_array_operations
./bin/array_multidim_array
./bin/array_array_pointer
```

## 📚 知识点总结

### 1. 数组基础
- 数组是相同类型元素的集合
- 数组在内存中连续存储
- 数组索引从0开始
- 数组大小在编译时确定（静态数组）

### 2. 数组初始化
```c
int arr1[5] = {1, 2, 3, 4, 5};  // 完全初始化
int arr2[5] = {1, 2};            // 部分初始化，其余为0
int arr3[5] = {0};               // 全零初始化
int arr4[] = {1, 2, 3};          // 自动确定大小
int arr5[10] = {[0]=1, [9]=10};  // 指定索引初始化（C99）
```

### 3. 多维数组
```c
int matrix[3][4];                // 3行4列的二维数组
int cube[2][3][4];               // 三维数组
```

### 4. 数组与指针
- 数组名可以转换为指向首元素的指针
- `arr[i]` 等价于 `*(arr + i)`
- 数组名不是真正的指针，不能改变指向
- `sizeof(arr)` 返回整个数组大小，`sizeof(ptr)` 返回指针大小

### 5. 重要概念
- **数组越界**：访问数组边界外的元素是未定义行为
- **数组作为参数**：传递的是指针，不是整个数组
- **动态数组**：使用 `malloc`/`calloc` 在堆上分配
- **VLA（可变长数组）**：C99引入，大小可在运行时确定

## ⚠️ 常见陷阱

1. **数组越界**
   ```c
   int arr[5];
   arr[5] = 10;  // 错误！索引范围是0-4
   ```

2. **数组大小**
   ```c
   void func(int arr[]) {
       // sizeof(arr) 这里返回的是指针大小，不是数组大小！
   }
   ```

3. **字符串结尾**
   ```c
   char str[5] = "Hello";  // 错误！需要6个字节（包括'\0'）
   char str[6] = "Hello";  // 正确
   ```

4. **数组赋值**
   ```c
   int a[5], b[5];
   a = b;  // 错误！数组不能直接赋值
   // 应使用循环或memcpy
   ```

## 💡 最佳实践

1. **总是初始化数组**，避免使用未初始化的值
2. **传递数组大小**，函数无法通过数组参数判断大小
3. **检查边界**，确保索引在有效范围内
4. **使用 `const`**，对于只读数组使用 `const` 修饰
5. **动态数组记得释放**，避免内存泄漏
6. **使用 `size_t`** 作为数组索引和大小的类型

## 🔗 相关主题

- **指针** - 数组与指针密切相关
- **内存管理** - 动态数组需要手动管理内存
- **字符串** - 字符数组的特殊应用
- **结构体** - 可以包含数组成员

## 📖 参考资源

- C17/C18 标准文档
- 《C Primer Plus》数组章节
- 《C程序设计语言》（K&R）第6章

---

**标准**: C17/C18  
**编译器**: GCC, Clang, MSVC (支持C99及以上)
