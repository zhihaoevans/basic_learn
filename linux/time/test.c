#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void signalHandler(int signo)
{
    switch (signo){
        case SIGALRM:
            printf("Caught the SIGALRM signal!\n");
            break;
   }
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, signalHandler);

    struct itimerval new_value, old_value;
    new_value.it_value.tv_sec = 4;
    new_value.it_value.tv_usec = 0;
    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_usec = 200000;
    setitimer(ITIMER_REAL, &new_value, &old_value);
    
    for(;;);
     
    return 0;
}