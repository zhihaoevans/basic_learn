/*
 * locale.h 演示程序
 * 
 * locale.h 提供了本地化支持功能，允许程序根据不同的地区和语言
 * 设置来格式化数字、货币、日期和时间等
 * 
 * 主要功能：
 * - setlocale(): 设置或查询程序的本地化信息
 * - localeconv(): 获取数字格式化信息
 * - 本地化类别常量 (LC_ALL, LC_NUMERIC, LC_TIME 等)
 * 
 * 编译: gcc -o locale_demo locale_demo.c
 * 运行: ./locale_demo
 */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

// 函数声明
void demo_basic_locale(void);
void demo_numeric_formatting(void);
void demo_currency_formatting(void);
void demo_time_formatting(void);
void demo_character_classification(void);
void demo_string_collation(void);
void demo_practical_localization(void);

// 辅助函数声明
void print_locale_info(const char *category_name, int category);
void print_numeric_info(struct lconv *lc);
void print_currency_info(struct lconv *lc);
void format_number_with_locale(double number);
void format_currency_with_locale(double amount);
void demonstrate_locale(const char *locale_name);

int main(void) {
    printf("=== locale.h 演示程序 ===\n\n");
    
    demo_basic_locale();
    demo_numeric_formatting();
    demo_currency_formatting();
    demo_time_formatting();
    demo_character_classification();
    demo_string_collation();
    demo_practical_localization();
    
    return 0;
}

/*
 * 基本本地化设置演示
 */
void demo_basic_locale(void) {
    printf("1. 基本本地化设置演示\n");
    printf("======================\n");
    
    // 显示当前本地化设置
    printf("当前本地化设置:\n");
    print_locale_info("LC_ALL", LC_ALL);
    print_locale_info("LC_NUMERIC", LC_NUMERIC);
    print_locale_info("LC_TIME", LC_TIME);
    print_locale_info("LC_MONETARY", LC_MONETARY);
    print_locale_info("LC_CTYPE", LC_CTYPE);
    print_locale_info("LC_COLLATE", LC_COLLATE);
    
    // 尝试设置不同的本地化
    printf("\n尝试设置不同的本地化:\n");
    
    // 设置为 C 本地化（默认）
    char *result = setlocale(LC_ALL, "C");
    printf("设置 LC_ALL 为 'C': %s\n", result ? result : "失败");
    
    // 尝试设置为系统默认本地化
    result = setlocale(LC_ALL, "");
    printf("设置 LC_ALL 为系统默认: %s\n", result ? result : "失败");
    
    // 尝试设置特定本地化
    const char *locales[] = {"en_US.UTF-8", "zh_CN.UTF-8", "fr_FR.UTF-8", "de_DE.UTF-8"};
    for (int i = 0; i < 4; i++) {
        result = setlocale(LC_ALL, locales[i]);
        printf("尝试设置为 '%s': %s\n", locales[i], result ? result : "不支持");
        if (result) {
            setlocale(LC_ALL, "C");  // 重置为默认
        }
    }
    
    printf("\n");
}

/*
 * 数字格式化演示
 */
void demo_numeric_formatting(void) {
    printf("2. 数字格式化演示\n");
    printf("==================\n");
    
    // 获取当前数字格式化信息
    struct lconv *lc = localeconv();
    printf("当前数字格式化设置:\n");
    print_numeric_info(lc);
    
    // 演示不同本地化下的数字格式
    printf("\n不同本地化下的数字格式:\n");
    double test_number = 1234567.89;
    
    printf("测试数字: %.2f\n", test_number);
    
    // C 本地化
    setlocale(LC_NUMERIC, "C");
    printf("C 本地化: ");
    format_number_with_locale(test_number);
    
    // 尝试其他本地化
    const char *numeric_locales[] = {"en_US.UTF-8", "de_DE.UTF-8", "fr_FR.UTF-8"};
    for (int i = 0; i < 3; i++) {
        if (setlocale(LC_NUMERIC, numeric_locales[i])) {
            printf("%s: ", numeric_locales[i]);
            format_number_with_locale(test_number);
            setlocale(LC_NUMERIC, "C");  // 重置
        }
    }
    
    printf("\n");
}

/*
 * 货币格式化演示
 */
