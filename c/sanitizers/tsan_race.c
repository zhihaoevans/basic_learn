#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// ThreadSanitizer (TSan) 示例：数据竞争 (Data Race)
// 编译命令: gcc -fsanitize=thread -g tsan_race.c -o tsan_race -pthread

int shared_counter = 0;

void *thread_func(void *arg) {
    for (int i = 0; i < 10000; ++i) {
        // 数据竞争：多个线程同时读写 shared_counter 且没有同步机制（如互斥锁）
        shared_counter++;
    }
    return NULL;
}

int main() {
    printf("ThreadSanitizer Data Race Example\n");

    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d (Expected: 20000)\n", shared_counter);
    return 0;
}
