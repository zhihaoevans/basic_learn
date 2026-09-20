/*
 * 主题说明：Java 控制流 —— if/else、switch（传统与箭头语法）、四种循环
 *           （for / 增强 for / while / do-while）、break/continue 与带标签的循环。
 * 运行命令：java java/05_control/ControlFlowDemo.java
 * 预期输出（关键行）：
 *   85 分 -> 及格，良好
 *   传统 switch: 星期三
 *   箭头 switch: 星期三（Wednesday）
 *   找到目标 7，跳出外层循环
 */
public class ControlFlowDemo {

    public static void main(String[] args) {
        // 知识点 1：if / else if / else 分支
        int score = 85;
        if (score >= 90) {
            System.out.println("[1] 优秀");
        } else if (score >= 60) {
            System.out.println("[1] 85 分 -> 及格，良好");
        } else {
            System.out.println("[1] 不及格");
        }

        // 知识点 2a：传统 switch —— case + break，漏写 break 会"贯穿"到下一个分支
        int day = 3;
        switch (day) {
            case 1:
                System.out.println("[2a] 传统 switch: 星期一");
                break;                        // break 不可少
            case 3:
                System.out.println("[2a] 传统 switch: 星期三");
                break;
            default:
                System.out.println("[2a] 其他");
        }

        // 知识点 2b：箭头语法 switch（JDK 14+）—— 无需 break，天然不贯穿，还能直接返回值
        String name = switch (day) {
            case 1 -> "星期一（Monday）";
            case 3 -> "星期三（Wednesday）";
            default -> "其他";
        };
        System.out.println("[2b] 箭头 switch: " + name);

        // 知识点 3：经典 for 循环 —— 计数器三段式（初始化; 条件; 步进）
        int sum = 0;
        for (int i = 1; i <= 5; i++) {
            sum += i;
        }
        System.out.println("[3] for 求 1..5 累加 = " + sum);

        // 知识点 4：增强 for（for-each）—— 直接遍历数组/集合的每个元素
        String[] fruits = {"苹果", "香蕉", "橘子"};
        for (String fruit : fruits) {
            System.out.println("[4] 水果: " + fruit);
        }

        // 知识点 5：while —— 先判断后执行；条件不满足时一次都不执行
        int n = 1;
        while (n <= 3) {
            System.out.println("[5] while 第 " + n + " 轮");
            n = n * 2;
        }

        // 知识点 6：do-while —— 先执行后判断，循环体至少跑一次
        int m = 10;
        do {
            System.out.println("[6] do-while 执行了一次（尽管 10 > 3）");
        } while (m < 3);

        // 知识点 7：break（结束整个循环）与 continue（跳过本轮，进入下一轮）
        for (int i = 1; i <= 5; i++) {
            if (i == 2) {
                continue;               // 跳过 2
            }
            if (i == 4) {
                break;                  // 到 4 为止
            }
            System.out.println("[7] i = " + i);
        }

        // 知识点 8：带标签的循环 —— label: 写在循环前，break/continue label 直接作用于外层
        int[][] grid = {{1, 2}, {3, 7}, {4, 5}};
        outer:
        for (int[] row : grid) {
            for (int v : row) {
                if (v == 7) {
                    System.out.println("[8] 找到目标 7，跳出外层循环");
                    break outer;        // 直接结束带 outer 标签的外层循环
                }
            }
        }
    }
}
