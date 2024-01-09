/*线程局部存储*/

#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

__thread FILE* thread_log = NULL;
void write_to_thread_log(const char* message)
{
    fprintf(thread_log, "%s\n", message);
}

void *thread_function(void* arg)
{
    char thread_log_filename[128];
    sprintf(thread_log_filename, "thread%d.log", (unsigned long)pthread_self());

    thread_log = fopen(thread_log_filename, "w");
    write_to_thread_log("Thread starting.");

    fclose(thread_log);
    return NULL;
}

int main()
{
    int i;
    pthread_t threads[5];

    for (i = 0; i < 5; ++i)
        pthread_create(&(threads[i]), NULL, thread_function, NULL);
    for (i = 0; i < 5; ++i)
        pthread_join(threads[i], NULL);
    return 0;
}
