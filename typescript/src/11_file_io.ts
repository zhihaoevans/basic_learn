// 主题说明：文件读写 —— fs/promises 的 writeFile/readFile/appendFile（异步优先）、泛型返回标注
//           （传编码返回 Promise<string>、不传返回 Promise<Buffer>）、同步版对比、readline 逐行读取；
//           临时文件写到 os.tmpdir() 并在 finally 中清理。
// 运行命令：npx tsx src/11_file_io.ts
// 预期输出（关键行）：
//   异步写入并读回 -> "第 1 行\n第 2 行\n追加的行\n"
//   Buffer 长度（字节数）-> 33
//   同步读回 -> 第 1 行
//   逐行读取 -> 3: 追加的行
//   临时文件已清理： true

import { writeFile, readFile, appendFile, rm } from 'node:fs/promises';
import { writeFileSync, readFileSync, createReadStream, existsSync } from 'node:fs';
import { createInterface } from 'node:readline/promises';
import os from 'node:os';
import path from 'node:path';

// 临时文件放系统临时目录（不污染仓库），用 pid 避免并发冲突
const tmp: string = path.join(os.tmpdir(), `basic_learn_ts_11_${process.pid}.txt`);

try {
  // 知识点 1：writeFile 写文件（utf8 指定编码），文件不存在会自动创建；返回 Promise<void>
  const written: Promise<void> = writeFile(tmp, '第 1 行\n第 2 行\n', 'utf8'); // 标注出泛型返回
  await written;

  // 知识点 2：appendFile 追加写入，不动已有内容
  await appendFile(tmp, '追加的行\n', 'utf8');

  // 知识点 3【TS 差异】：fs/promises 的泛型返回 —— readFile 是重载函数：
  //   readFile(路径, 'utf8') 的返回类型是 Promise<string>；readFile(路径) 是 Promise<Buffer>
  const text: string = await readFile(tmp, 'utf8'); // 传编码：TS 知道结果是 string
  console.log('异步写入并读回 ->', JSON.stringify(text));
  const buf: Buffer = await readFile(tmp); // 不传编码：结果是原始字节 Buffer
  console.log('Buffer 长度（字节数）->', buf.length, '；toString 还原 ->', JSON.stringify(buf.toString('utf8')));

  // 知识点 4：同步版 —— 用法相同但会阻塞事件循环，仅在启动加载配置等场景使用
  writeFileSync(tmp, '第 1 行\n第 2 行\n追加的行\n', 'utf8');
  console.log('同步读回 ->', readFileSync(tmp, 'utf8').split('\n')[0]);

  // 知识点 5：逐行读取 —— readline/promises 配合 createReadStream 流式处理，大文件不占内存
  const rl = createInterface({ input: createReadStream(tmp, 'utf8') });
  let no = 0;
  for await (const line of rl) {
    no++;
    console.log(`逐行读取 -> ${no}: ${line}`);
  }
} finally {
  // 知识点 6：清理临时文件 —— finally 保证无论成败都执行；force: true 让文件不存在时也不报错
  await rm(tmp, { force: true });
  console.log('临时文件已清理：', !existsSync(tmp));
}
