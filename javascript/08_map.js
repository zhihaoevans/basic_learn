// 主题说明：映射 / 字典 —— Map 与普通对象的区别（任意类型键、保持插入顺序、直接取 size）、
//           Map 的 set/get/has/delete、for-of entries 遍历、对象的 keys/values/entries。
// 运行命令：node javascript/08_map.js
// 预期输出（关键行）：
//   get('name') -> Li ；has(42) -> true ；size = 3
//   Map 遍历保持插入顺序： name Li / 42 answer / true yes（三行，前缀相同）
//   Object.keys -> [ 'b', 'a' ]
//   对象里 1 会先于字符串键出现： [ '1', 'x' ]

// 知识点 1：Map —— 任意类型的键、保持插入顺序、size 直接可得
const m = new Map();
m.set('name', 'Li')
  .set(42, 'answer')   // 数字键
  .set(true, 'yes');   // 布尔键 —— 普通对象做不到（会被转成字符串）
console.log("get('name') ->", m.get('name'), '；has(42) ->', m.has(42), '；size =', m.size);

// 知识点 2：get 不存在的键返回 undefined（而不是报错）；delete 删除后 size 减一
m.set('tmp', 1);
console.log('get 缺失键 ->', m.get('nope'));
m.delete('tmp');
console.log('delete 后 size =', m.size);

// 知识点 3：for-of 直接遍历 Map（默认就是 [键, 值] 数对，常配合解构）
for (const [k, v] of m) {
  console.log('Map 遍历保持插入顺序：', k, v);
}
for (const [k, v] of m.entries()) {
  // 显式写法 .entries()，与上一行等价；还有 m.keys() / m.values()
  console.log('entries 写法 ->', k, '=', v);
}

// 知识点 4：普通对象当字典用 —— Object.keys/values/entries（拿不到 size，需 .length）
const conf = { b: 2, a: 1 };
console.log('Object.keys ->', Object.keys(conf));
console.log('Object.values ->', Object.values(conf));
console.log('Object.entries ->', Object.entries(conf));
for (const [k, v] of Object.entries(conf)) {
  console.log(`对象条目 ${k} = ${v}`);
}

// 知识点 5：对象键的本质 —— 非字符串键会被转成字符串，且"整数样"的键会排到最前
console.log('对象里 1 会先于字符串键出现：', Object.keys({ 1: '一', x: '叉' }));

// 知识点 6：选型建议 —— 固定结构的实体用对象；动态键值对（尤其中文以外的键、需要顺序）用 Map
console.log('普通对象 -> 结构固定；Map -> 动态字典的首选');
