// 主题说明：变量声明三兄弟 let/const/var 的区别、JavaScript 的动态类型、typeof 判断类型，
//           以及基本类型（按值复制）与引用类型（按引用共享）的赋值差异。
// 运行命令：node javascript/02_variable.js
// 预期输出（关键行）：
//   let 可重新赋值：2
//   const 数组内容可改：[ 1, 2 ]
//   typeof null 是 object（著名的历史怪点）
//   基本类型赋值后互不影响：10
//   引用类型共享同一对象：99

// 知识点 1：let —— 块级作用域（{} 内有效），可重新赋值
let count = 1;
count = 2;
console.log('let 可重新赋值：', count);

// 知识点 2：const —— 块级作用域，声明后不可重新赋值；但对象/数组的"内容"仍然可以修改
const PI = 3.14;
// PI = 3.15; // TypeError: Assignment to constant variable.
const list = [1];
list.push(2); // 合法：改的是数组内容，不是 const 绑定本身
console.log('const 数组内容可改：', list);

// 知识点 3：var —— 函数作用域、有变量提升，现代 JavaScript 已基本弃用，这里仅作识别
var legacy = '旧写法';
console.log(`var 声明仍会见到：${legacy}（新代码请用 let/const）`);

// 知识点 4：动态类型 —— 同一变量可先后存放不同类型的值，类型跟着值走
let x = 42;
x = 'hello';
x = true;
console.log('动态类型最终值：', x);

// 知识点 5：typeof 判断类型（返回字符串）
console.log('number string boolean undefined bigint symbol object ->',
  typeof 42, typeof 'a', typeof true, typeof undefined, typeof 1n, typeof Symbol(), typeof {});
console.log('typeof null 是', typeof null, '（著名的历史怪点）');
console.log('typeof 函数是', typeof (() => {}), '（函数是一种特殊的对象）');

// 知识点 6：基本类型（number/string/boolean 等）赋值时复制"值"
let a = 10;
let b = a;
b = 99;
console.log('基本类型赋值后互不影响：', a); // 10

// 知识点 7：引用类型（对象/数组）赋值时复制"地址"，两个变量指向同一个对象
const obj1 = { v: 1 };
const obj2 = obj1;
obj2.v = 99;
console.log('引用类型共享同一对象：', obj1.v); // 99
