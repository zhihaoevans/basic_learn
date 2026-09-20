// 主题说明：字符串操作 —— 常用方法（slice/replaceAll/includes/padStart/split/join）、
//           模板字符串多行写法、字符串不可变、charCodeAt 编码。
// 运行命令：node javascript/04_string.js
// 预期输出（关键行）：
//   slice(7) -> JavaScript!
//   replaceAll 后 -> a+b+c
//   padStart(3, '0') -> 007
//   split 后 -> [ 'a', 'b', 'c' ]
//   '中' 的字符编码 -> 20013 （0x4e2d）

const s = 'Hello, JavaScript!';

// 知识点 1：slice 切片（含头不含尾，支持负索引从末尾数）
console.log('slice(7) ->', s.slice(7));
console.log('slice(7, -1) ->', s.slice(7, -1)); // JavaScript（去掉结尾的 !）

// 知识点 2：replaceAll 全量替换（replace 只替换第一处）
console.log('replaceAll 后 ->', 'a-b-c'.replaceAll('-', '+'));
console.log('replace 只换第一处 ->', 'a-b-c'.replace('-', '+'));

// 知识点 3：includes 是否包含（配套 startsWith / endsWith）
console.log("includes('Java') ->", s.includes('Java'), "；endsWith('!') ->", s.endsWith('!'));

// 知识点 4：padStart / padEnd 补齐长度（编号、月份补零常用）
console.log("padStart(3, '0') ->", '7'.padStart(3, '0'));

// 知识点 5：split 切成数组、join 拼回字符串
const parts = 'a,b,c'.split(',');
console.log('split 后 ->', parts);
console.log('join 拼回 ->', parts.join('-'));

// 知识点 6：其他高频方法：length / toUpperCase / trim / indexOf / repeat / at
console.log('length ->', s.length, '；repeat ->', 'ab'.repeat(3));
console.log('trim ->', '  hi  '.trim(), '；at(-1) ->', s.at(-1));

// 知识点 7：字符串不可变 —— 所有"修改"方法都返回新字符串，原串不变
const lower = s.toLowerCase();
console.log('原串不变 ->', s.slice(0, 5), '；新串 ->', lower.slice(0, 5));

// 知识点 8：模板字符串直接换行，无需 \n 转义
const poem = `第一行：鹅鹅鹅
第二行：曲项向天歌`;
console.log(poem);

// 知识点 9：编码 —— charCodeAt 取 UTF-16 码元、fromCharCode 还原
const zh = '中';
console.log("'中' 的字符编码 ->", zh.charCodeAt(0), `（0x${zh.charCodeAt(0).toString(16)}）`);
console.log('fromCharCode(0x4e2d) ->', String.fromCharCode(0x4e2d));
console.log("'中文'.length ->", '中文'.length, '（length 按 UTF-16 码元计数，中文常用字恰好 1:1）');
