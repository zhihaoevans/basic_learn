// 主题说明：常用标准库速览 —— JSON 处理、Math 数学、Date 与 Intl 国际化（用 UTC 方法保证输出确定）、
//           URL 解析、structuredClone 深拷贝。
// 运行命令：node javascript/13_stdlib.js
// 预期输出（关键行）：
//   解析回来的 tags[1] -> b
//   Math：max=7 ；round(4.5)=5 ；floor(-4.5)=-5 ；sqrt(144)=12
//   UTC 日期 -> 2026-09-19 08:30:00
//   Intl 货币 -> ¥1,234.50
//   URL 解析 -> protocol=https: ；pathname=/a/b ；x=1
//   深拷贝后原对象不受影响 -> [ 1, 2 ]

// 知识点 1：JSON —— stringify 序列化（可缩进）、parse 反序列化
const conf = { name: 'Li', tags: ['a', 'b'], nested: { ok: true } };
const json = JSON.stringify(conf, null, 2);
console.log('JSON 字符串（缩进 2）->', JSON.stringify(json.slice(0, 20) + '...'));
console.log('解析回来的 tags[1] ->', JSON.parse(json).tags[1]);
console.log('JSON 不支持的类型：', JSON.stringify({ f: () => 1, u: undefined, big: NaN }));

// 知识点 2：Math —— 常用函数一次看全（random 每次不同）
console.log('Math：max=%d ；round(4.5)=%d ；floor(-4.5)=%d ；sqrt(144)=%d',
  Math.max(3, 7, 5), Math.round(4.5), Math.floor(-4.5), Math.sqrt(144));
console.log('Math：abs(-8)=8 ；2**0.5=%d ；trunc(-9.9)=%d ；随机数区间 [0,1) ->',
  2 ** 0.5, Math.trunc(-9.9), Math.random() >= 0);

// 知识点 3：Date —— UTC 系列方法输出与时区无关（本地方法 getMonth 从 0 开始数）
const d = new Date('2026-09-19T08:30:00Z'); // 末尾 Z 表示 UTC
console.log('UTC 日期 ->', `${d.getUTCFullYear()}-${String(d.getUTCMonth() + 1).padStart(2, '0')}-${String(d.getUTCDate()).padStart(2, '0')} ${String(d.getUTCHours()).padStart(2, '0')}:${String(d.getUTCMinutes()).padStart(2, '0')}:00`);
console.log('getTime 时间戳(毫秒) ->', d.getTime(), '；Date.now() 取当前');

// 知识点 4：Intl —— 内置国际化（格式随传入 locale 确定，这里显式指定保证一致）
console.log('Intl 货币 ->', new Intl.NumberFormat('zh-CN', { style: 'currency', currency: 'CNY' }).format(1234.5));
console.log('Intl 千分位 ->', new Intl.NumberFormat('zh-CN').format(9876543));
console.log('Intl 日期 ->', new Intl.DateTimeFormat('zh-CN', { dateStyle: 'full', timeZone: 'UTC' }).format(d));

// 知识点 5：URL —— 解析与查询参数（node:url 的 WHATWG 实现，与浏览器一致）
const u = new URL('https://example.com:8080/a/b?x=1&y=%E4%B8%AD#top');
console.log('URL 解析 -> protocol=%s ；pathname=%s ；port=%s ；hash=%s',
  u.protocol, u.pathname, u.port, u.hash);
console.log('查询参数 -> x=%s ；y=%s', u.searchParams.get('x'), u.searchParams.get('y'));

// 知识点 6：structuredClone —— 内置深拷贝（连嵌套对象/数组都是新的，比展开运算符深一层一层的递归省事）
const orig = { list: [1, 2], meta: { ok: true } };
const copy = structuredClone(orig);
copy.list.push(3);
copy.meta.ok = false;
console.log('深拷贝后原对象不受影响 ->', orig.list, orig.meta.ok);
