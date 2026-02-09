#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int a = 0;

void *thread1_func(void *p_arg)
{
        while (1)
        {
                a++;
                sleep(10);
        }
}

int main(int argc, char* argv[])
{
        pthread_t t1;

        pthread_create(&t1, NULL, thread1_func, "Thread 1");

        sleep(1000);
        return 0;
}
