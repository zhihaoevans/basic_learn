/*
 * 主题说明：Java 的第一个程序 —— 打印输出与三种注释写法。
 *           System.out.println 是最常用的控制台输出方式；注释用于解释代码，不参与编译执行。
 * 运行命令：java java/01_hello/Hello.java
 * 预期输出（关键行）：
 *   Hello, Java!
 *   1 + 1 = 2
 */
public class Hello {

    // 单行注释：以 // 开头，到行尾结束，最常用
    public static void main(String[] args) {
        // 知识点 1：System.out.println —— 输出一行内容并换行
        System.out.println("Hello, Java!");

        /* 知识点 2：多行注释（块注释）
           以斜杠星号开头、星号斜杠结尾，中间可以跨多行，
           常用于解释一段逻辑或临时屏蔽代码 */
        System.out.println("1 + 1 = " + (1 + 1));

        // println 也可以打印数字、布尔值等，再用 print 试一下不换行的输出
        System.out.print("同一行");
        System.out.println("输出");

        System.out.println("行数统计: 4 行输出");
    }

    /**
     * 知识点 3：Javadoc 注释 —— 以 /** 开头、星号斜杠结尾，
     * 用于生成官方风格的 API 文档（javadoc 工具），通常写在类和方法上方。
     * 这里是本程序的说明：演示 Java 的三种注释与基本打印。
     */
}
