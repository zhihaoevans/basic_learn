/*
 * 基础输出函数示例
 * 演示C语言中的基本输出函数：printf, puts, putchar等
 * C17/C18 标准
 */

#include <stdio.h>
#include <string.h>

// 演示printf基础用法
void demo_printf_basics() {
    printf("=== printf 基础用法 ===\n");
    
    // 简单文本输出
    printf("Hello, World!\n");
    
    // 整数输出
    int num = 42;
    printf("整数: %d\n", num);
    
    // 浮点数输出
    double pi = 3.14159;
    printf("浮点数: %f\n", pi);
    
    // 字符输出
    char ch = 'A';
    printf("字符: %c\n", ch);
    
    // 字符串输出
    char str[] = "Hello";
    printf("字符串: %s\n", str);
    
    // 多个参数
    int x = 10, y = 20;
    printf("x = %d, y = %d, 和 = %d\n", x, y, x + y);
    
    printf("\n");
}

// 演示puts和putchar
void demo_puts_putchar() {
    printf("=== puts 和 putchar ===\n");
    
    // puts - 输出字符串并自动添加换行
    puts("使用 puts 输出字符串");
    puts("自动添加换行符");
    
    // putchar - 输出单个字符
    printf("使用 putchar: ");
    putchar('H');
    putchar('e');
    putchar('l');
    putchar('l');
    putchar('o');
    putchar('\n');
    
    // 使用putchar输出一行字符
    printf("输出一行星号: ");
    for (int i = 0; i < 10; i++) {
        putchar('*');
    }
    putchar('\n');
    
    printf("\n");
}

// 演示fprintf和其他输出函数
void demo_fprintf() {
    printf("=== fprintf 和其他输出函数 ===\n");
    
    // fprintf - 输出到指定流
    fprintf(stdout, "使用 fprintf 输出到 stdout\n");
    fprintf(stderr, "使用 fprintf 输出到 stderr\n");
    
    // 输出到文件
    FILE *fp = fopen("/tmp/output.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "这是写入文件的内容\n");
        fprintf(fp, "数字: %d, 浮点数: %.2f\n", 123, 45.67);
        fclose(fp);
        printf("内容已写入 /tmp/output.txt\n");
    }
    
    // 读取并显示文件内容
    fp = fopen("/tmp/output.txt", "r");
    if (fp != NULL) {
        printf("文件内容:\n");
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("  %s", buffer);
        }
        fclose(fp);
    }
    
    printf("\n");
}

// 演示sprintf和snprintf
void demo_sprintf() {
    printf("=== sprintf 和 snprintf ===\n");
    
    char buffer[100];
    int num = 42;
    double value = 3.14159;
    
    // sprintf - 格式化到字符串
    sprintf(buffer, "数字: %d, 值: %.2f", num, value);
    printf("sprintf 结果: %s\n", buffer);
    
    // snprintf - 安全版本，限制最大长度
    snprintf(buffer, sizeof(buffer), "这是一个很长的字符串，数字=%d", num);
    printf("snprintf 结果: %s\n", buffer);
    
    // 演示snprintf的安全性
    char small_buf[10];
    snprintf(small_buf, sizeof(small_buf), "这是一个很长的字符串");
    printf("小缓冲区: %s\n", small_buf);  // 会被截断
    
    printf("\n");
}

// 演示格式化输出的宽度和精度
void demo_width_precision() {
    printf("=== 宽度和精度控制 ===\n");
    
    int num = 123;
    
    // 最小字段宽度
    printf("无宽度: %d\n", num);
    printf("宽度10: %10d\n", num);
    printf("宽度10左对齐: %-10d|结束\n", num);
    
    // 用0填充
    printf("用0填充: %05d\n", num);
    
    // 浮点数精度
    double pi = 3.14159265358979;
    printf("默认精度: %f\n", pi);
    printf("精度2位: %.2f\n", pi);
    printf("精度5位: %.5f\n", pi);
    printf("精度10位: %.10f\n", pi);
    
    // 宽度和精度结合
    printf("宽度10精度2: %10.2f\n", pi);
    printf("宽度10精度2左对齐: %-10.2f|结束\n", pi);
    
    // 字符串宽度和精度
    char str[] = "Hello, World!";
    printf("字符串无限制: %s\n", str);
    printf("字符串宽度20: %20s\n", str);
    printf("字符串精度5: %.5s\n", str);  // 只输出前5个字符
    printf("字符串宽度20精度5: %20.5s\n", str);
    
    printf("\n");
}

