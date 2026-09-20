// 主题说明：12_module 的配套模块 —— 演示 TS 模块的两类导出："值"（常量/函数）与"类型"（接口/类型别名）。
//           导入方见 src/12_module.ts。本文件单独运行时无输出、退出码 0（类型导出编译后完全消失）。
// 运行命令：npx tsx src/lib/math_utils.ts（无输出；正常用法见 npx tsx src/12_module.ts）

// —— 值的导出 ——
export const PI_APPROX = 3.14159; // export const：导出常量（类型被推断为 3.14159 的字面量）

export function add(a: number, b: number): number {
  // export function：导出函数
  return a + b;
}

function multiply(a: number, b: number): number {
  return a * b;
}
export { multiply }; // 统一写在底部的另一种风格（与逐个 export 等价）

// —— 类型的导出 ——
export interface Vec2 {
  // 接口：二维向量的形状
  x: number;
  y: number;
}

export type OpName = 'add' | 'multiply'; // 类型别名：函数名的字面量联合

// 类型可以直接参与"值"的定义：Record<OpName, ...> 保证这张表不缺函数、不多函数、不拼错名字
export const opTable: Record<OpName, (a: number, b: number) => number> = {
  add,
  multiply,
};

// 默认导出：每个模块最多一个，导入方可以任意命名
export default function circleArea(r: number): number {
  return PI_APPROX * r * r;
}
