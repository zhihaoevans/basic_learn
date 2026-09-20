/*
 * 主题说明：Java 集合 —— 数组与 Arrays 工具类、ArrayList / LinkedList / HashSet，
 *           以及 for / for-each / 迭代器 / forEach 四种遍历方式的对比。
 * 运行命令：java java/07_collection/CollectionDemo.java
 * 预期输出（关键行）：
 *   数组长度 = 3，排序后 [1, 2, 3] （Arrays.toString 打印）
 *   LinkedList 同样是 List，可以当队列用: 头=甲 尾=丙
 *   HashSet 去重后大小 = 3，无序不重复
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

public class CollectionDemo {

    public static void main(String[] args) {
        // 知识点 1：数组 —— 定长，声明/赋值/按下标访问
        int[] nums = {3, 1, 2};
        System.out.println("[1] 数组长度 = " + nums.length + "，首元素 = " + nums[0]);
        Arrays.sort(nums);                                   // Arrays 工具类：排序
        System.out.println("    排序后 " + Arrays.toString(nums) + " （Arrays.toString 打印）");
        int idx = Arrays.binarySearch(nums, 2);              // 二分查找（需已排序）
        System.out.println("    binarySearch 找 2 的下标 = " + idx);

        // 知识点 2：ArrayList —— 最常用的动态数组，长度可变，尾部追加 O(1)
        List<String> list = new ArrayList<>();
        list.add("甲");
        list.add("乙");
        list.add("丙");
        list.add("乙");
        list.remove("乙");                 // 删除第一个匹配元素
        list.set(0, "甲(改)");             // 修改下标 0
        System.out.println("[2] ArrayList: " + list + "，大小 = " + list.size());
        System.out.println("    contains(\"丙\") = " + list.contains("丙"));

        // 知识点 3：LinkedList —— 双向链表实现，头尾操作快，也可当队列/栈用
        LinkedList<String> linked = new LinkedList<>();
        linked.addLast("甲");
        linked.addLast("乙");
        linked.addLast("丙");
        System.out.println("[3] LinkedList 同样是 List，可以当队列用: 头=" + linked.getFirst()
                + " 尾=" + linked.getLast());
        linked.addFirst("队首");
        System.out.println("    addFirst 后: " + linked);

        // 知识点 4：HashSet —— 元素不重复、无序，查 contains 是 O(1)
        Set<String> set = new HashSet<>(List.of("甲", "乙", "丙", "乙"));
        System.out.println("[4] HashSet 去重后大小 = " + set.size() + "，无序不重复");
        set.add("丙");                                     // 重复添加不生效
        System.out.println("    再 add(\"丙\") 后大小仍是 " + set.size());

        // 知识点 5：遍历方式对比
        List<String> words = List.of("a", "b", "c");
        StringBuilder byFor = new StringBuilder();          // (a) 传统 for：有下标，能改元素
        for (int i = 0; i < words.size(); i++) {
            byFor.append(words.get(i));
        }
        StringBuilder byEach = new StringBuilder();         // (b) 增强 for：最简洁，只读遍历
        for (String w : words) {
            byEach.append(w);
        }
        StringBuilder byIter = new StringBuilder();         // (c) 迭代器：遍历中可安全删除元素
        for (Iterator<String> it = words.iterator(); it.hasNext(); ) {
            byIter.append(it.next());
        }
        StringBuilder byLambda = new StringBuilder();       // (d) forEach + Lambda：函数式写法
        words.forEach(w -> byLambda.append(w));
        System.out.println("[5] 四种遍历结果一致: " + byFor + " / " + byEach + " / "
                + byIter + " / " + byLambda);
        System.out.println("    选用：只读用增强 for，要下标用传统 for，边遍历边删用迭代器");
    }
}
