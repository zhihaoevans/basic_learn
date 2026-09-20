// 主题说明：模块 —— TS 的 ESM 导入导出：值与类型一起导、import type（类型专用导入，编译后整句擦除）、
//           内联 type 修饰、默认/换名/命名空间导入。配套库在 src/lib/math_utils.ts。
// 运行命令：npx tsx src/12_module.ts
// 预期输出（关键行）：
//   命名导入：add(2, 3) = 5 ；multiply(4, 5) = 20
//   默认导入（可随意命名）：circleArea(2) = 12.56636
//   类型导入 Vec2(3, 4) 的模长 = 5
//   类型参与取值：opTable.add(10, 1) = 11 （OpName 限定键）
//   命名空间导入：circleArea 是 function ；运行时导出 5 个名字（类型导出已被擦除）
//   （fileURLToPath 会打印本文件的绝对路径，随所在机器变化，不列入关键行）

// 知识点 1：命名导入 { }（名字必须与导出一致）+ 默认导入（不带花括号、可任意命名）；
//           内联 type 修饰：同一个 import 语句里捎带导入类型
import circleArea, { add, multiply, opTable, type OpName } from './lib/math_utils.js';

// 知识点 2【TS 差异】：import type —— 类型专用导入：整条语句编译后被完全擦除，
//           只剩类型的模块（或纯类型成员）必须这样导，避免打包器把"只有类型"的依赖打进产物
import type { Vec2 } from './lib/math_utils.js';

// 知识点 3：命名空间导入 * as —— 把模块的所有导出收进一个对象
import * as math from './lib/math_utils.js';

// 知识点 4：Node 内置模块也是 ESM 导入（推荐带 node: 前缀）
import { fileURLToPath } from 'node:url';

// 导入的类型马上就能用：v 的形状由 Vec2 约束
const v: Vec2 = { x: 3, y: 4 };
const lengthOf = (p: Vec2): number => Math.hypot(p.x, p.y);
const op: OpName = 'add'; // OpName 只有 'add' | 'multiply' 两个合法值

console.log('命名导入：add(2, 3) =', add(2, 3), '；multiply(4, 5) =', multiply(4, 5));
console.log('默认导入（可随意命名）：circleArea(2) =', circleArea(2));
console.log('类型导入 Vec2(3, 4) 的模长 =', lengthOf(v));
console.log('类型参与取值：opTable.add(10, 1) =', opTable[op](10, 1), '（OpName 限定键）');

// 命名空间对象上：默认导出挂在 default 属性；类型导出（Vec2/OpName）运行时不存在
console.log('命名空间导入：circleArea 是', typeof math.default, '；运行时导出', Object.keys(math).length,
  '个名字（类型导出已被擦除）');

// node:url 的实用函数：拿到当前文件的绝对路径（__dirname 的 ESM 等价物）
console.log('fileURLToPath(import.meta.url) ->', fileURLToPath(import.meta.url));

// 说明：相对路径导入写全 ./ 与 .js 扩展名 —— tsc 的 NodeNext 约定把 './lib/math_utils.js'
//       解析到源文件 './lib/math_utils.ts'，tsx 运行时同样按此规则查找
