-- 主题说明：事务 —— BEGIN 开启事务、COMMIT 提交（成功路径）、ROLLBACK 回滚（失败路径），
--           以及 SQLite 的自动提交（autocommit）模式、约束错误与回滚的配合、事务的原子性验证。
--           为保证脚本可重复执行：演示表 transfer_log 每次重建，对主表的修改全部包在
--           ROLLBACK 的事务里（改完即复原），连跑多遍结果一致。
-- 运行命令：sqlite3 sql/db.sqlite < sql/06_transaction.sql
-- 预期结果：成功事务提交后 transfer_log 剩 2 行且一直保留；回滚事务里的 1 行插入"消失"，
--           COUNT 前后都是 2；主表演示里全体成绩 +100 后又被 ROLLBACK 复原，平均分回到 75.8。

.headers on
.mode column

-- 演示表：每次运行先重建，保证幂等；amount 列的 CHECK 约束后面会用到
DROP TABLE IF EXISTS transfer_log;
CREATE TABLE transfer_log (
    id     INTEGER PRIMARY KEY,
    remark TEXT NOT NULL,
    amount REAL NOT NULL CHECK (amount > 0)   -- 金额必须为正：约束错误的"事故现场"
);

.print "=== 0. 背景：SQLite 默认自动提交（autocommit）==="
-- 不写 BEGIN 时，每条 INSERT/UPDATE/DELETE 都是一个独立事务、立即落盘；
-- 把多条语句包进 BEGIN ... COMMIT，它们才"要么全成功，要么全不动"（原子性 A）
SELECT '接下来每段都会显式 BEGIN' AS "说明";

.print "=== 1. 成功路径：BEGIN → 多条写入 → COMMIT ==="
BEGIN;                                                  -- 开启事务
INSERT INTO transfer_log (remark, amount) VALUES ('报名费', 100.0);
INSERT INTO transfer_log (remark, amount) VALUES ('教材费', 58.5);
SELECT COUNT(*) AS "事务内行数（本连接自己看得到）" FROM transfer_log;   -- 未提交，但本连接可见
COMMIT;                                                 -- 提交：两条一起持久化
SELECT remark, amount FROM transfer_log;                -- 提交后仍在：真的落盘了

.print "=== 2. 失败路径：BEGIN → 写入 → ROLLBACK（全部撤销）==="
BEGIN;
INSERT INTO transfer_log (remark, amount) VALUES ('这笔会被回滚', 66.6);
UPDATE transfer_log SET amount = amount * 10 WHERE remark = '报名费';
SELECT remark, amount FROM transfer_log;                -- 事务内看：3 行，且报名费被改成 1000
ROLLBACK;                                               -- 回滚：本事务的所有修改一笔勾销
SELECT remark, amount FROM transfer_log;                -- 回滚后：只剩 COMMIT 过的 2 行，报名费复原为 100

-- 真实应用里 ROLLBACK 通常由两类失败触发：
--   a) 语句违反约束（如下面这句会触发 CHECK，注释掉以保证脚本退出码为 0，可手动放开体验）：
--        INSERT INTO transfer_log (remark, amount) VALUES ('坏数据', -1);   -- Runtime error: CHECK constraint failed
--   b) 应用层校验失败（如转账双方金额对不上账），由程序主动执行 ROLLBACK
-- 注：sqlite3 命令行跑脚本时，运行时错误会让整脚本以非零退出码结束，因此这里演示的是 b) 主动回滚

.print "=== 3. 原子性验证：在主表上演示「大批量修改，一键复原」==="
BEGIN;
UPDATE scores SET score = score + 5;                    -- 全表 22 条成绩一起改（+5 不越过 CHECK 上限 100）
SELECT COUNT(*) AS "已改行数", ROUND(AVG(score), 1) AS "事务内平均分" FROM scores;   -- 80.8
ROLLBACK;                                               -- 撤销：所有成绩复原
SELECT COUNT(*) AS "复原后行数", ROUND(AVG(score), 1) AS "复原后平均分" FROM scores; -- 75.8

.print "=== 4. 事务要点速记 ==="
-- 1) BEGIN / BEGIN TRANSACTION / BEGIN DEFERRED 都能开启事务，COMMIT（或 END）提交、ROLLBACK 回滚
-- 2) 未 COMMIT 前的修改只有本连接可见，其他连接看不到（隔离性 I）；进程崩溃未提交也会丢（持久性 D 只在 COMMIT 后）
-- 3) SQLite 中没有嵌套事务，但可以用 SAVEPOINT sp1 ... ROLLBACK TO sp1 实现部分回滚
-- 4) 大批量写入包成事务还能显著提速：免于每行一次磁盘同步
SELECT '事务演示完成，transfer_log 保留 2 行 COMMIT 数据' AS "结论",
       (SELECT COUNT(*) FROM transfer_log) AS "行数";
