#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    
    int fd;
    fd = open("/dev/tty0", O_RDWR);
    if(fd < 0){
        perror("open failed\n");
    }
    pid_t foreground_pgid = tcgetpgrp(fd);
    if (foreground_pgid == -1) {
        perror("tcgetpgrp");
        return 1;
    }

    printf("Foreground process group ID: %d\n", foreground_pgid);

    return 0;
}
