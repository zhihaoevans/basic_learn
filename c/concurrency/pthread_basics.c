/*
 * 主题说明：C 并发入门（POSIX 线程）—— pthread_create 创建线程、pthread_join 等待回收，
 *           pthread_mutex 保护共享计数器：4 个线程各累加 100000 次结果恒为 400000。
 * 运行命令：./c/build/bin/concurrency_pthread_basics
 * 预期输出（关键行）：
 *   创建 4 个线程，每个对共享计数器加 100000 次（互斥锁保护）
 *   线程 0 结束，返回值 1（线程 1/2/3 依创建顺序 join，返回 2/3/4）
 *   互斥保护下 counter = 400000（4 × 100000，结果恒定）
 */

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_COUNT 4
#define LOOP_COUNT   100000

static long counter = 0;               /* 多线程共享的可变数据 */
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

/* 线程入口：签名必须是 void *(*fn)(void *) */
static void *worker(void *arg) {
    int id = *(int *)arg;              /* 主线程传入的 id 数组元素地址 */
    for (int i = 0; i < LOOP_COUNT; i++) {
        pthread_mutex_lock(&counter_mutex);   /* 加锁：同一时刻只有一个线程进入 */
        counter = counter + 1;                /* “读-改-写”三步必须是临界区 */
        pthread_mutex_unlock(&counter_mutex); /* 解锁：尽快释放，别把无关工作锁进去 */
    }
    return (void *)(intptr_t)(id + 1); /* 返回值经 pthread_join 的二级指针带出 */
}

int main(void) {
    printf("C 并发入门示例（pthread）\n");
    printf("==========================================\n\n");

    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT];             /* 每线程一个槽位，避免传同一地址互相覆盖 */

    printf("创建 %d 个线程，每个对共享计数器加 %d 次（互斥锁保护）\n",
           THREAD_COUNT, LOOP_COUNT);

    for (int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i;
        int rc = pthread_create(&threads[i], NULL, worker, &ids[i]);
        if (rc != 0) {                 /* pthread_create 出错返回错误码（非 -1，不设 errno） */
            fprintf(stderr, "pthread_create 失败: %d\n", rc);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        void *ret = NULL;
        pthread_join(threads[i], &ret); /* 等待线程结束并回收，取回返回值 */
        printf("线程 %d 结束，返回值 %ld\n", i, (long)(intptr_t)ret);
    }

    printf("互斥保护下 counter = %ld（%d × %d，结果恒定）\n",
           counter, THREAD_COUNT, LOOP_COUNT);
    /*
     * 反面教材（仅注释，不运行）：若 counter++ 不加锁，多线程的“读-改-写”
     * 相互交错，结果通常小于 400000 且每次不同——更严重的是，C11 起对
     * 非原子变量的并发读写（数据竞争）属于未定义行为，见 c/sanitizers/。
     */

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
