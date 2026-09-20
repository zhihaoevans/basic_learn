// 主题说明：TypeScript 特色主题 —— 类型工具与联合类型：联合 | 与交叉 &、字面量联合、
//           as const（深层只读 + 字面量化）、keyof/typeof、内置工具类型实战（Pick/Omit/Record/Partial/Readonly）。
//           这是 TS 在"运行前"用类型系统建模业务的核心招式。
// 运行命令：npx tsx src/16_type_utils.ts
// 预期输出（关键行）：
//   联合类型收窄 -> 鸟在飞 / 鱼在游
//   交叉类型 Admin -> root （拥有 user 与 permissions 两组字段）
//   as const -> 200 未找到 服务器错误 （键与值都成了只读字面量类型 200 | 404 | 500）
//   Pick 用户预览 -> { id: 1, name: 'Li' }
//   Omit 公开资料 -> { id: 1, name: 'Li' }
//   Record 按角色查表 -> admin 可写： true ；viewer 可写： false

// 知识点 1：联合类型 | —— "或"关系：值是几种类型之一，用之前必须收窄（in / typeof / 标签字段）
interface Bird {
  fly(): void;
}
interface Fish {
  swim(): void;
}
type Pet = Bird | Fish; // Pet 是鸟或鱼
function move(pet: Pet): string {
  if ('fly' in pet) {
    pet.fly(); // in 收窄：这个分支里 pet 是 Bird
    return '鸟在飞';
  }
  pet.swim(); // 剩下的一定是 Fish
  return '鱼在游';
}
console.log('联合类型收窄 ->', move({ fly() {} }), '/', move({ swim() {} }));

// 知识点 2：交叉类型 & —— "与"关系：把多个形状合并成一个（复用已有类型组装新类型）
interface User {
  id: number;
  name: string;
  email: string;
  age: number;
}
type Admin = User & { permissions: string[] }; // Admin 拥有 User 的全部字段再加 permissions
const root: Admin = { id: 0, name: 'root', email: 'root@example.com', age: 30, permissions: ['read', 'write'] };
console.log('交叉类型 Admin ->', root.name, '（拥有 user 与 permissions 两组字段）');

// 知识点 3：字面量联合 + 可辨识标签 —— 把取值范围枚举出来，非法值进不了类型系统
type Direction = 'up' | 'down' | 'left' | 'right';
interface KeyPress {
  key: Direction;
  ctrl?: boolean;
}
function describeKey(kp: KeyPress): string {
  return `${kp.ctrl ? 'Ctrl+' : ''}${kp.key}`;
}
console.log('字面量联合 ->', describeKey({ key: 'up' }), '；', describeKey({ key: 'right', ctrl: true }));

// 知识点 4：as const —— 把对象"冻"成深层只读，且每个值都收窄成字面量类型（常量表的标准写法）
const HTTP_STATUS = {
  ok: 200,
  notFound: 404,
  serverError: 500,
} as const;
// HTTP_STATUS.ok = 201; // 编译错误：readonly，不能改
type StatusCode = (typeof HTTP_STATUS)[keyof typeof HTTP_STATUS]; // 200 | 404 | 500 —— keyof/typeof 组合拳
function nameOf(code: StatusCode): string {
  switch (code) {
    // switch 字面量联合：不写 default 也必须全覆盖，否则返回类型不稳
    case HTTP_STATUS.ok:
      return '成功';
    case HTTP_STATUS.notFound:
      return '未找到';
    case HTTP_STATUS.serverError:
      return '服务器错误';
  }
}
console.log('as const ->', HTTP_STATUS.ok, nameOf(HTTP_STATUS.notFound), nameOf(HTTP_STATUS.serverError),
  '（键与值都成了只读字面量类型 200 | 404 | 500）');

// 知识点 5：Pick<T, K> —— 从 T 里"挑选"几个字段组成新类型（给列表页瘦身）
type UserPreview = Pick<User, 'id' | 'name'>;
const preview: UserPreview = { id: 1, name: 'Li' };
console.log('Pick 用户预览 ->', preview);

// 知识点 6：Omit<T, K> —— 反向"剔除"几个字段（隐藏敏感信息）
type UserPublic = Omit<User, 'email' | 'age'>;
const publicInfo: UserPublic = { id: 1, name: 'Li' };
console.log('Omit 公开资料 ->', publicInfo);

// 知识点 7：Record<K, V> —— "键的全集 → 值"的查表类型：三个角色一个都不能少
type Role = 'admin' | 'editor' | 'viewer';
type Permissions = Record<Role, string[]>;
const permissions: Permissions = {
  admin: ['read', 'write'],
  editor: ['read', 'write'],
  viewer: ['read'],
};
const canWrite = (role: Role): boolean => permissions[role].includes('write');
console.log('Record 按角色查表 -> admin 可写：', canWrite('admin'), '；viewer 可写：', canWrite('viewer'));

// 知识点 8：Partial<T> 与 Readonly<T> —— 已在 08 见过 Partial（局部更新）；Readonly 把所有字段变只读
const frozenUser: Readonly<User> = { id: 1, name: 'Li', email: 'li@example.com', age: 30 };
// frozenUser.age = 31; // 编译错误：所有字段 readonly
const patch: Partial<User> = { age: 31 }; // Partial：所有字段可选
const updated: User = { ...frozenUser, ...patch };
console.log('Partial 合并更新 ->', updated.age === 31, '；Readonly -> 只读不可改');

// 知识点 9：工具类型的组合 —— 类型的"乐高"：先 Pick 再 Partial，一步到位"可部分提交的预览"
type PreviewPatch = Partial<Pick<User, 'name' | 'age'>>;
const patch2: PreviewPatch = { name: '李' };
console.log('Partial<Pick<...>> ->', patch2, '（只允许 name/age 且都可选）');
