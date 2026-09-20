// 主题说明：运算符与表达式 —— 算术（含 0.1+0.2 浮点精度）、宽松 == 与严格 ===、逻辑与短路、
//           空值合并 ?? 与可选链 ?.、位运算。
// 运行命令：node javascript/03_operator.js
// 预期输出（关键行）：
//   0.1 + 0.2 = 0.30000000000000004
//   严格比较 (0.1+0.2) === 0.3 -> false
//   1 == '1' -> true ；1 === '1' -> false
//   ?? 与 || 的区别：0 ?? 8080 = 0 ；0 || 8080 = 8080

// 知识点 1：算术运算 + - * / % **（** 是幂运算）
console.log('7 / 2 =', 7 / 2, '（整数除法也得小数）');
console.log('7 % 3 =', 7 % 3, '；2 ** 10 =', 2 ** 10);

// 知识点 2：浮点精度 —— 二进制浮点数无法精确表示部分十进制小数（与 Java/C 的 double 同源问题）
console.log('0.1 + 0.2 =', 0.1 + 0.2);
console.log('严格比较 (0.1+0.2) === 0.3 ->', 0.1 + 0.2 === 0.3);
console.log('实务做法 toFixed(2) ->', Number((0.1 + 0.2).toFixed(2)));

// 知识点 3：== vs === —— == 会先做类型转换再比较，=== 严格比较类型与值（始终优先用 ===）
console.log("1 == '1' ->", 1 == '1', '（字符串被转成了数字）');
console.log("1 === '1' ->", 1 === '1');
console.log('null == undefined ->', null == undefined, '（一对特例：宽松相等）');
console.log('NaN === NaN ->', NaN === NaN, '；Number.isNaN(NaN) ->', Number.isNaN(NaN));

// 知识点 4：逻辑与短路 —— && / || 返回的是"操作数本身"，不是布尔值
console.log("true && '命中' ->", true && '命中');
console.log("false || '备选' ->", false || '备选');
console.log("0 || '默认' ->", 0 || '默认', '（0 是假值，被跳过）');

// 知识点 5：?? 空值合并 —— 只在 null/undefined 时取右侧，保留 0、''、false 等假值
const port = 0;
console.log('?? 与 || 的区别：0 ?? 8080 =', port ?? 8080, '；0 || 8080 =', port || 8080);

// 知识点 6：?. 可选链 —— 对 null/undefined 安全地取属性/调用方法，不再抛 TypeError
const user = { name: 'Li' };
console.log('可选链取缺失属性：', user.address?.city);
user.address = { city: '北京' };
console.log('可选链取存在属性：', user.address?.city);

// 知识点 7：位运算 & | ^ ~ << >>（按 32 位整数处理）
console.log('5 & 3 =', 5 & 3, '；5 | 3 =', 5 | 3, '；5 ^ 3 =', 5 ^ 3);
console.log('~5 =', ~5, '；5 << 1 =', 5 << 1, '；5 >> 1 =', 5 >> 1);
console.log('掩码判断 0b1010 含第 2 位：', ((0b1010 & 0b0100) !== 0)); // false：第 2 位是 0
