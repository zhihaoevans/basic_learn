import java.io.IOException;

/*
 * 主题说明：Java 异常处理 —— try/catch/finally、多 catch、异常层级（受检 vs 非受检）、
 *           throw/throws、自定义异常与 try-with-resources 自动关闭资源。
 * 运行命令：java java/10_error/ErrorDemo.java
 * 预期输出（关键行）：
 *   捕获算术异常: / by zero
 *   finally 总会执行（无论是否异常）
 *   自定义异常: 取款失败: 余额不足，差 30.0 元
 */
public class ErrorDemo {

    /** 自定义异常：继承 Exception 成为受检异常，构造器把消息传给 super */
    static class InsufficientBalanceException extends Exception {
        InsufficientBalanceException(String message) {
            super(message);
        }
    }

    /** throws：声明本方法可能抛出的受检异常，交给调用者处理 */
    static void withdraw(double balance, double amount) throws InsufficientBalanceException {
        if (amount > balance) {
            // throw：主动抛出异常对象
            throw new InsufficientBalanceException(
                    "余额不足，差 " + (amount - balance) + " 元");
        }
        System.out.println("取款成功: " + amount);
    }

    /** 模拟一个可关闭资源：演示 try-with-resources */
    static class FakeResource implements AutoCloseable {
        private final String name;
        FakeResource(String name) {
            this.name = name;
            System.out.println("    打开资源 " + name);
        }
        void use() {
            System.out.println("    使用资源 " + name);
        }
        @Override
        public void close() {
            System.out.println("    自动关闭资源 " + name + "（close 由 try-with-resources 调用）");
        }
    }

    public static void main(String[] args) {
        // 知识点 1：try/catch —— 捕获并处理，程序不再崩溃
        try {
            int r = 10 / 0;                        // 这里抛出 ArithmeticException
            System.out.println("不会执行到这里: " + r);
        } catch (ArithmeticException e) {
            System.out.println("[1] 捕获算术异常: " + e.getMessage());
        }

        // 知识点 2：finally —— 无论是否异常都执行，常用于清理
        try {
            int[] a = new int[2];
            a[5] = 1;                              // 数组越界
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("[2] 捕获越界异常，下标 = " + e.getMessage());
        } finally {
            System.out.println("[2] finally 总会执行（无论是否异常）");
        }

        // 知识点 3：多 catch —— 不同异常分别处理（注意子类异常要写在前面）
        String input = "abc";
        try {
            int n = Integer.parseInt(input);       // NumberFormatException
            System.out.println(10 / (n - 3));      // 可能除零
        } catch (NumberFormatException | ArithmeticException e) {
            // JDK 7+ 的多类型 catch（按位或写法），两类异常共用同一段处理
            System.out.println("[3] 多 catch（合并写法）: " + input + " 无法安全计算 -> " + e.getClass().getSimpleName());
        }

        // 知识点 4：异常层级 —— Throwable 分 Error / Exception；Exception 又分受检与非受检
        //   受检（如 IOException）：编译器强制 try 或 throws；非受检（如 RuntimeException）：不强制
        System.out.println("[4] 层级: ArithmeticException 是 RuntimeException 的子类 -> "
                + (RuntimeException.class.isAssignableFrom(ArithmeticException.class)));
        try {
            throwIOException();                    // 受检异常必须处理
        } catch (IOException e) {
            System.out.println("[4] 受检异常 IOException 被捕获: " + e.getMessage());
        }

        // 知识点 5：throw / throws / 自定义异常
        try {
            withdraw(70.0, 100.0);
        } catch (InsufficientBalanceException e) {
            System.out.println("[5] 自定义异常: 取款失败: " + e.getMessage());
        }

        // 知识点 6：try-with-resources —— 实现 AutoCloseable 的资源放括号里，自动 close
        System.out.println("[6] try-with-resources:");
        try (FakeResource res = new FakeResource("demo.txt")) {
            res.use();
        }                                          // 无需 finally，close 自动调用
    }

    static void throwIOException() throws IOException {
        throw new IOException("磁盘满了（模拟）");
    }
}
