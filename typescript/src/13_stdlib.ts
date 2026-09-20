// 主题说明：常用标准库速览 —— JSON 处理（parse 返回 any 的治理）、Math、Date 与 Intl（UTC 方法
//           保证输出确定）、URL 解析、structuredClone 深拷贝；泛型包装 JSON.parse 的安全用法。
// 运行命令：npx tsx src/13_stdlib.ts
// 预期输出（关键行）：
//   解析回来的 tags[1] -> b
//   Math：max=7 ；round(4.5)=5 ；floor(-4.5)=-5 ；sqrt(144)=12
//   UTC 日期 -> 2026-09-19 08:30:00
//   Intl 货币 -> ¥1,234.50
//   URL 解析 -> protocol=https: ；pathname=/a/b ；port=8080 ；hash=#top
//   查询参数 -> x=1 ；y=中
//   深拷贝后原对象不受影响 -> [ 1, 2 ] true

// 知识点 1：JSON —— stringify 序列化（可缩进）；parse 返回 any（它无法知道 JSON 里是什么形状）
interface Conf {
  name: string;
  tags: string[];
  nested: { ok: boolean };
}
const conf: Conf = { name: 'Li', tags: ['a', 'b'], nested: { ok: true } };
const json: string = JSON.stringify(conf, null, 2);
console.log('JSON 字符串（缩进 2）->', JSON.stringify(json.slice(0, 20) + '...'));

// 治理 any 的两个惯用法：泛型包装收窄入口；断言只改变类型、不做运行时校验（外部数据务必先验证）
function parseJson<T>(text: string): T {
  return JSON.parse(text) as T; // 调用方指定 T —— 收窄的责任随之转移到调用方
}
const back: Conf = parseJson<Conf>(json);
console.log('解析回来的 tags[1] ->', back.tags[1]);
console.log('JSON 不支持的类型：', JSON.stringify({ f: () => 1, u: undefined, big: NaN }));

// 知识点 2：Math —— 常用函数一次看全（random 每次不同）
console.log('Math：max=%d ；round(4.5)=%d ；floor(-4.5)=%d ；sqrt(144)=%d',
  Math.max(3, 7, 5), Math.round(4.5), Math.floor(-4.5), Math.sqrt(144));
console.log('Math：abs(-8)=8 ；2**0.5=%d ；trunc(-9.9)=%d ；随机数区间 [0,1) ->',
  2 ** 0.5, Math.trunc(-9.9), Math.random() >= 0);

// 知识点 3：Date —— UTC 系列方法输出与时区无关（本地方法 getMonth 从 0 开始数）
const d: Date = new Date('2026-09-19T08:30:00Z'); // 末尾 Z 表示 UTC
console.log('UTC 日期 ->', `${d.getUTCFullYear()}-${String(d.getUTCMonth() + 1).padStart(2, '0')}-${String(d.getUTCDate()).padStart(2, '0')} ${String(d.getUTCHours()).padStart(2, '0')}:${String(d.getUTCMinutes()).padStart(2, '0')}:00`);
console.log('getTime 时间戳(毫秒) ->', d.getTime(), '；Date.now() 取当前');

// 知识点 4：Intl —— 内置国际化（格式随传入 locale 确定，这里显式指定保证一致）
console.log('Intl 货币 ->', new Intl.NumberFormat('zh-CN', { style: 'currency', currency: 'CNY' }).format(1234.5));
console.log('Intl 千分位 ->', new Intl.NumberFormat('zh-CN').format(9876543));
console.log('Intl 日期 ->', new Intl.DateTimeFormat('zh-CN', { dateStyle: 'full', timeZone: 'UTC' }).format(d));

// 知识点 5：URL —— 解析与查询参数（node:url 的 WHATWG 实现，与浏览器一致；类型是全局 URL 类）
const u = new URL('https://example.com:8080/a/b?x=1&y=%E4%B8%AD#top');
console.log('URL 解析 -> protocol=%s ；pathname=%s ；port=%s ；hash=%s',
  u.protocol, u.pathname, u.port, u.hash);
console.log('查询参数 -> x=%s ；y=%s', u.searchParams.get('x'), u.searchParams.get('y'));

// 知识点 6：structuredClone —— 内置深拷贝；泛型签名 <T>(value: T) => T 保证"进去什么类型出来什么类型"
const orig: { list: number[]; meta: { ok: boolean } } = { list: [1, 2], meta: { ok: true } };
const copy: typeof orig = structuredClone(orig); // typeof orig：直接取变量的类型来标注
copy.list.push(3);
copy.meta.ok = false;
console.log('深拷贝后原对象不受影响 ->', orig.list, orig.meta.ok);
