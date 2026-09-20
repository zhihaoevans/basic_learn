/*
 * 主题说明：Java 常用标准库速览 —— Optional 优雅处理可能为空的值、
 *           Arrays 工具（asList/sort/stream）、日期时间（LocalDate/LocalDateTime）、
 *           Objects 工具类与 String.join。
 * 运行命令：java java/13_stdlib/StdlibDemo.java
 * 预期输出（关键行）：
 *   Optional: 找到了 -> 苹果
 *   Optional: 空值兜底 -> 无
 *   排序后: [1, 2, 3, 5, 9]，最大值 = 9
 *   今天: 2026-（运行当天日期）
 */

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

public class StdlibDemo {

    public static void main(String[] args) {
        // 知识点 1：Optional —— 用类型系统表达"可能有值也可能没有"，替代 null 判空
        Optional<String> found = List.of("苹果", "香蕉").stream()
                .filter(s -> s.startsWith("苹"))
                .findFirst();
        System.out.println("[1] Optional: " + found.map(v -> "找到了 -> " + v).orElse("没找到"));
        Optional<String> empty = Optional.empty();
        System.out.println("[1] Optional: 空值兜底 -> " + empty.orElse("无"));
        System.out.println("[1] Optional: isPresent = " + empty.isPresent()
                + "，orElseGet 惰性取值 -> " + empty.orElseGet(() -> "默认值"));

        // 知识点 2：Arrays 工具类 —— asList 快速造列表、sort 排序、stream 流式处理
        List<String> asList = Arrays.asList("甲", "乙", "丙");   // 定长列表（不能 add/remove）
        System.out.println("[2] Arrays.asList: " + asList);
        int[] arr = {5, 2, 9, 1, 3};
        Arrays.sort(arr);                                        // 原地排序
        System.out.println("[2] 排序后: " + Arrays.toString(arr));
        int sum = Arrays.stream(arr).sum();                      // 流式求和
        int max = Arrays.stream(arr).max().getAsInt();
        System.out.println("[2] stream: 总和 = " + sum + "，最大值 = " + max);

        // 知识点 3：LocalDate / LocalDateTime —— 新日期 API（JDK 8+），不可变且线程安全
        LocalDate today = LocalDate.now();
        System.out.println("[3] 今天: " + today + "，年份 = " + today.getYear());
        System.out.println("    10 天后: " + today.plusDays(10) + "，是否闰年 = " + today.isLeapYear());
        LocalDateTime now = LocalDateTime.now();
        String formatted = now.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        System.out.println("    LocalDateTime 格式化: " + formatted);
        LocalDate newYear = LocalDate.of(2026, 1, 1);
        System.out.println("    距 2026-01-01 已过天数 = "
                + java.time.temporal.ChronoUnit.DAYS.between(newYear, today));

        // 知识点 4：Objects 工具类 —— 判空、比较、hashCode 等静态方法
        String maybeNull = null;
        System.out.println("[4] Objects.isNull = " + Objects.isNull(maybeNull)
                + "，requireNonNullElse 兜底 -> " + Objects.requireNonNullElse(maybeNull, "默认"));
        System.out.println("    Objects.equals(null, null) = " + Objects.equals(null, null)
                + "（用 Objects.equals 避免 null.equals 崩溃）");

        // 知识点 5：String.join —— 用分隔符拼接一组字符串
        String joined = String.join(" -> ", "入队", "处理", "出队");
        System.out.println("[5] String.join: " + joined);
        System.out.println("    String.join(\", \", list) = " + String.join(", ", asList));
    }
}
