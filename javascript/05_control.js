// 主题说明：控制流 —— if/else、switch（含 case 贯穿 fallthrough）、for/for-of/for-in 三种循环的区别、
//           while、break/continue、标签（label）跳出多重循环。
// 运行命令：node javascript/05_control.js
// 预期输出（关键行）：
//   78: 继续
//   92: 优秀
//   switch 命中 apple 后未 break，贯穿执行了 banana 分支
//   for-in: x = 1
//   遇到 0，通过标签 break outer 直接跳出外层循环

// 知识点 1：if / else if / else
const scores = [78, 92, 65, 88];
for (const score of scores) {
  if (score >= 90) {
    console.log(`${score}: 优秀`);
  } else if (score >= 80) {
    console.log(`${score}: 良好`);
  } else {
    console.log(`${score}: 继续`);
  }
}

// 知识点 2：switch —— case 匹配后若不写 break，会"贯穿"继续执行下一个 case 的语句体
const fruit = 'apple';
switch (fruit) {
  case 'apple':
    console.log('苹果 ¥5');
    // 故意不写 break，演示贯穿（fallthrough）
  case 'banana':
    console.log('switch 命中 apple 后未 break，贯穿执行了 banana 分支');
    break; // break 才是常规写法：到此结束
  default:
    console.log('未知水果');
}

// 知识点 3：经典 for 三段式（初始化; 条件; 步进）—— 需要下标时用
const arr = ['a', 'b', 'c'];
for (let i = 0; i < arr.length; i++) {
  console.log(`for 下标 ${i} -> ${arr[i]}`);
}

// 知识点 4：for-of 遍历"值"—— 数组首选，写法最简
for (const v of arr) {
  console.log('for-of 值 ->', v);
}

// 知识点 5：for-in 遍历"键"—— 为对象设计；用于数组拿到的是字符串下标，不推荐
const point = { x: 1, y: 2 };
for (const key in point) {
  console.log(`for-in: ${key} = ${point[key]}`);
}

// 知识点 6：while 与 break/continue（continue 跳过本次循环体剩余部分）
let i = 0;
while (i < 6) {
  i++;
  if (i % 2 === 0) continue; // 跳过偶数
  if (i > 5) break;          // i 为 5 时打印后 i 变 6，下一轮直接结束
  console.log('while 奇数 ->', i);
}

// 知识点 7：标签（label）—— 给外层循环起名，break outer 可一次跳出多重循环
outer:
for (const row of [[1, 2], [3, 0], [4, 5]]) {
  for (const n of row) {
    if (n === 0) {
      console.log('遇到 0，通过标签 break outer 直接跳出外层循环');
      break outer;
    }
    console.log('矩阵元素 ->', n);
  }
}
console.log('循环结束');
