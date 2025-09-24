/*
 * string.h 标准头文件演示
 * 演示字符串处理库的各种函数用法
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void demo_string_length() {
    printf("=== 字符串长度演示 ===\n");
    
    char str1[] = "Hello, World!";
    char str2[] = "C Programming";
    char empty[] = "";
    
    printf("strlen(\"%s\") = %zu\n", str1, strlen(str1));
    printf("strlen(\"%s\") = %zu\n", str2, strlen(str2));
    printf("strlen(\"%s\") = %zu\n", empty, strlen(empty));
    
    // 包含中文的字符串（UTF-8编码）
    char chinese[] = "你好世界";
    printf("strlen(\"%s\") = %zu (字节数，不是字符数)\n", chinese, strlen(chinese));
}

void demo_string_copy() {
    printf("\n=== 字符串复制演示 ===\n");
    
    char source[] = "Hello, C Programming!";
    char dest1[50];
    char dest2[50];
    char dest3[10];  // 较小的缓冲区
    
    // strcpy - 复制整个字符串
    strcpy(dest1, source);
    printf("strcpy结果: \"%s\"\n", dest1);
    
    // strncpy - 复制指定长度的字符串
    strncpy(dest2, source, 5);
    dest2[5] = '\0';  // 手动添加结束符
    printf("strncpy(source, 5)结果: \"%s\"\n", dest2);
    
    // 安全的strncpy使用
    strncpy(dest3, source, sizeof(dest3) - 1);
    dest3[sizeof(dest3) - 1] = '\0';  // 确保以null结尾
    printf("安全的strncpy到小缓冲区: \"%s\"\n", dest3);
    
    // 演示strcpy的危险性（注释掉避免缓冲区溢出）
    /*
    char small[5];
    strcpy(small, source);  // 这会导致缓冲区溢出！
    */
    printf("注意: strcpy不检查目标缓冲区大小，可能导致溢出\n");
}

void demo_string_concatenation() {
    printf("\n=== 字符串连接演示 ===\n");
    
    char str1[100] = "Hello";
    char str2[] = ", World!";
    char str3[] = " How are you?";
    
    printf("初始字符串: \"%s\"\n", str1);
    
    // strcat - 连接字符串
    strcat(str1, str2);
    printf("strcat后: \"%s\"\n", str1);
    
    // strncat - 连接指定长度的字符串
    strncat(str1, str3, 5);  // 只连接前5个字符
    printf("strncat(str3, 5)后: \"%s\"\n", str1);
    
    // 重新初始化演示完整连接
    strcpy(str1, "C");
    strcat(str1, " Programming");
    strcat(str1, " is");
    strcat(str1, " fun!");
    printf("多次strcat结果: \"%s\"\n", str1);
}

void demo_string_comparison() {
    printf("\n=== 字符串比较演示 ===\n");
    
    char str1[] = "apple";
    char str2[] = "banana";
    char str3[] = "apple";
    char str4[] = "Apple";
    
    // strcmp - 比较字符串
    int result1 = strcmp(str1, str2);
    int result2 = strcmp(str1, str3);
    int result3 = strcmp(str1, str4);
    
    printf("strcmp(\"%s\", \"%s\") = %d %s\n", str1, str2, result1, 
           result1 < 0 ? "(str1 < str2)" : result1 > 0 ? "(str1 > str2)" : "(相等)");
    printf("strcmp(\"%s\", \"%s\") = %d %s\n", str1, str3, result2,
           result2 < 0 ? "(str1 < str3)" : result2 > 0 ? "(str1 > str3)" : "(相等)");
    printf("strcmp(\"%s\", \"%s\") = %d %s\n", str1, str4, result3,
           result3 < 0 ? "(str1 < str4)" : result3 > 0 ? "(str1 > str4)" : "(相等)");
    
    // strncmp - 比较指定长度的字符串
    char long1[] = "programming";
    char long2[] = "program";
    
    int result4 = strncmp(long1, long2, 7);  // 只比较前7个字符
    int result5 = strncmp(long1, long2, 10); // 比较前10个字符
    
    printf("strncmp(\"%s\", \"%s\", 7) = %d\n", long1, long2, result4);
    printf("strncmp(\"%s\", \"%s\", 10) = %d\n", long1, long2, result5);
}

void demo_string_search() {
    printf("\n=== 字符串搜索演示 ===\n");
    
    char text[] = "The quick brown fox jumps over the lazy dog";
    char ch = 'o';
    char substr[] = "fox";
    char chars[] = "aeiou";
    
    printf("原始字符串: \"%s\"\n", text);
    
    // strchr - 查找字符首次出现的位置
    char *pos1 = strchr(text, ch);
    if (pos1 != NULL) {
        printf("strchr找到字符'%c'的位置: %ld\n", ch, pos1 - text);
        printf("从该位置开始的字符串: \"%s\"\n", pos1);
    }
    
    // strrchr - 查找字符最后出现的位置
    char *pos2 = strrchr(text, ch);
    if (pos2 != NULL) {
        printf("strrchr找到字符'%c'最后位置: %ld\n", ch, pos2 - text);
    }
    
    // strstr - 查找子字符串
    char *pos3 = strstr(text, substr);
    if (pos3 != NULL) {
        printf("strstr找到子字符串\"%s\"的位置: %ld\n", substr, pos3 - text);
        printf("从该位置开始: \"%s\"\n", pos3);
    }
    
    // strspn - 计算字符串开头连续包含指定字符集的长度
    char test_str[] = "aeiou123";
    size_t span1 = strspn(test_str, chars);
    printf("strspn(\"%s\", \"%s\") = %zu\n", test_str, chars, span1);
    
    // strcspn - 计算字符串开头连续不包含指定字符集的长度
    char test_str2[] = "hello world";
    size_t span2 = strcspn(test_str2, chars);
    printf("strcspn(\"%s\", \"%s\") = %zu\n", test_str2, chars, span2);
    
    // strpbrk - 查找字符串中首次出现指定字符集中任一字符的位置
    char *pos4 = strpbrk(test_str2, chars);
    if (pos4 != NULL) {
        printf("strpbrk在\"%s\"中找到字符'%c'的位置: %ld\n", test_str2, *pos4, pos4 - test_str2);
    }
}

