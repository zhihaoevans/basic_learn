/*
 * 字符串基础示例
 * 演示C语言中字符串的基本概念、声明和初始化
 * C17/C18 标准
 */

#include <stdio.h>
#include <string.h>

// 演示字符串的基本概念
void demo_string_basics() {
    printf("=== 字符串基础概念 ===\n");
    
    // 字符串是以'\0'结尾的字符数组
    char str1[] = "Hello";
    printf("字符串: %s\n", str1);
    printf("字符串长度: %zu\n", strlen(str1));
    printf("数组大小: %zu (包括'\\0')\n", sizeof(str1));
    
    // 逐个字符打印
    printf("字符串的各个字符:\n");
    for (size_t i = 0; i < strlen(str1); i++) {
        printf("  str1[%zu] = '%c' (ASCII: %d)\n", i, str1[i], str1[i]);
    }
    printf("  str1[%zu] = '\\0' (ASCII: %d) - 字符串结束符\n", 
           strlen(str1), str1[strlen(str1)]);
    
    printf("\n");
}

// 演示字符串的声明和初始化
void demo_string_declaration() {
    printf("=== 字符串声明和初始化 ===\n");
    
    // 方式1: 字符数组初始化
    char str1[] = "Hello";
    printf("方式1 (字符数组): %s\n", str1);
    
    // 方式2: 字符数组逐个初始化
    char str2[] = {'W', 'o', 'r', 'l', 'd', '\0'};
    printf("方式2 (逐个字符): %s\n", str2);
    
    // 方式3: 指定大小的字符数组
    char str3[20] = "C Language";
    printf("方式3 (指定大小): %s\n", str3);
    
    // 方式4: 字符串指针（指向字符串字面量）
    const char *str4 = "String Literal";
    printf("方式4 (字符串指针): %s\n", str4);
    
    // 注意：字符串字面量是只读的
    // str4[0] = 'X';  // 错误！会导致运行时错误
    
    // 方式5: 部分初始化
    char str5[10] = "Hi";
    printf("方式5 (部分初始化): %s\n", str5);
    printf("剩余部分被填充为0: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", str5[i]);
    }
    printf("\n\n");
}

// 演示字符串的输入
void demo_string_input() {
    printf("=== 字符串输入 ===\n");
    
    char name[50];
    
    // 使用fgets（推荐，更安全）
    printf("请输入你的名字（使用fgets）: ");
    if (fgets(name, sizeof(name), stdin) != NULL) {
        // 移除fgets读取的换行符
        size_t len = strlen(name);
        if (len > 0 && name[len-1] == '\n') {
            name[len-1] = '\0';
        }
        printf("你好, %s!\n", name);
    }
    
    // scanf的问题演示（注释掉避免实际输入）
    /*
    // scanf会在空格处停止读取
    printf("请输入你的全名: ");
    scanf("%s", name);  // 只能读取到第一个空格
    printf("读取到: %s\n", name);
    
    // 使用scanf读取带空格的字符串
    printf("请输入一行文本: ");
    scanf(" %[^\n]", name);  // 读取直到换行符
    printf("读取到: %s\n", name);
    */
    
    printf("\n");
}

// 演示字符串的访问和修改
void demo_string_access() {
    printf("=== 字符串访问和修改 ===\n");
    
    char str[] = "Hello World";
    printf("原始字符串: %s\n", str);
    
    // 访问单个字符
    printf("第一个字符: %c\n", str[0]);
    printf("第五个字符: %c\n", str[4]);
    
    // 修改字符
    str[0] = 'h';  // 改为小写
    printf("修改后: %s\n", str);
    
    // 修改整个单词
    str[6] = 'C';
    str[7] = '+';
    str[8] = '+';
    str[9] = '\0';  // 缩短字符串
    printf("修改后: %s\n", str);
    
    printf("\n");
}

// 演示字符串长度和大小
void demo_string_length() {
    printf("=== 字符串长度和大小 ===\n");
    
    char str1[50] = "Hello";
    
    printf("字符串内容: \"%s\"\n", str1);
    printf("strlen(str1): %zu (字符串长度，不包括'\\0')\n", strlen(str1));
    printf("sizeof(str1): %zu (数组大小，字节数)\n", sizeof(str1));
    
    // 空字符串
    char str2[10] = "";
    printf("\n空字符串内容: \"%s\"\n", str2);
    printf("strlen(str2): %zu\n", strlen(str2));
    printf("sizeof(str2): %zu\n", sizeof(str2));
    
    // 中文字符串（UTF-8编码）
    char str3[] = "你好世界";
    printf("\n中文字符串: \"%s\"\n", str3);
    printf("strlen(str3): %zu (字节数)\n", strlen(str3));
    printf("sizeof(str3): %zu\n", sizeof(str3));
    
    printf("\n");
}

