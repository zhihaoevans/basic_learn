/*
 * 主题说明：C 控制流 —— if/else、switch（含 fallthrough 说明）、for/while/do-while 三种循环、
 *           break/continue，以及 goto 的一个恰当用例（跳出多重循环）。
 * 运行命令：./c/build/bin/control_control_flow
 * 预期输出（关键行）：
 *   if-else: score=72 → 及格（C 档）
 *   switch: "hello world" 中元音 3 个，其他字符 8 个（a/e/i/o/u 共用一个分支）
 *   switch: day=0 → 周日，随后落入 case 6 → 周末（fallthrough：不加 break 会继续执行）
 *   for: 1+2+...+100 = 5050
 *   while: 3 2 1 发射！
 *   do-while: 条件一开始为假（10 < 5 不成立），循环体仍执行了一次
 *   break/continue: 1 3 5 7 （偶数跳过，遇 8 提前退出），累加 = 16
 *   goto: 在 3x3 网格找到 9，位置 (1, 2)（一次跳出双重循环）
 */

#include <stdio.h>

static void demo_if(void) {
    printf("=== if / else if / else ===\n");
    int score = 72;
    if (score >= 90) {
        printf("if-else: score=%d → 优秀（A 档）\n", score);
    } else if (score >= 60) {
        printf("if-else: score=%d → 及格（C 档）\n", score);
    } else {
        printf("if-else: score=%d → 不及格\n", score);
    }
}

static void demo_switch(void) {
    printf("\n=== switch 与 fallthrough ===\n");
    const char *text = "hello world";
    int vowels = 0, others = 0;

    /* 写法1：多个 case 标签叠在一起，共享同一段代码 */
    for (size_t i = 0; text[i] != '\0'; i++) {
        switch (text[i]) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            vowels++;
            break;                     /* break 跳出 switch；漏写会“落入”下一分支 */
        default:
            others++;
            break;
        }
    }
    printf("switch: \"%s\" 中元音 %d 个，其他字符 %d 个（a/e/i/o/u 共用一个分支）\n",
           text, vowels, others);

    /* 写法2：故意 fallthrough——不加 break，执行流落入下一 case 的代码 */
    int day = 0;                       /* 0=周日，6=周六，其余为工作日 */
    switch (day) {
    case 0:
        printf("switch: day=0 → 周日，");
        printf("随后落入 case 6 → 周末（fallthrough：不加 break 会继续执行）\n");
        /* fallthrough：故意不加 break */
    case 6:
        printf("switch: 判定为周末\n");
        break;
    default:
        printf("switch: 判定为工作日\n");
        break;
    }
}

static void demo_loops(void) {
    printf("\n=== 三种循环 ===\n");

    int sum = 0;
    for (int i = 1; i <= 100; i++) {   /* for：次数已知时首选 */
        sum += i;
    }
    printf("for: 1+2+...+100 = %d\n", sum);

    int n = 3;
    printf("while: ");
    while (n > 0) {                    /* while：先判断后执行 */
        printf("%d ", n);
        n--;
    }
    printf("发射！\n");

    int i = 10;                        /* 条件一开始就为假 */
    do {
        printf("do-while: 条件一开始为假（%d < 5 不成立），循环体仍执行了一次\n", i);
        i++;
    } while (i < 5);                   /* do-while：先执行后判断，至少跑一次 */
}

static void demo_break_continue(void) {
    printf("\n=== break 与 continue ===\n");
    int total = 0;
    for (int i = 1; i < 10; i++) {
        if (i == 8) {
            break;                     /* break：彻底退出循环 */
        }
        if (i % 2 == 0) {
            continue;                  /* continue：跳过本轮剩余代码，进入下一轮 */
        }
        printf("%d ", i);
        total += i;
    }
    printf("（偶数跳过，遇 8 提前退出），累加 = %d\n", total);
}

static void demo_goto(void) {
    printf("\n=== goto：跳出多重循环 ===\n");
    int grid[3][3] = {{1, 2, 3}, {4, 5, 9}, {7, 8, 6}};
    int found_r = -1, found_c = -1;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[r][c] == 9) {
                found_r = r;
                found_c = c;
                goto found;            /* 一次跳出两层循环；break 只能退出一层 */
            }
        }
    }
found:
    printf("goto: 在 3x3 网格找到 9，位置 (%d, %d)（一次跳出双重循环）\n",
           found_r, found_c);
    /*
     * goto 只建议用于：跳出多重循环、统一的错误清理出口。
     * 其余场合的跳转用结构化语句（if/循环/break）表达，滥用 goto 会破坏可读性。
     */
}

int main(void) {
    printf("C 控制流示例\n");
    printf("==========================================\n\n");

    demo_if();
    demo_switch();
    demo_loops();
    demo_break_continue();
    demo_goto();

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
