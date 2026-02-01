/*
 * 高级格式化技巧示例
 * 演示printf的高级用法和实用技巧
 * C17/C18 标准
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

// 演示颜色输出（ANSI转义序列）
void demo_color_output() {
    printf("=== 颜色输出（ANSI转义序列） ===\n");
    
    // 基本颜色
    printf("\033[31m红色文本\033[0m\n");
    printf("\033[32m绿色文本\033[0m\n");
    printf("\033[33m黄色文本\033[0m\n");
    printf("\033[34m蓝色文本\033[0m\n");
    printf("\033[35m紫色文本\033[0m\n");
    printf("\033[36m青色文本\033[0m\n");
    
    // 背景颜色
    printf("\033[41m红色背景\033[0m\n");
    printf("\033[42m绿色背景\033[0m\n");
    printf("\033[43m黄色背景\033[0m\n");
    printf("\033[44m蓝色背景\033[0m\n");
    
    // 文本样式
    printf("\033[1m粗体文本\033[0m\n");
    printf("\033[4m下划线文本\033[0m\n");
    printf("\033[7m反转颜色\033[0m\n");
    
    // 组合使用
    printf("\033[1;31m粗体红色\033[0m\n");
    printf("\033[1;32;44m粗体绿色文字蓝色背景\033[0m\n");
    
    printf("\n");
}

// 演示表格输出
void demo_table_output() {
    printf("=== 表格输出 ===\n");
    
    // 简单表格
    printf("+----------+------+------+------+\n");
    printf("| 姓名     | 语文 | 数学 | 英语 |\n");
    printf("+----------+------+------+------+\n");
    printf("| %-8s | %4d | %4d | %4d |\n", "张三", 85, 90, 88);
    printf("| %-8s | %4d | %4d | %4d |\n", "李四", 92, 87, 95);
    printf("| %-8s | %4d | %4d | %4d |\n", "王五", 78, 94, 82);
    printf("+----------+------+------+------+\n");
    printf("\n");
    
    // 使用函数生成表格
    const char *headers[] = {"ID", "名称", "价格", "库存"};
    int col_widths[] = {5, 15, 10, 8};
    int num_cols = 4;
    
    // 顶部边框
    printf("+");
    for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < col_widths[i] + 2; j++) printf("-");
        printf("+");
    }
    printf("\n");
    
    // 表头
    printf("|");
    for (int i = 0; i < num_cols; i++) {
        printf(" %-*s |", col_widths[i], headers[i]);
    }
    printf("\n");
    
    // 分隔线
    printf("+");
    for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < col_widths[i] + 2; j++) printf("-");
        printf("+");
    }
    printf("\n");
    
    // 数据行
    printf("| %-*d | %-*s | %-*.2f | %-*d |\n", 
           col_widths[0], 1, 
           col_widths[1], "笔记本", 
           col_widths[2], 15.50, 
           col_widths[3], 100);
    printf("| %-*d | %-*s | %-*.2f | %-*d |\n", 
           col_widths[0], 2, 
           col_widths[1], "钢笔", 
           col_widths[2], 8.80, 
           col_widths[3], 50);
    
    // 底部边框
    printf("+");
    for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < col_widths[i] + 2; j++) printf("-");
        printf("+");
    }
    printf("\n\n");
}

// 演示进度条
void demo_progress_bar() {
    printf("=== 进度条演示 ===\n");
    
    // 简单进度条
    printf("基本进度条:\n");
    for (int i = 0; i <= 100; i += 5) {
        printf("\r[");
        int pos = i / 5;
        for (int j = 0; j < 20; j++) {
            if (j < pos) printf("=");
            else if (j == pos) printf(">");
            else printf(" ");
        }
        printf("] %3d%%", i);
        fflush(stdout);
    }
    printf("\n\n");
    
    // 彩色进度条
    printf("彩色进度条:\n");
    for (int i = 0; i <= 100; i += 5) {
        printf("\r[");
        int pos = i / 5;
        for (int j = 0; j < 20; j++) {
            if (j < pos) {
                if (i < 30) printf("\033[31m█\033[0m");  // 红色
                else if (i < 70) printf("\033[33m█\033[0m");  // 黄色
                else printf("\033[32m█\033[0m");  // 绿色
            } else {
                printf(" ");
            }
        }
        printf("] %3d%%", i);
        fflush(stdout);
    }
    printf("\n\n");
}

// 演示数字格式化技巧
void demo_number_formatting() {
    printf("=== 数字格式化技巧 ===\n");
    
    // 货币格式
    double price = 1234.56;
    printf("货币格式: $%.2f\n", price);
    printf("货币格式: ¥%.2f\n", price);
    
    // 千位分隔符（手动实现）
    long num = 1234567890;
    printf("普通格式: %ld\n", num);
    
    // 百分比
    double percent = 0.7856;
    printf("百分比: %.2f%%\n", percent * 100);
    
    // 科学计数法
    double large = 1234567890.0;
    double small = 0.0000001234;
    printf("大数: %e\n", large);
    printf("小数: %e\n", small);
    
    // 填充和对齐
    printf("右对齐: %10.2f\n", price);
    printf("左对齐: %-10.2f\n", price);
    printf("零填充: %010.2f\n", price);
    
    printf("\n");
}

// 演示时间日期格式化
void demo_datetime_formatting() {
    printf("=== 时间日期格式化 ===\n");
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    
    // 基本格式
    printf("默认格式: %s", ctime(&now));
    
    // 自定义格式
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", local);
    printf("日期: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%H:%M:%S", local);
    printf("时间: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    printf("日期时间: %s\n", buffer);
    
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", local);
    printf("完整日期: %s\n", buffer);
    
    printf("\n");
}

// 演示多行字符串和ASCII艺术
void demo_ascii_art() {
    printf("=== ASCII 艺术 ===\n");
    
    // 简单的ASCII艺术
    printf("  *****  \n");
    printf(" *     * \n");
    printf("*  C语言 *\n");
    printf(" *     * \n");
    printf("  *****  \n");
    printf("\n");
    
    // 使用多行字符串
    printf(
        "┌─────────────────────┐\n"
        "│  欢迎使用C语言程序  │\n"
        "├─────────────────────┤\n"
        "│  1. 开始            │\n"
        "│  2. 设置            │\n"
        "│  3. 退出            │\n"
        "└─────────────────────┘\n"
    );
    printf("\n");
}

// 演示对齐和填充技巧
void demo_alignment_padding() {
    printf("=== 对齐和填充技巧 ===\n");
    
    // 右对齐
    printf("右对齐:\n");
    printf("%10s\n", "短");
    printf("%10s\n", "中等长度");
    printf("%10s\n", "很长的字符串");
    printf("\n");
    
    // 左对齐
    printf("左对齐:\n");
    printf("%-10s|\n", "短");
    printf("%-10s|\n", "中等长度");
    printf("%-10s|\n", "很长的字符串");
    printf("\n");
    
    // 居中对齐（需要手动计算）
    printf("居中对齐:\n");
    const char *strs[] = {"短", "中等长度", "很长的字符串"};
    int width = 20;
    for (int i = 0; i < 3; i++) {
        int len = strlen(strs[i]);
        int padding = (width - len) / 2;
        printf("%*s%s%*s|\n", padding, "", strs[i], width - len - padding, "");
    }
    printf("\n");
}

// 可变参数格式化函数
void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

// 演示自定义格式化函数
void demo_custom_formatting() {
    printf("=== 自定义格式化函数 ===\n");
    
    my_printf("这是自定义printf: %d, %s, %.2f\n", 42, "Hello", 3.14);
    
    // 格式化到缓冲区
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "格式化的字符串: %d", 123);
    printf("缓冲区内容: %s\n", buffer);
    
    printf("\n");
}

// 演示数据可视化
void demo_data_visualization() {
    printf("=== 数据可视化 ===\n");
    
    // 简单的条形图
    int data[] = {75, 50, 90, 60, 85};
    const char *labels[] = {"A", "B", "C", "D", "E"};
    
    printf("条形图:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: ", labels[i]);
        for (int j = 0; j < data[i] / 5; j++) {
            printf("█");
        }
        printf(" %d%%\n", data[i]);
    }
    printf("\n");
    
    // 简单的折线图（ASCII版本）
    printf("简单趋势:\n");
    int values[] = {3, 5, 2, 8, 6, 9, 4};
    for (int i = 0; i < 7; i++) {
        printf("%2d | ", values[i]);
        for (int j = 0; j < values[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("   +");
    for (int i = 0; i < 10; i++) printf("-");
    printf("\n\n");
}

// 演示实用输出技巧
void demo_practical_tips() {
    printf("=== 实用输出技巧 ===\n");
    
    // 1. 输出分隔线
    printf("分隔线示例:\n");
    for (int i = 0; i < 50; i++) printf("=");
    printf("\n");
    for (int i = 0; i < 50; i++) printf("-");
    printf("\n");
    for (int i = 0; i < 50; i++) printf("*");
    printf("\n\n");
    
    // 2. 标题输出
    printf("标题输出:\n");
    const char *title = "C语言教程";
    int title_len = strlen(title) * 2;  // 中文字符
    int total_width = 40;
    int padding = (total_width - title_len) / 2;
    
    for (int i = 0; i < total_width; i++) printf("=");
    printf("\n");
    printf("%*s%s%*s\n", padding, "", title, padding, "");
    for (int i = 0; i < total_width; i++) printf("=");
    printf("\n\n");
    
    // 3. 状态信息
    printf("状态信息:\n");
    printf("[\033[32mOK\033[0m] 操作成功\n");
    printf("[\033[33mWARN\033[0m] 警告信息\n");
    printf("[\033[31mERROR\033[0m] 错误信息\n");
    printf("[\033[34mINFO\033[0m] 提示信息\n");
    printf("\n");
    
    // 4. 列表输出
    printf("列表输出:\n");
    const char *items[] = {"项目1", "项目2", "项目3"};
    for (int i = 0; i < 3; i++) {
        printf("  %d. %s\n", i + 1, items[i]);
    }
}

int main(void) {
    printf("C语言高级格式化技巧示例\n");
    printf("==========================================\n\n");
    
    demo_color_output();
    demo_table_output();
    demo_progress_bar();
    demo_number_formatting();
    demo_datetime_formatting();
    demo_ascii_art();
    demo_alignment_padding();
    demo_custom_formatting();
    demo_data_visualization();
    demo_practical_tips();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