// 演示字符串字面量
void demo_string_literals() {
    printf("=== 字符串字面量 ===\n");
    
    // 普通字符串字面量
    printf("普通字符串: %s\n", "Hello, World!");
    
    // 多行字符串（相邻字符串会自动连接）
    printf("多行字符串: %s\n", 
           "这是第一行 "
           "这是第二行 "
           "这是第三行");
    
    printf("\n实际的多行:\n%s\n", 
           "第一行\n"
           "第二行\n"
           "第三行");
    
    // 转义字符
    printf("\n转义字符演示:\n");
    printf("换行符: 第一行\\n第二行\n");
    printf("制表符: 列1\\t列2\\t列3\n");
    printf("反斜杠: C:\\\\Users\\\\Documents\n");
    printf("引号: 他说\"你好\"\n");
    printf("单引号: It\\'s a test\n");
    
    // 原始字符串（C11不支持，但可以手动处理）
    printf("\n路径字符串: %s\n", "C:\\Program Files\\MyApp");
    
    printf("\n");
}

// 演示字符串与字符数组的区别
void demo_string_vs_char_array() {
    printf("=== 字符串 vs 字符数组 ===\n");
    
    // 字符串（以'\0'结尾）
    char str[] = "Hello";
    printf("字符串: %s\n", str);
    printf("长度: %zu\n", strlen(str));
    
    // 字符数组（不以'\0'结尾）
    char arr[] = {'H', 'e', 'l', 'l', 'o'};
    printf("字符数组大小: %zu\n", sizeof(arr));
    // printf("字符串: %s\n", arr);  // 危险！没有'\0'结束符
    
    // 打印字符数组
    printf("字符数组内容: ");
    for (size_t i = 0; i < sizeof(arr); i++) {
        printf("%c", arr[i]);
    }
    printf("\n\n");
}

// 演示常见错误
void demo_common_mistakes() {
    printf("=== 常见错误演示 ===\n");
    
    // 错误1: 缓冲区太小
    char small[5];
    // strcpy(small, "这是一个很长的字符串");  // 缓冲区溢出！
    strncpy(small, "这是一个很长的字符串", sizeof(small) - 1);
    small[sizeof(small) - 1] = '\0';
    printf("安全复制（截断）: %s\n", small);
    
    // 错误2: 忘记'\0'结束符
    char no_null[5] = {'H', 'e', 'l', 'l', 'o'};
    char safe[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    printf("带结束符的字符串: %s\n", safe);
    // printf("不带结束符: %s\n", no_null);  // 危险！
    
    // 错误3: 修改字符串字面量
    // const char *literal = "Hello";
    // literal[0] = 'h';  // 运行时错误！
    
    // 正确做法：复制到可修改的数组
    char modifiable[] = "Hello";
    modifiable[0] = 'h';
    printf("可修改的字符串: %s\n", modifiable);
    
    printf("\n");
}

// 演示字符串的遍历
void demo_string_traversal() {
    printf("=== 字符串遍历 ===\n");
    
    char str[] = "Hello, World!";
    
    // 方法1: 使用索引
    printf("方法1 - 使用索引:\n");
    for (size_t i = 0; i < strlen(str); i++) {
        printf("%c ", str[i]);
    }
    printf("\n");
    
    // 方法2: 使用指针
    printf("方法2 - 使用指针:\n");
    for (char *p = str; *p != '\0'; p++) {
        printf("%c ", *p);
    }
    printf("\n");
    
    // 方法3: 计数器优化（避免重复计算strlen）
    printf("方法3 - 使用缓存长度:\n");
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        printf("%c ", str[i]);
    }
    printf("\n\n");
}

int main(void) {
    printf("C语言字符串基础示例\n");
    printf("==========================================\n\n");
    
    demo_string_basics();
    demo_string_declaration();
    // demo_string_input();  // 需要用户输入，注释掉
    demo_string_access();
    demo_string_length();
    demo_string_literals();
    demo_string_vs_char_array();
    demo_common_mistakes();
    demo_string_traversal();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