void demo_currency_formatting(void) {
    printf("3. 货币格式化演示\n");
    printf("==================\n");
    
    // 获取当前货币格式化信息
    struct lconv *lc = localeconv();
    printf("当前货币格式化设置:\n");
    print_currency_info(lc);
    
    // 演示不同本地化下的货币格式
    printf("\n不同本地化下的货币格式:\n");
    double test_amount = 1234.56;
    
    printf("测试金额: %.2f\n", test_amount);
    
    // C 本地化
    setlocale(LC_MONETARY, "C");
    printf("C 本地化: ");
    format_currency_with_locale(test_amount);
    
    // 尝试其他本地化
    const char *monetary_locales[] = {"en_US.UTF-8", "de_DE.UTF-8", "ja_JP.UTF-8"};
    for (int i = 0; i < 3; i++) {
        if (setlocale(LC_MONETARY, monetary_locales[i])) {
            printf("%s: ", monetary_locales[i]);
            format_currency_with_locale(test_amount);
            setlocale(LC_MONETARY, "C");  // 重置
        }
    }
    
    printf("\n");
}

/*
 * 时间格式化演示
 */
void demo_time_formatting(void) {
    printf("4. 时间格式化演示\n");
    printf("==================\n");
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char buffer[256];
    
    printf("当前时间的不同格式化:\n");
    
    // C 本地化
    setlocale(LC_TIME, "C");
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y %H:%M:%S", tm_info);
    printf("C 本地化: %s\n", buffer);
    
    // 尝试其他本地化
    const char *time_locales[] = {"en_US.UTF-8", "de_DE.UTF-8", "fr_FR.UTF-8", "zh_CN.UTF-8"};
    for (int i = 0; i < 4; i++) {
        if (setlocale(LC_TIME, time_locales[i])) {
            strftime(buffer, sizeof(buffer), "%A, %B %d, %Y %H:%M:%S", tm_info);
            printf("%s: %s\n", time_locales[i], buffer);
            setlocale(LC_TIME, "C");  // 重置
        }
    }
    
    // 不同的时间格式
    printf("\n不同的时间格式模式:\n");
    const char *formats[] = {
        "%Y-%m-%d",           // ISO 日期格式
        "%d/%m/%Y",           // 欧洲日期格式
        "%m/%d/%Y",           // 美国日期格式
        "%A, %d %B %Y",       // 完整日期
        "%H:%M:%S",           // 24小时时间
        "%I:%M:%S %p"         // 12小时时间
    };
    
    for (int i = 0; i < 6; i++) {
        strftime(buffer, sizeof(buffer), formats[i], tm_info);
        printf("格式 '%s': %s\n", formats[i], buffer);
    }
    
    printf("\n");
}

/*
 * 字符分类演示
 */
void demo_character_classification(void) {
    printf("5. 字符分类演示\n");
    printf("================\n");
    
    printf("字符分类在不同本地化下的行为:\n");
    
    // 测试字符 (使用ASCII字符避免编码问题)
    const char test_chars[] = {'a', 'A', '1', ' ', 'x', 'y', 'z', '\0'};
    
    printf("字符\t");
    for (int i = 0; test_chars[i] != '\0'; i++) {
        printf("%c\t", test_chars[i]);
    }
    printf("\n");
    
    // C 本地化
    setlocale(LC_CTYPE, "C");
    printf("C本地化\t");
    for (int i = 0; test_chars[i] != '\0'; i++) {
        printf("%d\t", isalpha(test_chars[i]) ? 1 : 0);
    }
    printf("\n");
    
    // 尝试 UTF-8 本地化
    if (setlocale(LC_CTYPE, "en_US.UTF-8")) {
        printf("UTF-8\t");
        for (int i = 0; test_chars[i] != '\0'; i++) {
            printf("%d\t", isalpha(test_chars[i]) ? 1 : 0);
        }
        printf("\n");
        setlocale(LC_CTYPE, "C");  // 重置
    }
    
    printf("\n");
}

/*
 * 字符串排序演示
 */
