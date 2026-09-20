-- 主题说明：单表查询 —— SELECT 投影与表达式、WHERE 精确/组合条件、LIKE 模糊匹配、
--           BETWEEN/IN 范围与集合、NULL 判断（IS NULL）、ORDER BY 排序、LIMIT/OFFSET 分页、
--           DISTINCT 去重，以及常用字符串/日期函数。本文件只读不改数据，可任意重复执行。
-- 运行命令：sqlite3 sql/db.sqlite < sql/01_select.sql
-- 预期结果：依次打印各知识点的查询结果；关键行：92 分的张伟、LIKE 命中的北京学生、
--           55/48/58/59 四个不及格分数、email 为空的学生（3/4/7 号）、按多列排序的课程表。

.headers on
.mode column

.print "=== 1. 投影：选择列、表达式与别名 ==="
-- SELECT 后跟列名（而不是 *）称为投影；可以写表达式并用 AS 起别名
SELECT name AS "姓名",
       birth_year AS "出生年",
       2025 - birth_year AS "年龄",
       city || '·' || name AS "城市与姓名"     -- || 是 SQL 标准的字符串拼接运算符
FROM students;

.print "=== 2. WHERE：精确条件与 AND/OR/NOT 组合 ==="
SELECT name, city, birth_year
FROM students
WHERE city = '北京' AND birth_year <= 2003;   -- 北京且 2003 年及以前出生

SELECT student_id, course_id, score
FROM scores
WHERE score >= 60 AND (course_id = 1 OR course_id = 2)   -- 括号控制优先级，等价于 IN (1, 2)
ORDER BY course_id, student_id;

.print "=== 3. LIKE 模糊匹配：% 匹配任意串，_ 匹配单个字符 ==="
SELECT name, email
FROM students
WHERE email LIKE '%@example.com'              -- 以 @example.com 结尾的任意邮箱
ORDER BY name;                                -- 没写 ORDER BY 时行的先后顺序是不保证的，要稳定输出就显式排序

SELECT name
FROM students
WHERE name LIKE '_娜';                        -- 两个字符且第二个字是"娜"

-- 【SQLite 方言】LIKE 对 ASCII 字母不区分大小写（其他数据库通常区分）；
-- 需要区分大小写可用 GLOB（通配符 * 和 ? 的写法同 shell）
SELECT 'SQL 入门' LIKE '%sql%' AS "LIKE 不区分大小写",   -- 1（真）
       'SQL 入门' GLOB  '*sql*' AS "GLOB 区分大小写";     -- 0（假）

.print "=== 4. 范围与集合：BETWEEN（闭区间）与 IN ==="
SELECT student_id, course_id, score
FROM scores
WHERE score BETWEEN 85 AND 95                 -- 双端都包含：85 和 95 本身也命中
ORDER BY score DESC, student_id, course_id;

SELECT name, city
FROM students
WHERE city IN ('北京', '杭州')                -- 集合成员判断，比多个 OR 清晰
ORDER BY city, name;

.print "=== 5. NULL 判断：只能用 IS NULL / IS NOT NULL ==="
SELECT name, email
FROM students
WHERE email IS NULL;                          -- 3/4/7 号学生没有邮箱

-- 陷阱演示：NULL 与任何值比较结果都是 UNKNOWN（不是真也不是假），= NULL 永远查不出来
SELECT COUNT(*) AS "email = NULL 命中数（错误写法）" FROM students WHERE email = NULL;    -- 0
SELECT COUNT(*) AS "email IS NULL 命中数（正确写法）" FROM students WHERE email IS NULL; -- 3

.print "=== 6. ORDER BY：多列排序，ASC 升序 / DESC 降序 ==="
SELECT title, credit, teacher
FROM courses
ORDER BY credit DESC, title ASC;              -- 先按学分降序，学分相同再按课程名升序

.print "=== 7. LIMIT 与 OFFSET：分页 ==="
SELECT student_id, course_id, score
FROM scores
ORDER BY score DESC
LIMIT 3 OFFSET 0;                             -- 第 1 页：成绩前 3 名

SELECT student_id, course_id, score
FROM scores
ORDER BY score DESC
LIMIT 3 OFFSET 3;                             -- 第 2 页：跳过前 3 条再取 3 条

.print "=== 8. DISTINCT：结果集去重 ==="
SELECT DISTINCT city FROM students ORDER BY city;         -- 学生来自哪些城市
SELECT COUNT(DISTINCT city) AS "不同城市数" FROM students; -- 去重后计数：5

.print "=== 9. 常用字符串函数速览 ==="
SELECT name,
       UPPER('a' || name)       AS "拼接后转大写",   -- UPPER/LOWER 仅对 ASCII 生效
       LENGTH(name)             AS "字符数",
       SUBSTR(name, 1, 1)       AS "取第 1 个字",
       REPLACE(name, '伟', 'W') AS "替换",
       TRIM('  两端空白  ')      AS "去两端空白"
FROM students
WHERE id <= 3;

.print "=== 10. 常用日期函数速览（TEXT 存日期的配套工具）==="
SELECT date('now')                        AS "今天",
       strftime('%Y-%m', 'now')           AS "年月",
       date('2025-04-10', '+7 days')      AS "期中后一周",
       CAST(julianday('2025-06-20') - julianday('2025-04-10') AS INTEGER) AS "两场考试间隔天数";

.print "=== 11. 综合：一条查询串起本主题全部子句 ==="
-- 执行顺序：FROM → WHERE → SELECT（投影/DISTINCT）→ ORDER BY → LIMIT
SELECT DISTINCT city AS "有 2003 年出生女生的城市"
FROM students
WHERE gender = '女' AND birth_year = 2003
ORDER BY city
LIMIT 5;
