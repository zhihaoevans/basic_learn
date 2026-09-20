// 主题说明：文件读写 —— fs/promises 的 writeFile/readFile/appendFile（异步优先）、
//           同步版 writeFileSync/readFileSync 对比、readline/promises 逐行读取；
//           临时文件写到 os.tmpdir() 并在 finally 中清理。
// 运行命令：node javascript/11_file_io.js
// 预期输出（关键行）：
//   异步写入并读回 -> "第 1 行\n第 2 行\n追加的行\n"
//   同步读回 -> 第 1 行
//   逐行读取 -> 1: 第 1 行
//   临时文件已清理：true

import { writeFile, readFile, appendFile, rm } from 'node:fs/promises';
import { writeFileSync, readFileSync, createReadStream, existsSync } from 'node:fs';
import readline from 'node:readline/promises';
import os from 'node:os';
import path from 'node:path';

// 临时文件放系统临时目录（不污染仓库），用 pid 避免并发冲突
const tmp = path.join(os.tmpdir(), `basic_learn_js_11_${process.pid}.txt`);

try {
  // 知识点 1：writeFile 写文件（utf8 指定编码），文件不存在会自动创建
  await writeFile(tmp, '第 1 行\n第 2 行\n', 'utf8');

  // 知识点 2：appendFile 追加写入，不动已有内容
  await appendFile(tmp, '追加的行\n', 'utf8');

  // 知识点 3：readFile 读回整个文件 —— 不传编码得到的是 Buffer（原始字节），传 'utf8' 得到字符串
  const text = await readFile(tmp, 'utf8');
  console.log('异步写入并读回 ->', JSON.stringify(text));
  const buf = await readFile(tmp);
  console.log('Buffer 长度（字节数）->', buf.length);

  // 知识点 4：同步版 —— 用法相同但会阻塞事件循环，仅在启动加载配置等场景使用
  writeFileSync(tmp, '第 1 行\n第 2 行\n追加的行\n', 'utf8');
  console.log('同步读回 ->', readFileSync(tmp, 'utf8').split('\n')[0]);

  // 知识点 5：逐行读取 —— 流式处理大文件不占内存（readline/promises 配合 for-await）
  const rl = readline.createInterface({ input: createReadStream(tmp, 'utf8') });
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
