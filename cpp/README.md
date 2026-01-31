# C++ 示例集合

本目录包含 C++ 基础语法、STL、设计模式、多线程与字符串等示例。子目录按主题组织。

## 目录结构

```
cpp/
├── container/        # 容器与泛型相关示例
├── cpp_primer_plus/  # C++ Primer Plus 练习代码
├── cpptest/          # 示例汇总（含 README）
├── design_mode/      # 设计模式示例
├── multi_thread/     # 多线程示例
├── string/           # 字符串相关示例
├── test/             # 测试/实验代码
└── uml_relation/     # UML 与关系示意
```

## 学习路径建议

1. string → container → cpptest
2. multi_thread 与 design_mode 作为进阶内容

## 运行方式

```bash
# 以单文件为例
c++ -std=c++11 string/test.cpp -o string_test
./string_test
```
