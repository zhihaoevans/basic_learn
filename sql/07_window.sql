-- 主题说明：窗口函数 —— OVER() 定义一个"窗口"，让聚合类函数不再压缩行数、而是逐行给出结果：
--           ROW_NUMBER 连续编号、RANK 并列同号跳空位、DENSE_RANK 并列同号不跳位、
--           OVER (PARTITION BY ... ORDER BY ...) 分区内排名、窗口聚合（每门课平均分与个人分的同行对比），
--           以及"取每组第一名"的经典模式（窗口函数 + 子查询过滤）。
--           【SQLite 方言】窗口函数需要 SQLite >= 3.25；本文件只读，可重复执行。
-- 运行命令：sqlite3 sql/db.sqlite < sql/07_window.sql
-- 预期结果：SQL 入门课内 95/92/88/73/64/55 分依次排第 1~6 名（无并列时三种口径一致）；
--           人为构造的两档并列里 RANK 跳位、DENSE_RANK 不跳；每门课第一名共 5 行；
--           「个人-平均」列直接读出每位学生高出/低于课程平均多少分。

.headers on
.mode column

.print "=== 1. ROW_NUMBER：不考虑并列的连续编号 ==="
SELECT s.name AS "姓名", c.title AS "课程", sc.score AS "分数",
       ROW_NUMBER() OVER (ORDER BY sc.score DESC) AS "全局名次"   -- 严格 1,2,3,... 即使分数相同
FROM scores sc
JOIN students s ON s.id = sc.student_id
JOIN courses  c ON c.id = sc.course_id
ORDER BY "全局名次"
LIMIT 6;                                     -- 只看前 6 名，避免刷屏

.print "=== 2. RANK 与 DENSE_RANK：处理并列的三种口径 ==="
SELECT s.name AS "姓名", sc.score AS "分数",
       ROW_NUMBER() OVER (ORDER BY sc.score DESC) AS "ROW_NUMBER",
       RANK()       OVER (ORDER BY sc.score DESC) AS "RANK",       -- 并列同名次，之后跳位
       DENSE_RANK() OVER (ORDER BY sc.score DESC) AS "DENSE_RANK"  -- 并列同名次，不跳位
FROM scores sc
JOIN students s ON s.id = sc.student_id
WHERE sc.course_id = 1                        -- SQL 入门：分数 95/92/88/73/64/55，无并列
ORDER BY sc.score DESC;

-- 原始分数没有并列，按「十分位」分桶制造并列对照（只看 80 分以上）：
-- 9 档 4 人并列第 1 → RANK 里 8 档从第 5 开始（跳过被占的 2~4 位），DENSE_RANK 里从第 2 开始（不跳位）
SELECT CAST(sc.score / 10 AS INTEGER) AS "十分位档",
       sc.score AS "分数",
       RANK()       OVER (ORDER BY CAST(sc.score / 10 AS INTEGER) DESC) AS "RANK",
       DENSE_RANK() OVER (ORDER BY CAST(sc.score / 10 AS INTEGER) DESC) AS "DENSE_RANK"
FROM scores sc
WHERE sc.score >= 80
ORDER BY "十分位档" DESC, sc.score DESC;

.print "=== 3. PARTITION BY：分区内各自排名（每门课内的名次）==="
SELECT c.title AS "课程", s.name AS "姓名", sc.score AS "分数",
       RANK() OVER (PARTITION BY sc.course_id            -- 先按课程分区
                    ORDER BY sc.score DESC) AS "课内名次"
FROM scores sc
JOIN students s ON s.id = sc.student_id
JOIN courses  c ON c.id = sc.course_id
ORDER BY c.title, "课内名次";

.print "=== 4. 窗口聚合：聚合函数 + OVER，行数不减 ==="
-- 普通用法的 AVG 按组压缩成 1 行；加 OVER (PARTITION BY ...) 后每行都带所在课的平均分
SELECT c.title AS "课程", s.name AS "姓名", sc.score AS "分数",
       ROUND(AVG(sc.score) OVER (PARTITION BY sc.course_id), 1) AS "课程平均",
       ROUND(sc.score - AVG(sc.score) OVER (PARTITION BY sc.course_id), 1) AS "个人-平均"
FROM scores sc
JOIN students s ON s.id = sc.student_id
JOIN courses  c ON c.id = sc.course_id
ORDER BY c.title, sc.score DESC;

.print "=== 5. 经典模式：窗口函数 + 子查询，取每门课第一名 ==="
-- 窗口函数不能直接写在 WHERE 里（它在 WHERE 之后才计算），所以要套一层子查询/CTE 过滤
WITH ranked AS (
    SELECT c.title AS "课程", s.name AS "姓名", sc.score AS "分数",
           RANK() OVER (PARTITION BY sc.course_id ORDER BY sc.score DESC) AS rn
    FROM scores sc
    JOIN students s ON s.id = sc.student_id
    JOIN courses  c ON c.id = sc.course_id
)
SELECT "课程", "姓名", "分数" AS "第一名分数"
FROM ranked
WHERE rn = 1
ORDER BY "课程";

.print "=== 6. 聚合之后再开窗：GROUP BY 与窗口函数分工 ==="
-- 窗口函数在 GROUP BY 之后计算，所以 OVER 里可以直接引用聚合结果 SUM(sc.score)
SELECT s.name AS "姓名",
       COUNT(*) AS "选课门数",
       SUM(sc.score) AS "总分",
       RANK() OVER (ORDER BY SUM(sc.score) DESC) AS "总分名次"
FROM scores sc
JOIN students s ON s.id = sc.student_id
GROUP BY s.id, s.name                        -- 先按学生聚合，再对聚合结果开窗排名
ORDER BY "总分名次";
