// 主题说明：变量与类型系统 —— let/const、类型标注与推断、any/unknown/never 三种"特殊类型"、
//           typeof/instanceof 类型收窄，以及基本类型（值复制）与引用类型（址共享）。
// 运行命令：npx tsx src/02_variable.ts
// 预期输出（关键行）：
//   let 可重新赋值： 2
//   const 数组内容可改： [ 1, 2 ]
//   unknown 收窄后加一 -> 3 4
//   基本类型赋值后互不影响： 10
//   引用类型共享同一对象： 99

// 知识点 1：let / const —— 语义与 JS 相同；let 的类型由初值推断后同样锁定
let count = 1;
count = 2; // 合法：还是 number
// count = '二'; // 编译错误：string 不能赋给 number
console.log('let 可重新赋值：', count);

const PI = 3.14; // 常量：绑定不可换（类型上还隐含"3.14 这个字面量"，见 16 的 as const）
const list: number[] = [1]; // number[] 是"元素全是数字的数组"类型标注
list.push(2); // 合法：改的是数组内容，不是 const 绑定本身
console.log('const 数组内容可改：', list);

// 知识点 2：类型标注 vs 类型推断 —— 简单初值交给推断，复杂形状（对象/联合）建议显式标注
let explicit: string = '显式标注的 string';
let implicit = '推断出的 string';
console.log('标注与推断都能用：', explicit, '/', implicit);

// 知识点 3：TS 没有 int/double 之分 —— 数字统一是 number；null/undefined 各自成独立类型
const n1: number = 42;
const s1: string = '四十二';
const b1: boolean = true;
const nil: null = null;
const undef: undefined = undefined;
console.log('五种初见类型：', n1, s1, b1, nil, undef);

// 知识点 4：any —— 关掉检查的逃生舱：什么都能放、什么都能做，TS 不再报错（能不用就不用）
let anything: any = 1;
anything = '一'; // any 允许换类型（等于回到 JS 的动态类型）
console.log('any 关掉检查：', anything, '（运行时是字符串）');

// 知识点 5：unknown —— any 的安全版：可以接收任何值，但用之前必须先"收窄"证明类型
function plusOne(v: unknown): number {
  if (typeof v === 'number') return v + 1; // typeof 收窄：这个分支里 v 已经是 number
  if (typeof v === 'string' && v !== '' && !Number.isNaN(Number(v))) return Number(v) + 1;
  throw new Error('v 不是数字或数字字符串');
}
const fromOutside: unknown = JSON.parse('2'); // 外部数据先进 unknown（JSON.parse 返回 any）
console.log('unknown 收窄后加一 ->', plusOne(fromOutside), plusOne('3'));

// 知识点 6：never —— "永远不会有值"的类型：抛错/死循环的函数没有返回值
function fail(msg: string): never {
  throw new Error(msg); // 执行不到 return —— 推断返回类型 never
}
try {
  fail('演示 never');
} catch {
  console.log('never：抛错的函数没有返回值，被 catch 接住');
}

// 知识点 7：instanceof 收窄 —— 把"可能是 A 也可能是 B"细化成具体一种
const maybe: Date | null = new Date(0); // 类型允许为空（模拟接口返回 null 的场景）
if (maybe instanceof Date) {
  console.log('instanceof 收窄 ->', maybe.getUTCFullYear()); // 这里 maybe 已收窄为 Date
}

// 知识点 8：基本类型（number/string/boolean）赋值复制"值"；引用类型（对象/数组）复制"地址"
let a = 10;
let b = a;
b = 99;
console.log('基本类型赋值后互不影响：', a); // 10
const obj1 = { v: 1 };
const obj2: { v: number } = obj1; // 对象类型标注：形状相同即兼容（结构化类型）
obj2.v = 99;
console.log('引用类型共享同一对象：', obj1.v); // 99
