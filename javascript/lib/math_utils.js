// 主题说明：12_module 的配套模块 —— 演示 ESM 的两种导出：命名导出（export）与默认导出（export default）。
//           本文件是被 javascript/12_module.js 导入的"库"，单独运行时无输出、退出码 0。
// 运行命令：node javascript/lib/math_utils.js（无输出；正常用法见 node javascript/12_module.js）

// 命名导出 1：export const —— 导出常量
export const PI_APPROX = 3.14159;
export const E_APPROX = 2.71828;

// 命名导出 2：export function —— 导出函数（导入方按名字取用）
export function add(a, b) {
  return a + b;
}

// 命名导出 3：统一写在底部（与逐个 export 等价的另一种风格）
function multiply(a, b) {
  return a * b;
}
export { multiply };

// 默认导出：每个模块最多一个，导入方可以任意命名（见 12_module.js 的 circleArea）
export default function circleArea(r) {
  return PI_APPROX * r * r;
}
