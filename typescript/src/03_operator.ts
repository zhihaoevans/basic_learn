// 主题说明：运算符与表达式 —— 算术（含 0.1+0.2 浮点精度）、宽松 == 与严格 ===、逻辑与短路、
//           空值合并 ?? 与可选链 ?.、位运算；以及 TS 在编译期替 === 挡掉的一类笔误。
// 运行命令：npx tsx src/03_operator.ts
// 预期输出（关键行）：
//   0.1 + 0.2 = 0.30000000000000004
//   宽松 == 隐式转换：1 == '1' -> true （TS 里同样不推荐）
//   ?? 与 || 的区别：0 ?? 8080 = 0 ；0 || 8080 = 8080
//   可选链兜底 -> 北京

// 知识点 1：算术运算 + - * / % **（** 是幂运算）—— 操作数类型不合适会被编译器拒绝
console.log('7 / 2 =', 7 / 2, '（整数除法也得小数）');
console.log('7 % 3 =', 7 % 3, '；2 ** 10 =', 2 ** 10);
// '3' * 2 在 TS 里是编译错误：算术运算符不接受 string（JS 会静默转成数字）

// 知识点 2：浮点精度 —— 二进制浮点数无法精确表示部分十进制小数（number 是 IEEE 754 双精度）
console.log('0.1 + 0.2 =', 0.1 + 0.2);
console.log('严格比较 (0.1+0.2) === 0.3 ->', 0.1 + 0.2 === 0.3);
console.log('实务做法 toFixed(2) ->', Number((0.1 + 0.2).toFixed(2)));

// 知识点 3：== vs === —— == 先做类型转换再比较，=== 严格比较类型与值（始终优先用 ===）
// 演示时放进函数参数：参数是联合类型且不会被"赋值收窄"，最接近真实调用场景
function looseEq(v: number | string): boolean {
  return v == '1'; // 宽松相等：字符串 '1' 被隐式转成数字再比
}
function strictEq(v: number | string): boolean {
  return v === '1'; // 严格相等：类型不同直接 false
}
console.log("宽松 == 隐式转换：1 == '1' ->", looseEq(1), '（TS 里同样不推荐）');
console.log("严格 === 类型不同即 false：1 === '1' ->", strictEq(1));
// TS 的加强：拿 === 比较两个"不可能相等"的类型，会直接报编译错误——
// console.log(1 === '1'); // 编译错误 TS2367：number 与 string 没有重叠，这个比较永远是 false
// 顺带一提：null == undefined 是 JS 的著名特例（宽松相等为 true）；但新版 TS 检查器认为
// nullish 之间的 == 没有意义会直接报错 —— 实务中判空用 x === null || x === undefined（或下面的 ?. 与 ??）
// NaN === NaN 恒为 false（新版 TS 检查器会直接报"这个条件永远为 false"）—— 判 NaN 一律用 Number.isNaN
console.log('Number.isNaN(NaN) ->', Number.isNaN(NaN));

// 知识点 4：逻辑与短路 —— && / || 返回的是"操作数本身"，不是布尔值
console.log("true && '命中' ->", true && '命中');
console.log("false || '备选' ->", false || '备选');
console.log("0 || '默认' ->", 0 || '默认', '（0 是假值，被跳过）');

// 知识点 5：?? 空值合并 —— 只在 null/undefined 时取右侧，保留 0、''、false 等假值
const port = 0;
console.log('?? 与 || 的区别：0 ?? 8080 =', port ?? 8080, '；0 || 8080 =', port || 8080);

// 知识点 6：?. 可选链 —— 对 null/undefined 安全取属性；strictNullChecks 下返回类型自动带 | undefined
interface Address {
  city: string;
}
interface User {
  name: string;
  address?: Address; // 可选属性：可能不存在
}
const user: User = { name: 'Li' };
console.log('可选链取缺失属性：', user.address?.city); // undefined，不抛错
user.address = { city: '北京' };
console.log('可选链兜底 ->', user.address?.city ?? '未知城市');

// 知识点 7：位运算 & | ^ ~ << >>（按 32 位整数处理）
console.log('5 & 3 =', 5 & 3, '；5 | 3 =', 5 | 3, '；5 ^ 3 =', 5 ^ 3);
console.log('~5 =', ~5, '；1 << 4 =', 1 << 4, '；-16 >> 2 =', -16 >> 2);
