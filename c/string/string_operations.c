/*
 * 字符串操作函数示例
 * 演示string.h中的各种字符串操作函数
 * C17/C18 标准
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 演示字符串复制函数
void demo_string_copy() {
    printf("=== 字符串复制 ===\n");
    
    char src[] = "Hello, World!";
    char dest[50];
    
    // strcpy - 复制整个字符串
    strcpy(dest, src);
    printf("strcpy: %s\n", dest);
    
    // strncpy - 复制指定长度
    char dest2[50] = {0};
    strncpy(dest2, src, 5);
    dest2[5] = '\0';  // 确保以'\0'结尾
    printf("strncpy (前5个字符): %s\n", dest2);
    
    // memcpy - 复制内存块
    char dest3[50];
    memcpy(dest3, src, strlen(src) + 1);  // +1包括'\0'
    printf("memcpy: %s\n", dest3);
    
    // 注意：strcpy不安全，strncpy更安全
    printf("\n");
}

// 演示字符串连接函数
void demo_string_concat() {
    printf("=== 字符串连接 ===\n");
    
    char str1[50] = "Hello";
    char str2[] = ", World!";
    
    // strcat - 连接字符串
    printf("连接前: %s\n", str1);
    strcat(str1, str2);
    printf("strcat后: %s\n", str1);
    
    // strncat - 连接指定长度
    char str3[50] = "Good";
    strncat(str3, " Morning!", 4);  // 只连接" Mor"
    printf("strncat: %s\n", str3);
    
    // 手动连接（更灵活）
    char result[100] = "";
    strcpy(result, "Part1");
    strcat(result, "-");
    strcat(result, "Part2");
    strcat(result, "-");
    strcat(result, "Part3");
    printf("手动连接: %s\n", result);
    
    printf("\n");
}

// 演示字符串比较函数
void demo_string_compare() {
    printf("=== 字符串比较 ===\n");
    
    char str1[] = "apple";
    char str2[] = "banana";
    char str3[] = "apple";
    
    // strcmp - 比较整个字符串
    int result1 = strcmp(str1, str2);
    int result2 = strcmp(str1, str3);
    int result3 = strcmp(str2, str1);
    
    printf("strcmp(\"%s\", \"%s\") = %d %s\n", 
           str1, str2, result1, result1 < 0 ? "(小于)" : "");
    printf("strcmp(\"%s\", \"%s\") = %d %s\n", 
           str1, str3, result2, result2 == 0 ? "(相等)" : "");
    printf("strcmp(\"%s\", \"%s\") = %d %s\n", 
           str2, str1, result3, result3 > 0 ? "(大于)" : "");
    
    // strncmp - 比较前n个字符
    char str4[] = "application";
    char str5[] = "apple";
    int result4 = strncmp(str4, str5, 3);
    printf("strncmp(\"%s\", \"%s\", 3) = %d (前3个字符%s)\n", 
           str4, str5, result4, result4 == 0 ? "相同" : "不同");
    
    // 大小写不敏感比较（自定义实现）
    printf("\n");
}

// 演示字符串搜索函数
void demo_string_search() {
    printf("=== 字符串搜索 ===\n");
    
    char str[] = "Hello, World! Hello, C!";
    
    // strchr - 查找字符第一次出现
    char *pos1 = strchr(str, 'W');
    if (pos1 != NULL) {
        printf("strchr 找到 'W' 在位置: %ld\n", pos1 - str);
        printf("从该位置开始: %s\n", pos1);
    }
    
    // strrchr - 查找字符最后一次出现
    char *pos2 = strrchr(str, 'o');
    if (pos2 != NULL) {
        printf("strrchr 找到最后的 'o' 在位置: %ld\n", pos2 - str);
    }
    
    // strstr - 查找子字符串
    char *pos3 = strstr(str, "Hello");
    if (pos3 != NULL) {
        printf("strstr 找到 \"Hello\" 在位置: %ld\n", pos3 - str);
    }
    
    // 查找第二次出现
    char *pos4 = strstr(pos3 + 1, "Hello");
    if (pos4 != NULL) {
        printf("strstr 找到第二个 \"Hello\" 在位置: %ld\n", pos4 - str);
    }
    
    // strspn - 计算前缀长度（只包含指定字符集）
    char str2[] = "12345abc";
    size_t len1 = strspn(str2, "0123456789");
    printf("strspn: 前%zu个字符都是数字\n", len1);
    
    // strcspn - 计算前缀长度（不包含指定字符集）
    size_t len2 = strcspn(str2, "abc");
    printf("strcspn: 前%zu个字符都不是字母\n", len2);
    
    // strpbrk - 查找字符集中任意字符的第一次出现
    char *pos5 = strpbrk(str, "CW");
    if (pos5 != NULL) {
        printf("strpbrk 找到 'C' 或 'W' 在位置: %ld (字符: %c)\n", 
               pos5 - str, *pos5);
    }
    
    printf("\n");
}

// 演示字符串分割函数
void demo_string_tokenize() {
    printf("=== 字符串分割 ===\n");
    
    // strtok - 分割字符串
    char str[] = "apple,banana,cherry,date";
    char copy[50];
    strcpy(copy, str);  // strtok会修改原字符串
    
    printf("原字符串: %s\n", str);
    printf("分割结果:\n");
    
    char *token = strtok(copy, ",");
    int count = 1;
    while (token != NULL) {
        printf("  %d: %s\n", count++, token);
        token = strtok(NULL, ",");
    }
    
    // 多个分隔符
    char str2[] = "one;two,three:four five";
    char copy2[50];
    strcpy(copy2, str2);
    
    printf("\n多个分隔符: %s\n", str2);
    printf("分割结果:\n");
    
    token = strtok(copy2, ";,: ");
    count = 1;
    while (token != NULL) {
        printf("  %d: %s\n", count++, token);
        token = strtok(NULL, ";,: ");
    }
    
    printf("\n");
}

// 演示字符串长度函数
void demo_string_length() {
    printf("=== 字符串长度 ===\n");
    
    char str1[] = "Hello";
    char str2[] = "Hello, World!";
    char str3[] = "";
    
    printf("\"%s\" 长度: %zu\n", str1, strlen(str1));
    printf("\"%s\" 长度: %zu\n", str2, strlen(str2));
    printf("\"\" (空字符串) 长度: %zu\n", strlen(str3));
    
    // 包含空字符的字符串
    char str4[] = "Hello\0World";
    printf("\"Hello\\0World\" strlen: %zu (只计算到第一个\\0)\n", strlen(str4));
    printf("\"Hello\\0World\" sizeof: %zu (整个数组大小)\n", sizeof(str4));
    
    printf("\n");
}

// 演示内存操作函数
void demo_memory_functions() {
    printf("=== 内存操作函数 ===\n");
    
    // memset - 设置内存
    char buffer[20];
    memset(buffer, 'A', 10);
    buffer[10] = '\0';
    printf("memset: %s\n", buffer);
    
    // memcpy - 复制内存（不重叠）
    char src[] = "Source";
    char dest[20];
    memcpy(dest, src, strlen(src) + 1);
    printf("memcpy: %s\n", dest);
    
    // memmove - 复制内存（可重叠）
    char str[] = "Hello, World!";
    memmove(str + 7, str, 5);  // 复制"Hello"到"World"的位置
    str[12] = '\0';
    printf("memmove: %s\n", str);
    
    // memcmp - 比较内存
    char arr1[] = {1, 2, 3, 4, 5};
    char arr2[] = {1, 2, 3, 4, 6};
    int result = memcmp(arr1, arr2, 5);
    printf("memcmp: %d (不相等)\n", result);
    
    // memchr - 在内存中查找字符
    char data[] = "Hello, World!";
    char *pos = (char *)memchr(data, 'W', strlen(data));
    if (pos != NULL) {
        printf("memchr 找到 'W' 在位置: %ld\n", pos - data);
    }
    
    printf("\n");
}

// 演示错误信息函数
void demo_error_functions() {
    printf("=== 错误信息函数 ===\n");
    
    // strerror - 获取错误描述
    printf("错误0: %s\n", strerror(0));
    printf("错误1: %s\n", strerror(1));
    printf("错误2: %s\n", strerror(2));
    
    printf("\n");
}

// 演示实用字符串操作
void demo_practical_operations() {
    printf("=== 实用字符串操作 ===\n");
    
    // 1. 转换大小写（手动实现）
    char str1[] = "Hello World";
    printf("原字符串: %s\n", str1);
    
    for (int i = 0; str1[i]; i++) {
        str1[i] = toupper(str1[i]);
    }
    printf("转大写: %s\n", str1);
    
    for (int i = 0; str1[i]; i++) {
        str1[i] = tolower(str1[i]);
    }
    printf("转小写: %s\n", str1);
    
    // 2. 去除前后空格
    char str2[] = "   trim me   ";
    char *start = str2;
    while (*start == ' ') start++;
    
    char *end = str2 + strlen(str2) - 1;
    while (end > start && *end == ' ') end--;
    
    size_t len = end - start + 1;
    char trimmed[50];
    strncpy(trimmed, start, len);
    trimmed[len] = '\0';
    
    printf("\n原字符串: \"%s\"\n", str2);
    printf("去除空格: \"%s\"\n", trimmed);
    
    // 3. 字符串反转
    char str3[] = "reverse";
    size_t len3 = strlen(str3);
    for (size_t i = 0; i < len3 / 2; i++) {
        char temp = str3[i];
        str3[i] = str3[len3 - 1 - i];
        str3[len3 - 1 - i] = temp;
    }
    printf("\n反转字符串: %s\n", str3);
    
    // 4. 统计字符出现次数
    char str4[] = "mississippi";
    int count = 0;
    char target = 's';
    for (int i = 0; str4[i]; i++) {
        if (str4[i] == target) count++;
    }
    printf("\n\"%s\" 中字符 '%c' 出现 %d 次\n", str4, target, count);
    
    // 5. 检查回文
    char str5[] = "madam";
    size_t len5 = strlen(str5);
    int is_palindrome = 1;
    for (size_t i = 0; i < len5 / 2; i++) {
        if (str5[i] != str5[len5 - 1 - i]) {
            is_palindrome = 0;
            break;
        }
    }
    printf("\n\"%s\" %s回文\n", str5, is_palindrome ? "是" : "不是");
}

int main(void) {
    printf("C语言字符串操作函数示例\n");
    printf("==========================================\n\n");
    
    demo_string_copy();
    demo_string_concat();
    demo_string_compare();
    demo_string_search();
    demo_string_tokenize();
    demo_string_length();
    demo_memory_functions();
    demo_error_functions();
    demo_practical_operations();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
