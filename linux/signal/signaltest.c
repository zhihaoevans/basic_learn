#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sighandler(){
    printf("in sighandler\n");
    _exit(1);
}

int main(void){
    signal(SIGINT, sighandler);
    while(1){
        printf("in main\n");
        sleep(2);
    }
}