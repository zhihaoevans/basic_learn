// 主题说明：JavaScript 的第一个程序 —— console.log 输出、模板字符串与注释写法，以及如何用 node 运行脚本。
//           node 是 JavaScript 的官方命令行运行时：写好 .js 文件后直接 node 文件名 即可执行，无需编译。
// 运行命令：node javascript/01_hello.js
// 预期输出（关键行）：
//   Hello, JavaScript!
//   Hi, Node! 你好，世界！
//   1 + 1 = 2

// 单行注释：以 // 开头，到行尾结束，最常用
/* 块注释：斜杠星号包裹，可跨多行，
   常用于解释一段逻辑或临时屏蔽代码 */

const runtime = 'Node';

// 知识点 1：console.log —— 输出一行内容并换行，是 Node 与浏览器里最常用的打印方式
console.log('Hello, JavaScript!');

// 知识点 2：模板字符串（反引号）—— ${} 中可以放任意表达式，比 + 拼接直观得多
console.log(`Hi, ${runtime}! 你好，世界！`);
console.log(`1 + 1 = ${1 + 1}`);

// 知识点 3：模板字符串中可直接换行，适合拼多行文本
const banner = `-----
菜单
-----`;
console.log(banner);

// 知识点 4：process 是 Node 提供的全局对象，可拿到运行环境信息（输出随本机版本变化）
console.log(`当前运行环境：${process.version}`);

// 知识点 5：注释本身不会产生任何输出，只给人看