// 演示不同的输出形式
void demo_output_styles() {
    printf("=== 不同输出形式 ===\n");
    
    // 表格形式输出
    printf("学生成绩表:\n");
    printf("%-10s %-8s %-8s %-8s\n", "姓名", "数学", "英语", "总分");
    printf("%-10s %-8d %-8d %-8d\n", "张三", 85, 90, 175);
    printf("%-10s %-8d %-8d %-8d\n", "李四", 92, 88, 180);
    printf("%-10s %-8d %-8d %-8d\n", "王五", 78, 95, 173);
    printf("\n");
    
    // 进度条
    printf("进度条示例:\n");
    for (int i = 0; i <= 100; i += 10) {
        printf("\r进度: [");
        int pos = i / 10;
        for (int j = 0; j < 10; j++) {
            if (j < pos) {
                printf("=");
            } else {
                printf(" ");
            }
        }
        printf("] %d%%", i);
        fflush(stdout);  // 强制刷新输出缓冲区
    }
    printf("\n\n");
    
    // 多行文本
    printf("多行文本:\n");
    printf("第一行\n"
           "第二行\n"
           "第三行\n");
    printf("\n");
}

// 演示返回值
void demo_return_value() {
    printf("=== printf 返回值 ===\n");
    
    // printf返回输出的字符数
    int count1 = printf("Hello, World!");
    printf("\n输出了 %d 个字符\n", count1);
    
    int count2 = printf("数字: %d\n", 42);
    printf("输出了 %d 个字符\n", count2);
    
    // 使用返回值检查错误
    char buffer[50];
    int len = snprintf(buffer, sizeof(buffer), "测试字符串");
    if (len >= 0 && (size_t)len < sizeof(buffer)) {
        printf("成功: %s\n", buffer);
    } else {
        printf("缓冲区太小或发生错误\n");
    }
    
    printf("\n");
}

// 演示刷新输出缓冲区
void demo_flush() {
    printf("=== 输出缓冲区 ===\n");
    
    // 正常情况（遇到\n自动刷新）
    printf("这行有换行符会立即显示\n");
    
    // 没有换行符，可能不会立即显示
    printf("这行没有换行符");
    fflush(stdout);  // 手动刷新
    printf("（已手动刷新）\n");
    
    // 演示缓冲区效果
    printf("倒计时: ");
    for (int i = 5; i >= 1; i--) {
        printf("%d ", i);
        fflush(stdout);  // 确保立即显示
    }
    printf("开始!\n");
    
    printf("\n");
}

// 演示组合输出
void demo_combined_output() {
    printf("=== 组合输出示例 ===\n");
    
    // 输出一个简单的菜单
    puts("========== 主菜单 ==========");
    puts("1. 选项一");
    puts("2. 选项二");
    puts("3. 选项三");
    puts("4. 退出");
    puts("===========================");
    printf("请选择 (1-4): ");
    fflush(stdout);
    
    printf("\n\n");
    
    // 输出一个简单的框
    printf("+");
    for (int i = 0; i < 30; i++) putchar('-');
    printf("+\n");
    printf("| %-28s |\n", "欢迎使用C语言程序");
    printf("+");
    for (int i = 0; i < 30; i++) putchar('-');
    printf("+\n");
}

int main(void) {
    printf("C语言基础输出函数示例\n");
    printf("==========================================\n\n");
    
    demo_printf_basics();
    demo_puts_putchar();
    demo_fprintf();
    demo_sprintf();
    demo_width_precision();
    demo_output_styles();
    demo_return_value();
    demo_flush();
    demo_combined_output();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
