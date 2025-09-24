/*
 * stdio.h 标准头文件演示
 * 演示标准输入输出库的各种函数用法
 */

#include <stdio.h>
#include <string.h>

void demo_basic_io() {
    printf("=== 基本输入输出演示 ===\n");
    
    // printf 系列函数
    printf("printf: 格式化输出\n");
    printf("整数: %d, 浮点数: %.2f, 字符: %c, 字符串: %s\n", 42, 3.14159, 'A', "Hello");
    
    // putchar 和 puts
    printf("putchar输出字符: ");
    putchar('H');
    putchar('i');
    putchar('\n');
    
    puts("puts输出字符串（自动换行）");
    
    // scanf 输入演示（注释掉避免交互）
    /*
    int num;
    char str[100];
    printf("请输入一个整数: ");
    scanf("%d", &num);
    printf("你输入的整数是: %d\n", num);
    
    printf("请输入一个字符串: ");
    scanf("%s", str);
    printf("你输入的字符串是: %s\n", str);
    */
}

void demo_file_io() {
    printf("\n=== 文件输入输出演示 ===\n");
    
    FILE *fp;
    char buffer[256];
    
    // 写文件
    fp = fopen("test.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "这是写入文件的第一行\n");
        fprintf(fp, "数字: %d, 浮点数: %.2f\n", 123, 45.67);
        fputs("这是用fputs写入的一行\n", fp);
        fputc('X', fp);
        fputc('\n', fp);
        fclose(fp);
        printf("文件写入完成\n");
    }
    
    // 读文件
    fp = fopen("test.txt", "r");
    if (fp != NULL) {
        printf("文件内容:\n");
        
        // 使用fgets逐行读取
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("读取: %s", buffer);
        }
        
        fclose(fp);
    }
    
    // 重新打开文件，演示其他读取方法
    fp = fopen("test.txt", "r");
    if (fp != NULL) {
        printf("\n使用fgetc逐字符读取:\n");
        int ch;
        int count = 0;
        while ((ch = fgetc(fp)) != EOF && count < 20) {  // 只读前20个字符
            putchar(ch);
            count++;
        }
        printf("...\n");
        fclose(fp);
    }
}

void demo_formatted_io() {
    printf("\n=== 格式化输入输出演示 ===\n");
    
    // sprintf - 格式化到字符串
    char buffer[200];
    int len = sprintf(buffer, "格式化到字符串: %d + %d = %d", 10, 20, 30);
    printf("sprintf结果: %s (长度: %d)\n", buffer, len);
    
    // snprintf - 安全的格式化到字符串
    char small_buffer[20];
    snprintf(small_buffer, sizeof(small_buffer), "这是一个很长的字符串，会被截断");
    printf("snprintf结果: %s\n", small_buffer);
    
    // sscanf - 从字符串解析
    char input[] = "123 45.67 Hello";
    int num;
    float fnum;
    char str[50];
    
    int parsed = sscanf(input, "%d %f %s", &num, &fnum, str);
    printf("sscanf解析 '%s':\n", input);
    printf("解析了 %d 个项目: 整数=%d, 浮点数=%.2f, 字符串=%s\n", parsed, num, fnum, str);
}

void demo_file_operations() {
    printf("\n=== 文件操作演示 ===\n");
    
    FILE *fp = fopen("demo.txt", "w+");  // 读写模式
    if (fp == NULL) {
        printf("无法创建文件\n");
        return;
    }
    
    // 写入一些数据
    fprintf(fp, "Line 1: Hello World\n");
    fprintf(fp, "Line 2: 12345\n");
    fprintf(fp, "Line 3: End of file\n");
    
    // 获取文件位置
    long pos = ftell(fp);
    printf("当前文件位置: %ld\n", pos);
    
    // 移动到文件开头
    rewind(fp);
    printf("移动到文件开头后位置: %ld\n", ftell(fp));
    
    // 使用fseek移动文件指针
    fseek(fp, 0, SEEK_END);  // 移动到文件末尾
    long file_size = ftell(fp);
    printf("文件大小: %ld 字节\n", file_size);
    
    // 移动到文件开头并读取
    fseek(fp, 0, SEEK_SET);
    char line[100];
    int line_num = 1;
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("第%d行: %s", line_num++, line);
    }
    
    fclose(fp);
    
    // 删除测试文件
    if (remove("demo.txt") == 0) {
        printf("测试文件已删除\n");
    }
    if (remove("test.txt") == 0) {
        printf("测试文件已删除\n");
    }
}

void demo_error_handling() {
    printf("\n=== 错误处理演示 ===\n");
    
    // 尝试打开不存在的文件
    FILE *fp = fopen("nonexistent.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件 'nonexistent.txt'\n");
        perror("错误详情");  // 打印系统错误信息
    }
    
    // 演示ferror和feof
    fp = fopen("temp.txt", "w+");
    if (fp != NULL) {
        fprintf(fp, "Test data");
        rewind(fp);
        
        int ch;
        while ((ch = fgetc(fp)) != EOF) {
            putchar(ch);
        }
        
        if (feof(fp)) {
            printf("\n到达文件末尾\n");
        }
        
        if (ferror(fp)) {
            printf("文件操作出错\n");
        } else {
            printf("文件操作正常\n");
        }
        
        fclose(fp);
        remove("temp.txt");
    }
}

int main() {
    printf("C语言 stdio.h 标准头文件演示\n");
    printf("================================\n");
    
    demo_basic_io();
    demo_file_io();
    demo_formatted_io();
    demo_file_operations();
    demo_error_handling();
    
    printf("\n演示完成！\n");
    return 0;
}