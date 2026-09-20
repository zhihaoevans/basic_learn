// 主题说明：JavaScript 特色主题 —— 解构与展开：对象/数组解构、默认值、换名、嵌套解构、
//           展开运算符（合并/复制/传参）、剩余收集（rest）、函数参数解构。
//           这是 JS 每天都在用的"按结构取值"语法，也是 15 generic 标 ➖ 后的语言亮点补充。
// 运行命令：node javascript/15_destructuring.js
// 预期输出（关键行）：
//   对象解构 -> Li 30
//   默认值+换名 -> 无名 / 北京
//   数组解构（跳位+默认值）-> a 缺省
//   解构交换 -> p=2, q=1
//   展开合并对象 -> { name: 'Li', age: 31, city: '北京', vip: true }
//   数组 rest -> head=1, tail=[2,3,4]
//   函数参数解构 drawRect({ w: 100 }) -> (0,0) 100x100

const user = { name: 'Li', age: 30, city: '北京' };

// 知识点 1：对象解构 —— 按属性名直接取值，声明即提取
const { name, age } = user;
console.log('对象解构 ->', name, age);

// 知识点 2：默认值 + 换名 —— 属性缺失时给默认值；用 as 语义改本地名（语法是 "属性名: 新名"）
const { nickname: aka = '无名' } = user; // nickname 不存在 -> 默认值
const { city: town } = user;             // 取 city，本地叫 town
console.log('默认值+换名 ->', aka, '/', town);

// 知识点 3：数组解构 —— 按位置取值，逗号跳位，缺失给默认值
const [first, , third = '缺省'] = ['a', 'b'];
console.log('数组解构（跳位+默认值）->', first, third);

// 知识点 4：经典应用 —— 不需要临时变量即可交换两个变量
let p = 1;
let q = 2;
[p, q] = [q, p];
console.log('解构交换 ->', `p=${p}, q=${q}`);

// 知识点 5：嵌套解构 —— 按结构一层层取
const resp = { data: { version: '2.0' }, code: 0 };
const { data: { version }, code } = resp;
console.log('嵌套解构 ->', `v${version}, code=${code}`);

// 知识点 6：展开 spread —— 复制/合并对象与数组（浅拷贝），后者覆盖前者
const merged = { ...user, age: 31, vip: true };
console.log('展开合并对象 ->', merged);
const concat = [1, 2, ...[3, 4], 5];
console.log('展开合并数组 ->', concat);
const max = Math.max(...[5, 9, 3]); // 展开传参
console.log('展开传参 Math.max ->', max);

// 知识点 7：收集 rest —— 与展开相反，把剩余的收起来（对象/数组/参数三处通用）
const { name: n, ...restObj } = user;
console.log('对象收集剩余 ->', `name=${n}, rest=${JSON.stringify(restObj)}`);
const [head, ...tail] = [1, 2, 3, 4];
console.log('数组 rest ->', `head=${head}, tail=${JSON.stringify(tail)}`);

// 知识点 8：函数参数解构 —— 形参直接按结构接住对象，每个字段还能带默认值
function drawRect({ x = 0, y = 0, w = 10, h = w }) {
  return `(${x},${y}) ${w}x${h}`;
}
console.log('函数参数解构 drawRect({ w: 100 }) ->', drawRect({ w: 100 }));
console.log('全默认 drawRect({}) ->', drawRect({}));

// 知识点 9：解构遍历 —— 配合 entries 一次拿到下标与值（见 07 数组示例，这里再巩固一遍）
for (const [i, v] of ['甲', '乙'].entries()) {
  console.log(`第 ${i} 位 -> ${v}`);
}
