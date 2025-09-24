/*
 * time.h 标准头文件演示
 * 演示时间和日期处理库的各种函数用法
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>  // for sleep()

void demo_basic_time() {
    printf("=== 基本时间函数演示 ===\n");
    
    // time() - 获取当前时间戳
    time_t current_time = time(NULL);
    printf("当前时间戳: %ld\n", (long)current_time);
    
    // ctime() - 将时间戳转换为可读字符串
    char *time_str = ctime(&current_time);
    printf("ctime()格式: %s", time_str);  // ctime已包含换行符
    
    // 演示时间戳的含义（从1970年1月1日00:00:00 UTC开始的秒数）
    time_t epoch = 0;
    printf("Unix纪元时间: %s", ctime(&epoch));
    
    // 计算程序运行时间
    time_t start_time = time(NULL);
    printf("开始计时...\n");
    
    // 模拟一些工作
    for (volatile int i = 0; i < 100000000; i++);
    
    time_t end_time = time(NULL);
    double elapsed = difftime(end_time, start_time);
    printf("计算耗时: %.0f 秒\n", elapsed);
}

void demo_struct_tm() {
    printf("\n=== struct tm 结构体演示 ===\n");
    
    time_t current_time = time(NULL);
    
    // localtime() - 转换为本地时间的struct tm
    struct tm *local_tm = localtime(&current_time);
    
    printf("本地时间详细信息:\n");
    printf("  年份: %d\n", local_tm->tm_year + 1900);  // tm_year是从1900年开始的年数
    printf("  月份: %d (%d月)\n", local_tm->tm_mon, local_tm->tm_mon + 1);  // tm_mon是0-11
    printf("  日期: %d\n", local_tm->tm_mday);
    printf("  小时: %d\n", local_tm->tm_hour);
    printf("  分钟: %d\n", local_tm->tm_min);
    printf("  秒数: %d\n", local_tm->tm_sec);
    printf("  星期: %d (0=周日, 1=周一, ..., 6=周六)\n", local_tm->tm_wday);
    printf("  年内第几天: %d\n", local_tm->tm_yday + 1);  // tm_yday是0-365
    printf("  夏令时标志: %d\n", local_tm->tm_isdst);
    
    // gmtime() - 转换为UTC时间的struct tm
    struct tm *utc_tm = gmtime(&current_time);
    printf("\nUTC时间: %04d-%02d-%02d %02d:%02d:%02d\n",
           utc_tm->tm_year + 1900, utc_tm->tm_mon + 1, utc_tm->tm_mday,
           utc_tm->tm_hour, utc_tm->tm_min, utc_tm->tm_sec);
    
    // mktime() - 将struct tm转换回time_t
    struct tm test_tm = *local_tm;  // 复制当前时间
    test_tm.tm_mday += 7;  // 加7天
    time_t future_time = mktime(&test_tm);
    
    printf("7天后的时间戳: %ld\n", (long)future_time);
    printf("7天后的时间: %s", ctime(&future_time));
}

void demo_time_formatting() {
    printf("\n=== 时间格式化演示 ===\n");
    
    time_t current_time = time(NULL);
    struct tm *tm_info = localtime(&current_time);
    char buffer[200];
    
    // strftime() - 格式化时间字符串
    printf("各种时间格式:\n");
    
    // 基本日期时间格式
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("标准格式: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", tm_info);
    printf("完整日期: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%a, %b %d, %y", tm_info);
    printf("简短日期: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%I:%M:%S %p", tm_info);
    printf("12小时制: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);
    printf("24小时制: %s\n", buffer);
    
    // 特殊格式
    strftime(buffer, sizeof(buffer), "今天是%Y年第%j天", tm_info);
    printf("年内天数: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "今天是第%U周 (周日开始)", tm_info);
    printf("周数(周日): %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "今天是第%W周 (周一开始)", tm_info);
    printf("周数(周一): %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "时区: %Z, UTC偏移: %z", tm_info);
    printf("时区信息: %s\n", buffer);
    
    // ISO 8601格式
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S%z", tm_info);
    printf("ISO 8601: %s\n", buffer);
    
    // 自定义格式
    strftime(buffer, sizeof(buffer), "现在是%Y年%m月%d日 %A %H点%M分", tm_info);
    printf("中文格式: %s\n", buffer);
}

void demo_time_parsing() {
    printf("\n=== 时间解析演示 ===\n");
    
    // strptime() - 解析时间字符串（POSIX函数，不是C标准）
    // 注意：strptime在某些系统上可能不可用
    #ifdef __APPLE__
    struct tm parsed_tm;
    memset(&parsed_tm, 0, sizeof(struct tm));
    
    char *time_string = "2024-12-25 15:30:45";
    char *format = "%Y-%m-%d %H:%M:%S";
    
    char *result = strptime(time_string, format, &parsed_tm);
    if (result != NULL) {
        printf("解析时间字符串: %s\n", time_string);
        printf("解析结果: %04d-%02d-%02d %02d:%02d:%02d\n",
               parsed_tm.tm_year + 1900, parsed_tm.tm_mon + 1, parsed_tm.tm_mday,
               parsed_tm.tm_hour, parsed_tm.tm_min, parsed_tm.tm_sec);
        
        // 转换为时间戳
        time_t parsed_time = mktime(&parsed_tm);
        printf("对应时间戳: %ld\n", (long)parsed_time);
        printf("验证: %s", ctime(&parsed_time));
    } else {
        printf("时间字符串解析失败\n");
    }
    #else
    printf("strptime函数在此系统上不可用\n");
    #endif
}

void demo_clock_function() {
    printf("\n=== clock()函数演示 ===\n");
    
    // clock() - 获取处理器时间
    clock_t start_clock = clock();
    printf("开始时钟计数: %ld\n", (long)start_clock);
    
    // 执行一些计算密集的操作
    printf("执行计算密集操作...\n");
    double sum = 0.0;
    for (int i = 0; i < 10000000; i++) {
        sum += i * i;
    }
    
    clock_t end_clock = clock();
    printf("结束时钟计数: %ld\n", (long)end_clock);
    
    // 计算CPU时间
    double cpu_time = ((double)(end_clock - start_clock)) / CLOCKS_PER_SEC;
    printf("CPU时间: %.6f 秒\n", cpu_time);
    printf("CLOCKS_PER_SEC = %ld\n", (long)CLOCKS_PER_SEC);
    printf("计算结果: %.0f (防止编译器优化)\n", sum);
}

void demo_time_calculations() {
    printf("\n=== 时间计算演示 ===\n");
    
    // 创建特定日期
    struct tm birthday = {0};
    birthday.tm_year = 1990 - 1900;  // 1990年
    birthday.tm_mon = 5 - 1;         // 5月 (0-based)
    birthday.tm_mday = 15;           // 15日
    birthday.tm_hour = 12;
    birthday.tm_min = 0;
    birthday.tm_sec = 0;
    birthday.tm_isdst = -1;          // 让系统决定夏令时
    
    time_t birthday_time = mktime(&birthday);
    time_t current_time = time(NULL);
    
    printf("生日: %s", ctime(&birthday_time));
    printf("现在: %s", ctime(&current_time));
    
    // 计算时间差
    double diff_seconds = difftime(current_time, birthday_time);
    double diff_days = diff_seconds / (24 * 60 * 60);
    double diff_years = diff_days / 365.25;  // 考虑闰年
    
    printf("时间差: %.0f 秒\n", diff_seconds);
    printf("相当于: %.1f 天\n", diff_days);
    printf("大约: %.1f 年\n", diff_years);
    
    // 计算未来日期
    struct tm future = *localtime(&current_time);
    future.tm_mday += 100;  // 100天后
    time_t future_time = mktime(&future);
    
    printf("100天后: %s", ctime(&future_time));
    
    // 计算月份边界
    struct tm month_start = *localtime(&current_time);
    month_start.tm_mday = 1;
    month_start.tm_hour = 0;
    month_start.tm_min = 0;
    month_start.tm_sec = 0;
    time_t month_start_time = mktime(&month_start);
    
    printf("本月第一天: %s", ctime(&month_start_time));
    
    // 下个月第一天
    struct tm next_month = month_start;
    next_month.tm_mon += 1;
    time_t next_month_time = mktime(&next_month);
    
    printf("下月第一天: %s", ctime(&next_month_time));
}

void demo_performance_timing() {
    printf("\n=== 性能计时演示 ===\n");
    
    // 比较不同计时方法的精度
    printf("比较不同算法的性能:\n");
    
    const int n = 1000000;
    
    // 方法1：简单循环
    clock_t start1 = clock();
    time_t time_start1 = time(NULL);
    
    long sum1 = 0;
    for (int i = 0; i < n; i++) {
        sum1 += i;
    }
    
    clock_t end1 = clock();
    time_t time_end1 = time(NULL);
    
    printf("方法1 (简单循环):\n");
    printf("  CPU时间: %.6f 秒\n", (double)(end1 - start1) / CLOCKS_PER_SEC);
    printf("  墙钟时间: %.0f 秒\n", difftime(time_end1, time_start1));
    printf("  结果: %ld\n", sum1);
    
    // 方法2：数学公式
    clock_t start2 = clock();
    time_t time_start2 = time(NULL);
    
    long sum2 = (long)n * (n - 1) / 2;
    
    clock_t end2 = clock();
    time_t time_end2 = time(NULL);
    
    printf("方法2 (数学公式):\n");
    printf("  CPU时间: %.6f 秒\n", (double)(end2 - start2) / CLOCKS_PER_SEC);
    printf("  墙钟时间: %.0f 秒\n", difftime(time_end2, time_start2));
    printf("  结果: %ld\n", sum2);
    
    printf("结果验证: %s\n", (sum1 == sum2) ? "正确" : "错误");
}

int main() {
    printf("C语言 time.h 标准头文件演示\n");
    printf("==============================\n");
    
    demo_basic_time();
    demo_struct_tm();
    demo_time_formatting();
    demo_time_parsing();
    demo_clock_function();
    demo_time_calculations();
    demo_performance_timing();
    
    printf("\n演示完成！\n");
    return 0;
}