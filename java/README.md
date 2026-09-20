# Java 基础语法示例

Java 是一门静态类型、面向对象的跨平台语言，"一次编写、到处运行"。本目录按 [TOPICS.md](../TOPICS.md) 的统一主题清单组织：一个主题一个自包含的可运行文件，用 `System.out` 逐个知识点演示结果。

- 官方文档：[dev.java（Java 语言入门）](https://dev.java/learn/) ｜ [Java API 规范（JDK 21）](https://docs.oracle.com/en/java/javase/21/docs/api/index.html)

## 环境要求

- **JDK 11+**：所有示例使用 JDK 11 引入的"单文件源码直运行"（`java Xxx.java`），无需先 `javac` 编译
- **JDK 21**：`16_records/RecordsDemo.java` 用到 JDK 21 正式特性（record 解构、switch 模式匹配），必须 21+
- 个别示例还使用了 JDK 14–17 的语法：04 的文本块（15+）、05 的箭头 switch（14+）、09 的 instanceof 模式匹配（16+），旧 JDK 跑不了这几题
- 推荐直接安装 JDK 21（与 CI 一致），如 [Temurin](https://adoptium.net/)；`java --version` 可查看当前版本

## 如何运行

单条命令直接运行某个示例（无需编译）：

```bash
java java/01_hello/Hello.java
```

一次性运行全部示例（与 CI 的验证方式相同）：

```bash
find java -name '*.java' | sort | while read -r f; do echo "== $f"; java "$f"; done
```

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [01_hello/Hello.java](01_hello/Hello.java) | `java java/01_hello/Hello.java` | 打印输出与三种注释 |
| 02 variable | [02_variable/VariableDemo.java](02_variable/VariableDemo.java) | `java java/02_variable/VariableDemo.java` | var 推断、8 种基本类型、final、类型转换 |
| 03 operator | [03_operator/OperatorDemo.java](03_operator/OperatorDemo.java) | `java java/03_operator/OperatorDemo.java` | 算术/自增/比较/逻辑短路/位运算/三元 |
| 04 string | [04_string/StringDemo.java](04_string/StringDemo.java) | `java java/04_string/StringDemo.java` | 字符串方法、equals vs ==、StringBuilder、文本块 |
| 05 control | [05_control/ControlFlowDemo.java](05_control/ControlFlowDemo.java) | `java java/05_control/ControlFlowDemo.java` | if/switch（传统+箭头）、四种循环、标签跳转 |
| 06 function | [06_function/FunctionDemo.java](06_function/FunctionDemo.java) | `java java/06_function/FunctionDemo.java` | 方法定义/重载/可变参数、Lambda、方法引用 |
| 07 collection | [07_collection/CollectionDemo.java](07_collection/CollectionDemo.java) | `java java/07_collection/CollectionDemo.java` | 数组与 Arrays、ArrayList/LinkedList/HashSet、遍历对比 |
| 08 map | [08_map/MapDemo.java](08_map/MapDemo.java) | `java java/08_map/MapDemo.java` | HashMap 增删改查、TreeMap 排序、LinkedHashMap 顺序 |
| 09 oop | [09_oop/OopDemo.java](09_oop/OopDemo.java) | `java java/09_oop/OopDemo.java` | 类/继承/抽象类/接口 default/多态/instanceof 模式匹配 |
| 10 error | [10_error/ErrorDemo.java](10_error/ErrorDemo.java) | `java java/10_error/ErrorDemo.java` | try/catch/finally、多 catch、自定义异常、try-with-resources |
| 11 file_io | [11_file_io/FileIoDemo.java](11_file_io/FileIoDemo.java) | `java java/11_file_io/FileIoDemo.java` | Files 读写、BufferedReader 逐行、File 遍历目录 |
| 12 module | [12_module/demo/ModuleDemo.java](12_module/demo/ModuleDemo.java) | `java java/12_module/demo/ModuleDemo.java` | 包与可见性（public/protected/包私有/private）、静态导入 |
| 13 stdlib | [13_stdlib/StdlibDemo.java](13_stdlib/StdlibDemo.java) | `java java/13_stdlib/StdlibDemo.java` | Optional、Arrays、日期时间、Objects、String.join |
| 14 concurrency | [14_concurrency/ConcurrencyDemo.java](14_concurrency/ConcurrencyDemo.java) | `java java/14_concurrency/ConcurrencyDemo.java` | Thread 两种创建、线程池+Future、synchronized、join |
| 15 generic | [15_generic/GenericDemo.java](15_generic/GenericDemo.java) | `java java/15_generic/GenericDemo.java` | 泛型方法/泛型类/有界参数/通配符 |
| + 特色 records | [16_records/RecordsDemo.java](16_records/RecordsDemo.java) | `java java/16_records/RecordsDemo.java` | record 定义/紧凑构造器/解构/switch 模式匹配（JDK 21） |

> 12_module 说明：单文件直跑要求"文件所在目录与 package 声明一致"，因此入口与工具类放在 `12_module/demo/` 子目录下（`package demo;`），运行时 `Util.java` 会被自动按需编译；`Util.java` 也可单独直跑。

## 进阶说明

- 早期收录的两个入门文件移到了 [legacy/](legacy/)：[HelloWorld.java](legacy/HelloWorld.java)（经典 Hello World）、[test.java](legacy/test.java)（构造器最小示例），仍可直跑
- 每个示例文件头部注释都标明了主题说明、运行命令与预期输出，适合按主题顺序阅读
- 之后的进阶方向：Stream API 与集合流水线、并发包 juc（锁/并发容器/CompletableFuture）、模块系统（JPMS）、JVM 基础（内存模型/GC/调优入门）
