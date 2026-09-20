// 主题说明：面向对象 —— implements 实现接口、abstract 抽象类与抽象方法、
//           访问修饰符 public/private/protected、readonly、参数属性简写、getter/setter、instanceof。
// 运行命令：npx tsx src/09_oop.ts
// 预期输出（关键行）：
//   旺财 在说话：汪！汪！ —— 柴犬
//   describe -> 旺财（柴犬，体力 95）
//   私有字段 -> 只有 Animal 自己的方法能读：秘密
//   getter -> 动物：旺财
//   instanceof Dog -> true ；instanceof Animal -> true
//   Animal.total() -> 2 ；旺财 的只读 id -> 1 ；咪咪 -> 2

// 知识点 1【TS 差异】：interface —— 描述"对象长什么样"的纯类型契约（编译后完全消失，不产生代码）
interface Pet {
  readonly id: number; // readonly：承诺初始化后不再改
  name: string;
  speak(): string;
}

// 知识点 2【TS 差异】：abstract 抽象类 —— "半成品"基类：不能 new，专门被继承；
//           abstract 标记的方法只声明签名，由子类实现
abstract class Animal implements Pet {
  private static nextId = 1; // private static：仅类内部可见的静态成员（所有实例共享）

  readonly id: number; // public readonly：不写修饰符默认 public；初始化后不可再赋值
  name: string; // public（默认）：实现 Pet 接口要求的公开字段
  protected energy: number; // protected：本类与子类可见，类外不可访问
  private secret: string; // private：仅本类可见，子类也不行

  constructor(name: string) {
    this.id = Animal.nextId++; // 静态计数器发号
    this.name = name;
    this.energy = 100;
    this.secret = '秘密';
  }

  abstract speak(): string; // 抽象方法：没有函数体，强制每个子类给出自己的实现

  protected spend(n: number): void {
    // protected 方法：给子类用的"内部工具"，类外调不到
    this.energy = Math.max(0, this.energy - n);
  }

  get label(): string {
    // getter：像属性一样访问的方法
    return `动物：${this.name}`;
  }
  set nickname(v: string) {
    // setter：拦截赋值
    this.name = v;
  }

  reveal(): string {
    return `只有 Animal 自己的方法能读：${this.secret}`; // private 字段的读取入口
  }

  static total(): number {
    return Animal.nextId - 1; // 静态方法：与实例无关，直接用类名调用
  }
}

// 知识点 3：extends 继承 + super 调用父类构造 + 方法重写；参数属性（public breed）是"声明即赋值"简写
class Dog extends Animal {
  constructor(name: string, public breed: string) {
    // 参数属性：构造参数加修饰符，TS 自动声明字段并赋值 this.breed
    super(name); // 必须先调 super 初始化父类部分
  }
  speak(): string {
    this.spend(5); // 子类里可以调用 protected 方法
    return `${this.name} 在说话：汪！汪！`;
  }
  describe(): string {
    return `${this.name}（${this.breed}，体力 ${this.energy}）`; // protected 字段子类可见
  }
}

class Cat extends Animal {
  speak(): string {
    return `${this.name} 在说话：喵～`; // 不实现 speak 会编译报错（抽象方法必须实现）
  }
}

// const ghost = new Animal('幽灵'); // 编译错误：抽象类不能实例化，只能 new 它的子类

const dog = new Dog('旺财', '柴犬');
const cat = new Cat('咪咪');

// 知识点 4：重写与继承来的行为
console.log(dog.speak(), `—— ${dog.breed}`);
console.log(cat.speak());
console.log('describe ->', dog.describe()); // 子类方法里读取 protected 的 energy

// 知识点 5：访问修饰符在类型层面的边界
console.log('私有字段 ->', dog.reveal());
// console.log(dog.secret);   // 编译错误：private，类外不可见
// dog.energy = 0;            // 编译错误：protected，仅类与子类内部可见
// dog.id = 99;               // 编译错误：readonly 属性不可重新赋值

// 知识点 6：getter / setter —— 像属性一样访问
console.log('getter ->', dog.label);
dog.nickname = '来福'; // 走 setter
console.log('setter 改名后 ->', dog.name);

// 知识点 7：instanceof —— 原型链上的类都算；interface 没有运行时存在，只能"鸭子类型"检查
console.log('instanceof Dog ->', dog instanceof Dog, '；instanceof Animal ->', dog instanceof Animal);
console.log('cat instanceof Dog ->', cat instanceof Dog);

// 知识点 8：静态成员与只读 id
console.log('Animal.total() ->', Animal.total(), '；旺财 的只读 id ->', dog.id, '；咪咪 ->', cat.id);
