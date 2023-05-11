#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int do_cleanup = 0;
char *mmap_file;

void sig_handler(int sig){

    printf("get signal %d\n", sig);
    switch (sig)
    {
    case SIGTERM:
        printf("get SIGTERM\n");
        munmap(mmap_file, 5);
        do_cleanup = 1;
        goto out;

    case SIGSEGV:
        printf("get SIGSEGV\n");
        goto out;

    case SIGINT:
        printf("get SIGINT\n");
        goto out;

    
    default:
        printf("others\n");
        break;
    }
out:
    kill(getpid(), SIGKILL);
}

int set_signal(void){
    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGSEGV, sig_handler);
}

int main(void){

    int fd = -1;

    struct stat file_stat;

    set_signal();

    fd = open("./test.txt", O_RDWR|O_CREAT);
    if(fd < 0){
        printf("open failed\n");
        return -1;
    }

    //fstat(fd, &file_stat);

    mmap_file = mmap(NULL, 5, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (MAP_FAILED == mmap_file){
        printf("mmap failed\n");
        close(fd);
        return -1;
    }

    while(!do_cleanup){
        mmap_file[0] = 'a';
        sleep(3);
        mmap_file[0] = 'b';
        sleep(3);
    }
    munmap(mmap_file, 5);
    return 0;
}