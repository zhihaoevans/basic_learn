// 主题说明：面向对象 —— class 定义、constructor、extends/super 继承与方法重写、
//           静态方法、私有字段 #、getter/setter、instanceof 判断实例关系。
// 运行命令：node javascript/09_oop.js
// 预期输出（关键行）：
//   旺财 在说话：汪！汪！ —— 柴犬
//   静态方法 total() -> 2
//   getter -> 动物：旺财
//   私有字段 -> 只有类自己的方法能读：秘密
//   instanceof Dog -> true ；instanceof Animal -> true

// 知识点 1：class + constructor；static 静态成员属于类本身
class Animal {
  static count = 0; // 静态属性：所有实例共享

  #secret = '秘密'; // 知识点 4（前置声明）：# 开头的私有字段，类外不可访问

  constructor(name) {
    this.name = name; // this 指向新创建的实例
    Animal.count++;
  }

  speak() {
    return `${this.name} 在说话`;
  }

  // 知识点 2：getter/setter —— 像属性一样访问的方法
  get label() {
    return `动物：${this.name}`;
  }
  set nickname(v) {
    this.name = v;
  }

  // 知识点 3：私有字段的读取入口 —— 类内部可以访问 #
  reveal() {
    return `只有类自己的方法能读：${this.#secret}`;
  }

  // 静态方法：直接用类名调用，常做工厂或与实例无关的工具
  static total() {
    return Animal.count;
  }
}

// 知识点 5：extends 继承 + super 调用父类构造与方法 + 方法重写
class Dog extends Animal {
  constructor(name, breed) {
    super(name); // 必须先调 super 初始化父类部分
    this.breed = breed;
  }
  speak() {
    return `${super.speak()}：汪！汪！`; // super.speak() 复用父类逻辑
  }
  describe() {
    return `${this.name}（${this.breed}）`;
  }
}

const dog = new Dog('旺财', '柴犬');
const cat = new Animal('咪咪');

// 重写后的 speak 与继承来的行为
console.log(dog.speak(), `—— ${dog.breed}`);
console.log(cat.speak());

// 静态成员
console.log('静态方法 total() ->', Animal.total());

// getter / setter
console.log('getter ->', dog.label);
dog.nickname = '来福'; // 走 setter
console.log('setter 改名后 ->', dog.name);

// 私有字段：类外直接访问 dog.#secret 会语法报错，只能通过类方法读
console.log('私有字段 ->', dog.reveal());

// 知识点 6：instanceof —— 原型链上的构造函数都算
console.log('instanceof Dog ->', dog instanceof Dog, '；instanceof Animal ->', dog instanceof Animal);
console.log('cat instanceof Dog ->', cat instanceof Dog);
