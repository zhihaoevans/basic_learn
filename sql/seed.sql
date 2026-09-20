-- 主题说明：建库脚本 —— 创建 students / courses / scores 三张表，集中演示 SQLite 建表与约束：
--           INTEGER PRIMARY KEY（rowid 别名）、NOT NULL、UNIQUE、CHECK、DEFAULT、联合主键、外键，
--          并写入供 01~08 各主题文件复用的样例数据（8 名学生、5 门课、22 条成绩）。
-- 运行命令：sqlite3 sql/db.sqlite < sql/seed.sql
-- 预期结果：无任何报错，末尾 SELECT 打印三张表的行数与样例数据；
--           脚本可重复执行（DROP TABLE IF EXISTS 后重建，数据回到初始状态）。

-- 【SQLite 方言】外键约束默认不强制执行，需要每个连接手动开启（只对当前连接有效）
PRAGMA foreign_keys = ON;

-- 幂等保证：先删旧表再重建（先删引用方 scores，再删被引用方，配合上面的外键开关不会报错）
DROP TABLE IF EXISTS scores;
DROP TABLE IF EXISTS courses;
DROP TABLE IF EXISTS students;

-- 表 1：学生表 —— 主键、非空、CHECK 枚举、唯一约束、可空列
CREATE TABLE students (
    id         INTEGER PRIMARY KEY,                             -- INTEGER PRIMARY KEY 是 rowid 的别名，插入时可省略自动分配
    name       TEXT    NOT NULL,                                -- 非空约束
    gender     TEXT    NOT NULL CHECK (gender IN ('男', '女')), -- CHECK 约束：只允许枚举值
    city       TEXT    NOT NULL,
    birth_year INTEGER CHECK (birth_year BETWEEN 1995 AND 2010),-- CHECK 约束：范围校验
    email      TEXT,                                            -- 可空列：部分学生没有邮箱，供空值查询演示
    UNIQUE (name, birth_year)                                   -- 唯一约束：同名同出生年视为重复
);

-- 表 2：课程表 —— 唯一列、DEFAULT 默认值、CHECK 范围
CREATE TABLE courses (
    id      INTEGER PRIMARY KEY,
    title   TEXT    NOT NULL UNIQUE,                    -- 课程名唯一
    credit  INTEGER NOT NULL DEFAULT 2 CHECK (credit BETWEEN 1 AND 5), -- 学分 1~5，缺省 2
    teacher TEXT    NOT NULL
);

-- 表 3：成绩表 —— 典型的"关系表"：联合主键 + 两个外键
CREATE TABLE scores (
    student_id INTEGER NOT NULL REFERENCES students(id), -- 外键：必须指向已存在的学生
    course_id  INTEGER NOT NULL REFERENCES courses(id),  -- 外键：必须指向已存在的课程
    score      REAL    NOT NULL CHECK (score BETWEEN 0 AND 100),
    exam_date  TEXT    NOT NULL,                         -- 【SQLite 方言】没有专门日期类型，约定用 TEXT 存 ISO 格式日期
    PRIMARY KEY (student_id, course_id)                  -- 联合主键：一名学生一门课只能有一条成绩
);

-- 样例数据：8 名学生（7 号赵磊是转学生，刻意没有任何成绩，供 LEFT JOIN 演示）
INSERT INTO students (id, name, gender, city, birth_year, email) VALUES
    (1, '张伟', '男', '北京', 2003, 'zhangwei@example.com'),
    (2, '李娜', '女', '上海', 2004, 'lina@example.com'),
    (3, '王芳', '女', '北京', 2003, NULL),
    (4, '刘强', '男', '广州', 2002, NULL),
    (5, '陈静', '女', '深圳', 2004, 'chenjing@example.com'),
    (6, '杨洋', '男', '杭州', 2003, 'yangyang@example.com'),
    (7, '赵磊', '男', '北京', 2005, NULL),
    (8, '孙丽', '女', '上海', 2003, 'sunli@example.com');

-- 5 门课（5 号算法设计只有 2 人选，供聚合/连接时观察数据稀疏）
INSERT INTO courses (id, title, credit, teacher) VALUES
    (1, 'SQL 入门',    3, '王老师'),
    (2, '数据结构',    4, '李老师'),
    (3, '操作系统',    4, '张老师'),
    (4, '计算机网络',  3, '刘老师'),
    (5, '算法设计',    5, '陈老师');

-- 22 条成绩：1~4 号有不及格记录（55/48/58/59），供 WHERE / HAVING / 窗口排名演示
INSERT INTO scores (student_id, course_id, score, exam_date) VALUES
    (1, 1, 92, '2025-04-10'),
    (1, 2, 85, '2025-04-10'),
    (1, 3, 78, '2025-06-20'),
    (1, 4, 88, '2025-06-20'),
    (2, 1, 95, '2025-04-10'),
    (2, 2, 90, '2025-04-10'),
    (2, 3, 82, '2025-06-20'),
    (2, 4, 91, '2025-06-20'),
    (2, 5, 89, '2025-06-20'),
    (3, 1, 88, '2025-04-10'),
    (3, 2, 76, '2025-04-10'),
    (4, 1, 55, '2025-04-10'),
    (4, 2, 48, '2025-04-10'),
    (4, 3, 62, '2025-06-20'),
    (5, 1, 73, '2025-04-10'),
    (5, 3, 81, '2025-06-20'),
    (5, 4, 66, '2025-06-20'),
    (6, 2, 58, '2025-04-10'),
    (6, 4, 71, '2025-06-20'),
    (8, 1, 64, '2025-04-10'),
    (8, 2, 59, '2025-04-10'),
    (8, 5, 77, '2025-06-20');

-- 末尾用 SELECT 展示建库结果
.headers on
.mode column

.print "=== 建库完成，三张表行数 ==="
SELECT (SELECT COUNT(*) FROM students) AS "学生数",
       (SELECT COUNT(*) FROM courses)  AS "课程数",
       (SELECT COUNT(*) FROM scores)   AS "成绩数";

.print "=== students 样例（前 3 行）==="
SELECT * FROM students ORDER BY id LIMIT 3;

.print "=== courses 全部 ==="
SELECT * FROM courses;

.print "=== scores 样例（前 5 行）==="
SELECT * FROM scores ORDER BY student_id, course_id LIMIT 5;
