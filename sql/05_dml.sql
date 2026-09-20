-- 主题说明：增删改（DML）—— INSERT 新增、UPDATE 修改、DELETE 删除，以及两个 SQLite 亮点语法：
--           UPSERT（INSERT ... ON CONFLICT，插入遇冲突改为更新）和 RETURNING（写操作直接返回受影响的行）。
--           为保证脚本可重复执行：所有写操作都落在脚本自建自重建的演示表 club_members 上，
--           不动 seed.sql 的三张主表。
-- 运行命令：sqlite3 sql/db.sqlite < sql/05_dml.sql
-- 预期结果：每次 INSERT/UPDATE/DELETE 后立即打印受影响的行（RETURNING 效果）；李娜换社那步
--           UPSERT 命中姓名唯一约束、只更新不新增（id 保持 2）；末尾 SELECT 剩 3 名成员。

.headers on
.mode column

-- 演示表：每次运行先重建，保证幂等（可连跑多遍，结果一致）
DROP TABLE IF EXISTS club_members;
CREATE TABLE club_members (
    id    INTEGER PRIMARY KEY,
    name  TEXT NOT NULL UNIQUE,             -- 姓名唯一：给后面的 UPSERT 提供冲突检测点
    club  TEXT NOT NULL,
    level TEXT NOT NULL DEFAULT '新手'       -- 未提供时走 DEFAULT 默认值
);

.print "=== 0. 初始数据 ==="
INSERT INTO club_members (name, club) VALUES ('张伟', '篮球社'), ('李娜', '网球社');
SELECT * FROM club_members;

.print "=== 1. INSERT + RETURNING：插入并立即看到新行 ==="
-- 【SQLite 方言】RETURNING 需要 SQLite >= 3.35：INSERT/UPDATE/DELETE 都可以带，省去再查一次
INSERT INTO club_members (name, club) VALUES ('王芳', '围棋社')
RETURNING id, name, club, level;            -- id 自动分配，level 走默认值"新手"

INSERT INTO club_members (name, club, level) VALUES ('孙丽', '书法社', '骨干')
RETURNING *;

.print "=== 2. UPDATE + RETURNING：修改并看到改后的行 ==="
UPDATE club_members
SET level = '骨干'
WHERE name = '张伟'
RETURNING id, name, level;                  -- 只返回被更新的行，没匹配上的行不出现

-- UPDATE 不带 WHERE 会改全表（危险操作），务必先写 WHERE 再按回车
SELECT COUNT(*) AS "level=骨干 的人数" FROM club_members WHERE level = '骨干';

.print "=== 3. UPSERT：INSERT ... ON CONFLICT DO UPDATE（撞唯一约束就改为更新）==="
-- 需求：李娜想从网球社换到羽毛球社。普通 INSERT 会因 name UNIQUE 报错；
-- UPSERT 让"已存在就更新指定列，不存在就插入"一条语句完成
INSERT INTO club_members (name, club) VALUES ('李娜', '羽毛球社')
ON CONFLICT (name) DO UPDATE SET club = excluded.club   -- excluded = "刚才试图插入的那行"
RETURNING id, name, club;                   -- 注意 id 还是 2：是原行被更新，不是删了重插

-- 冲突时什么都不做：DO NOTHING（常用于"存在即跳过"的幂等写入）
INSERT INTO club_members (name, club) VALUES ('张伟', '游泳社')
ON CONFLICT (name) DO NOTHING;              -- 0 行受影响，无输出
SELECT name, club AS "张伟仍在原社(没被改成游泳社)" FROM club_members WHERE name = '张伟';

-- 【SQLite 方言】老写法 INSERT OR IGNORE / INSERT OR REPLACE 仍可用：
--   OR IGNORE  遇冲突跳过（等价 DO NOTHING，但无法指定更新的列）
--   OR REPLACE 遇冲突先删旧行再插新行（会换 id、触发外键级联，慎用）
-- ON CONFLICT 是 SQL 标准风格的 UPSERT 写法，需要 SQLite >= 3.24

.print "=== 4. DELETE + RETURNING：删除并看到被删的行 ==="
DELETE FROM club_members
WHERE club = '围棋社'                       -- 围棋社解散：王芳的记录被删除
RETURNING id, name, club;

-- DELETE 不带 WHERE 会清空整表；需要全清时显式写 DELETE FROM 表名，更推荐有 WHERE 的习惯

.print "=== 5. 最终结果 ==="
SELECT * FROM club_members ORDER BY id;
SELECT (SELECT COUNT(*) FROM club_members)        AS "社团人数",
       (SELECT COUNT(DISTINCT club) FROM club_members) AS "社团数";
