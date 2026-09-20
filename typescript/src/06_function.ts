// 主题说明：函数 —— 类型签名与推断、可选参数与默认参数、剩余参数、函数重载、
//           闭包计数器、回调与高阶函数（函数是"一等公民"，类型上用签名描述形状）。
// 运行命令：npx tsx src/06_function.ts
// 预期输出（关键行）：
//   声明 5 / 表达式 6 / 箭头 -1
//   greet() -> 你好，游客 ；greet('Li', '博士') -> 你好，博士 Li
//   重载 formatValue('7', 3) -> ..7 ；formatValue(3.14159, 2) -> 3.14
//   闭包计数器： 1 2 3
//   高阶函数 applyTwice -> 63

// 知识点 1：三种写法 + 类型签名 —— (a: number, b: number) => number 是"函数的类型"（箭头形状）
function add(a: number, b: number): number {
  return a + b;
}
const mul: (a: number, b: number) => number = function (a, b) {
  return a * b; // 参数类型由签名反向推断，函数体里不必重复写
};
const sub = (a: number, b: number): number => a - b; // 箭头函数：单表达式可省 return 与花括号
console.log('声明', add(2, 3), '/ 表达式', mul(2, 3), '/ 箭头', sub(2, 3));

// 知识点 2：类型别名描述函数形状 —— type Fn = ... 把签名起名复用（回调参数到处都是这种形状）
type BinOp = (a: number, b: number) => number;
const maxOf: BinOp = (a, b) => (a >= b ? a : b);
console.log('BinOp 类型别名 maxOf ->', maxOf(3, 7));

// 知识点 3：可选参数（?:）与默认参数（=默认值）—— 可选参数必须排在必选参数后面
function greet(name = '游客', title?: string): string {
  return title === undefined ? `你好，${name}` : `你好，${title} ${name}`;
}
console.log('greet() ->', greet(), '；greet(\'Li\', \'博士\') ->', greet('Li', '博士'));

// 知识点 4：剩余参数（rest）—— 把多余的实参收成数组，类型标注是"元素类型的数组"
function sum(...nums: number[]): number {
  return nums.reduce((acc, n) => acc + n, 0);
}
console.log('剩余参数 sum ->', sum(1, 2, 3, 4));

// 知识点 5【TS 差异】：函数重载 —— 同名函数给多套"参数形态 → 返回"签名，编译器按实参挑选；
// 实现签名（带完整逻辑的那条）对调用方不可见，必须能覆盖所有重载
function formatValue(value: string, width: number): string; // 形态一：字符串左补齐
function formatValue(value: number, digits: number): string; // 形态二：数字定小数位
function formatValue(value: string | number, n: number): string {
  if (typeof value === 'string') {
    return value.padStart(n, '.'); // typeof 收窄后走形态一
  }
  return value.toFixed(n); // 形态二
}
console.log("重载 formatValue('7', 3) ->", formatValue('7', 3), '；formatValue(3.14159, 2) ->', formatValue(3.14159, 2));
// formatValue(true, 2); // 编译错误：没有任何重载匹配 (boolean, number)

// 知识点 6：闭包 —— 内层函数记住外层函数的变量，外层返回后依然可用；类型上返回"函数"
function makeCounter(): () => number {
  let n = 0; // 这个变量被返回的函数"关住"了
  return () => ++n;
}
const next = makeCounter();
console.log('闭包计数器：', next(), next(), next());
const next2 = makeCounter(); // 每次调用 makeCounter 都是独立的闭包环境
console.log('另一个计数器互不干扰：', next2());

// 知识点 7：回调 —— 把函数作为参数传给另一个函数；参数类型直接写函数签名
function doWork(task: string, callback: (result: string) => void): void {
  callback(`${task} 完成`);
}
doWork('任务A', (msg) => console.log('回调收到：', msg)); // msg 的类型 string 由签名推断

// 知识点 8：高阶函数 —— 接收函数作参数、或返回函数的函数；配泛型可做到"形状跟着值走"（见 15）
function applyTwice(fn: (v: number) => number, v: number): number {
  return fn(fn(v));
}
console.log('高阶函数 applyTwice ->', applyTwice((n) => n * 3, 7)); // (7*3)*3 = 63
function makeMultiplier(k: number): (n: number) => number {
  return (n) => n * k; // 返回函数：函数也是值
}
const double = makeMultiplier(2);
console.log('返回函数 double(21) ->', double(21));
