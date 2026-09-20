// 主题说明：字符串操作 —— 常用方法（slice/replaceAll/includes/padStart/split/join）、模板字符串、
//           字符串不可变；TS 差异点：字符串字面量类型与模板字面量类型（把"字符串"细到"值"）。
// 运行命令：npx tsx src/04_string.ts
// 预期输出（关键行）：
//   slice(7) -> TypeScript!
//   replaceAll 后 -> a+b+c
//   padStart(3, '0') -> 007
//   split 后 -> [ 'a', 'b', 'c' ]
//   字符串字面量类型 -> north （只能是四个罗盘方向之一）；右转后 -> east
//   模板字面量类型 -> Hello, north!

const s = 'Hello, TypeScript!';

// 知识点 1：slice 切片（含头不含尾，支持负索引从末尾数）
console.log('slice(7) ->', s.slice(7));
console.log('slice(7, -1) ->', s.slice(7, -1)); // TypeScript（去掉结尾的 !）

// 知识点 2：replaceAll 全量替换（replace 只替换第一处）
console.log('replaceAll 后 ->', 'a-b-c'.replaceAll('-', '+'));
console.log('replace 只换第一处 ->', 'a-b-c'.replace('-', '+'));

// 知识点 3：includes 是否包含（配套 startsWith / endsWith）
console.log("includes('Type') ->", s.includes('Type'), "；endsWith('!') ->", s.endsWith('!'));

// 知识点 4：padStart / padEnd 补齐长度（编号、月份补零常用）
console.log("padStart(3, '0') ->", '7'.padStart(3, '0'));

// 知识点 5：split 切成数组、join 拼回字符串 —— split 返回 string[]，join 的分隔符也要求是字符串
const parts: string[] = 'a,b,c'.split(',');
console.log('split 后 ->', parts);
console.log('join 拼回 ->', parts.join('-'));

// 知识点 6：字符串不可变 —— 所有"修改"方法都返回新字符串，原串不变
const lower = s.toLowerCase();
console.log('原串不变 ->', s.slice(0, 5), '；新串 ->', lower.slice(0, 5));

// 知识点 7：编码 —— charCodeAt 取 UTF-16 码元、fromCharCode 还原（string 的单位是 UTF-16 码元）
const zh = '中';
console.log("'中' 的字符编码 ->", zh.charCodeAt(0), `（0x${zh.charCodeAt(0).toString(16)}）`);
console.log('fromCharCode(0x4e2d) ->', String.fromCharCode(0x4e2d));

// 知识点 8【TS 差异】：字符串字面量类型 —— string 是"所有字符串"；'north' 这样的字面量类型只有那一个值
type Direction = 'north' | 'south' | 'east' | 'west'; // 四个字面量组成的联合（联合详见 16）
const dir: Direction = 'north';
// dir = 'up'; // 编译错误：'up' 不在四个方向里 —— 拼错方向名在编译期就被抓住
const ROTATE: Record<Direction, Direction> = {
  // Record<Direction, Direction>：查表必须四键齐全、值也只能是方向（少一键都编译报错）
  north: 'east',
  east: 'south',
  south: 'west',
  west: 'north',
};
console.log('字符串字面量类型 ->', dir, '（只能是四个罗盘方向之一）；右转后 ->', ROTATE[dir]);

// 知识点 9【TS 差异】：模板字面量类型 —— 用模板字符串的语法在"类型层面"拼出新类型
type Greeting = `Hello, ${Direction}!`; // 合法的 Greeting 只有四个：Hello, north! / south / east / west
const g: Greeting = `Hello, ${dir}!`; // 拼错任意一个字母都不匹配这个类型
console.log('模板字面量类型 ->', g);
