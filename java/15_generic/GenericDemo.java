import java.util.List;

/*
 * 主题说明：Java 泛型 —— 泛型方法 <T>、泛型类 Box<T>、有界类型参数
 *           <T extends Comparable<T>>，以及通配符 ? extends / ? super 的用途。
 * 运行命令：java java/15_generic/GenericDemo.java
 * 预期输出（关键行）：
 *   泛型方法: first([甲, 乙, 丙]) = 甲
 *   Box<String> 装的是: 苹果
 *   最大值 = cherry （字典序）
 *   sum(List<? extends Number>) = 6.0
 */
public class GenericDemo {

    // 知识点 1：泛型方法 —— <T> 写在返回类型前，T 由调用处的实参推断
    static <T> T first(List<T> list) {
        return list.get(0);
    }

    // 知识点 2：泛型类 —— 类名后带 <T>，字段/方法都能用这个类型参数
    static class Box<T> {
        private T content;                        // 内容类型由使用时决定

        public void put(T item) {                 // 存：参数类型是 T
            this.content = item;
        }

        public T get() {                          // 取：返回类型是 T
            return content;
        }

        @Override
        public String toString() {
            return content == null ? "空箱子" : String.valueOf(content);
        }
    }

    // 知识点 3：有界类型参数 —— T 必须是 Comparable<T> 的子类型，才能调用 compareTo
    static <T extends Comparable<T>> T max(List<T> list) {
        T best = list.get(0);
        for (T t : list) {
            if (t.compareTo(best) > 0) {          // 有了边界，T 一定有 compareTo 方法
                best = t;
            }
        }
        return best;
    }

    // 知识点 4a：上界通配符 —— List<? extends Number> 能装 Number 的任意子类列表，只读不写
    static double sum(List<? extends Number> nums) {
        double total = 0;
        for (Number n : nums) {                   // 读出来一律当 Number 用
            total += n.doubleValue();
        }
        return total;
    }

    // 知识点 4b：下界通配符 —— List<? super Integer> 接收 Integer 的任意父类列表，只写不读
    static void fillWithZero(List<? super Integer> sink) {
        for (int i = 0; i < 3; i++) {
            sink.add(0);                          // Integer 一定能放进父类列表
        }
    }

    public static void main(String[] args) {
        // 知识点 1：调用泛型方法，T 自动推断为 String
        List<String> names = List.of("甲", "乙", "丙");
        System.out.println("[1] 泛型方法: first(" + names + ") = " + first(names));
        List<Integer> ints = List.of(10, 20);
        System.out.println("[1] 同一个方法换类型: first(" + ints + ") = " + first(ints));

        // 知识点 2：泛型类 —— 同一个 Box，装字符串或装整数，编译期就检查类型
        Box<String> stringBox = new Box<>();
        stringBox.put("苹果");
        // stringBox.put(123);   // 取消注释会编译错误：Integer 放不进 Box<String>
        Box<Integer> intBox = new Box<>();
        intBox.put(42);
        System.out.println("[2] Box<String> 装的是: " + stringBox.get());
        System.out.println("[2] Box<Integer> 装的是: " + intBox.get());
        System.out.println("[2] 类型在编译期已确定: stringBox.get() 是 String，无需强转");

        // 知识点 3：有界类型参数 —— 换成 List.of(1,2,3) 也能用同一个 max
        List<String> fruits = List.of("apple", "banana", "cherry");
        System.out.println("[3] 最大值 = " + max(fruits) + " （字典序）");
        System.out.println("[3] 最大值 = " + max(List.of(3, 7, 5)) + " （数值）");

        // 知识点 4：通配符简述 —— "生产者用 extends（读），消费者用 super（写）"（PECS 原则）
        System.out.println("[4] sum(List<? extends Number>) = " + sum(List.of(1, 2, 3)));
        System.out.println("    传入 List<Double> 也行 = " + sum(List.of(1.5, 2.5)));
        List<Object> sink = new java.util.ArrayList<>(List.of("占位"));
        fillWithZero(sink);                       // List<Object> 是 List<? super Integer>
        System.out.println("    fillWithZero(List<? super Integer>) 后 = " + sink);
    }
}
