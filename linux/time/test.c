#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main(void){

    struct timeval mytimeval;
    time_t  mytime;
    time_t thetime;
    
    if (!gettimeofday(&mytimeval, NULL)){
        printf("sec: %d, msec: %d\n", mytimeval.tv_sec, mytimeval.tv_usec);
    }

    thetime = time(&mytime);
    printf("sec: %d,%d\n", thetime, mytime);
    printf("time: %s", ctime(&mytime));



    return 0;
}