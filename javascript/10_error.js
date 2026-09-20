// 主题说明：错误与异常处理 —— 内置 Error 子类型、throw/try/catch/finally、
//           自定义 Error 类（带额外字段）、异步错误的 catch（Promise/async 中的异常）。
// 运行命令：node javascript/10_error.js
// 预期输出（关键行）：
//   TypeError: Cannot read properties of null (reading 'foo')
//   finally 总会执行
//   自定义错误 ValidationError: age 不合法（字段：age）
//   异步错误被 catch 住：网络超时

// 知识点 1：常见内置 Error 子类型 —— TypeError（类型用错）、RangeError、SyntaxError（如 JSON 解析失败）
try {
  null.foo; // 对 null 取属性
} catch (e) {
  console.log(e.name + ':', e.message);
}
try {
  JSON.parse('不是 JSON');
} catch (e) {
  console.log(e.name, '—— JSON 解析失败的典型来源');
}

// 知识点 2：throw 抛出 + try/catch/finally —— finally 无论是否出错都会执行（常用于清理）
try {
  throw new RangeError('下标越界');
} catch (e) {
  console.log('catch 捕获：', e.name, e.message);
} finally {
  console.log('finally 总会执行');
}

// 知识点 3：自定义 Error 类 —— 继承 Error，设置 name 与业务字段， instanceof 可精确区分
class ValidationError extends Error {
  constructor(field) {
    super(`${field} 不合法`); // 调用 Error 构造器设置 message
    this.name = 'ValidationError';
    this.field = field; // 业务字段：调用方拿到更多上下文
  }
}
function setAge(age) {
  if (typeof age !== 'number' || age < 0) {
    throw new ValidationError('age');
  }
  return age;
}
try {
  setAge(-1);
} catch (e) {
  if (e instanceof ValidationError) {
    console.log(`自定义错误 ${e.name}: ${e.message}（字段：${e.field}）`);
  } else {
    throw e; // 不认识的错误继续往上抛
  }
}

// 知识点 4：异步错误 —— Promise 的 reject 与 async 函数里的 throw，都变成"被拒绝的 Promise"，用 catch 接
function fetchUser() {
  return new Promise((resolve, reject) => {
    setTimeout(() => reject(new Error('网络超时')), 10); // 模拟请求失败
  });
}
fetchUser().catch((e) => console.log('异步错误被 catch 住：', e.message));

// 知识点 5：async/await 中 try/catch 同样有效（await 会把 rejected Promise 转成可 catch 的异常）
async function load() {
  try {
    await fetchUser();
  } catch (e) {
    console.log('await 版捕获：', e.message);
  } finally {
    console.log('异步清理完成');
  }
}
await load(); // 顶层 await（ESM 支持）
console.log('全部错误都被妥善处理，程序正常结束');