void demo_string_collation(void) {
    printf("6. 字符串排序演示\n");
    printf("==================\n");
    
    const char *strings[] = {"apple", "Banana", "cherry", "Date", "elderberry"};
    int count = 5;
    
    printf("原始字符串顺序:\n");
    for (int i = 0; i < count; i++) {
        printf("  %s\n", strings[i]);
    }
    
    printf("\n不同本地化下的字符串比较:\n");
    
    // C 本地化比较
    setlocale(LC_COLLATE, "C");
    printf("C 本地化下 'apple' vs 'Banana': %d\n", strcoll("apple", "Banana"));
    printf("C 本地化下 'Apple' vs 'apple': %d\n", strcoll("Apple", "apple"));
    
    // 尝试其他本地化
    if (setlocale(LC_COLLATE, "en_US.UTF-8")) {
        printf("en_US.UTF-8 下 'apple' vs 'Banana': %d\n", strcoll("apple", "Banana"));
        printf("en_US.UTF-8 下 'Apple' vs 'apple': %d\n", strcoll("Apple", "apple"));
        setlocale(LC_COLLATE, "C");  // 重置
    }
    
    printf("\n");
}

/*
 * 实用本地化应用演示
 */
void demo_practical_localization(void) {
    printf("7. 实用本地化应用演示\n");
    printf("======================\n");
    
    printf("多语言应用程序示例:\n");
    
    // 演示不同本地化设置
    const char *demo_locales[] = {"C", "en_US.UTF-8", "de_DE.UTF-8", "fr_FR.UTF-8"};
    
    for (int i = 0; i < 4; i++) {
        printf("\n--- %s ---\n", demo_locales[i]);
        demonstrate_locale(demo_locales[i]);
    }
    
    printf("\n");
}

// 辅助函数实现

/*
 * 打印本地化信息
 */
void print_locale_info(const char *category_name, int category) {
    char *current = setlocale(category, NULL);
    printf("  %s: %s\n", category_name, current ? current : "未设置");
}

/*
 * 打印数字格式化信息
 */
void print_numeric_info(struct lconv *lc) {
    printf("  小数点符号: '%s'\n", lc->decimal_point);
    printf("  千位分隔符: '%s'\n", lc->thousands_sep);
    printf("  分组规则: ");
    if (lc->grouping && lc->grouping[0]) {
        for (int i = 0; lc->grouping[i]; i++) {
            printf("%d ", lc->grouping[i]);
        }
    } else {
        printf("无");
    }
    printf("\n");
}

/*
 * 打印货币格式化信息
 */
void print_currency_info(struct lconv *lc) {
    printf("  货币符号: '%s'\n", lc->currency_symbol);
    printf("  国际货币符号: '%s'\n", lc->int_curr_symbol);
    printf("  货币小数点: '%s'\n", lc->mon_decimal_point);
    printf("  货币千位分隔符: '%s'\n", lc->mon_thousands_sep);
    printf("  货币小数位数: %d\n", lc->frac_digits);
    printf("  货币符号位置: %d\n", lc->p_cs_precedes);
}

/*
 * 使用当前本地化格式化数字
 */
void format_number_with_locale(double number) {
    struct lconv *lc = localeconv();
    
    // 简单的数字格式化（实际应用中可能需要更复杂的逻辑）
    char buffer[64];
    sprintf(buffer, "%.2f", number);
    
    // 替换小数点
    char *decimal_pos = strchr(buffer, '.');
    if (decimal_pos && strcmp(lc->decimal_point, ".") != 0) {
        *decimal_pos = lc->decimal_point[0];
    }
    
    printf("%s\n", buffer);
}

/*
 * 使用当前本地化格式化货币
 */
void format_currency_with_locale(double amount) {
    struct lconv *lc = localeconv();
    
    char buffer[64];
    sprintf(buffer, "%.2f", amount);
    
    // 简单的货币格式化
    if (lc->p_cs_precedes) {
        printf("%s%s\n", lc->currency_symbol, buffer);
    } else {
        printf("%s%s\n", buffer, lc->currency_symbol);
    }
}

/*
 * 演示特定本地化设置
 */
void demonstrate_locale(const char *locale_name) {
    char *result = setlocale(LC_ALL, locale_name);
    if (!result) {
        printf("无法设置本地化: %s\n", locale_name);
        return;
    }
    
    // 数字格式化
    printf("数字 1234.56: ");
    format_number_with_locale(1234.56);
    
    // 货币格式化
    printf("货币 99.99: ");
    format_currency_with_locale(99.99);
    
    // 时间格式化
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_buffer[128];
    strftime(time_buffer, sizeof(time_buffer), "%A, %B %d, %Y", tm_info);
    printf("日期: %s\n", time_buffer);
    
    // 重置为 C 本地化
    setlocale(LC_ALL, "C");
}