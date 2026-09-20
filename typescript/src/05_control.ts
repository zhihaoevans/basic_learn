// 主题说明：控制流 —— if/else、switch（含 case 贯穿）、for/for-of/for-in、while、break/continue、
//           标签跳出多重循环；TS 差异点：可辨识联合 + switch 的 never 穷尽检查。
// 运行命令：npx tsx src/05_control.ts
// 预期输出（关键行）：
//   78: 继续
//   92: 优秀
//   switch 命中 apple 后未 break，贯穿执行了 banana 分支
//   遇到 0，通过标签 break outer 直接跳出外层循环
//   可辨识联合 area -> 28.27 15
//   新增 triangle 后 area2 覆盖全部情况 -> 28.27 15 6

// 知识点 1：if / else if / else —— 条件的真值规则与 JS 相同（0/''/null 等为假）
const scores: number[] = [78, 92, 65, 88];
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
type Fruit = 'apple' | 'banana' | 'cherry'; // 字面量联合做 switch，TS 能检查 case 是否拼错
const rawFruit = 'apple';
const fruit = rawFruit as Fruit; // 模拟外部输入：解析后断言成联合（直写 const fruit: Fruit = 'apple'
// 会被收窄成 'apple' 一个成员，switch 其余 case 反而报"不可比较"——这也是真实的收窄行为）
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
const arr: string[] = ['a', 'b', 'c'];
for (let i = 0; i < arr.length; i++) {
  console.log(`for 下标 ${i} -> ${arr[i]}`);
}

// 知识点 4：for-of 遍历"值"—— 数组首选；元素类型随数组类型确定
for (const v of arr) {
  console.log('for-of 值 ->', v);
}

// 知识点 5：for-in 遍历"键"—— 为对象设计；键的类型是 string（数组拿到的也是字符串下标）
const point: Record<string, number> = { x: 1, y: 2 };
for (const key in point) {
  console.log(`for-in: ${key} = ${point[key]}`);
}

// 知识点 6：while 与 break/continue —— while(true) + break 主动跳出；continue 跳过本轮剩余部分
let i = 0;
while (true) {
  i++;
  if (i > 5) break;          // i 到 6 时 break 主动结束循环
  if (i % 2 === 0) continue; // 跳过偶数，直接进入下一轮
  console.log('while 奇数 ->', i); // 只打印 1、3、5
}

// 知识点 7：标签（label）—— 给外层循环起名，break outer 可一次跳出多重循环
outer:
for (const row of [[1, 2], [3, 0], [4, 5]] as number[][]) {
  for (const n of row) {
    if (n === 0) {
      console.log('遇到 0，通过标签 break outer 直接跳出外层循环');
      break outer;
    }
    console.log('矩阵元素 ->', n);
  }
}
console.log('循环结束');

// 知识点 8【TS 差异】：可辨识联合 —— 每个成员都带一个"标签字段"（kind），
// switch 这个标签后，各分支里 TS 自动收窄出该成员独有的字段
type Shape =
  | { kind: 'circle'; radius: number }
  | { kind: 'rect'; w: number; h: number };

function area(s: Shape): number {
  switch (s.kind) {
    case 'circle':
      return Math.PI * s.radius ** 2; // 此分支 s 只有 radius —— 用 s.w 会编译报错
    case 'rect':
      return s.w * s.h;
    default: {
      // 穷尽检查：两个 case 都处理完后，s 只能是 never；若漏掉任何成员，这里就会编译报错
      const unreachable: never = s;
      return unreachable;
    }
  }
}
const shapes: Shape[] = [
  { kind: 'circle', radius: 3 },
  { kind: 'rect', w: 5, h: 3 },
];
console.log('可辨识联合 area ->', ...shapes.map((s) => Number(area(s).toFixed(2))));

// 穷尽检查的威力：新增一个成员，漏改 switch 会在编译期（而不是线上）被发现
type Shape2 = Shape | { kind: 'triangle'; base: number; height: number };
function area2(s: Shape2): number {
  switch (s.kind) {
    case 'circle':
      return Math.PI * s.radius ** 2;
    case 'rect':
      return s.w * s.h;
    case 'triangle':
      return (s.base * s.height) / 2;
    default: {
      const unreachable: never = s; // 少写任何一个 case，这行都会报"不能赋给 never"
      return unreachable;
    }
  }
}
const shapes2: Shape2[] = [
  { kind: 'circle', radius: 3 },
  { kind: 'rect', w: 5, h: 3 },
  { kind: 'triangle', base: 4, height: 3 },
];
console.log('新增 triangle 后 area2 覆盖全部情况 ->', ...shapes2.map((s) => Number(area2(s).toFixed(2))));
