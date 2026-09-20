// 主题说明：数组与集合 —— 常用方法（map/filter/reduce/find/some/every/sort/slice/splice）、Set 去重、
//           TS 差异点：泛型数组 number[] 与 Array<T>、readonly 只读数组、元组（定长定类型）。
// 运行命令：npx tsx src/07_collection.ts
// 预期输出（关键行）：
//   map -> [ 10, 6, 16, 2, 18, 6 ]
//   filter -> [ 5, 8, 9 ]
//   reduce 求和 -> 29
//   sort 升序 -> [ 1, 3, 3, 5, 8, 9 ]
//   Set 去重 -> [ 1, 2, 3 ]
//   元组 point -> (3, 4) 长度固定为 2
//   readonly 数组只能读： 3 ；复制后可变副本 -> [ 1, 2, 3, 4 ]

const nums: number[] = [5, 3, 8, 1, 9, 3]; // number[] 是 Array<number> 的简写（泛型见 15）

// 知识点 1：map —— 一一映射成新数组（不改原数组）；回调参数类型由元素类型推断
console.log('map ->', nums.map((n) => n * 2));

// 知识点 2：filter —— 按条件筛选
console.log('filter ->', nums.filter((n) => n > 4));

// 知识点 3：reduce —— 折叠成一个值（第二参 0 是初始值）
console.log('reduce 求和 ->', nums.reduce((acc, n) => acc + n, 0));

// 知识点 4：find 找第一个满足条件的元素（类型是 T | undefined）；some/every 返回布尔
const found: number | undefined = nums.find((n) => n > 4);
console.log('find ->', found, '；find 未命中 ->', nums.find((n) => n > 99));
console.log('some(>8) ->', nums.some((n) => n > 8), '；every(>0) ->', nums.every((n) => n > 0));

// 知识点 5：sort —— 默认按"字符串"排序，数字排序必须给比较函数；(a, b) => a - b 升序
console.log('sort 默认数字会错 ->', [10, 9, 100].sort()); // [10, 100, 9]：按字符串比较！
console.log('sort 升序 ->', [...nums].sort((a, b) => a - b));

// 知识点 6：slice 切片（不改原数组）vs splice 拼接（原地增删，返回被删元素）
const letters: string[] = ['a', 'b', 'c', 'd'];
console.log('slice(1, 3) ->', letters.slice(1, 3), '；原数组不变 ->', letters);
console.log('splice 删掉的 ->', letters.splice(1, 2, 'X'), '；splice 后原数组 ->', letters);

// 知识点 7：Set<T> —— 值唯一的集合；add/has/delete/size；数组去重的惯用法 [...new Set(arr)]
const set = new Set<number>([1, 2, 2, 3]);
set.add(3).add(4);
set.delete(4);
console.log('Set ->', set, '；size =', set.size, '；has(2) =', set.has(2));
console.log('Set 去重 ->', [...new Set([1, 1, 2, 3, 3])]);

// 知识点 8：entries + 解构遍历 —— 同时拿下标和值
for (const [i, v] of ['x', 'y', 'z'].entries()) {
  console.log(`第 ${i} 个是 ${v}`);
}

// 知识点 9【TS 差异】：元组 tuple —— 定长、每位定类型的数组，比 number[] 表达力强得多
const point: [number, number] = [3, 4]; // 恰好两个 number：多一个、少一个、换 string 都编译报错
const labeled: [name: string, age: number] = ['Li', 30]; // 命名元组：给每位起名（仅文档作用）
console.log('元组 point ->', `(${point[0]}, ${point[1]})`, '长度固定为', point.length);
console.log('命名元组 ->', labeled[0], labeled[1]);

// 知识点 10【TS 差异】：readonly 数组 —— 类型层面禁止一切修改（push/splice 等都编译报错）
const frozen: readonly number[] = [1, 2, 3];
// frozen.push(4);    // 编译错误：readonly number[] 上没有 push
// frozen.splice(0);  // 编译错误：同样被禁止
const copy: number[] = [...frozen]; // 想改就先复制一份可变副本
copy.push(4);
console.log('readonly 数组只能读：', frozen.length, '；复制后可变副本 ->', copy);
