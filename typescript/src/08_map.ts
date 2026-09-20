// 主题说明：映射 / 字典 —— Map<K,V> 与普通对象当字典的区别（任意类型键、保持插入顺序、size）、
//           TS 差异点：Record 工具类型、索引签名、Partial 的典型应用（安全地"部分更新"）。
// 运行命令：npx tsx src/08_map.ts
// 预期输出（关键行）：
//   get('name') -> Li ；has(42) -> true ；size = 3
//   Map 遍历保持插入顺序： name=Li / 42=answer / true=yes（三行，前缀相同）
//   Record 字典 -> apple ¥5 ；cherry ¥20
//   Partial 局部更新 -> { host: 'example.com', port: 8081, debug: true }
//   对象里 42 会先于字符串键出现： [ '1', 'x' ]

// 知识点 1：Map<K, V> —— 泛型参数写明键值类型；任意类型的键、保持插入顺序、size 直接可得
const m = new Map<string | number | boolean, string>();
m.set('name', 'Li')
  .set(42, 'answer') // 数字键
  .set(true, 'yes'); // 布尔键 —— 普通对象做不到（会被转成字符串）
console.log("get('name') ->", m.get('name'), '；has(42) ->', m.has(42), '；size =', m.size);

// 知识点 2：get 不存在的键返回 undefined（Map 的 V 类型上自动带 | undefined）；delete 后 size 减一
m.set('tmp', 'x');
const missing: string | undefined = m.get('nope');
console.log('get 缺失键 ->', missing);
m.delete('tmp');
console.log('delete 后 size =', m.size);

// 知识点 3：for-of 直接遍历 Map（默认就是 [键, 值] 数对，配合解构）
for (const [k, v] of m) {
  console.log('Map 遍历保持插入顺序：', `${k}=${v}`);
}

// 知识点 4【TS 差异】：Record<K, V> —— 内置工具类型："键为 K、值为 V 的对象"（泛型见 15/16）
const prices: Record<string, number> = {
  apple: 5,
  banana: 3,
};
prices.cherry = 20; // Record 允许任意 string 键的新增（强类型字段请用普通 interface，见 09）
console.log('Record 字典 ->', `apple ¥${prices.apple}`, '；cherry ¥' + prices.cherry);

// 知识点 5【TS 差异】：索引签名 —— 手写"任意键 → 值类型"的对象类型（Record 的展开形态）
interface WordCount {
  [word: string]: number; // 每个属性的值都必须是 number
}
const count: WordCount = {};
for (const w of ['ts', 'js', 'ts']) {
  count[w] = (count[w] ?? 0) + 1; // ?? 处理"键还不存在"的 undefined
}
console.log('索引签名计词 ->', count);

// 知识点 6【TS 差异】：Partial<T> —— 把 T 的所有属性变成可选，"部分更新"场景的标准写法
interface ServerConf {
  host: string;
  port: number;
  debug: boolean;
}
const conf: ServerConf = { host: 'example.com', port: 80, debug: false };
function updateConf(c: ServerConf, patch: Partial<ServerConf>): ServerConf {
  return { ...c, ...patch }; // patch 里只放要改的字段，其余沿用
}
console.log('Partial 局部更新 ->', updateConf(conf, { port: 8081, debug: true }));
// updateConf(conf, { post: 99 }); // 编译错误：'post' 不在 ServerConf 里 —— 拼错字段名当场暴露

// 知识点 7：普通对象的 keys/values/entries —— Object.keys 返回 string[]（对象键本质都是字符串）
const dict: Record<string, number> = { b: 2, a: 1 };
console.log('Object.keys ->', Object.keys(dict), '；values ->', Object.values(dict));

// 知识点 8：对象键的排序陷阱 —— 整数样的键会被提前且升序排列（与 Map 的插入序对比鲜明）
console.log('对象里 42 会先于字符串键出现：', Object.keys({ 1: '一', x: '叉' }));
console.log('选型：固定结构的实体用 interface；动态键值对 / 需要顺序与非字符串键用 Map');
