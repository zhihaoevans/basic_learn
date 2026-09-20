/*
 * 主题说明：Java 特色主题 —— record 记录类与模式匹配（需 JDK 21+）。
 *           record 一行定义不可变数据载体；紧凑构造器做校验；
 *           record 解构与 switch 模式匹配让类型判断像写数学式子一样直白。
 * 运行命令：java java/16_records/RecordsDemo.java   （本示例需要 JDK 21 或更高版本）
 * 预期输出（关键行）：
 *   Point[x=3, y=4]
 *   解构: x=3, y=4
 *   紧凑构造器校验通过: Range[lo=1, hi=10]
 *   switch 模式匹配: 坐标(3, 4)
 */
public class RecordsDemo {

    /** 知识点 1：record 定义 —— 一行顶一个类：自动生成构造器/访问器/equals/hashCode/toString */
    record Point(int x, int y) {
        // 组件访问器自动生成：point.x() / point.y()（注意不是 getX()）
    }

    /** 知识点 2：紧凑构造器（compact constructor）—— 不写参数列表，只放校验/规范化逻辑 */
    record Range(int lo, int hi) {
        Range {                                    // 注意：Range 后面没有括号
            if (lo > hi) {                         // 校验不合法就直接抛异常
                throw new IllegalArgumentException("lo 不能大于 hi: " + lo + " > " + hi);
            }
        }
    }

    /** record 可以嵌套 —— 解构嵌套记录时会逐层拆开 */
    record Line(Point start, Point end) {}

    public static void main(String[] args) {
        // 知识点 1：record 是不可变数据载体 —— toString/equals 都是现成的
        Point p = new Point(3, 4);
        System.out.println("[1] " + p);                       // 自动 toString: Point[x=3, y=4]
        System.out.println("[1] 访问器: x()=" + p.x() + ", y()=" + p.y());
        System.out.println("[1] 值相等: " + new Point(3, 4).equals(p) + "（自动 equals）");

        // 知识点 2：紧凑构造器 —— 非法数据在构造时就被拦下
        System.out.println("[2] 紧凑构造器校验通过: " + new Range(1, 10));
        try {
            new Range(10, 1);                                  // lo > hi，触发校验
        } catch (IllegalArgumentException e) {
            System.out.println("[2] 紧凑构造器拦截非法数据: " + e.getMessage());
        }

        // 知识点 3：record 解构（record patterns，JDK 21）—— instanceof 直接把组件拆成变量
        Object obj = p;
        if (obj instanceof Point(int x, int y)) {              // 一行完成"判断类型 + 拆组件"
            System.out.println("[3] 解构: x=" + x + ", y=" + y);
        }

        // 嵌套解构：Line 里装着两个 Point，可以一层层拆到底
        Object shape = new Line(new Point(0, 0), new Point(3, 4));
        if (shape instanceof Line(Point s, Point e)) {         // 外层先拆，内层接着拆
            System.out.println("[3] 嵌套解构: 起点" + s + " 终点" + e
                    + "，长度^2 = " + (e.x() - s.x()) * (e.x() - s.x())
                    + "+" + (e.y() - s.y()) * (e.y() - s.y()));
        }

        // 知识点 4：switch 表达式 + 模式匹配（JDK 21）—— 按类型分派，还能加 when 条件
        Object[] values = {p, "你好", 42, new Range(1, 10)};
        for (Object v : values) {
            String desc = switch (v) {                          // switch 是表达式，有返回值
                case Point(int x, int y) -> "坐标(" + x + ", " + y + ")";   // 类型 + 解构
                case String s when s.length() > 1 -> "长字符串: " + s;      // when 守卫条件
                case String s -> "短字符串: " + s;
                case Integer i -> "整数: " + i;
                case null -> "空值";                             // 连 null 都能单独处理
                default -> "其他: " + v;
            };
            System.out.println("[4] switch 模式匹配: " + desc);
        }

        System.out.println("[5] 提示: 本文件用了 JDK 21 正式特性（record patterns / "
                + "switch 模式匹配），低于 21 的 JDK 无法编译运行");
    }
}
