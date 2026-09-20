# JavaScript 基础语法示例

JavaScript 是一门运行在浏览器与服务器（Node.js）上的动态类型脚本语言，函数是一等公民，异步编程以事件循环 + Promise 为核心。本目录按 [TOPICS.md](../TOPICS.md) 的统一主题清单组织：一个主题一个自包含的可运行文件，用 `console.log` 逐个知识点演示结果。

- 官方文档：[MDN JavaScript 指南（中文）](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Guide) ｜ [Node.js API 文档](https://nodejs.org/docs/latest/api/)

## 环境要求

- **Node ≥ 18**：示例使用 ESM 模块（`javascript/package.json` 声明 `"type": "module"`）、顶层 await、`structuredClone`、`readline/promises` 等 Node 18 起稳定可用的能力（本地验证版本 v26，CI 同样满足）
- 安装：从 [nodejs.org](https://nodejs.org/) 装 LTS 版，`node --version` 确认；无需 npm 依赖，零第三方包
- 用任意编辑器 + node 命令行即可，无需 IDE

## 如何运行

单条命令直接运行某个示例：

```bash
node javascript/01_hello.js
```

一次性运行全部示例（与 CI 的验证方式相同）：

```bash
for f in javascript/*.js; do echo "== $f"; node "$f"; done
```

> 12 模块的配套库 `javascript/lib/math_utils.js` 在子目录，不会被上面的 glob 命中，它由 `12_module.js` 导入执行。

## 主题索引

| 主题 | 示例文件 | 运行命令 | 一句话说明 |
|---|---|---|---|
| 01 hello | [01_hello.js](01_hello.js) | `node javascript/01_hello.js` | console.log、模板字符串、注释、node 运行方式 |
| 02 variable | [02_variable.js](02_variable.js) | `node javascript/02_variable.js` | let/const/var、动态类型、typeof、基本 vs 引用类型 |
| 03 operator | [03_operator.js](03_operator.js) | `node javascript/03_operator.js` | 算术与 0.1+0.2 精度、== vs ===、短路、?? 与 ?.、位运算 |
| 04 string | [04_string.js](04_string.js) | `node javascript/04_string.js` | slice/replaceAll/includes/padStart/split/join、模板多行、编码 |
| 05 control | [05_control.js](05_control.js) | `node javascript/05_control.js` | if/switch（贯穿）、for/for-of/for-in、while、break/continue、标签 |
| 06 function | [06_function.js](06_function.js) | `node javascript/06_function.js` | 声明/表达式/箭头、默认/剩余参数、闭包、回调、高阶函数 |
| 07 collection | [07_collection.js](07_collection.js) | `node javascript/07_collection.js` | map/filter/reduce 等数组方法、sort 陷阱、Set 去重、解构遍历 |
| 08 map | [08_map.js](08_map.js) | `node javascript/08_map.js` | Map vs 普通对象、set/get/has/size、entries 遍历 |
| 09 oop | [09_oop.js](09_oop.js) | `node javascript/09_oop.js` | class/extends/super、静态方法、私有字段 #、getter/setter、instanceof |
| 10 error | [10_error.js](10_error.js) | `node javascript/10_error.js` | Error 子类型、try/catch/finally、自定义 Error、异步错误 |
| 11 file_io | [11_file_io.js](11_file_io.js) | `node javascript/11_file_io.js` | fs/promises 读写追加、同步版对比、readline 逐行读取 |
| 12 module | [12_module.js](12_module.js) | `node javascript/12_module.js` | ESM 命名/默认导出、as 换名、命名空间导入（配套 lib/math_utils.js） |
| 13 stdlib | [13_stdlib.js](13_stdlib.js) | `node javascript/13_stdlib.js` | JSON、Math、Date/Intl、URL、structuredClone 深拷贝 |
| 14 concurrency | [14_concurrency.js](14_concurrency.js) | `node javascript/14_concurrency.js` | Promise 链、async/await、all/allSettled、串行 vs 并行计时 |
| 15 generic | ➖ | — | JavaScript 无编译期泛型（脚本语言运行时定型，类型参数无从谈起），标 ➖ |
| + 特色 destructuring | [15_destructuring.js](15_destructuring.js) | `node javascript/15_destructuring.js` | 对象/数组解构、默认值与换名、展开与收集、函数参数解构 |

## 进阶说明

- 每个示例文件头部注释都标明了主题说明、运行命令与预期输出，适合按主题顺序阅读；`11_file_io.js` 的临时文件写入系统临时目录并自动清理
- [languages/javascript](../languages/javascript/) 是早期章节式练习（src + Node 原生测试），用 `node --test languages/javascript/tests` 运行，保留作进阶参考，后续计划迁移合并
- 浏览器端与工程化方向见 [web/frontend](../web/frontend/)（Vue3 工程）：组件、构建工具与前端调试
- 之后的进阶方向：TypeScript 类型系统（见仓库 typescript/）、事件循环与微任务时序、迭代器/生成器、Fetch 与流（stream）
