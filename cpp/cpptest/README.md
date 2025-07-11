# C++ 示例程序集合

本项目包含了一系列 C++ 示例程序，涵盖了基础特性和 C++11 新特性。每个文件都专注于展示特定的功能特性。

## 文件说明

### 基础特性示例

1. `basic_types.cpp` - 基本类型和运算符
   - 整数类型和大小
   - 浮点类型
   - 字符和布尔类型
   - 算术运算符
   - 位运算符
   - 类型转换

2. `class_basics.cpp` - 类和对象基础
   - 类定义和对象创建
   - 构造函数和析构函数
   - 成员函数
   - 访问控制
   - 继承
   - 友元函数
   - 运算符重载

3. `template_basics.cpp` - 模板基础
   - 函数模板
   - 类模板
   - 模板特化
   - 多参数模板
   - 成员函数模板

4. `stl_examples.cpp` - STL 容器和算法
   - vector 用法
   - list 用法
   - deque 用法
   - set 用法
   - map 用法
   - 常用算法示例

5. `exception_handling.cpp` - 异常处理
   - try-catch 基础
   - 多重异常处理
   - 自定义异常
   - RAII 和异常安全
   - 嵌套异常
   - noexcept 说明符
   - 函数 try 块

6. `file_stream.cpp` - 文件和流操作
   - 基本文件输入输出
   - 文本文件操作
   - 二进制文件操作
   - 字符串流
   - 格式化输出
   - 自定义对象序列化
   - 文件位置操作

### C++11 新特性示例

1. `auto_decltype.cpp` - 自动类型推导
2. `lambda.cpp` - Lambda 表达式
3. `smart_pointers.cpp` - 智能指针
4. `rvalue_move.cpp` - 右值引用和移动语义
5. `variadic_templates.cpp` - 可变参数模板
6. `range_based_for.cpp` - 基于范围的 for 循环
7. `nullptr_example.cpp` - nullptr 关键字
8. `enum_class.cpp` - 强类型枚举
9. `thread_example.cpp` - 线程支持
10. `initializer_lists.cpp` - 初始化列表

## 编译和运行

### 使用 CMake 构建

1. 创建构建目录：
```bash
mkdir build
cd build
```

2. 生成构建文件：
```bash
cmake ..
```

3. 编译项目：
```bash
make
```

4. 运行示例：

基础特性示例：
```bash
./basic_types
./class_basics
./template_basics
./stl_examples
./exception_handling
./file_stream
```

C++11 新特性示例：
```bash
./auto_decltype
./lambda_examples
./smart_pointers
./rvalue_move
./variadic_templates
./range_based_for
./nullptr_example
./enum_class
./thread_example
./initializer_lists
```

### 直接使用 g++ 编译

如果你想单独编译某个示例，可以使用以下命令：

基础特性示例：
```bash
g++ -std=c++11 basic_types.cpp -o basic_types
g++ -std=c++11 class_basics.cpp -o class_basics
g++ -std=c++11 template_basics.cpp -o template_basics
g++ -std=c++11 stl_examples.cpp -o stl_examples
g++ -std=c++11 exception_handling.cpp -o exception_handling
g++ -std=c++11 file_stream.cpp -o file_stream
```

C++11 新特性示例：
```bash
g++ -std=c++11 auto_decltype.cpp -o auto_decltype
g++ -std=c++11 lambda.cpp -o lambda
g++ -std=c++11 smart_pointers.cpp -o smart_pointers
g++ -std=c++11 rvalue_move.cpp -o rvalue_move
g++ -std=c++11 variadic_templates.cpp -o variadic_templates
g++ -std=c++11 range_based_for.cpp -o range_based_for
g++ -std=c++11 nullptr_example.cpp -o nullptr_example
g++ -std=c++11 enum_class.cpp -o enum_class
g++ -std=c++11 thread_example.cpp -o thread_example -pthread
g++ -std=c++11 initializer_lists.cpp -o initializer_lists
```

## 注意事项

1. 确保你的编译器支持 C++11（GCC 4.8.1 及以上版本）
2. 线程示例需要链接 pthread 库
3. 所有示例都包含详细的注释，说明了每个特性的用法
4. 每个示例都是独立的，可以单独编译和运行
5. 建议按照以下顺序学习：
   - 先学习基础特性（basic_types → class_basics → template_basics → stl_examples → exception_handling → file_stream）
   - 再学习 C++11 新特性
6. 每个文件都包含了多个小的示例，展示了相应特性的不同方面
7. 文件操作示例会创建一些临时文件，运行完成后可以删除这些文件 