void demo_string_tokenization() {
    printf("\n=== 字符串分割演示 ===\n");
    
    // 注意：strtok会修改原字符串，所以使用副本
    char text[] = "apple,banana;orange:grape|lemon";
    char delimiters[] = ",;:|";
    
    printf("原始字符串: \"%s\"\n", text);
    printf("分隔符: \"%s\"\n", delimiters);
    printf("分割结果:\n");
    
    char *token = strtok(text, delimiters);
    int count = 1;
    
    while (token != NULL) {
        printf("  Token %d: \"%s\"\n", count++, token);
        token = strtok(NULL, delimiters);  // 后续调用传入NULL
    }
    
    // 演示strtok修改了原字符串
    printf("strtok后的原字符串（已被修改）: ");
    for (int i = 0; i < 30; i++) {
        if (text[i] == '\0') {
            printf("\\0");
        } else {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}

void demo_memory_functions() {
    printf("\n=== 内存操作函数演示 ===\n");
    
    char buffer1[20];
    char buffer2[20];
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[5];
    
    // memset - 设置内存块
    memset(buffer1, 'A', 10);
    buffer1[10] = '\0';
    printf("memset设置的缓冲区: \"%s\"\n", buffer1);
    
    memset(buffer1, 0, sizeof(buffer1));  // 清零
    printf("memset清零后的缓冲区长度: %zu\n", strlen(buffer1));
    
    // memcpy - 复制内存块
    strcpy(buffer1, "Hello World");
    memcpy(buffer2, buffer1, strlen(buffer1) + 1);
    printf("memcpy复制结果: \"%s\"\n", buffer2);
    
    // 复制整数数组
    memcpy(arr2, arr1, sizeof(arr1));
    printf("memcpy复制数组: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    
    // memmove - 安全的内存移动（处理重叠区域）
    char overlap[] = "1234567890";
    printf("memmove前: \"%s\"\n", overlap);
    memmove(overlap + 2, overlap, 5);  // 重叠移动
    printf("memmove后: \"%s\"\n", overlap);
    
    // memcmp - 比较内存块
    char mem1[] = "abcdef";
    char mem2[] = "abcdxy";
    int mem_result = memcmp(mem1, mem2, 4);  // 只比较前4个字节
    printf("memcmp(\"%s\", \"%s\", 4) = %d\n", mem1, mem2, mem_result);
    
    mem_result = memcmp(mem1, mem2, 6);  // 比较全部6个字节
    printf("memcmp(\"%s\", \"%s\", 6) = %d\n", mem1, mem2, mem_result);
    
    // memchr - 在内存块中查找字符
    char *found = (char*)memchr(mem1, 'd', 6);
    if (found != NULL) {
        printf("memchr在\"%s\"中找到字符'd'的位置: %ld\n", mem1, found - mem1);
    }
}

void demo_string_transformation() {
    printf("\n=== 字符串转换演示 ===\n");
    
    // 注意：C标准库没有直接的大小写转换函数，这里演示手动实现
    char text[] = "Hello World 123!";
    char upper[50], lower[50];
    
    printf("原始字符串: \"%s\"\n", text);
    
    // 手动转换为大写
    strcpy(upper, text);
    for (int i = 0; upper[i]; i++) {
        if (upper[i] >= 'a' && upper[i] <= 'z') {
            upper[i] = upper[i] - 'a' + 'A';
        }
    }
    printf("转换为大写: \"%s\"\n", upper);
    
    // 手动转换为小写
    strcpy(lower, text);
    for (int i = 0; lower[i]; i++) {
        if (lower[i] >= 'A' && lower[i] <= 'Z') {
            lower[i] = lower[i] - 'A' + 'a';
        }
    }
    printf("转换为小写: \"%s\"\n", lower);
    
    // 字符串反转
    char reverse[50];
    strcpy(reverse, text);
    int len = strlen(reverse);
    for (int i = 0; i < len / 2; i++) {
        char temp = reverse[i];
        reverse[i] = reverse[len - 1 - i];
        reverse[len - 1 - i] = temp;
    }
    printf("字符串反转: \"%s\"\n", reverse);
}

void demo_error_messages() {
    printf("\n=== 错误信息演示 ===\n");
    
    // strerror - 获取错误码对应的错误信息
    printf("一些常见的错误信息:\n");
    for (int i = 0; i < 10; i++) {
        printf("错误码 %d: %s\n", i, strerror(i));
    }
    
    // perror 在 stdio.h 中，这里只是提及
    printf("\n注意: perror()函数在stdio.h中，用于打印系统错误信息\n");
}

int main() {
    printf("C语言 string.h 标准头文件演示\n");
    printf("=================================\n");
    
    demo_string_length();
    demo_string_copy();
    demo_string_concatenation();
    demo_string_comparison();
    demo_string_search();
    demo_string_tokenization();
    demo_memory_functions();
    demo_string_transformation();
    demo_error_messages();
    
    printf("\n演示完成！\n");
    return 0;
}