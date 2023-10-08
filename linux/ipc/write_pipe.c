#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *message = "1";
    
    // 打开管道以进行写入
    fd = open("mypipe", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // 写入数据到管道
    write(fd, message, sizeof(message));
    
    // 关闭管道
    close(fd);
    
    return 0;
}
