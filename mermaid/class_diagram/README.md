# UML类图关系演示项目

本项目展示了UML中的各种类关系，包括Mermaid图表和对应的C++实现。

## 项目结构

```
class_diagram/
├── uml_relationships.md    # Mermaid类图定义和关系说明
├── uml_classes.h          # C++头文件 - 类定义
├── uml_classes.cpp        # C++实现文件 - 方法实现
├── main.cpp               # 主程序 - 演示各种关系
├── Makefile               # 编译配置
└── README.md              # 项目说明文档
```

## UML关系类型

### 1. 继承 (Inheritance)
- **关系**: Dog → Animal, Bird → Animal, Duck → Bird
- **特点**: "is-a" 关系，子类继承父类的属性和方法
- **C++实现**: 使用 `class Derived : public Base`

### 2. 实现 (Realization)
- **关系**: Bird → Flyable, Duck → Flyable/Swimmable
- **特点**: 类实现接口的关系
- **C++实现**: 使用纯虚函数和多重继承

### 3. 组合 (Composition)
- **关系**: Car → Engine/Wheel
- **特点**: "part-of" 关系，强拥有关系，整体销毁时部分也销毁
- **C++实现**: 使用 `std::unique_ptr` 或直接成员对象

### 4. 聚合 (Aggregation)
- **关系**: Company → Person
- **特点**: "has-a" 关系，弱拥有关系，整体销毁时部分可以独立存在
- **C++实现**: 使用指针或引用，不负责对象的生命周期

### 5. 关联 (Association)
- **关系**: Person → Department, Library → Book
- **特点**: 类之间的结构化关系，表示一个类知道另一个类
- **C++实现**: 使用指针、引用或对象成员

### 6. 依赖 (Dependency)
- **关系**: Student → Book, Library → Student
- **特点**: 一个类使用另一个类，通常是临时性的
- **C++实现**: 方法参数、局部变量或临时对象

## 编译和运行

### 使用Makefile编译

```bash
# 编译程序
make

# 编译并运行
make run

# 清理编译文件
make clean

# 重新编译
make rebuild

# 查看帮助
make help
```

### 手动编译

```bash
# 编译
g++ -std=c++14 -Wall -Wextra -O2 main.cpp uml_classes.cpp -o uml_demo

# 运行
./uml_demo
```

## 程序输出说明

程序运行时会依次演示：

1. **继承和实现关系演示**
   - 多态性调用
   - 接口方法实现
   - 子类特有方法

2. **组合关系演示**
   - 汽车对象的创建和销毁
   - 组件对象的自动管理

3. **聚合和关联关系演示**
   - 公司和员工的聚合关系
   - 部门和经理的关联关系

4. **依赖关系演示**
   - 学生使用书籍学习
   - 图书馆为学生提供服务

5. **多态性综合演示**
   - 基类指针调用派生类方法
   - 接口指针的多态调用

## 关键设计模式和技术

- **RAII**: 使用智能指针管理资源
- **多态性**: 虚函数和接口实现
- **组合优于继承**: 在Car类中体现
- **依赖注入**: 在构造函数中传入依赖对象
- **内存安全**: 使用智能指针避免内存泄漏

## 学习要点

1. **理解不同关系的语义差异**
2. **掌握C++中实现各种关系的技术**
3. **体会面向对象设计的核心思想**
4. **学习现代C++的最佳实践**