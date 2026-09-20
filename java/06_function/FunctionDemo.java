import java.util.function.Function;
import java.util.function.Predicate;

/*
 * 主题说明：Java 的"函数"（方法）—— 定义与重载、可变参数、返回值，
 *           以及 Lambda 表达式（Function/Predicate 函数式接口）与方法引用。
 * 运行命令：java java/06_function/FunctionDemo.java
 * 预期输出（关键行）：
 *   add(3, 5) = 8
 *   sum(1, 2, 3) = 6
 *   Function 平方: 9
 *   Predicate 判断: abc 是不是长度>2 -> true
 *   方法引用转大写: ABC
 */
public class FunctionDemo {

    // 知识点 1：方法定义 —— 修饰符 返回类型 方法名(参数列表)
    static int add(int a, int b) {
        return a + b;                     // return 返回结果并结束方法
    }

    // 知识点 2：方法重载（overload）—— 同名不同参数（个数或类型不同），编译器按实参选择
    static double add(double a, double b) {
        return a + b;
    }

    // 知识点 3：可变参数 —— 类型后跟 ...，方法内当数组用；只能放参数表最后
    static int sum(int... numbers) {
        int total = 0;
        for (int v : numbers) {
            total += v;
        }
        return total;
    }

    // 无返回值方法用 void
    static void greet(String name) {
        System.out.println("你好, " + name + "!");
    }

    public static void main(String[] args) {
        // 知识点 1：调用并接收返回值
        int r = add(3, 5);
        System.out.println("[1] add(3, 5) = " + r);

        // 知识点 2：重载 —— 同一个名字，按参数类型匹配到不同版本
        System.out.println("[2] 重载 add(2.5, 1.5) = " + add(2.5, 1.5));

        // 知识点 3：可变参数 —— 传任意个实参
        System.out.println("[3] sum(1, 2, 3) = " + sum(1, 2, 3));
        System.out.println("    sum() = " + sum() + "，不传也行");
        greet("方法");

        // 知识点 4：Lambda 表达式 —— (参数) -> 表达式，是把"一段行为"当值传递
        // Function<T, R>：接收 T 返回 R —— 标准函数式接口之一
        Function<Integer, Integer> square = x -> x * x;
        System.out.println("[4] Function 平方: " + square.apply(3));

        // Predicate<T>：接收 T 返回 boolean，常用于条件判断/过滤
        Predicate<String> isLong = s -> s.length() > 2;
        System.out.println("[4] Predicate 判断: abc 是不是长度>2 -> " + isLong.test("abc"));

        // 知识点 5：方法引用 —— Lambda 的简写，直接引用已有方法，形式：类名::方法名
        Function<String, Integer> len = String::length;       // 等价于 s -> s.length()
        Function<String, String> upper = String::toUpperCase; // 等价于 s -> s.toUpperCase()
        System.out.println("[5] 方法引用取长度: " + len.apply("hello"));
        System.out.println("    方法引用转大写: " + upper.apply("abc"));
    }
}
