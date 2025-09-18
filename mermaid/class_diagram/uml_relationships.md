# UML类图关系示例

本文档展示了UML中的各种关系类型，包括继承、实现、组合、聚合、关联和依赖关系。

## Mermaid类图代码

```mermaid
classDiagram
    %% 定义抽象类和接口
    class Animal {
        <<abstract>>
        #name: string
        #age: int
        +getName(): string
        +getAge(): int
        +makeSound()* void
    }
    
    class Flyable {
        <<interface>>
        +fly(): void
    }
    
    class Swimmable {
        <<interface>>
        +swim(): void
    }
    
    %% 具体动物类
    class Dog {
        -breed: string
        +Dog(name: string, age: int, breed: string)
        +makeSound(): void
        +bark(): void
        +getBreed(): string
    }
    
    class Bird {
        -wingspan: double
        +Bird(name: string, age: int, wingspan: double)
        +makeSound(): void
        +getWingspan(): double
    }
    
    class Duck {
        -waterproof: bool
        +Duck(name: string, age: int, wingspan: double)
        +makeSound(): void
        +dive(): void
    }
    
    %% 汽车相关类 - 展示组合和聚合
    class Car {
        -model: string
        -year: int
        -engine: Engine
        -wheels: Wheel[4]
        +Car(model: string, year: int)
        +start(): void
        +stop(): void
        +getModel(): string
    }
    
    class Engine {
        -horsepower: int
        -type: string
        +Engine(hp: int, type: string)
        +start(): void
        +stop(): void
        +getHorsepower(): int
    }
    
    class Wheel {
        -size: int
        -brand: string
        +Wheel(size: int, brand: string)
        +rotate(): void
        +getSize(): int
    }
    
    %% 人员和组织类 - 展示关联和聚合
    class Person {
        -name: string
        -id: int
        +Person(name: string, id: int)
        +getName(): string
        +getId(): int
        +work(): void
    }
    
    class Company {
        -name: string
        -employees: Person[]
        +Company(name: string)
        +addEmployee(person: Person): void
        +removeEmployee(person: Person): void
        +getEmployeeCount(): int
    }
    
    class Department {
        -name: string
        -manager: Person
        +Department(name: string, manager: Person)
        +setManager(person: Person): void
        +getManager(): Person
    }
    
    %% 学习相关类 - 展示依赖关系
    class Student {
        -studentId: string
        -name: string
        +Student(id: string, name: string)
        +study(book: Book): void
        +takeExam(): void
    }
    
    class Book {
        -title: string
        -author: string
        -isbn: string
        +Book(title: string, author: string, isbn: string)
        +getTitle(): string
        +getAuthor(): string
    }
    
    class Library {
        -books: Book[]
        +addBook(book: Book): void
        +findBook(title: string): Book
        +lendBook(book: Book, student: Student): void
    }
    
    %% 关系定义
    %% 继承关系 (Inheritance) - 实线三角箭头
    Animal <|-- Dog : 继承
    Animal <|-- Bird : 继承
    Bird <|-- Duck : 继承
    
    %% 实现关系 (Realization) - 虚线三角箭头
    Flyable <|.. Bird : 实现
    Flyable <|.. Duck : 实现
    Swimmable <|.. Duck : 实现
    
    %% 组合关系 (Composition) - 实线菱形箭头，强拥有关系
    Car *-- Engine : 组合
    Car *-- Wheel : 组合
    
    %% 聚合关系 (Aggregation) - 空心菱形箭头，弱拥有关系
    Company o-- Person : 聚合
    Department o-- Person : 聚合
    
    %% 关联关系 (Association) - 实线箭头
    Person --> Department : 属于
    Library --> Book : 管理
    
    %% 依赖关系 (Dependency) - 虚线箭头
    Student ..> Book : 使用
    Library ..> Student : 服务
    
    %% 多重性标注
    Company "1" o-- "0..*" Person : 雇佣
    Car "1" *-- "4" Wheel : 拥有
    Library "1" --> "0..*" Book : 收藏
```

## 关系类型说明

### 1. 继承 (Inheritance) - `<|--`
- **含义**: "is-a" 关系，子类继承父类的属性和方法
- **箭头**: 实线三角箭头，指向父类
- **示例**: Dog继承Animal，Bird继承Animal

### 2. 实现 (Realization) - `<|..`
- **含义**: 类实现接口的关系
- **箭头**: 虚线三角箭头，指向接口
- **示例**: Bird实现Flyable接口，Duck实现Flyable和Swimmable接口

### 3. 组合 (Composition) - `*--`
- **含义**: "part-of" 关系，强拥有关系，整体销毁时部分也销毁
- **箭头**: 实心菱形箭头，菱形指向整体
- **示例**: Car拥有Engine，Car销毁时Engine也销毁

### 4. 聚合 (Aggregation) - `o--`
- **含义**: "has-a" 关系，弱拥有关系，整体销毁时部分可以独立存在
- **箭头**: 空心菱形箭头，菱形指向整体
- **示例**: Company拥有Employee，Company解散时Employee可以存在

### 5. 关联 (Association) - `-->`
- **含义**: 类之间的结构化关系，通常表示一个类知道另一个类
- **箭头**: 实线箭头，指向被关联的类
- **示例**: Person关联Department，Library关联Book

### 6. 依赖 (Dependency) - `..>`
- **含义**: 一个类使用另一个类，通常是临时性的
- **箭头**: 虚线箭头，指向被依赖的类
- **示例**: Student使用Book学习，Library为Student提供服务