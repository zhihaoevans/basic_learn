// 主题说明：错误与异常处理 —— try/catch/finally、自定义 Error 类、strict 模式下 catch 变量是 unknown、
//           TS 差异点：unknown 收窄与 is 类型守卫、非空断言绕过检查的代价、异步错误。
// 运行命令：npx tsx src/10_error.ts
// 预期输出（关键行）：
//   TypeError: Cannot read properties of null (reading 'length')
//   finally 总会执行
//   自定义错误 ValidationError: age 不合法（字段：age）
//   类型守卫 isValidationError -> true
//   异步错误被 catch 住： 网络超时
//   全部错误都被妥善处理，程序正常结束

// 知识点 1【TS 差异】：strict 模式下 catch 的变量是 unknown（不是 any）—— 必须收窄才能用
const bad: string | null = null;
try {
  console.log('非空断言绕过检查 ->', bad!.length); // ! 骗过编译器，运行时照样 TypeError
} catch (e: unknown) {
  if (e instanceof TypeError) {
    // instanceof 收窄：这个分支里 e 已是 TypeError，.message 可用
    console.log(e.name + ':', e.message);
  } else {
    throw e; // 不认识的错误继续往上抛
  }
}

// 知识点 2：内置 Error 子类型 —— SyntaxError（如 JSON 解析失败）、RangeError
try {
  JSON.parse('不是 JSON');
} catch (e: unknown) {
  if (e instanceof SyntaxError) {
    console.log(e.name, '—— JSON 解析失败的典型来源');
  }
}

// 知识点 3：throw + try/catch/finally —— finally 无论是否出错都会执行（常用于清理）
try {
  throw new RangeError('下标越界');
} catch (e: unknown) {
  const msg = e instanceof Error ? e.message : String(e); // 三元里同样完成收窄
  console.log('catch 捕获：', e instanceof Error ? e.name : '未知', msg);
} finally {
  console.log('finally 总会执行');
}

// 知识点 4【TS 差异】：自定义 Error 类 —— 继承 Error、带业务字段；TS 里用 implements/builder 都不如直接继承直观
class ValidationError extends Error {
  constructor(public readonly field: string) {
    // 参数属性 + readonly 一行搞定业务字段
    super(`${field} 不合法`); // 调用 Error 构造器设置 message
    this.name = 'ValidationError'; // 修正 name，日志里更好认
  }
}

// 知识点 5【TS 差异】：is 类型守卫 —— "返回真时，参数就是 X"的自定义判定函数
function isValidationError(e: unknown): e is ValidationError {
  //                ^^^^ 谓词签名：返回 true 时调用方视角里 e 就是 ValidationError
  return e instanceof ValidationError;
}
function setAge(age: unknown): number {
  if (typeof age !== 'number' || !Number.isInteger(age) || age < 0) {
    throw new ValidationError('age'); // 入口收 unknown：外部数据先验证再使用
  }
  return age;
}
try {
  setAge(-1);
} catch (e: unknown) {
  if (isValidationError(e)) {
    // 守卫生效：这里 e 已是 ValidationError，.field 直接可读
    console.log(`自定义错误 ${e.name}: ${e.message}（字段：${e.field}）`);
    console.log('类型守卫 isValidationError ->', isValidationError(e));
  } else {
    throw e;
  }
}

// 知识点 6：异步错误 —— Promise 的 reject 与 async 函数里的 throw，都变成"被拒绝的 Promise"
function fetchUser(): Promise<{ id: number; name: string }> {
  // 返回类型标注：调用方在 .then/.catch 里能拿到精确类型
  return new Promise((resolve, reject) => {
    setTimeout(() => reject(new Error('网络超时')), 10); // 模拟请求失败
  });
}
fetchUser().catch((e: unknown) => {
  console.log('异步错误被 catch 住：', e instanceof Error ? e.message : String(e));
});

// 知识点 7：async/await 中 try/catch 同样有效（await 把 rejected Promise 转成可 catch 的异常）
async function load(): Promise<void> {
  try {
    await fetchUser();
  } catch (e: unknown) {
    console.log('await 版捕获：', e instanceof Error ? e.message : String(e));
  } finally {
    console.log('异步清理完成');
  }
}
await load(); // 顶层 await（ESM 模块支持）
console.log('全部错误都被妥善处理，程序正常结束');

// 说明：本文件用到顶层 await，TS 要求"模块"里才允许 —— 末尾的 export {} 把脚本标记为模块
export {};
