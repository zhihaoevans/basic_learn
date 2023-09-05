#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[1];
    
    // 打开管道以进行读取
    fd = open("mypipe", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // 从管道中读取数据
    read(fd, buffer, sizeof(buffer));
    
    // 打印读取到的数据
    printf("Received message: %s\n", buffer);
    
    // 关闭管道
    close(fd);
    
    return 0;
}
