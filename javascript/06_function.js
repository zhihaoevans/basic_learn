// 主题说明：函数 —— 声明/表达式/箭头函数三种写法、默认参数与剩余参数、闭包计数器、
//           回调与高阶函数（函数是"一等公民"，可以像值一样传递）。
// 运行命令：node javascript/06_function.js
// 预期输出（关键行）：
//   声明 5 / 表达式 6 / 箭头 -1
//   你好，博士·教授 Li
//   闭包计数器：1 2 3
//   回调收到：任务A 完成
//   高阶函数 applyTwice -> 63

// 知识点 1：函数声明（有提升，可在定义前调用）、函数表达式、箭头函数（this 行为更简单）
function add(a, b) { return a + b; }
const mul = function (a, b) { return a * b; };
const sub = (a, b) => a - b; // 单表达式可省略 return 与花括号
console.log('声明', add(2, 3), '/ 表达式', mul(2, 3), '/ 箭头', sub(2, 3));

// 知识点 2：默认参数 —— 调用时不传就取默认值
function greet(name = '游客') {
  return `你好，${name}`;
}
console.log(greet('Li'), '/', greet());

// 知识点 3：剩余参数（rest）—— 把多余的实参收成数组
function intro(name, ...titles) {
  return `你好，${titles.join('·') || '无头衔'} ${name}`;
}
console.log(intro('Li', '博士', '教授'));

// 知识点 4：闭包 —— 内层函数记住外层函数的变量，外层返回后依然可用
function makeCounter() {
  let n = 0; // 这个变量被返回的函数"关住"了
  return () => ++n;
}
const next = makeCounter();
console.log('闭包计数器：', next(), next(), next());
const next2 = makeCounter(); // 每次调用 makeCounter 都是独立的闭包环境
console.log('另一个计数器互不干扰：', next2());

// 知识点 5：回调 —— 把函数作为参数传给另一个函数，完成后被"回调"
function doWork(task, callback) {
  const result = `${task} 完成`;
  callback(result);
}
doWork('任务A', (msg) => console.log('回调收到：', msg));

// 知识点 6：高阶函数 —— 接收函数作参数、或返回函数的函数
function applyTwice(fn, v) {
  return fn(fn(v));
}
console.log('高阶函数 applyTwice ->', applyTwice((n) => n * 3, 7)); // (7*3)*3 = 63
function makeMultiplier(k) {
  return (n) => n * k; // 返回函数：函数也是值
}
const double = makeMultiplier(2);
console.log('返回函数 double(21) ->', double(21));
