/*
 * 主题说明：Java 运算符与表达式 —— 算术（整数除法、取余）、自增自减前后缀、
 *           比较运算、逻辑短路、位运算与三元运算符。
 * 运行命令：java java/03_operator/OperatorDemo.java
 * 预期输出（关键行）：
 *   整数除法 7 / 2 = 3 （直接舍去小数）
 *   取余 7 % 2 = 1
 *   ~5 = -6 （按位取反：~x = -x - 1）
 *   短路: 右侧没有被执行
 */
public class OperatorDemo {

    // 用于演示短路的小工具：打印并返回 true
    static boolean touch(String tag) {
        System.out.println("      （右侧 " + tag + " 被求值了）");
        return true;
    }

    public static void main(String[] args) {
        // 知识点 1：算术运算符 —— + - * / %，重点：两个整数相除结果还是整数
        System.out.println("[1] 7 + 2 = " + (7 + 2));
        System.out.println("    7 - 2 = " + (7 - 2));
        System.out.println("    7 * 2 = " + (7 * 2));
        System.out.println("    整数除法 7 / 2 = " + (7 / 2) + " （直接舍去小数）");
        System.out.println("    取余 7 % 2 = " + (7 % 2));
        System.out.println("    想要小数: 7 / 2.0 = " + (7 / 2.0) + " （任一边是浮点即可）");

        // 知识点 2：自增 ++ / 自减 -- 的前缀与后缀区别
        int n = 5;
        int a = n++;   // 后缀：先用旧值，再 +1 —— a=5, n=6
        int b = ++n;   // 前缀：先 +1，再用新值 —— n=7, b=7
        System.out.println("[2] n=5; a=n++ 后 a=" + a + "; b=++n 后 b=" + b + ", n=" + n);

        // 知识点 3：比较运算符 —— 结果是 boolean（true / false）
        System.out.println("[3] 3 < 5 是 " + (3 < 5) + ", 3 == 5 是 " + (3 == 5) + ", 3 != 5 是 " + (3 != 5));

        // 知识点 4：逻辑运算符 &&（与）||（或）!（非），重点：短路求值
        // && 左边为 false 时右边不再执行；|| 左边为 true 时右边不再执行
        boolean r1 = (3 > 5) && touch("&&");
        System.out.println("[4] false && ... = " + r1 + "，短路: 右侧没有被执行");
        boolean r2 = (3 < 5) || touch("||");
        System.out.println("    true || ... = " + r2 + "，同样短路；而不短路的 & | 两边总会执行");

        // 知识点 5：位运算符 —— 按二进制位计算：& 与 | 或 ^ 异或 ~ 取反 << 左移 >> 右移
        int x = 0b1100;   // 12
        int y = 0b1010;   // 10
        System.out.println("[5] 12 & 10 = " + (x & y) + " （1000，按位与）");
        System.out.println("    12 | 10 = " + (x | y) + " （1110，按位或）");
        System.out.println("    12 ^ 10 = " + (x ^ y) + " （0110，异或：不同为 1）");
        System.out.println("    ~5      = " + (~5) + " （按位取反：~x = -x - 1）");
        System.out.println("    1 << 4  = " + (1 << 4) + " （左移相当于乘 2 的 4 次方）");
        System.out.println("    -16 >> 2 = " + (-16 >> 2) + " （带符号右移，保留负号）");
        System.out.println("    -1 >>> 28 = " + (-1 >>> 28) + " （无符号右移，高位补 0）");

        // 知识点 6：三元运算符 条件 ? 值A : 值B —— 一行完成简单分支
        int score = 61;
        String result = score >= 60 ? "及格" : "不及格";
        System.out.println("[6] score=61, 三元判断: " + result);
    }
}
