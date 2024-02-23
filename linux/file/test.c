#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#if 0
int main() {
    int fd1, fd2;

    // 打开一个文件
    fd1 = open("file1.txt", O_RDONLY);
    if (fd1 == -1) {
        perror("open");
        return 1;
    }

    // 复制文件描述符
    fd2 = dup2(fd1, 10);
    if (fd2 == -1) {
        perror("dup2");
        return 1;
    }

    // 关闭原来的文件描述符
    close(fd1);

    // 使用新的文件描述符进行读操作
    char buf[1024];
    ssize_t num_read = read(fd2, buf, sizeof(buf));
    if (num_read == -1) {
        perror("read");
        return 1;
    }

    // 输出读取的内容
    write(STDOUT_FILENO, buf, num_read);

    return 0;
}
#endif

/* test if fprintf overlay */
int main(void){
    FILE *fp;
	fp = fopen("./test.txt", "w");
    fprintf(fp,"hello\n");
    fprintf(fp,"world\n");
    fclose(fp);
    return 0;
}
