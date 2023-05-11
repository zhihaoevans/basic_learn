#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#define MAP_LENGTH (1*1024*1024) // 10MB
 int main()
 {
    int fd;
    void * addr;
    /* 1. 创建一个 Hugetlb 文件系统的文件 */
    fd = open("/dev/huge/hugepage1", O_CREAT|O_RDWR);
    if (fd < 0) {
        perror("open()");
        return -1;
    }
    /* 2. 把虚拟内存映射到 Hugetlb 文件系统的文件中 */
    addr = mmap(0, MAP_LENGTH, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap()");
        close(fd);
        unlink("/mnt/huge/hugepage1");
        return -1;
    }
    strcpy(addr, "This is HugePages example...");
    printf("%s\n", addr);
    /* 3. 使用完成后，解除映射关系 */
    munmap(addr, MAP_LENGTH);
    close(fd);
    unlink("/mnt/huge/hugepage1");
    return 0;
 }
