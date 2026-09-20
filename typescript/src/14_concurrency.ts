// 主题说明：并发入门 —— 单线程事件循环上的异步：Promise 链、async/await、Promise.all / allSettled、
//           串行 await 与并行 all 的计时对比；TS 差异点：Promise<T> 的返回类型标注与收窄。
// 运行命令：npx tsx src/14_concurrency.ts
// 预期输出（关键行）：
//   Promise 链结果： 20
//   async/await -> 用户7
//   串行 3 个任务约 150ms；并行 Promise.all 约 50ms —— 并行快 3 倍左右
//   allSettled: [ 'fulfilled: ok', 'rejected: boom', 'fulfilled: slow ok' ]
//   一批 3 个任务，成功 2 个、失败 1 个 —— 单个失败不会丢掉整批

// 知识点 0：工具函数 —— setTimeout 包成 Promise，模拟耗时 IO；返回类型标注 Promise<void>
const sleep = (ms: number): Promise<void> => new Promise((resolve) => setTimeout(resolve, ms));

// 知识点 1：Promise 链 —— then 依次传递结果，catch 兜底；
//           每个 then 的回调参数类型由上一步的返回类型推断（这里是 number 一路传下去）
Promise.resolve(1)
  .then((v) => v + 1) // v: number —— 上一环返回 number
  .then((v) => v * 10) // v: number
  .then((v) => console.log('Promise 链结果：', v))
  .catch((e: unknown) => console.log('链中出错：', e instanceof Error ? e.message : String(e)));

// 知识点 2：async/await —— 用同步写法表达异步；返回类型是 Promise<结果类型>
async function fetchUser(id: number): Promise<{ id: number; name: string }> {
  await sleep(50); // 模拟网络请求 50ms
  return { id, name: `用户${id}` };
}
const user = await fetchUser(7); // await 把 Promise<"结果类型"> 解包成结果类型
console.log('async/await ->', user.name);

// 知识点 3：串行 vs 并行计时 —— 逐个 await 是串行（时间累加），Promise.all 是并行（时间取最慢）
const work = async (): Promise<string> => {
  await sleep(50);
  return 'done';
};

let t0 = Date.now();
await work(); await work(); await work(); // 串行：50+50+50
const serialMs = Date.now() - t0;

t0 = Date.now();
await Promise.all([work(), work(), work()]); // 并行：≈50
const parallelMs = Date.now() - t0;
console.log(`串行 3 个任务约 ${serialMs}ms；并行 Promise.all 约 ${parallelMs}ms —— 并行快 3 倍左右`);

// 知识点 4：Promise.all —— 全部成功才成功；结果数组按传入顺序，且每个元素的类型一一对应
const results = await Promise.all(['立即值', sleep(10).then(() => '延迟值')]); // (string | Promise<string>)[]
console.log('Promise.all 结果按序 ->', results); // string[]，顺序与传入一致

// 知识点 5：Promise.allSettled —— 无论成败都等完；返回"可辨识联合"（status 是标签，见 05）：
//   fulfilled 的成员才有 value，rejected 的成员才有 reason —— switch/三元判断后自动收窄
const settled: PromiseSettledResult<string>[] = await Promise.allSettled([
  Promise.resolve('ok'),
  Promise.reject(new Error('boom')),
  sleep(10).then(() => 'slow ok'),
]);
console.log('allSettled:', settled.map((r) =>
  r.status === 'fulfilled' ? `fulfilled: ${r.value}` : `rejected: ${r.reason.message}` // 收窄后 value/reason 才可读
));

// 知识点 6：并行任务的错误处理 —— allSettled 后按 status 分流，失败不影响其他任务的结果
const okCount = settled.filter((r) => r.status === 'fulfilled').length;
console.log(`一批 3 个任务，成功 ${okCount} 个、失败 ${settled.length - okCount} 个 —— 单个失败不会丢掉整批`);
console.log('（对比：Promise.all 遇到第一个失败就整体 reject，成功的结果也拿不到）');

// 说明：顶层 await 需要"模块"环境 —— 末尾 export {} 把本文件标记为模块（无导入的文件默认算脚本）
export {};
