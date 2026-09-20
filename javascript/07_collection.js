// 主题说明：数组与集合 —— 常用方法（map/filter/reduce/find/some/every/sort/slice/splice）、
//           Set 去重、entries 配合解构遍历。
// 运行命令：node javascript/07_collection.js
// 预期输出（关键行）：
//   map -> [ 10, 6, 16, 2, 18, 6 ]
//   filter -> [ 5, 8, 9 ]
//   reduce 求和 -> 29
//   sort 升序 -> [ 1, 3, 3, 5, 8, 9 ]
//   splice 删掉的 -> [ 'b', 'c' ] ；splice 后原数组 -> [ 'a', 'X', 'd' ]
//   Set 去重 -> [ 1, 2, 3 ]

const nums = [5, 3, 8, 1, 9, 3];

// 知识点 1：map —— 一一映射成新数组（不改原数组）
console.log('map ->', nums.map((n) => n * 2));

// 知识点 2：filter —— 按条件筛选
console.log('filter ->', nums.filter((n) => n > 4));

// 知识点 3：reduce —— 折叠成一个值（第二参 0 是初始值）
console.log('reduce 求和 ->', nums.reduce((acc, n) => acc + n, 0));

// 知识点 4：find 找第一个满足条件的元素；some/every 返回布尔
console.log('find ->', nums.find((n) => n > 4));
console.log('some(>8) ->', nums.some((n) => n > 8), '；every(>0) ->', nums.every((n) => n > 0));

// 知识点 5：sort —— 默认按"字符串"排序，数字排序必须给比较函数；(a, b) => a - b 升序
console.log('sort 默认（字符串序）->', [...nums].sort()); // [1,3,3,5,8,9] 此组恰好同序，见下例反例
console.log('sort 默认数字会错 ->', [10, 9, 100].sort()); // [10, 100, 9]：按字符串比较！
console.log('sort 升序 ->', [...nums].sort((a, b) => a - b));

// 知识点 6：slice 切片（不改原数组）vs splice 拼接（原地增删，返回被删元素）
const letters = ['a', 'b', 'c', 'd'];
console.log('slice(1, 3) ->', letters.slice(1, 3), '；原数组不变 ->', letters);
console.log('splice 删掉的 ->', letters.splice(1, 2, 'X'), '；splice 后原数组 ->', letters);

// 知识点 7：Set —— 值唯一的集合；add/has/delete/size；数组去重的惯用法 [...new Set(arr)]
const set = new Set([1, 2, 2, 3]);
set.add(3).add(4);
set.delete(4);
console.log('Set ->', set, '；size =', set.size, '；has(2) =', set.has(2));
console.log('Set 去重 ->', [...new Set([1, 1, 2, 3, 3])]);

// 知识点 8：entries + 解构遍历 —— 同时拿下标和值
for (const [i, v] of ['x', 'y', 'z'].entries()) {
  console.log(`第 ${i} 个是 ${v}`);
}
