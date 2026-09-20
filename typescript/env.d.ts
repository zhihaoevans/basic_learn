// 主题说明：tsc 的"环境声明"文件 —— 本工程刻意只装 tsx 一个 devDependency（运行器），
//           不引入 @types/node，因此这里手写示例会用到的极小一部分 Node API 类型。
//           tsx 运行不受影响（esbuild 只剥离类型不查类型）；`npx --package typescript tsc --noEmit` 依赖本文件通过检查（裸 npx tsc 会命中 npm 假包 tsc）。
//           若日后想改用官方类型包：npm i -D @types/node 后删除本文件即可（tsconfig 的 "types": []
//           已阻止 @types 自动生效，届时需将其改为 "types": ["node"]）。
// 运行命令：npx --package typescript tsc --noEmit（本文件只参与类型检查，没有运行产物）

// —— Node 注入的全局对象（TC39 标准 lib 里没有）——
declare var console: {
  log(...data: unknown[]): void;
  info(...data: unknown[]): void;
  warn(...data: unknown[]): void;
  error(...data: unknown[]): void;
};

declare var process: {
  readonly pid: number;
  readonly version: string;
  readonly platform: string;
  readonly argv: string[];
  exit(code?: number): never;
};

// —— 定时器（句柄是不透明对象，示例里只当"取消凭证"用）——
declare function setTimeout(handler: () => void, ms?: number, ...args: unknown[]): object;
declare function clearTimeout(handle: object | undefined): void;

// —— Buffer：readFile 不传编码时的返回类型（只声明示例用到的成员）——
declare class Buffer {
  readonly length: number;
  toString(encoding?: string, start?: number, end?: number): string;
}

// —— WHATWG URL 与深拷贝：Node 的全局实现，类型定义与浏览器同名 ——
declare class URLSearchParams {
  constructor(init?: string | string[][] | Record<string, string>);
  get(name: string): string | null;
  has(name: string): boolean;
}
declare class URL {
  readonly protocol: string;
  readonly host: string;
  readonly hostname: string;
  readonly port: string;
  readonly pathname: string;
  readonly search: string;
  readonly hash: string;
  readonly searchParams: URLSearchParams;
  constructor(url: string, base?: string | URL);
  toString(): string;
}
declare function structuredClone<T>(value: T): T;

// —— ESM 模块的自描述地址（12_module 示例使用）——
interface ImportMeta {
  readonly url: string;
}

// —— Node 内置模块（node: 前缀形式），只声明示例用到的方法 ——
declare module 'node:os' {
  export function tmpdir(): string;
  export function platform(): string;
}

declare module 'node:path' {
  export function join(...paths: string[]): string;
  export function basename(p: string, ext?: string): string;
  export function dirname(p: string): string;
}

declare module 'node:fs/promises' {
  // 重载体现"泛型返回标注"：传编码返回 string，不传返回 Buffer（见 11_file_io.ts）
  export function readFile(path: string, encoding: string): Promise<string>;
  export function readFile(path: string): Promise<Buffer>;
  export function writeFile(path: string, data: string, encoding: string): Promise<void>;
  export function appendFile(path: string, data: string, encoding: string): Promise<void>;
  export function rm(path: string, options?: { force?: boolean; recursive?: boolean }): Promise<void>;
}

declare module 'node:fs' {
  export function writeFileSync(path: string, data: string, encoding: string): void;
  export function readFileSync(path: string, encoding: string): string;
  export function existsSync(path: string): boolean;
  // 流式读取：示例里只做 for-await 逐行消费，故标注为可异步迭代
  export function createReadStream(path: string, encoding: string): AsyncIterable<string>;
}

declare module 'node:readline/promises' {
  export function createInterface(options: {
    input: AsyncIterable<string>;
  }): AsyncIterable<string>;
}

declare module 'node:url' {
  export function fileURLToPath(url: string): string;
}
