-- 主题说明：子查询与 CTE —— 标量子查询（返回单个值）、IN / NOT IN 子查询（返回一列集合）、
--           相关子查询（引用外层列）、WITH 普通 CTE（先分解再组装）、WITH RECURSIVE 递归 CTE 一例，
--           以及结果集的集合操作（UNION / UNION ALL / INTERSECT / EXCEPT）。本文件只读，可重复执行。
-- 运行命令：sqlite3 sql/db.sqlite < sql/04_subquery_cte.sql
-- 预期结果：高于全体平均分（75.8）的成绩 13 条；有不及格记录的 3 名学生；递归 CTE 生成 1~10 的序列；
--           UNION 去重后 5 个城市（UNION ALL 则是 8 行）；EXCEPT 差集为「没选 SQL 入门的学生」。

.headers on
.mode column

.print "=== 1. 标量子查询：返回单个值的子查询，可以当常量用 ==="
SELECT ROUND(AVG(score), 1) AS "全体平均分" FROM scores;   -- 先单独看一眼这个值

SELECT s.name AS "姓名", sc.course_id AS "课程号", sc.score AS "分数",
       ROUND(sc.score - (SELECT AVG(score) FROM scores), 1) AS "高出平均"
FROM scores sc
JOIN students s ON s.id = sc.student_id
WHERE sc.score > (SELECT AVG(score) FROM scores)   -- 子查询先算出平均分，外层再逐行比较
ORDER BY sc.score DESC;

.print "=== 2. IN 子查询：子查询返回一列，当集合用 ==="
-- 有不及格记录的学生（两步并一步：以前要先查出学生编号，再写 WHERE id IN (4, 6, 8)）
SELECT name AS "有不及格的学生", city
FROM students
WHERE id IN (SELECT student_id FROM scores WHERE score < 60);

-- NOT IN 的 NULL 陷阱：若子查询结果里含 NULL，NOT IN 会一个都查不出来（UNKNOWN 不通过）
SELECT name AS "没有不及格记录的学生"
FROM students
WHERE id NOT IN (SELECT student_id FROM scores WHERE score < 60)
ORDER BY id;
-- 更稳的写法是 NOT EXISTS（不受 NULL 影响）：
SELECT name AS "没有不及格记录(NOT EXISTS 写法)"
FROM students s
WHERE NOT EXISTS (SELECT 1 FROM scores sc WHERE sc.student_id = s.id AND sc.score < 60)
ORDER BY id;

.print "=== 3. 相关子查询：子查询里引用外层的列，每行各算一次 ==="
-- SELECT 列位置放一个标量子查询：给每个学生算他自己的平均分
SELECT s.name AS "姓名",
       (SELECT COUNT(*) FROM scores sc WHERE sc.student_id = s.id) AS "选课门数",
       (SELECT ROUND(AVG(sc.score), 1) FROM scores sc WHERE sc.student_id = s.id) AS "个人平均"
FROM students s
ORDER BY "选课门数" DESC, s.id;

.print "=== 4. WITH 普通 CTE：先分解、再组装，替代层层嵌套 ==="
-- 需求：每门课的平均分 + 选课人数，只看平均分不低于 75 的，按平均分降序
WITH course_stats AS (                                  -- CTE 像临时视图，只在本条查询内有效
    SELECT course_id,
           COUNT(*)            AS cnt,
           ROUND(AVG(score), 1) AS avg_score
    FROM scores
    GROUP BY course_id
)
SELECT c.title AS "课程", cs.cnt AS "选课人数", cs.avg_score AS "平均分"
FROM course_stats cs
JOIN courses c ON c.id = cs.course_id
WHERE cs.avg_score >= 75
ORDER BY cs.avg_score DESC;

.print "=== 5. 多个 CTE 串联：一条查询读成一小段程序 ==="
WITH
high AS (SELECT * FROM scores WHERE score >= 80),        -- 高分成绩
by_course AS (SELECT course_id, COUNT(*) AS n FROM high GROUP BY course_id)  -- 按课统计
SELECT c.title AS "有 80+ 成绩的课程", bc.n AS "80+ 人数"
FROM by_course bc
JOIN courses c ON c.id = bc.course_id
ORDER BY bc.n DESC, c.title;

.print "=== 6. WITH RECURSIVE 递归 CTE：让 SQL 自己循环生成数据 ==="
-- 三段式解剖：初始行（VALUES (1)）→ 递归项（n+1，引用上一轮结果）→ 终止条件（WHERE n < 10）
WITH RECURSIVE seq(n) AS (
    VALUES (1)                       -- 1) 种子：从 1 开始
    UNION ALL
    SELECT n + 1 FROM seq WHERE n < 10   -- 2) 递归：上一轮每行 +1；3) n 到 10 停
)
SELECT n, n * n AS "平方", printf('%02d', n) AS "补零" FROM seq;

.print "=== 7. 集合操作：把多个查询的结果当集合运算 ==="
-- UNION 去重合并；UNION ALL 不去重（快，但可能出重复行）
SELECT city FROM students WHERE gender = '男'
UNION                                            -- 去重后的所有城市：10 行里去重成 5 行
SELECT city FROM students WHERE gender = '女'
ORDER BY city;

SELECT COUNT(*) AS "UNION 去重后城市数"
FROM (SELECT city FROM students WHERE gender = '男'
      UNION
      SELECT city FROM students WHERE gender = '女');

.print "=== 8. INTERSECT 与 EXCEPT：交集与差集 ==="
-- 选了「数据结构」的学生 ∩ 选了「SQL 入门」的学生
SELECT s.name AS "两门都选的学生"
FROM students s
JOIN scores sc ON sc.student_id = s.id
JOIN courses c ON c.id = sc.course_id
WHERE c.title = '数据结构'
INTERSECT
SELECT s.name
FROM students s
JOIN scores sc ON sc.student_id = s.id
JOIN courses c ON c.id = sc.course_id
WHERE c.title = 'SQL 入门'
ORDER BY 1;

-- 全体学生 - 选了「SQL 入门」的学生 = 没选这门课的学生（7 号赵磊 + 5 号陈静）
SELECT name AS "没选 SQL 入门的学生"
FROM students
EXCEPT
SELECT s.name
FROM students s
JOIN scores sc ON sc.student_id = s.id
JOIN courses c ON c.id = sc.course_id
WHERE c.title = 'SQL 入门'
ORDER BY 1;
