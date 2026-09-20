/*
 * 主题说明：Java 的 Map（键值对）—— HashMap 增删改查与遍历、getOrDefault 默认值，
 *           TreeMap 按键排序、LinkedHashMap 保持插入顺序。
 * 运行命令：java java/08_map/MapDemo.java
 * 预期输出（关键行）：
 *   查: apple -> 苹果
 *   getOrDefault: 没有的键返回默认值 -> 未知
 *   TreeMap 按键排序: {apple=1, banana=2, cherry=3}
 */

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;

public class MapDemo {

    public static void main(String[] args) {
        // 知识点 1：HashMap 增删改查 —— 键唯一，最常用的 Map 实现
        Map<String, String> dict = new HashMap<>();
        dict.put("apple", "苹果");            // 增
        dict.put("banana", "香蕉");
        dict.put("cherry", "樱桃");
        dict.put("apple", "苹果(红)");        // 改：同键再 put 就是覆盖
        System.out.println("[1] 增/改后: " + dict);
        System.out.println("    查: apple -> " + dict.get("apple"));   // 查
        System.out.println("    无效的键返回: " + dict.get("pear"));
        dict.remove("banana");                                     // 删
        System.out.println("    删掉 banana 后大小 = " + dict.size());

        // 知识点 2：getOrDefault —— 键不存在时返回默认值，避免判空
        System.out.println("[2] getOrDefault: 没有的键返回默认值 -> " + dict.getOrDefault("pear", "未知"));
        // computeIfAbsent：没有才计算并放入，适合做分组计数
        Map<Character, Integer> counter = new HashMap<>();
        for (char c : "apple".toCharArray()) {
            counter.merge(c, 1, Integer::sum);   // 每遇到一次 +1
        }
        System.out.println("    单词计数: " + counter);

        // 知识点 3：HashMap 遍历 —— entrySet 拿键值对，keySet 拿键，values 拿值
        for (Map.Entry<String, String> e : dict.entrySet()) {
            System.out.println("[3] " + e.getKey() + " = " + e.getValue());
        }
        dict.forEach((k, v) -> System.out.println("    Lambda 遍历: " + k + " -> " + v));

        // 知识点 4：TreeMap —— 按键的自然顺序（或比较器）排序
        Map<String, Integer> tree = new TreeMap<>();
        tree.put("cherry", 3);
        tree.put("apple", 1);
        tree.put("banana", 2);
        System.out.println("[4] TreeMap 按键排序: " + tree);

        // 知识点 5：LinkedHashMap —— 保持插入顺序（HashMap 本身无序）
        Map<String, Integer> linked = new LinkedHashMap<>();
        linked.put("cherry", 3);
        linked.put("apple", 1);
        linked.put("banana", 2);
        System.out.println("[5] LinkedHashMap 保持插入顺序: " + linked);
        System.out.println("    对比：同样数据 HashMap 的顺序不保证 -> " + new HashMap<>(linked));
    }
}
