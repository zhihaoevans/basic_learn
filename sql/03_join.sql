-- 主题说明：多表连接 —— INNER JOIN 内连接（只留两表都匹配的行）、LEFT JOIN 左连接（保留左表全部行）、
--           三表连接（学生-成绩-课程的经典链路）、自连接（self join，表和自己连接，用小演示表），
--           以及连接 + 聚合的组合用法。除自连接用自带演示表（每次重建）外，只读不改主数据，可重复执行。
-- 运行命令：sqlite3 sql/db.sqlite < sql/03_join.sql
-- 预期结果：三表连接输出 22 行带姓名课程名的成绩；LEFT JOIN 输出 23 行，其中 7 号赵磊成绩列为 NULL；
--           自连接输出 5 行员工-上级配对（校长的上级为 NULL）；每门课统计里 SQL 入门 6 人平均 77.8。

.headers on
.mode column

.print "=== 1. INNER JOIN：两表连接，只保留两边都能匹配上的行 ==="
-- 成绩表只有编号，连上学生表才有姓名；ON 写连接条件，表可用 AS 起别名
SELECT s.name AS "姓名", sc.course_id AS "课程号", sc.score AS "分数"
FROM scores sc
JOIN students s ON s.id = sc.student_id        -- JOIN 是 INNER JOIN 的简写
WHERE sc.course_id = 5
ORDER BY sc.score DESC;

.print "=== 2. 三表连接：把编号全部翻译成可读名称 ==="
SELECT s.name  AS "姓名",
       c.title AS "课程",
       c.credit AS "学分",
       sc.score AS "分数",
       sc.exam_date AS "考试日期"
FROM scores sc
JOIN students s ON s.id = sc.student_id        -- 成绩 → 学生
JOIN courses  c ON c.id = sc.course_id         -- 成绩 → 课程
ORDER BY s.id, c.id;

.print "=== 3. LEFT JOIN：保留左表全部行，右表没匹配上就补 NULL ==="
-- 7 号赵磊没有任何成绩：INNER JOIN 会把他"弄丢"，LEFT JOIN 能查出来
SELECT s.name AS "姓名", COUNT(sc.score) AS "有成绩的门数"
FROM students s
LEFT JOIN scores sc ON sc.student_id = s.id    -- 左表 students 全保留
GROUP BY s.name
ORDER BY "有成绩的门数", s.name;

.print "=== 4. LEFT JOIN + IS NULL：反连接，找「没有成绩」的学生 ==="
SELECT s.name AS "姓名", s.city AS "城市"
FROM students s
LEFT JOIN scores sc ON sc.student_id = s.id
WHERE sc.score IS NULL;                        -- 右表列是 NULL = 没匹配上

.print "=== 5. 自连接：表与自己连接（演示表每次重建，保证可重复执行）==="
-- 组织架构表：manager_id 指向本表 id；自连接把「员工 → 上级」两行接成一行
DROP TABLE IF EXISTS emp_demo;
CREATE TABLE emp_demo (
    id         INTEGER PRIMARY KEY,
    name       TEXT    NOT NULL,
    manager_id INTEGER REFERENCES emp_demo(id) -- 自引用外键，构成树形结构
);
INSERT INTO emp_demo (id, name, manager_id) VALUES
    (1, '校长',     NULL),
    (2, '教务主任', 1),
    (3, '王老师',   2),
    (4, '李老师',   2),
    (5, '陈老师',   3);

-- 同一张表起两个别名，当成"员工表"和"上级表"两张表用
SELECT e.name AS "员工",
       IFNULL(m.name, '（无上级）') AS "上级"    -- IFNULL：NULL 时给默认值
FROM emp_demo e
LEFT JOIN emp_demo m ON e.manager_id = m.id    -- 必须用 LEFT JOIN，否则校长（上级为 NULL）会丢失
ORDER BY e.id;

.print "=== 6. 连接 + 聚合：每门课的选课人数与平均分（带课程名）==="
SELECT c.title AS "课程",
       COUNT(sc.score)            AS "选课人数",   -- COUNT(列) 不数 LEFT JOIN 凑出来的 NULL
       ROUND(AVG(sc.score), 1)    AS "平均分",
       MAX(sc.score)              AS "最高分"
FROM courses c
LEFT JOIN scores sc ON sc.course_id = c.id
GROUP BY c.title
ORDER BY "选课人数" DESC, c.title;

.print "=== 7. 每个学生总分排行（连接 + 聚合 + 排序 + 分页）==="
SELECT s.name AS "姓名",
       s.city AS "城市",
       SUM(sc.score) AS "总分",
       ROUND(AVG(sc.score), 1) AS "平均分"
FROM students s
JOIN scores sc ON sc.student_id = s.id          -- 内连接：没成绩的学生不参与总分排行
GROUP BY s.id, s.name, s.city
ORDER BY "总分" DESC
LIMIT 3;
