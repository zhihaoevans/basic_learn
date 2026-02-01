/*
 * 字符串处理技巧示例
 * 演示实用的字符串处理技巧和高级用法
 * C17/C18 标准
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

// 安全的字符串复制
size_t safe_strcpy(char *dest, const char *src, size_t dest_size) {
    if (dest_size == 0) return 0;
    
    size_t src_len = strlen(src);
    size_t copy_len = (src_len < dest_size - 1) ? src_len : dest_size - 1;
    
    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';
    
    return copy_len;
}

// 演示安全字符串操作
void demo_safe_string_ops() {
    printf("=== 安全字符串操作 ===\n");
    
    char buffer[10];
    const char *long_str = "这是一个很长的字符串";
    
    // 不安全的操作（注释掉）
    // strcpy(buffer, long_str);  // 缓冲区溢出！
    
    // 安全的操作
    safe_strcpy(buffer, long_str, sizeof(buffer));
    printf("安全复制结果: %s\n", buffer);
    
    // 使用strncpy（注意要手动添加'\0'）
    char buffer2[10];
    strncpy(buffer2, long_str, sizeof(buffer2) - 1);
    buffer2[sizeof(buffer2) - 1] = '\0';
    printf("strncpy结果: %s\n", buffer2);
    
    // 使用snprintf
    char buffer3[10];
    snprintf(buffer3, sizeof(buffer3), "%s", long_str);
    printf("snprintf结果: %s\n", buffer3);
    
    printf("\n");
}

// 字符串格式化和构建
void demo_string_formatting() {
    printf("=== 字符串格式化和构建 ===\n");
    
    // 使用sprintf构建字符串
    char result[100];
    sprintf(result, "姓名: %s, 年龄: %d, 分数: %.2f", "张三", 20, 95.5);
    printf("sprintf: %s\n", result);
    
    // 使用snprintf（更安全）
    snprintf(result, sizeof(result), "ID: %04d, 状态: %s", 42, "Active");
    printf("snprintf: %s\n", result);
    
    // 拼接多个部分
    char message[200] = "";
    snprintf(message, sizeof(message), "%s", "消息: ");
    snprintf(message + strlen(message), sizeof(message) - strlen(message), 
             "%s", "操作成功, ");
    snprintf(message + strlen(message), sizeof(message) - strlen(message), 
             "代码: %d", 200);
    printf("拼接结果: %s\n", message);
    
    printf("\n");
}

// 字符串大小写转换
void demo_case_conversion() {
    printf("=== 大小写转换 ===\n");
    
    char str[] = "Hello, World! 123";
    char upper[50], lower[50];
    
    // 转大写
    strcpy(upper, str);
    for (int i = 0; upper[i]; i++) {
        upper[i] = toupper((unsigned char)upper[i]);
    }
    printf("原字符串: %s\n", str);
    printf("转大写: %s\n", upper);
    
    // 转小写
    strcpy(lower, str);
    for (int i = 0; lower[i]; i++) {
        lower[i] = tolower((unsigned char)lower[i]);
    }
    printf("转小写: %s\n", lower);
    
    // 首字母大写
    char title[] = "hello world from c";
    title[0] = toupper(title[0]);
    for (size_t i = 1; i < strlen(title); i++) {
        if (title[i-1] == ' ') {
            title[i] = toupper(title[i]);
        }
    }
    printf("首字母大写: %s\n", title);
    
    printf("\n");
}

// 字符串修剪（去除空白）
char* trim(char *str) {
    // 去除前导空格
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == '\0') return str;
    
    // 去除尾随空格
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    
    *(end + 1) = '\0';
    return str;
}

void demo_string_trim() {
    printf("=== 字符串修剪 ===\n");
    
    char str1[] = "   hello   ";
    char str2[] = "\t\n  world  \n\t";
    char str3[] = "no spaces";
    
    printf("原字符串1: \"%s\"\n", str1);
    printf("修剪后: \"%s\"\n", trim(str1));
    
    printf("原字符串2: \"%s\"\n", str2);
    printf("修剪后: \"%s\"\n", trim(str2));
    
    printf("原字符串3: \"%s\"\n", str3);
    printf("修剪后: \"%s\"\n", trim(str3));
    
    printf("\n");
}

// 字符串替换
void string_replace(char *str, char old_char, char new_char) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == old_char) {
            str[i] = new_char;
        }
    }
}

void demo_string_replace() {
    printf("=== 字符串替换 ===\n");
    
    char str[] = "Hello, World!";
    printf("原字符串: %s\n", str);
    
    string_replace(str, 'o', '0');
    printf("替换 'o' 为 '0': %s\n", str);
    
    char str2[] = "a-b-c-d-e";
    printf("\n原字符串: %s\n", str2);
    string_replace(str2, '-', '_');
    printf("替换 '-' 为 '_': %s\n", str2);
    
    printf("\n");
}

// 字符串分割成数组
int split_string(char *str, char delimiter, char **tokens, int max_tokens) {
    int count = 0;
    char *token = strtok(str, &delimiter);
    
    while (token != NULL && count < max_tokens) {
        tokens[count++] = token;
        token = strtok(NULL, &delimiter);
    }
    
    return count;
}

void demo_string_split() {
    printf("=== 字符串分割 ===\n");
    
    char str[] = "apple,banana,cherry,date,elderberry";
    char *tokens[10];
    
    printf("原字符串: %s\n", str);
    int count = split_string(str, ',', tokens, 10);
    
    printf("分割结果 (%d 个部分):\n", count);
    for (int i = 0; i < count; i++) {
        printf("  %d: %s\n", i + 1, tokens[i]);
    }
    
    printf("\n");
}

// 字符串反转
void string_reverse(char *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void demo_string_reverse() {
    printf("=== 字符串反转 ===\n");
    
    char str1[] = "Hello";
    printf("原字符串: %s\n", str1);
    string_reverse(str1);
    printf("反转后: %s\n", str1);
    
    char str2[] = "12345";
    printf("\n原字符串: %s\n", str2);
    string_reverse(str2);
    printf("反转后: %s\n", str2);
    
    printf("\n");
}

// 检查字符串是否为回文
bool is_palindrome(const char *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        if (tolower(str[i]) != tolower(str[len - 1 - i])) {
            return false;
        }
    }
    return true;
}

void demo_palindrome() {
    printf("=== 回文检查 ===\n");
    
    const char *strings[] = {
        "madam",
        "racecar",
        "hello",
        "A man a plan a canal Panama",  // 这个例子需要忽略空格
        "Was it a car or a cat I saw"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("\"%s\" %s回文\n", 
               strings[i], 
               is_palindrome(strings[i]) ? "是" : "不是");
    }
    
    printf("\n");
}

// 计算子字符串出现次数
int count_occurrences(const char *str, const char *substr) {
    int count = 0;
    const char *pos = str;
    size_t substr_len = strlen(substr);
    
    while ((pos = strstr(pos, substr)) != NULL) {
        count++;
        pos += substr_len;
    }
    
    return count;
}

void demo_count_occurrences() {
    printf("=== 统计子字符串出现次数 ===\n");
    
    const char *text = "Hello hello HELLO hello";
    
    printf("文本: %s\n", text);
    printf("\"hello\" 出现次数: %d\n", count_occurrences(text, "hello"));
    printf("\"Hello\" 出现次数: %d\n", count_occurrences(text, "Hello"));
    printf("\"ll\" 出现次数: %d\n", count_occurrences(text, "ll"));
    
    printf("\n");
}

// 字符串中的单词数
int count_words(const char *str) {
    int count = 0;
    bool in_word = false;
    
    while (*str) {
        if (isspace((unsigned char)*str)) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            count++;
        }
        str++;
    }
    
    return count;
}

void demo_word_count() {
    printf("=== 单词计数 ===\n");
    
    const char *sentences[] = {
        "Hello World",
        "One two three four five",
        "  Spaces   around   words  ",
        "Single",
        ""
    };
    
    for (int i = 0; i < 5; i++) {
        printf("\"%s\" -> %d 个单词\n", sentences[i], count_words(sentences[i]));
    }
    
    printf("\n");
}

// 字符串连接（多个）
void demo_string_join() {
    printf("=== 字符串连接 ===\n");
    
    const char *parts[] = {"one", "two", "three", "four"};
    const char *separator = ", ";
    char result[100] = "";
    
    for (int i = 0; i < 4; i++) {
        if (i > 0) {
            strcat(result, separator);
        }
        strcat(result, parts[i]);
    }
    
    printf("连接结果: %s\n", result);
    
    printf("\n");
}

// 字符串包含检查
bool string_contains(const char *str, const char *substr) {
    return strstr(str, substr) != NULL;
}

void demo_string_contains() {
    printf("=== 字符串包含检查 ===\n");
    
    const char *text = "The quick brown fox jumps over the lazy dog";
    
    printf("文本: %s\n\n", text);
    printf("包含 \"fox\": %s\n", string_contains(text, "fox") ? "是" : "否");
    printf("包含 \"cat\": %s\n", string_contains(text, "cat") ? "是" : "否");
    printf("包含 \"quick\": %s\n", string_contains(text, "quick") ? "是" : "否");
    
    printf("\n");
}

// 字符串前缀和后缀检查
bool starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

bool ends_with(const char *str, const char *suffix) {
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    
    if (suffix_len > str_len) return false;
    
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

void demo_prefix_suffix() {
    printf("=== 前缀和后缀检查 ===\n");
    
    const char *filename = "document.txt";
    
    printf("文件名: %s\n", filename);
    printf("以 \"doc\" 开头: %s\n", starts_with(filename, "doc") ? "是" : "否");
    printf("以 \"file\" 开头: %s\n", starts_with(filename, "file") ? "是" : "否");
    printf("以 \".txt\" 结尾: %s\n", ends_with(filename, ".txt") ? "是" : "否");
    printf("以 \".pdf\" 结尾: %s\n", ends_with(filename, ".pdf") ? "是" : "否");
    
    printf("\n");
}

int main(void) {
    printf("C语言字符串处理技巧示例\n");
    printf("==========================================\n\n");
    
    demo_safe_string_ops();
    demo_string_formatting();
    demo_case_conversion();
    demo_string_trim();
    demo_string_replace();
    demo_string_split();
    demo_string_reverse();
    demo_palindrome();
    demo_count_occurrences();
    demo_word_count();
    demo_string_join();
    demo_string_contains();
    demo_prefix_suffix();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
