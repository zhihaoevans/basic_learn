// 主题说明：TypeScript 泛型 —— 泛型函数（类型参数的推断与显式指定）、约束 extends（keyof / 结构约束）、
//           泛型接口与泛型类、泛型默认值。这是 JS 里没有的能力：类型层面的"参数化"。
// 运行命令：npx tsx src/15_generic.ts
// 预期输出（关键行）：
//   identity 推断 -> 42 是 number ； ts 是 string
//   约束 keyof -> name = Li ；age = 30
//   结构约束 longest -> pineapple （比的是 length）；数组版 -> [ 1, 2, 3 ]
//   泛型接口 Box<number> -> 99 ； 分数
//   Box 默认 T=string -> hello ；覆盖默认 -> [ 1, 2 ]
//   泛型默认值 Pair -> [ 'a', 1 ] 与 [ 1, 'a' ]
//   泛型类 Stack -> 栈顶 3 ；出栈后大小 2

// 知识点 1：泛型函数 —— T 是"调用时才确定"的类型参数；传 number 进去 T 就是 number，传 string 就是 string
function identity<T>(value: T): T {
  return value; // 进什么类型出什么类型 —— 丢 any 的"万能"换来"形状保持"
}
const fromNumber: number = identity(42); // 不写 <number>，从实参推断
const fromString: string = identity('ts');
console.log('identity 推断 ->', fromNumber, '是', typeof fromNumber, '；', fromString, '是', typeof fromString);
const explicit = identity<boolean>(true); // 也可以显式指定类型参数
console.log('identity 显式 <boolean> ->', explicit);

// 知识点 2：约束 extends keyof —— "K 必须是 T 的键"，取值类型还能精确到 T[K]（键对应的值类型）
function pick<T, K extends keyof T>(obj: T, key: K): T[K] {
  return obj[key];
}
const profile = { name: 'Li', age: 30, vip: true };
console.log('约束 keyof -> name =', pick(profile, 'name'), '；age =', pick(profile, 'age'));
// pick(profile, 'nickname'); // 编译错误：'nickname' 不是 profile 的键 —— 拼错键名当场暴露
const age: number = pick(profile, 'age'); // T[K] 在这里精确到 number
const vip: boolean = pick(profile, 'vip'); // 在这里精确到 boolean
console.log('T[K] 精确返回类型 -> age:', age, '；vip:', vip);

// 知识点 3：约束 extends 结构 —— 只要"有 length: number"就能进来，返回值保持原类型（不是裸 string）
function longest<T extends { length: number }>(a: T, b: T): T {
  return a.length >= b.length ? a : b;
}
const word = longest('pineapple', 'fig'); // T 推断为 string（字面量收窄后仍是 string）
const firstArr = longest([1, 2, 3], [1]); // T 推断为 number[] —— 同一函数服务两种形状
console.log('结构约束 longest ->', word, '（比的是 length）；数组版 ->', firstArr);

// 知识点 4：泛型接口 —— 描述"盒子"这类容器：装什么类型，value 就是什么类型
interface Box<T> {
  value: T;
  tag: string;
}
const numBox: Box<number> = { value: 99, tag: '分数' };
console.log('泛型接口 Box<number> ->', numBox.value, '；', numBox.tag);

// 知识点 5：泛型默认值 —— 不传类型参数时取默认，接口与函数都支持
interface Box2<T = string> {
  // T 默认是 string
  value: T;
}
const strBox: Box2 = { value: 'hello' }; // 未指定 -> T=string
const anyBox: Box2<number[]> = { value: [1, 2] }; // 显式覆盖默认
console.log('Box 默认 T=string ->', strBox.value, '；覆盖默认 ->', anyBox.value);

function makePair<A, B = A>(a: A, b: B): [A, B] {
  // 函数的泛型默认值：只给 A 时 B 跟着取 A
  return [a, b];
}
console.log('泛型默认值 Pair ->', makePair('a', 1), '与', makePair(1, 'a'));

// 知识点 6：泛型类 —— 类的字段与方法共享同一组类型参数
class Stack<T> {
  private items: T[] = [];

  push(v: T): void {
    this.items.push(v);
  }
  pop(): T | undefined {
    return this.items.pop(); // 空栈弹出的可能是 undefined
  }
  get size(): number {
    return this.items.length;
  }
}
const stack = new Stack<number>(); // 实例化时确定 T
stack.push(1);
stack.push(2);
stack.push(3);
console.log('泛型类 Stack -> 栈顶', stack.pop(), '；出栈后大小', stack.size);
const strStack = new Stack<string>();
strStack.push('甲');
console.log('另一个 Stack<string> ->', strStack.pop(), '；互不干扰', stack.size === 2);

// 知识点 7：泛型不只是"容器" —— Array<T>、Promise<T>、Map<K,V>、Record<K,V>（见 07/08/11/13/16）
//           都是泛型：类型参数让同一套代码/接口服务所有形状，这正是 15 generic 主题在 TS 的完整体现
