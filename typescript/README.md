# TypeScript 基础语法示例

TypeScript 是 JavaScript 的超集：在 JS 全部语法之上增加静态类型系统，编译（或用 tsx 转译）后仍运行在 Node/浏览器上。类型在编译期检查、运行前擦除，换来的是编辑器提示与一大类错误的前移。本目录按 [TOPICS.md](../TOPICS.md) 的统一主题清单组织：一个主题一个自包含的可运行文件，主题与 [javascript](../javascript/) 平行示例一一对应，并逐题加入 TS 差异点（类型标注/unknown/字面量类型/可辨识联合/重载/元组/接口/类型守卫/import type/泛型/工具类型）。

- 官方文档：[TypeScript Handbook（中文）](https://typescript.bootcss.com/) ｜ [typescriptlang.org](https://www.typescriptlang.org/docs/) ｜ [Node.js API 文档](https://nodejs.org/docs/latest/api/)

## 环境要求

- **Node ≥ 18**：示例使用 ESM（本目录 `package.json` 声明 `"type": "module"`）、顶层 await、`structuredClone`、`node:readline/promises` 等能力（本地验证版本 v26，CI 用 Node 20）
- 工具链：`npm install` 安装唯一 devDependency [tsx](https://tsx.is/)（基于 esbuild 的 TS 直跑器，免手动编译）；类型检查用 `npx --package typescript tsc --noEmit`（npx 按需临时下载 tsc）
- 本目录刻意不引入 `@types/node`：示例用到的少量 Node API 类型由 [`env.d.ts`](env.d.ts) 手写环境声明提供，`tsconfig.json` 为 strict 严格模式

## 如何运行

进入本目录并安装依赖（仅需一次）：

```bash
cd typescript && npm install
```

单条命令直接运行某个示例：

```bash
npx tsx src/01_hello.ts
```

类型检查（严格模式，零错误通过）：

```bash
npx --package typescript tsc --noEmit
```

一次性运行全部示例（与 CI 的验证方式相同）：

```bash
for f in src/*.ts; do echo "== $f"; npx tsx "$f"; done
```

> 12 模块的配套库 `src/lib/math_utils.ts` 在子目录，不会被上面的 glob 命中，它由 `12_module.ts` 导入执行（单独运行无输出、退出码 0）。

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [01_hello.ts](src/01_hello.ts) | `npx tsx src/01_hello.ts` | console.log、模板字符串、类型标注与推断、tsx 运行方式 |
| 02 variable | [02_variable.ts](src/02_variable.ts) | `npx tsx src/02_variable.ts` | let/const、any/unknown/never、typeof/instanceof 收窄、值 vs 址 |
| 03 operator | [03_operator.ts](src/03_operator.ts) | `npx tsx src/03_operator.ts` | 算术与 0.1+0.2 精度、== vs ===、?? 与 ?.、位运算、编译期拦截笔误 |
| 04 string | [04_string.ts](src/04_string.ts) | `npx tsx src/04_string.ts` | slice/replaceAll/padStart/split、字符串字面量类型、模板字面量类型 |
| 05 control | [05_control.ts](src/05_control.ts) | `npx tsx src/05_control.ts` | if/switch（贯穿）、三种循环、标签；可辨识联合 + never 穷尽检查 |
| 06 function | [06_function.ts](src/06_function.ts) | `npx tsx src/06_function.ts` | 类型签名、可选/默认/剩余参数、函数重载、闭包、回调与高阶函数 |
| 07 collection | [07_collection.ts](src/07_collection.ts) | `npx tsx src/07_collection.ts` | map/filter/reduce 等方法、Set 去重、泛型数组、元组、readonly |
| 08 map | [08_map.ts](src/08_map.ts) | `npx tsx src/08_map.ts` | Map vs 对象、Record 工具类型、索引签名、Partial 局部更新 |
| 09 oop | [09_oop.ts](src/09_oop.ts) | `npx tsx src/09_oop.ts` | implements 接口、抽象类、public/private/protected、readonly、参数属性 |
| 10 error | [10_error.ts](src/10_error.ts) | `npx tsx src/10_error.ts` | catch 的 unknown 收窄、自定义 Error、is 类型守卫、异步错误 |
| 11 file_io | [11_file_io.ts](src/11_file_io.ts) | `npx tsx src/11_file_io.ts` | fs/promises 泛型返回标注、同步版对比、readline 逐行、临时文件清理 |
| 12 module | [12_module.ts](src/12_module.ts) | `npx tsx src/12_module.ts` | 值与类型一起导出、import type、命名空间导入（配套 lib/math_utils.ts） |
| 13 stdlib | [13_stdlib.ts](src/13_stdlib.ts) | `npx tsx src/13_stdlib.ts` | JSON（any 的治理）、Math、Date/Intl、URL、structuredClone |
| 14 concurrency | [14_concurrency.ts](src/14_concurrency.ts) | `npx tsx src/14_concurrency.ts` | Promise<T> 标注、async/await、all/allSettled 的可辨识联合收窄 |
| 15 generic | [15_generic.ts](src/15_generic.ts) | `npx tsx src/15_generic.ts` | 泛型函数/接口/类、约束 extends keyof、泛型默认值 |
| + 特色 type_utils | [16_type_utils.ts](src/16_type_utils.ts) | `npx tsx src/16_type_utils.ts` | 联合/交叉类型、as const、Pick/Omit/Record/Partial/Readonly 实战 |

## 进阶说明

- 每个示例文件头部注释都标明了主题说明、运行命令与预期输出，适合按主题顺序阅读；`11_file_io.ts` 的临时文件写入系统临时目录并自动清理
- 与 [javascript](../javascript/) 的 15 个平行示例对照阅读效果最好：同一主题先看 JS 再看 TS，差异点都标了【TS 差异】
- 与 [languages/javascript](../languages/javascript/) 的早期章节式练习（含 Node 原生测试）互补；浏览器端与工程化方向见 [web/frontend](../web/frontend/)（Vue3 + TS 工程）
- 之后的进阶方向：类型体操（条件类型/infer/递归类型）、装饰器、模块解析与 `verbatimModuleSyntax`、`satisfies` 操作符、tsup/Vite 里的 TS 工程化
