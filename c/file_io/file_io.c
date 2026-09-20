/*
 * 主题说明：C 文件读写 —— fopen 六种常用模式、fprintf 写文本、fgets 逐行读、
 *           fwrite/fread 二进制读写结构体，以及 fclose 与错误检查的完整约定。
 * 运行命令：./c/build/bin/file_io_file_io
 * 预期输出（关键行）：
 *   常用模式: r 读(须存在) / w 写(清空或创建) / a 追加 / r+ 读写 / w+ 读写清空 / 加 b 为二进制
 *   写入 3 行文本后关闭
 *   读出: C 文件读写示例
 *   读出: 第二行：fprintf 写入文本
 *   读出: 第三行：fgets 逐行读取
 *   读回记录: Alice 92 / Bob 85 / Carol 78，共 3 条，二进制读写校验一致
 *   清理临时文件完成（remove 删除演示文件）
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_FILE "file_io_demo.txt"
#define BIN_FILE  "file_io_demo.bin"

/* 固定长度的 POD 结构体适合直接二进制存取 */
typedef struct {
    char name[16];
    int score;
} Score;

static int write_text(void) {
    FILE *f = fopen(TEXT_FILE, "w");   /* w：文件不存在则创建，存在则清空 */
    if (f == NULL) {
        perror("fopen " TEXT_FILE);
        return -1;
    }
    fprintf(f, "C 文件读写示例\n");
    fprintf(f, "第二行：fprintf 写入文本\n");
    fprintf(f, "第三行：fgets 逐行读取\n");
    fclose(f);                         /* 每次成功 fopen 都要配对 fclose */
    printf("写入 3 行文本后关闭\n");
    return 0;
}

static int read_text(void) {
    FILE *f = fopen(TEXT_FILE, "r");   /* r：只读，文件必须已存在 */
    if (f == NULL) {
        perror("fopen " TEXT_FILE);
        return -1;
    }
    char line[128];
    while (fgets(line, sizeof line, f) != NULL) {
        /* fgets 保留行尾 '\n'；去掉它便于处理 */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        printf("读出: %s\n", line);
    }
    if (ferror(f)) {                   /* 区分“读完了”与“读出错了” */
        fprintf(stderr, "fgets 出错\n");
        fclose(f);
        return -1;
    }
    fclose(f);                         /* fgets 返回 NULL 且无错 = 正常读完 */
    return 0;
}

static int write_bin(void) {
    Score records[3] = {{"Alice", 92}, {"Bob", 85}, {"Carol", 78}};
    FILE *f = fopen(BIN_FILE, "wb");   /* wb：二进制写，避免文本模式的换行转换 */
    if (f == NULL) {
        perror("fopen " BIN_FILE);
        return -1;
    }
    size_t n = fwrite(records, sizeof records[0], 3, f);
    fclose(f);
    if (n != 3) {                      /* fwrite 返回成功写入的元素个数 */
        fprintf(stderr, "fwrite 只写入 %zu 个元素\n", n);
        return -1;
    }
    return 0;
}

static int read_bin(void) {
    Score back[3];
    FILE *f = fopen(BIN_FILE, "rb");
    if (f == NULL) {
        perror("fopen " BIN_FILE);
        return -1;
    }
    size_t n = fread(back, sizeof back[0], 3, f);
    fclose(f);
    if (n != 3) {
        fprintf(stderr, "fread 只读到 %zu 个元素\n", n);
        return -1;
    }
    for (size_t i = 0; i < 3; i++) {
        printf("读回记录: %s %d\n", back[i].name, back[i].score);
    }
    if (memcmp(back, (Score[3]){{"Alice", 92}, {"Bob", 85}, {"Carol", 78}},
               sizeof back) == 0) {
        printf("共 %zu 条，二进制读写校验一致\n", n);
        return 0;
    }
    return -1;
}

int main(void) {
    printf("C 文件读写示例\n");
    printf("==========================================\n\n");

    printf("常用模式: r 读(须存在) / w 写(清空或创建) / a 追加 / r+ 读写 / w+ 读写清空 / 加 b 为二进制\n\n");

    /* 每一步都检查返回值，失败立即退出（错误处理见 c/error/ 主题） */
    if (write_text() != 0 || read_text() != 0 ||
        write_bin() != 0 || read_bin() != 0) {
        fprintf(stderr, "文件操作失败\n");
        return EXIT_FAILURE;
    }

    remove(TEXT_FILE);                 /* 演示文件用完即删，不留垃圾 */
    remove(BIN_FILE);
    printf("清理临时文件完成（remove 删除演示文件）\n");

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
