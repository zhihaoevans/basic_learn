/*
 * 主题说明：C 错误处理 —— C 没有异常机制，靠“返回码约定”（0 成功、非 0 失败）
 *           加 errno/perror/strerror 查询失败细节，失败路径统一用 EXIT_FAILURE 退出。
 * 运行命令：./c/build/bin/error_error_handling
 * 预期输出（关键行）：
 *   safe_div(10, 3) = 0，结果 3.33
 *   safe_div(1, 0) = -1（返回码约定：0 成功，非 0 失败）
 *   fopen no_such_file_for_error_demo.txt: No such file or directory（perror，输出到 stderr）
 *   errno = 2，strerror(errno) = No such file or directory
 *   EXIT_SUCCESS = 0，EXIT_FAILURE = 1
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 返回码约定：0 表示成功，非 0（常用 -1 或错误码）表示失败。
 * 结果经指针参数带出——这是 C 里“返回值留给状态”的常见写法。
 */
static int safe_div(int a, int b, double *out) {
    if (b == 0) {
        return -1;                     /* 失败：调用方必须检查返回值 */
    }
    *out = (double)a / (double)b;
    return 0;                          /* 成功 */
}

static void demo_return_code(void) {
    printf("=== 返回码约定 ===\n");
    double result = 0.0;

    int rc = safe_div(10, 3, &result);
    if (rc == 0) {
        printf("safe_div(10, 3) = %d，结果 %.2f\n", rc, result);
    }

    rc = safe_div(1, 0, &result);
    if (rc != 0) {
        printf("safe_div(1, 0) = %d（返回码约定：0 成功，非 0 失败）\n", rc);
        /* 真实程序里致命错误常直接 return EXIT_FAILURE / exit(EXIT_FAILURE) */
    }
}

static void demo_errno(void) {
    printf("\n=== errno / perror / strerror ===\n");

    errno = 0;                         /* 好习惯：调用前清零 */
    FILE *f = fopen("no_such_file_for_error_demo.txt", "r");
    if (f == NULL) {
        /* 失败后立即保存 errno：后续任何库函数（哪怕成功）都可能改写它 */
        int saved_errno = errno;
        /* perror：自动打印 "前缀: <系统错误信息>"，输出到 stderr */
        perror("fopen no_such_file_for_error_demo.txt");
        /* errno 保存最近一次错误的编号；strerror 把编号翻译成可读文本 */
        printf("errno = %d，strerror(errno) = %s\n", saved_errno,
               strerror(saved_errno));
        /*
         * 约定：errno 只有在函数报告失败（返回 NULL/-1 等）之后才去查；
         * 它不会被成功调用清零，所以不能单凭 errno != 0 判断出错。
         */
    } else {
        fclose(f);                     /* 不可能走到，但每个分支都要处理 */
    }
}

static void demo_exit_status(void) {
    printf("\n=== 退出码 ===\n");
    printf("EXIT_SUCCESS = %d，EXIT_FAILURE = %d\n",
           EXIT_SUCCESS, EXIT_FAILURE);
    /* main 的返回值就是进程退出码：shell 用 $? 检查，CI 靠非 0 退出码判失败 */
}

int main(void) {
    printf("C 错误处理示例\n");
    printf("==========================================\n\n");

    demo_return_code();
    demo_errno();
    demo_exit_status();

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
