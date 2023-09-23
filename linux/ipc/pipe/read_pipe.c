#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    // 打开有名管道以进行读取
    fd = open(myfifo, O_RDONLY);

    printf("等待写入端写入有名管道...\n");

    // 从有名管道中读取消息
    read(fd, buf, MAX_BUF);
    printf("接收到的消息：%s\n", buf);

    close(fd);

    return 0;
}
