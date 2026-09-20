// 主题说明：TypeScript 的第一个程序 —— console.log 输出、模板字符串、类型标注与类型推断初体验，
//           以及如何用 tsx 直接运行 .ts 文件（进入本 typescript/ 目录后先执行一次 npm install）。
// 运行命令：npx tsx src/01_hello.ts
// 预期输出（关键行）：
//   Hello, TypeScript!
//   Hi, tsx! 你好，类型世界！
//   1 + 1 = 2
//   answer 的类型是 number，值是 42

// 单行注释：与 JavaScript 完全一致；TS 文件里的注释不会被编译进产物
/* 块注释：斜杠星号包裹，可跨多行 */

// 知识点 1：console.log —— 与 JavaScript 相同的打印方式
console.log('Hello, TypeScript!');

// 知识点 2：模板字符串（反引号 + ${}）—— 语法与 JS 相同，${} 里表达式的类型会被检查
const runner = 'tsx';
console.log(`Hi, ${runner}! 你好，类型世界！`);
console.log(`1 + 1 = ${1 + 1}`);

// 知识点 3：TS 的第一课 —— 类型标注。answer: number 表示这个变量只能存放数字
const answer: number = 42;
// answer = '42'; // 编译错误：不能把 string 赋给 number（tsx 只转译不报错，npx --package typescript tsc --noEmit 会报）
console.log('answer 的类型是 number，值是', answer);

// 知识点 4：类型推断 —— 不写标注，TS 也能从初值推出类型，之后存放别的类型同样报编译错误
const inferred = '推断出的 string';
// inferred = 3.14; // 编译错误：number 不能赋给 string
console.log(inferred);

// 知识点 5：process 是 Node 提供的全局对象（类型来自本目录 env.d.ts 的环境声明）
console.log(`当前运行环境：Node ${process.version}（tsx 免编译直跑 .ts）`);

// 知识点 6：注释本身不产生任何输出，只给人看
