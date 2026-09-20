// 主题说明：并发入门 —— JavaScript 单线程事件循环上的异步：Promise 链、async/await、
//           Promise.all / allSettled，以及串行 await 与并行 all 的计时对比。
// 运行命令：node javascript/14_concurrency.js
// 预期输出（关键行）：
//   Promise 链结果： 20
//   async/await -> 用户7
//   串行 3 个任务约 150ms；并行 Promise.all 约 50ms —— 并行快 3 倍左右
//   allSettled: [ 'fulfilled: ok', 'rejected: boom', 'fulfilled: slow ok' ]

// 知识点 0：工具函数 —— setTimeout 包成 Promise，模拟耗时 IO
const sleep = (ms) => new Promise((resolve) => setTimeout(resolve, ms));

// 知识点 1：Promise 链 —— then 依次传递结果，catch 兜底（Promise 是"未来才有值"的容器）
Promise.resolve(1)
  .then((v) => v + 1)        // 2
  .then((v) => v * 10)       // 20
  .then((v) => console.log('Promise 链结果：', v))
  .catch((e) => console.log('链中出错：', e.message));

// 知识点 2：async/await —— 用同步写法表达异步，await 会"让出"线程不阻塞（单线程不等于不能等）
async function fetchUser(id) {
  await sleep(50); // 模拟网络请求 50ms
  return { id, name: `用户${id}` };
}
const user = await fetchUser(7);
console.log('async/await ->', user.name);

// 知识点 3：串行 vs 并行计时 —— 逐个 await 是串行（时间累加），Promise.all 是并行（时间取最慢）
const work = async () => {
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

// 知识点 4：Promise.all —— 全部成功才成功（返回结果数组，顺序与传入一致），任一失败立即整体失败
const [r1, r2] = await Promise.all(['立即值', sleep(10).then(() => '延迟值')]);
console.log('Promise.all 结果按序 ->', [r1, r2]);

// 知识点 5：Promise.allSettled —— 无论成败都等完，结果带 status（适合同步一批互不依赖的任务）
const settled = await Promise.allSettled([
  Promise.resolve('ok'),
  Promise.reject(new Error('boom')),
  sleep(10).then(() => 'slow ok'),
]);
console.log('allSettled:', settled.map((r) =>
  r.status === 'fulfilled' ? `fulfilled: ${r.value}` : `rejected: ${r.reason.message}`
));

// 知识点 6：并行任务的错误处理 —— allSettled 后按 status 分流，失败不影响其他任务的结果
const ok = settled.filter((r) => r.status === 'fulfilled').length;
console.log(`一批 3 个任务，成功 ${ok} 个、失败 ${settled.length - ok} 个 —— 单个失败不会丢掉整批`);
console.log('（对比：Promise.all 遇到第一个失败就整体 reject，成功的结果也拿不到）');
