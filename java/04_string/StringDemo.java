/*
 * 主题说明：Java 字符串操作 —— 拼接、常用方法（length/charAt/substring/indexOf）、
 *           equals 与 == 的区别、StringBuilder、String.format 与文本块（"""）。
 * 运行命令：java java/04_string/StringDemo.java
 * 预期输出（关键行）：
 *   equals 比较内容: true
 *   == 比较引用: false
 *   format: 你好 Java，第 3 天
 */
public class StringDemo {

    public static void main(String[] args) {
        // 知识点 1：字符串拼接 —— + 号最直接；字符串不可变（immutable），拼接产生新对象
        String first = "Java";
        String s = "Hello, " + first + "!";
        System.out.println("[1] 拼接: " + s);

        // 知识点 2：常用方法
        System.out.println("[2] length() = " + s.length() + " （字符个数）");
        System.out.println("    charAt(0) = " + s.charAt(0));
        System.out.println("    substring(7) = " + s.substring(7) + " （从下标 7 到结尾）");
        System.out.println("    substring(0, 5) = " + s.substring(0, 5) + " （下标 [0,5) 左闭右开）");
        System.out.println("    indexOf(\"Java\") = " + s.indexOf("Java") + " （首次出现位置，找不到返回 -1）");
        System.out.println("    toUpperCase() = " + s.toUpperCase());
        System.out.println("    replace('l', 'L') = " + s.replace('l', 'L'));

        // 知识点 3：equals 与 == 的区别 —— 面试高频
        String a = new String("Java");
        String b = new String("Java");
        System.out.println("[3] equals 比较内容: " + a.equals(b));
        System.out.println("    == 比较引用: " + (a == b) + " （两个 new 出来的对象地址不同）");
        System.out.println("    结论：比较字符串内容一律用 equals，不要用 ==");

        // 知识点 4：StringBuilder —— 循环里反复拼接时用它，避免产生大量中间对象
        StringBuilder sb = new StringBuilder();
        for (int i = 1; i <= 3; i++) {
            sb.append("第").append(i).append("段 ");
        }
        System.out.println("[4] StringBuilder: " + sb.toString());
        sb.insert(0, "【开头】");     // 任意位置插入
        sb.reverse();                // 反转
        System.out.println("    插入并反转后: " + sb);

        // 知识点 5：String.format —— 格式化生成字符串（类似 C 的 printf）
        String name = "Java";
        int day = 3;
        String fmt = String.format("你好 %s，第 %d 天", name, day);
        System.out.println("[5] format: " + fmt);
        System.out.printf("    printf 直接输出: %.2f%n", 3.14159);   // 保留两位小数

        // 知识点 6：文本块（Text Block，JDK 15+）—— 三个双引号，保留换行与缩进
        String json = """
                {
                  "language": "Java",
                  "version": 21
                }""";
        System.out.println("[6] 文本块（多行字符串）:");
        System.out.println(json);
    }
}
