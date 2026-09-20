package demo;

/*
 * 主题说明：同包工具类 Util —— 与 ModuleDemo 同在 demo 包，演示 Java 的
 *           四种可见性：public / protected / 默认（包私有）/ private。
 * 运行命令：java java/12_module/demo/Util.java
 * 预期输出（关键行）：
 *   Util.APP_NAME = demo-util
 *   Util.helper() = helper(长度 5)
 *
 * 单文件运行约束：用 java xxx.java 直跑时，文件路径末尾目录必须与 package 名一致
 *（本文件声明 package demo，因此位于 demo/ 子目录）；被入口类引用时会按需一起编译。
 */
public class Util {

    /** public 字段：任何包的任何类都能访问 */
    public static final String APP_NAME = "demo-util";

    /** protected 字段：同包的类或任意子类可访问 */
    protected static int callCount = 0;

    /** 默认（包私有）字段：不加修饰符，仅同包类可访问 */
    static String maintainer = "basic_learn";

    /** private 字段：只有 Util 自己能访问，外界拿不到 */
    private static final String SECRET = "hidden";

    /** public 方法：对外暴露的服务 */
    public static String version() {
        callCount++;                                  // 类内部可以自由访问所有字段
        return "1.0 (第 " + callCount + " 次调用)";
    }

    /** protected 方法：同包（或子类）可调用 */
    protected static String helper() {
        // private 的 SECRET 只能在本类内部使用，间接对外提供信息
        return "helper(长度 " + SECRET.length() + ")";
    }

    /** 包私有方法：仅 demo 包内的类能调用，包外不可见 */
    static String packageOnly() {
        return "package-only: 仅同包可调用，维护者=" + maintainer;
    }

    /** 单独直跑本文件时的入口（CI 会逐个运行每个 .java 文件） */
    public static void main(String[] args) {
        System.out.println("Util.APP_NAME = " + APP_NAME);
        System.out.println("Util.helper() = " + helper());
    }
}
