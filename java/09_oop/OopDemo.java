/*
 * 主题说明：Java 面向对象 —— 类/字段/构造器/this、getter/setter 封装、
 *           继承（super/@Override）、抽象类、接口 default 方法、多态与 instanceof 模式匹配。
 *           文件内其余类不加 public：一个源文件只能有一个公共类（入口 OopDemo）。
 * 运行命令：java java/09_oop/OopDemo.java
 * 预期输出（关键行）：
 *   [3] 汪汪！小狗 4 岁
 *   [5] 接口 default: 我会狗刨
 *   instanceof 模式匹配: 它是小狗，毛色 = 白色
 */
public class OopDemo {

    public static void main(String[] args) {
        // 知识点 1：类与对象 —— 用 new 调用构造器创建实例
        Dog dog = new Dog("小狗", 3, "白色");

        // 知识点 2：封装 —— 字段私有，通过 getter/setter 访问（可加校验）
        System.out.println("[2] getter 读取: " + dog.getName() + " / " + dog.getAge() + " 岁");
        dog.setAge(4);                              // setter 修改
        System.out.println("    setter 修改后年龄 = " + dog.getAge());

        // 知识点 3：继承与方法覆盖 —— Dog 是 Animal，调用的是子类重写后的版本（多态）
        dog.makeSound();

        // 知识点 4：抽象类 —— 不能 new，只被继承；定义公共骨架
        System.out.println("[4] 抽象类方法: " + dog.describe());

        // 知识点 5：接口 default 方法 —— JDK 8+ 接口可带默认实现
        Swimmer swimmer = dog;
        swimmer.swim();

        // 知识点 6：多态 —— 父类/接口引用指向子类对象，同一调用各自表现不同
        Animal[] zoo = {new Dog("大黄", 2, "黄色"), new Cat("咪咪")};
        for (Animal a : zoo) {
            a.makeSound();                          // 运行时决定调用谁的实现
        }

        // 知识点 7：instanceof 模式匹配（JDK 16+）—— 判断类型并直接绑定变量，免强转
        Object obj = dog;
        if (obj instanceof Dog d) {
            System.out.println("[7] instanceof 模式匹配: 它是小狗，毛色 = " + d.getFurColor());
        } else if (obj instanceof Cat c) {
            System.out.println("[7] 它是猫: " + c.getName());
        }
    }
}

/** 动物接口：能力的抽象（interface） */
interface Swimmer {
    void swim();                                    // 抽象方法：只有签名

    /** default 方法：接口里的默认实现，实现类可直接继承使用 */
    default void float_() {
        System.out.println("[5] 接口 default: 我能漂在水上");
    }
}

/** 抽象类：公共骨架，不能实例化，留给子类继承 */
abstract class Animal {
    private final String name;                      // 字段：private 封装；final 初始化后不可变
    private int age;                                // 非 final：后续可通过 setter 修改

    /** 构造器：与类同名、无返回类型；this.name 区分字段与参数 */
    protected Animal(String name, int age) {
        this.name = name;                           // this.name 是字段，name 是参数
        this.age = age;
    }

    String getName() { return name; }               // getter：读字段
    int getAge() { return age; }
    void setAge(int age) {                          // setter：写字段，可加校验
        if (age > 0) {
            this.age = age;
        }
    }

    /** 抽象方法：只有声明，由子类实现 */
    abstract void makeSound();

    /** 普通方法：子类直接复用 */
    String describe() {
        return "我是 " + name + "，" + age + " 岁";
    }
}

/** 子类 Dog：继承 Animal 并实现 Swimmer */
class Dog extends Animal implements Swimmer {
    private final String furColor;

    /** 子类构造器：super(...) 先调用父类构造器 */
    Dog(String name, int age, String furColor) {
        super(name, age);                           // super：调用父类构造器，必须是第一条语句
        this.furColor = furColor;
    }

    String getFurColor() { return furColor; }

    /** @Override：标注覆盖父类方法，编译器帮助检查签名是否一致 */
    @Override
    void makeSound() {
        System.out.println("[3] 汪汪！" + getName() + " " + getAge() + " 岁");
    }

    @Override
    public void swim() {
        System.out.println("[5] 接口 default: 我会狗刨");
        float_();                                   // 继承自接口的 default 方法
    }
}

/** 子类 Cat：同一个抽象，另一种实现 —— 多态的基础 */
class Cat extends Animal {
    Cat(String name) {
        super(name, 1);
    }

    @Override
    void makeSound() {
        System.out.println("[6] 喵喵！" + getName());
    }
}
