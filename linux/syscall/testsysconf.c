#include <stdio.h>
#include <unistd.h>


int main(void){
    printf("it is %x\n", sysconf(_SC_THREAD_STACK_MION));
    return 0;
}