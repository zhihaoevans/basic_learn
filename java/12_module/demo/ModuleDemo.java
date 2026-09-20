package demo;

import static demo.Util.APP_NAME;        // 静态导入字段：之后直接写 APP_NAME，不用 Util.APP_NAME
import static demo.Util.version;         // 静态导入方法：直接调用 version()

/*
 * 主题说明：Java 的包（package）与可见性 —— 包是类的组织单位（对应目录结构），
 *           本例与同包的 Util.java 一起演示 public / protected / 包私有 / private
 *           四种访问级别，以及 import 与静态导入。
 * 运行命令：java java/12_module/demo/ModuleDemo.java
 * 预期输出（关键行）：
 *   [1] 包名 = demo
 *   [2] 静态导入字段: APP_NAME = demo-util
 *   [4] private 成员包外不可见，只能通过 Util 的公开方法间接访问
 *
 * 单文件运行约束（重点说明）：
 *   1) java 单文件直跑时，源文件路径的末级目录必须与 package 声明一致 ——
 *      本文件声明 package demo，所以放在 demo/ 子目录，运行命令是
 *      java java/12_module/demo/ModuleDemo.java；
 *   2) 单文件模式只编译入口文件，但引用到的同目录（同包）类（如 Util）
 *      会被自动按需编译，无需手动 javac；
 *   3) 传统方式则是先 javac -d out 编译再 java -cp out demo.ModuleDemo。
 */
public class ModuleDemo {

    public static void main(String[] args) {
        // 知识点 1：包声明 —— 每个 Java 文件第一行声明自己所属的包
        System.out.println("[1] 包名 = " + ModuleDemo.class.getPackage().getName());

        // 知识点 2：静态导入 —— import static 包名.类名.成员，直接用短名
        System.out.println("[2] 静态导入字段: APP_NAME = " + APP_NAME);
        System.out.println("[2] 静态导入方法: version() -> " + version());

        // 知识点 3：跨类访问与可见性（ModuleDemo 与 Util 同在 demo 包）
        // public：任何地方可访问
        System.out.println("[3a] public: Util.APP_NAME = " + Util.APP_NAME);
        // protected + 默认（包私有）：因为同包，所以都能访问到
        System.out.println("[3b] protected: Util.callCount = " + Util.callCount);
        System.out.println("[3c] 包私有: Util.packageOnly() -> " + Util.packageOnly());
        // private：只属于 Util 自己 —— 下面这行取消注释会编译报错：
        // System.out.println(Util.SECRET);   // 错误: SECRET 在 demo.Util 中是 private 的
        System.out.println("[4] private 成员包外不可见，只能通过 Util 的公开方法间接访问");

        // 知识点 5：普通 import —— 使用其他包的类时引入全限定名（本文件顶部已示范）：
        // import java.util.List; 之后即可写 List<String> 而不用 java.util.List<String>
        java.util.List<String> full = java.util.List.of("不 import 时的全限定名写法");
        System.out.println("[5] " + full.get(0) + "，长度 " + full.get(0).length());
    }
}
