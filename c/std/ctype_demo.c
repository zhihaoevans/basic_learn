/*
 * ctype.h 标准头文件演示
 * 演示字符分类和转换函数的用法
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void demo_character_classification() {
    printf("=== 字符分类函数演示 ===\n");
    
    // 测试字符集
    char test_chars[] = "aZ3@\t\n 中";
    char *descriptions[] = {
        "小写字母a", "大写字母Z", "数字3", "符号@", 
        "制表符\\t", "换行符\\n", "空格", "中文字符"
    };
    
    printf("字符\t描述\t\t字母\t数字\t字母数字\t小写\t大写\t空白\t标点\t打印\t控制\t图形\t十六进制\n");
    printf("---------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < strlen(test_chars); i++) {
        unsigned char ch = test_chars[i];
        
        printf("'%c'\t%-12s\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
               (ch >= 32 && ch < 127) ? ch : '?',  // 只显示可打印ASCII字符
               descriptions[i],
               isalpha(ch) ? "是" : "否",
               isdigit(ch) ? "是" : "否", 
               isalnum(ch) ? "是" : "否",
               islower(ch) ? "是" : "否",
               isupper(ch) ? "是" : "否",
               isspace(ch) ? "是" : "否",
               ispunct(ch) ? "是" : "否",
               isprint(ch) ? "是" : "否",
               iscntrl(ch) ? "是" : "否",
               isgraph(ch) ? "是" : "否",
               isxdigit(ch) ? "是" : "否");
    }
}

void demo_detailed_classification() {
    printf("\n=== 详细字符分类演示 ===\n");
    
    // ASCII字符完整测试
    printf("ASCII字符分类统计:\n");
    
    int alpha_count = 0, digit_count = 0, space_count = 0;
    int punct_count = 0, cntrl_count = 0, print_count = 0;
    
    for (int i = 0; i < 128; i++) {
        if (isalpha(i)) alpha_count++;
        if (isdigit(i)) digit_count++;
        if (isspace(i)) space_count++;
        if (ispunct(i)) punct_count++;
        if (iscntrl(i)) cntrl_count++;
        if (isprint(i)) print_count++;
    }
    
    printf("字母字符: %d 个\n", alpha_count);
    printf("数字字符: %d 个\n", digit_count);
    printf("空白字符: %d 个\n", space_count);
    printf("标点符号: %d 个\n", punct_count);
    printf("控制字符: %d 个\n", cntrl_count);
    printf("可打印字符: %d 个\n", print_count);
    
    // 显示各类字符的具体内容
    printf("\n各类字符详情:\n");
    
    printf("数字字符: ");
    for (int i = 0; i < 128; i++) {
        if (isdigit(i)) printf("'%c' ", i);
    }
    printf("\n");
    
    printf("小写字母: ");
    for (int i = 0; i < 128; i++) {
        if (islower(i)) printf("'%c' ", i);
    }
    printf("\n");
    
    printf("大写字母: ");
    for (int i = 0; i < 128; i++) {
        if (isupper(i)) printf("'%c' ", i);
    }
    printf("\n");
    
    printf("空白字符: ");
    for (int i = 0; i < 128; i++) {
        if (isspace(i)) {
            switch (i) {
                case ' ': printf("'空格' "); break;
                case '\t': printf("'\\t' "); break;
                case '\n': printf("'\\n' "); break;
                case '\r': printf("'\\r' "); break;
                case '\f': printf("'\\f' "); break;
                case '\v': printf("'\\v' "); break;
                default: printf("'%d' ", i); break;
            }
        }
    }
    printf("\n");
    
    printf("十六进制字符: ");
    for (int i = 0; i < 128; i++) {
        if (isxdigit(i)) printf("'%c' ", i);
    }
    printf("\n");
}

void demo_character_conversion() {
    printf("\n=== 字符转换函数演示 ===\n");
    
    char test_string[] = "Hello, World! 123 ABC xyz";
    printf("原始字符串: \"%s\"\n", test_string);
    
    // 转换为大写
    printf("转换为大写: \"");
    for (int i = 0; test_string[i]; i++) {
        printf("%c", toupper(test_string[i]));
    }
    printf("\"\n");
    
    // 转换为小写
    printf("转换为小写: \"");
    for (int i = 0; test_string[i]; i++) {
        printf("%c", tolower(test_string[i]));
    }
    printf("\"\n");
    
    // 演示转换函数的详细行为
    printf("\n字符转换详情:\n");
    printf("字符\t原值\ttoupper\ttolower\n");
    printf("--------------------------------\n");
    
    char samples[] = "aZ3@\t ";
    for (int i = 0; i < strlen(samples); i++) {
        char ch = samples[i];
        char upper = toupper(ch);
        char lower = tolower(ch);
        
        printf("'%c'\t%d\t%d('%c')\t%d('%c')\n", 
               ch, ch, upper, upper, lower, lower);
    }
}

void demo_string_processing() {
    printf("\n=== 字符串处理应用演示 ===\n");
    
    char input[] = "  Hello, World! 123  ";
    printf("原始字符串: \"%s\"\n", input);
    
    // 1. 去除前导空白
    char *start = input;
    while (*start && isspace(*start)) {
        start++;
    }
    printf("去除前导空白: \"%s\"\n", start);
    
    // 2. 去除尾随空白（需要修改字符串）
    char trimmed[100];
    strcpy(trimmed, start);
    int len = strlen(trimmed);
    while (len > 0 && isspace(trimmed[len - 1])) {
        trimmed[--len] = '\0';
    }
    printf("去除尾随空白: \"%s\"\n", trimmed);
    
    // 3. 统计各类字符
    int letters = 0, digits = 0, spaces = 0, others = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) letters++;
        else if (isdigit(input[i])) digits++;
        else if (isspace(input[i])) spaces++;
        else others++;
    }
    
    printf("字符统计:\n");
    printf("  字母: %d 个\n", letters);
    printf("  数字: %d 个\n", digits);
    printf("  空白: %d 个\n", spaces);
    printf("  其他: %d 个\n", others);
    
    // 4. 提取数字
    printf("提取的数字: ");
    for (int i = 0; input[i]; i++) {
        if (isdigit(input[i])) {
            printf("%c", input[i]);
        }
    }
    printf("\n");
    
    // 5. 提取字母并转换大小写
    printf("字母转大写: ");
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            printf("%c", toupper(input[i]));
        }
    }
    printf("\n");
}

void demo_input_validation() {
    printf("\n=== 输入验证演示 ===\n");
    
    // 模拟各种输入验证场景
    char *test_inputs[] = {
        "abc123",      // 字母数字混合
        "123456",      // 纯数字
        "ABCDEF",      // 纯字母大写
        "abcdef",      // 纯字母小写
        "123.45",      // 包含小数点
        "user@email.com", // 邮箱格式
        "Hello World!", // 包含空格和标点
        "",            // 空字符串
        "   ",         // 纯空白
        "1A2B3C"       // 十六进制样式
    };
    
    int num_tests = sizeof(test_inputs) / sizeof(test_inputs[0]);
    
    printf("输入\t\t长度\t纯字母\t纯数字\t字母数字\t包含空白\t全大写\t全小写\t有效十六进制\n");
    printf("----------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < num_tests; i++) {
        char *input = test_inputs[i];
        int len = strlen(input);
        
        // 检查各种属性
        int all_alpha = 1, all_digit = 1, all_alnum = 1;
        int has_space = 0, all_upper = 1, all_lower = 1, valid_hex = 1;
        
        if (len == 0) {
            all_alpha = all_digit = all_alnum = all_upper = all_lower = valid_hex = 0;
        }
        
        for (int j = 0; j < len; j++) {
            char ch = input[j];
            
            if (!isalpha(ch)) all_alpha = 0;
            if (!isdigit(ch)) all_digit = 0;
            if (!isalnum(ch)) all_alnum = 0;
            if (isspace(ch)) has_space = 1;
            if (isalpha(ch) && !isupper(ch)) all_upper = 0;
            if (isalpha(ch) && !islower(ch)) all_lower = 0;
            if (!isxdigit(ch)) valid_hex = 0;
        }
        
        printf("%-15s\t%d\t%s\t%s\t%s\t\t%s\t\t%s\t%s\t%s\n",
               input, len,
               all_alpha ? "是" : "否",
               all_digit ? "是" : "否", 
               all_alnum ? "是" : "否",
               has_space ? "是" : "否",
               (all_upper && len > 0) ? "是" : "否",
               (all_lower && len > 0) ? "是" : "否",
               valid_hex ? "是" : "否");
    }
}

void demo_case_conversion_applications() {
    printf("\n=== 大小写转换应用演示 ===\n");
    
    char text[] = "hello world programming";
    printf("原始文本: \"%s\"\n", text);
    
    // 1. 首字母大写
    char title_case[100];
    strcpy(title_case, text);
    int capitalize_next = 1;
    
    for (int i = 0; title_case[i]; i++) {
        if (isalpha(title_case[i])) {
            if (capitalize_next) {
                title_case[i] = toupper(title_case[i]);
                capitalize_next = 0;
            } else {
                title_case[i] = tolower(title_case[i]);
            }
        } else if (isspace(title_case[i])) {
            capitalize_next = 1;
        }
    }
    printf("标题格式: \"%s\"\n", title_case);
    
    // 2. 句子格式（首字母大写）
    char sentence[100];
    strcpy(sentence, text);
    if (strlen(sentence) > 0 && isalpha(sentence[0])) {
        sentence[0] = toupper(sentence[0]);
    }
    printf("句子格式: \"%s\"\n", sentence);
    
    // 3. 交替大小写
    char alternating[100];
    strcpy(alternating, text);
    int is_upper = 1;
    
    for (int i = 0; alternating[i]; i++) {
        if (isalpha(alternating[i])) {
            alternating[i] = is_upper ? toupper(alternating[i]) : tolower(alternating[i]);
            is_upper = !is_upper;
        }
    }
    printf("交替大小写: \"%s\"\n", alternating);
    
    // 4. 反转大小写
    char inverted[100];
    strcpy(inverted, text);
    
    for (int i = 0; inverted[i]; i++) {
        if (islower(inverted[i])) {
            inverted[i] = toupper(inverted[i]);
        } else if (isupper(inverted[i])) {
            inverted[i] = tolower(inverted[i]);
        }
    }
    printf("反转大小写: \"%s\"\n", inverted);
}

void demo_locale_considerations() {
    printf("\n=== 本地化考虑演示 ===\n");
    
    printf("注意事项:\n");
    printf("1. ctype.h函数主要针对ASCII字符设计\n");
    printf("2. 对于国际化字符（如中文、日文等），可能需要使用宽字符函数\n");
    printf("3. 某些字符的分类可能依赖于当前的locale设置\n");
    
    // 演示扩展ASCII字符的处理
    printf("\n扩展ASCII字符测试:\n");
    for (int i = 128; i < 256; i++) {
        if (isprint(i)) {
            printf("字符 %d ('%c'): ", i, i);
            if (isalpha(i)) printf("字母 ");
            if (isdigit(i)) printf("数字 ");
            if (isspace(i)) printf("空白 ");
            if (ispunct(i)) printf("标点 ");
            printf("\n");
        }
    }
    
    printf("\n建议:\n");
    printf("- 对于Unicode字符，使用wctype.h中的宽字符函数\n");
    printf("- 对于UTF-8字符串，考虑使用专门的Unicode库\n");
    printf("- 在处理用户输入时，始终验证字符范围\n");
}

int main() {
    printf("C语言 ctype.h 标准头文件演示\n");
    printf("===============================\n");
    
    demo_character_classification();
    demo_detailed_classification();
    demo_character_conversion();
    demo_string_processing();
    demo_input_validation();
    demo_case_conversion_applications();
    demo_locale_considerations();
    
    printf("\n演示完成！\n");
    return 0;
}