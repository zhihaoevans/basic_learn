# C++ 示例集合

C++ 是静态类型的编译型系统语言，兼顾高性能抽象与贴近硬件的控制力。本目录按 [TOPICS.md](../TOPICS.md) 的统一主题清单组织基础语法示例：一个主题一个自包含可运行文件，每个文件头注释含主题说明、运行命令与预期输出。

- 权威参考：[cppreference C++（含 C++17 标准）](https://en.cppreference.com/w/cpp)
- 语言标准与提案：[WG21 / ISO C++ 委员会](https://www.open-std.org/jtc1/sc22/wg21/)

## 环境要求

- **C++17** 标准（g++ 7+ 或 clang 5+，`basics/CMakeLists.txt` 已固定 `CMAKE_CXX_STANDARD 17`）
- **CMake ≥ 3.16**
- **pthread**（POSIX 线程，Linux/macOS 系统自带；`basics/14_concurrency` 由 CMake 自动链接 Threads::Threads）

## 如何运行

统一用 CMake 构建，产物名与源文件同名（如 `basics/01_hello.cpp` → `build/01_hello`），全部输出到 `cpp/basics/build/` 根目录：

```bash
# 在仓库根目录执行
cmake -S cpp/basics -B cpp/basics/build         # 配置
cmake --build cpp/basics/build -j8              # 构建（零错误零警告）
./cpp/basics/build/01_hello                     # 运行任意示例
for b in cpp/basics/build/[0-9]*; do "$b" >/dev/null 2>&1 || echo "FAIL: $b"; done  # CI 同款全量门禁
```

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [basics/01_hello.cpp](basics/01_hello.cpp) | `./cpp/basics/build/01_hello` | iostream 输出、注释、endl 与 '\n' |
| 02 variable | [basics/02_variable.cpp](basics/02_variable.cpp) | `./cpp/basics/build/02_variable` | auto/基本类型、const/constexpr、统一初始化、static_cast |
| 03 operator | [basics/03_operator.cpp](basics/03_operator.cpp) | `./cpp/basics/build/03_operator` | 算术/比较/短路/位运算/自增/三元/优先级 |
| 04 string | [basics/04_string.cpp](basics/04_string.cpp) | `./cpp/basics/build/04_string` | 拼接、substr/find/replace、to_string/stoi、原始字符串 |
| 05 control | [basics/05_control.cpp](basics/05_control.cpp) | `./cpp/basics/build/05_control` | if/switch 初始化器（C++17）、range-for、while、break/continue |
| 06 function | [basics/06_function.cpp](basics/06_function.cpp) | `./cpp/basics/build/06_function` | 重载、默认参、inline、lambda 捕获列表、函数对象 |
| 07 collection | [basics/07_collection.cpp](basics/07_collection.cpp) | `./cpp/basics/build/07_collection` | array/vector/list/set 与迭代器、range-for |
| 08 map | [basics/08_map.cpp](basics/08_map.cpp) | `./cpp/basics/build/08_map` | map/unordered_map、[] vs at、insert、词频统计经典例 |
| 09 oop | [basics/09_oop.cpp](basics/09_oop.cpp) | `./cpp/basics/build/09_oop` | 封装、构造析构顺序、继承、纯虚抽象类、多态 |
| 10 error | [basics/10_error.cpp](basics/10_error.cpp) | `./cpp/basics/build/10_error` | 异常层次、throw、引用捕获、自定义异常类、noexcept |
| 11 file_io | [basics/11_file_io.cpp](basics/11_file_io.cpp) | `./cpp/basics/build/11_file_io` | ofstream 写、ifstream 逐行读、stringstream 解析拼接 |
| 12 module | [basics/12_module.cpp](basics/12_module.cpp) | `./cpp/basics/build/12_module` | namespace、声明/定义分离（单文件演示+多文件注释）、using |
| 13 stdlib | [basics/13_stdlib.cpp](basics/13_stdlib.cpp) | `./cpp/basics/build/13_stdlib` | algorithm（sort/find_if/count）、accumulate、chrono、string_view |
| 14 concurrency | [basics/14_concurrency.cpp](basics/14_concurrency.cpp) | `./cpp/basics/build/14_concurrency` | thread、mutex+lock_guard、async+future 入门 |
| 15 generic | [basics/15_generic.cpp](basics/15_generic.cpp) | `./cpp/basics/build/15_generic` | 函数模板、类模板、非类型参数、auto 返回推导 |
| 特色 | [basics/16_raii.cpp](basics/16_raii.cpp) | `./cpp/basics/build/16_raii` | RAII 构造获取析构释放、unique_ptr、lock_guard 原理、异常安全 |

## 进阶专题

以下目录为早期积累的进阶示例（不按 15 题清单组织），尚未统一到 CMake 门禁，按需阅读源码：

- [container/](container/) —— 容器与泛型相关示例
- [cpp_primer_plus/](cpp_primer_plus/) —— 《C++ Primer Plus》练习代码
- [cpptest/](cpptest/) —— 示例汇总（含 README，CI 构建：`cmake -S cpp/cpptest -B cpp/cpptest/build`）
- [design_mode/](design_mode/) —— 设计模式示例
- [frameworks/](frameworks/) —— 框架使用示例
- [google_suites/](google_suites/) —— Google 测试三件套：[gtest](google_suites/gtest_example/)、[benchmark](google_suites/benchmark_example/)、[glog](google_suites/glog_example/)（CI 构建）
- [libs/](libs/) —— 第三方库使用示例
- [protobuf/](protobuf/README.md) —— Protobuf 序列化示例
- [string/](string/) —— 字符串处理技巧
- [test/](test/) —— 测试/实验代码
- [uml_relation/](uml_relation/) —— UML 类关系示意
