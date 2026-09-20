/*
 * 主题说明：Java 的变量与数据类型 —— 8 种基本类型、String、final 常量、
 *           var 局部类型推断，以及隐式类型转换与显式强制转换（cast）。
 * 运行命令：java java/02_variable/VariableDemo.java
 * 预期输出（关键行）：
 *   int 最大值 = 2147483647
 *   隐式转换: long 接住 int -> 100
 *   显式强转: 3.99 -> 3 （直接截断，不四舍五入）
 */
public class VariableDemo {

    public static void main(String[] args) {
        // 知识点 1：var 局部类型推断（JDK 10+）—— 编译器根据右侧的值推断类型
        // 只能用于局部变量，仍是一种静态类型：var name = "Java"; 推断为 String
        var language = "Java";          // 推断为 String
        var year = 2026;                // 推断为 int
        System.out.println("[1] var 推断: " + language + " " + year);

        // 知识点 2：8 种基本类型（primitive types）
        byte  tiny   = 127;                     // 1 字节整数
        short small  = 32_000;                  // 2 字节整数
        int   count  = 2_147_483_647;           // 4 字节整数（最常用）
        long  big    = 9_000_000_000L;          // 8 字节整数，字面量加 L
        float pi     = 3.14f;                   // 4 字节浮点，字面量加 f
        double precise = 3.141592653589793;     // 8 字节浮点（默认浮点类型）
        char  letter = 'A';                     // 2 字节 Unicode 字符，单引号
        boolean ok   = true;                    // 真 / 假
        System.out.println("[2] byte=" + tiny + ", short=" + small + ", int最大值=" + count);
        System.out.println("    long=" + big + ", float=" + pi + ", double=" + precise);
        System.out.println("    char=" + letter + ", boolean=" + ok);

        // 知识点 3：String 引用类型（不是基本类型），双引号包裹
        String greeting = "你好, " + language;  // + 号拼接字符串
        System.out.println("[3] String: " + greeting + ", 长度=" + greeting.length());

        // 知识点 4：final 常量 —— 只能赋值一次，习惯上全大写
        final double TAX_RATE = 0.13;
        // TAX_RATE = 0.2;  // 取消注释会编译错误：无法为最终变量赋值
        double price = 100.0;
        System.out.println("[4] final 常量: 100 元含税价 = " + price * (1 + TAX_RATE));

        // 知识点 5：隐式类型转换（小容量 -> 大容量，自动完成，不丢精度）
        int i = 100;
        long l = i;        // int -> long：自动放宽（widening）
        double d = l;      // long -> double：自动放宽
        System.out.println("[5] 隐式转换: long 接住 int -> " + l + ", 再变 double -> " + d);

        // 知识点 6：显式强制转换（大容量 -> 小容量，需要写 (目标类型)，可能丢精度）
        double weight = 3.99;
        int truncated = (int) weight;       // double -> int：小数部分直接截断
        long bigValue = 100_000_000_000L;
        int narrowed = (int) bigValue;      // long -> int：溢出后数值回绕
        System.out.println("[6] 显式强转: " + weight + " -> " + truncated + " （直接截断，不四舍五入）");
        System.out.println("    溢出示例: " + bigValue + " 强转 int -> " + narrowed);
    }
}
