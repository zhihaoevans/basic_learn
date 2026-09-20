// 主题说明：模块 —— ESM（ECMAScript Modules）的 export/import：命名导入、默认导入、
//           整体命名空间导入、导入时换名（as）。本目录 package.json 的 "type": "module"
//           声明 .js 按 ESM 解析；配套库在 lib/math_utils.js。
// 运行命令：node javascript/12_module.js
// 预期输出（关键行）：
//   命名导入：add(2, 3) = 5 ；multiply(4, 5) = 20
//   常量导入：PI_APPROX = 3.14159
//   默认导入（可随意命名）：circleArea(2) = 12.56636
//   换名导入：plus(10, 1) = 11
//   命名空间导入：circleArea 是 function

// 知识点 1：命名导入 { } —— 名字必须与导出一致；默认导入不带花括号、可任意命名
import circleArea, { add, multiply, PI_APPROX } from './lib/math_utils.js';

// 知识点 2：导入时换名 as —— 避免与本地变量重名
import { add as plus } from './lib/math_utils.js';

// 知识点 3：命名空间导入 * as —— 把模块的所有导出收进一个对象
import * as math from './lib/math_utils.js';

// 知识点 4：Node 内置模块也是 ESM 导入（推荐带 node: 前缀）
import { fileURLToPath } from 'node:url';

console.log('命名导入：add(2, 3) =', add(2, 3), '；multiply(4, 5) =', multiply(4, 5));
console.log('常量导入：PI_APPROX =', PI_APPROX);
console.log('默认导入（可随意命名）：circleArea(2) =', circleArea(2));
console.log('换名导入：plus(10, 1) =', plus(10, 1));

// 命名空间对象上，默认导出挂在 default 属性
console.log('命名空间导入：circleArea 是', typeof math.default, '；共导出', Object.keys(math).length, '个名字');
console.log('命名空间取命名导出：math.E_APPROX =', math.E_APPROX);

// node:url 的实用函数：拿到当前文件的绝对路径（__dirname 的 ESM 等价物）
console.log('fileURLToPath(import.meta.url) ->', fileURLToPath(import.meta.url));

// 说明：相对路径导入必须写全 ./ 与扩展名 .js（浏览器/Node ESM 均如此），与 CommonJS 的 require 不同
