-- 主题说明：聚合与分组 —— COUNT/SUM/AVG/MAX/MIN 五个聚合函数、COUNT(*) 与 COUNT(列) 对 NULL 的区别、
--           GROUP BY 分组、HAVING 过滤分组（与 WHERE 的分工）、CASE WHEN 条件表达式（SQL 的"控制流"），
--           以及聚合函数里嵌 CASE 实现条件计数与透视。本文件只读不改数据，可任意重复执行。
-- 运行命令：sqlite3 sql/db.sqlite < sql/02_aggregate.sql
-- 预期结果：全体平均分约 75.8；SQL 入门平均分 77.8；不及格成绩共 4 条、涉及 3 名学生；
--           按分数段透视能看到 60 分以下 4 条、80 分及以上 10 条。

.headers on
.mode column

.print "=== 1. 五个聚合函数：把多行压成一个值 ==="
SELECT COUNT(*)        AS "成绩条数",
       SUM(score)      AS "总分",
       ROUND(AVG(score), 1) AS "平均分",      -- ROUND 保留 1 位小数，避免浮点长尾
       MAX(score)      AS "最高分",
       MIN(score)      AS "最低分"
FROM scores;

.print "=== 2. COUNT(*) 与 COUNT(列)：NULL 不计入 COUNT(列) ==="
SELECT COUNT(*)          AS "学生总数",        -- 数行数，包含 NULL
       COUNT(email)      AS "有邮箱的学生",    -- 数该列非 NULL 的行
       COUNT(DISTINCT city) AS "不同城市数"    -- 去重后计数
FROM students;
-- 注意：SUM/AVG/MAX/MIN 同样忽略 NULL（AVG 的分母只统计非 NULL 的行）

.print "=== 3. GROUP BY：按课程分组统计 ==="
SELECT course_id,
       COUNT(*)         AS "选课人数",
       ROUND(AVG(score), 1) AS "平均分",
       MAX(score)       AS "最高分"
FROM scores
GROUP BY course_id;                             -- 聚合函数按组分别计算

.print "=== 4. GROUP BY 多列 + 多种聚合 ==="
SELECT city, gender, COUNT(*) AS "人数", MIN(birth_year) AS "最小出生年"
FROM students
GROUP BY city, gender                            -- 先按城市再按性别细分
ORDER BY city, gender;

.print "=== 5. WHERE 与 HAVING 的分工：过滤行 vs 过滤组 ==="
-- WHERE 在分组前过滤"行"（不能用聚合函数），HAVING 在分组后过滤"组"（可以用聚合函数）
SELECT course_id,
       COUNT(*)              AS "选课人数",
       ROUND(AVG(score), 1)  AS "平均分"
FROM scores
WHERE score >= 40             -- 先剔除 40 分以下（本数据没有，仅演示位置）
GROUP BY course_id
HAVING COUNT(*) >= 3          -- 只要选课人数 >= 3 的课程
ORDER BY "选课人数" DESC, course_id;   -- 并列时补一个决胜列，输出顺序才稳定

.print "=== 6. CASE WHEN：SQL 里的条件分支（类似其他语言的 switch）==="
SELECT s.name AS "姓名", sc.score AS "分数",
       CASE
           WHEN sc.score >= 90 THEN '优秀'
           WHEN sc.score >= 80 THEN '良好'
           WHEN sc.score >= 60 THEN '及格'
           ELSE                   '不及格'
       END AS "等级"
FROM scores sc
JOIN students s ON s.id = sc.student_id
WHERE sc.course_id = 1                         -- 只看 SQL 入门这门课
ORDER BY sc.score DESC;

.print "=== 7. 聚合 + CASE：条件计数与透视 ==="
SELECT course_id,
       COUNT(*)                                  AS "总条数",
       COUNT(CASE WHEN score >= 60 THEN 1 END)   AS "及格数",   -- ELSE 缺省为 NULL，不被 COUNT 计入
       SUM(CASE WHEN score >= 60 THEN 1 ELSE 0 END) AS "及格数(写法二)",
       ROUND(100.0 * AVG(CASE WHEN score >= 60 THEN 1.0 ELSE 0.0 END), 0) AS "及格率%"
FROM scores
GROUP BY course_id;

.print "=== 8. 全体分数段透视：一条查询出报表 ==="
SELECT SUM(score < 60)                    AS "60 分以下",   -- 【SQLite 方言】真值为 1/0，可直接 SUM
       SUM(score >= 60 AND score < 80)    AS "60~79",
       SUM(score >= 80)                   AS "80 分及以上"
FROM scores;

.print "=== 9. 找「至少有一门不及格」的学生（GROUP BY + HAVING 的经典用法）==="
SELECT s.name,
       COUNT(*) AS "不及格门数",
       MIN(sc.score) AS "最低分"
FROM scores sc
JOIN students s ON s.id = sc.student_id
WHERE sc.score < 60           -- 行级过滤：先只留不及格的成绩
GROUP BY s.name               -- 想只看挂科 >= 2 门的学生时，再加 HAVING COUNT(*) >= 2
ORDER BY "不及格门数" DESC, s.name;

.print "=== 10. 数值函数速览：ROUND / ABS / MAX-MIN 极差 ==="
SELECT ROUND(AVG(score), 2)      AS "平均分(2 位小数)",
       ABS(MIN(score) - MAX(score)) AS "极差(最高-最低)",
       MAX(score) - MIN(score)   AS "极差(普通写法)"
FROM scores;
