-- 主题说明：索引与执行计划 —— CREATE INDEX 建索引、EXPLAIN QUERY PLAN 查看查询将如何执行、
--           建索引前后 SCAN（全表扫描）→ SEARCH（索引查找）的对比、主键/UNIQUE 自带的自动索引、
--           覆盖索引（COVERING INDEX，只读索引不回表）、复合索引的最左前缀，以及索引的代价。
--           为保证可重复执行：先 DROP 上次运行留下的演示索引，再走一遍「建前/建后」对比。
-- 运行命令：sqlite3 sql/db.sqlite < sql/08_index_explain.sql
-- 预期结果：无索引时按城市查学生显示「SCAN students」；建 idx_students_city 后变为「SEARCH ... USING INDEX」；
--           按联合主键左列查成绩走的是主键自带的 sqlite_autoindex；复合索引让查询变成
--           「USING COVERING INDEX」；只按复合索引第二列查仍回到 SCAN；连接查询中成绩表从 SCAN 变为 SEARCH。

.headers on
.mode column

-- 幂等：清掉上次运行留下的演示索引，保证每次都能看到「建索引前」的真实计划
DROP INDEX IF EXISTS idx_students_city;
DROP INDEX IF EXISTS idx_scores_student;
DROP INDEX IF EXISTS idx_scores_student_score;
DROP INDEX IF EXISTS idx_scores_course;

.print "=== 1. EXPLAIN QUERY PLAN：先看查询打算怎么跑 ==="
-- detail 列读法：SCAN 表名 = 全表逐行扫；SEARCH 表名 USING INDEX 索引名 = 走索引定位
-- city 列没有任何索引，是最干净的「全表扫描」示例
EXPLAIN QUERY PLAN SELECT * FROM students WHERE city = '北京';

.print "=== 2. 建索引 ==="
-- 索引建在「经常出现在 WHERE / JOIN ON / ORDER BY 里的列」上；IF NOT EXISTS 保证语句可重复执行
CREATE INDEX IF NOT EXISTS idx_students_city ON students(city);

.print "=== 3. 建索引后：同一查询的计划 ==="
EXPLAIN QUERY PLAN SELECT * FROM students WHERE city = '北京';
-- 对比第 1 步：SCAN（逐行扫全表）→ SEARCH USING INDEX（在索引里直接定位，数据量越大差距越大）

.print "=== 4. 主键 / UNIQUE 自带的「自动索引」==="
-- scores 的联合主键 (student_id, course_id) 会让 SQLite 自动建一个唯一索引 sqlite_autoindex_scores_1，
-- 所以按 student_id（主键最左列）查天生就走索引，不用手工建任何东西
EXPLAIN QUERY PLAN SELECT * FROM scores WHERE student_id = 2;

.print "=== 5. 覆盖索引：查询要的列全在索引里，连表都不用回 ==="
-- 这个查询只要 student_id 和 score 两列，若都装进一个复合索引，就无需再回 scores 表取数
EXPLAIN QUERY PLAN SELECT student_id, score FROM scores WHERE student_id = 2;  -- 走主键自动索引：还要回表
CREATE INDEX IF NOT EXISTS idx_scores_student_score ON scores(student_id, score);
EXPLAIN QUERY PLAN SELECT student_id, score FROM scores WHERE student_id = 2;  -- 复合索引：COVERING

.print "=== 6. 复合索引与最左前缀 ==="
-- 复合索引 (student_id, score) 按「先 student_id 再 score」排序，相当于电话簿按姓+名排
-- 能服务：WHERE student_id = ? ；WHERE student_id = ? AND score > ?
-- 不能有效服务：只按第二列查（WHERE score > ?，相当于只知名字翻电话簿）→ 仍然 SCAN
EXPLAIN QUERY PLAN SELECT * FROM scores WHERE score > 90;

.print "=== 7. 连接查询的执行计划 ==="
-- 未建课程索引前：成绩表只能全表扫
EXPLAIN QUERY PLAN
SELECT s.name, c.title, sc.score
FROM scores sc
JOIN students s ON s.id = sc.student_id
JOIN courses  c ON c.id = sc.course_id
WHERE c.title = 'SQL 入门';

CREATE INDEX IF NOT EXISTS idx_scores_course ON scores(course_id);

.print "--- 建了课程索引后 ---"
EXPLAIN QUERY PLAN
SELECT s.name, c.title, sc.score
FROM scores sc
JOIN students s ON s.id = sc.student_id
JOIN courses  c ON c.id = sc.course_id
WHERE c.title = 'SQL 入门';
-- 三行计划各管一段：courses 按 title 的 UNIQUE 自动索引定位 → scores 换成走 idx_scores_course
-- → students 按 INTEGER PRIMARY KEY（rowid）定位

.print "=== 8. 现有索引清单与要点速记 ==="
SELECT name AS "students/scores 表上的索引" FROM sqlite_master
WHERE type = 'index' AND tbl_name IN ('students', 'scores')
ORDER BY tbl_name, name;

-- 要点：
-- 1) 索引加速读、拖慢写（每次 INSERT/UPDATE/DELETE 都要同步维护索引），也别忘了它占磁盘
-- 2) 小表全表扫可能更快（本例几十行只是演示语法，数据量上来后差距才明显）
-- 3) WHERE 里对列做函数/运算（如 WHERE UPPER(name) = 'A'）会让普通索引失效
-- 4) EXPLAIN QUERY PLAN 是 SQLite 官方推荐的「看懂查询」第一步，优化前先看计划
SELECT '演示结束：三枚演示索引已留在库里，重跑本文件会先 DROP 再重建' AS "说明";
