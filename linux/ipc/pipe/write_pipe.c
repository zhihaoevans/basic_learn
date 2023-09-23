#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define MAX_BUF 1024
#define DPCP_FIFO  "/var/run/dpcp_fifo"
#define IFNAMSIZ 16

int dpdk_secproc_enable_dpcp(void){
    printf("hello from %s\n", __FUNCTION__);
    return 0;
}

void *thread_dpcp_monit(void){//maybe exec it at driver level? so ids do nothing 
	int fd;
    char buffer[1];
	int ret;
    
    // 打开管道以进行读取
    fd = open(DPCP_FIFO, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // 从管道中读取数据
	while(1){
   		read(fd, buffer, sizeof(buffer));
    	if(!strncmp("1", buffer, 1)){
			printf("%s exec dpdk_secproc_enable_dpcp\n", __FUNCTION__);
			ret = dpdk_secproc_enable_dpcp();//lookup the ring
			if(!ret){
				printf("secondary enable dpcp success!\n");
			}else{
				printf("secondary enable dpcp failed!\n");				
			}
		}
	}
    
    // 关闭管道
    close(fd);
    
    return 0;
}

int dpdk_sec_wait_pri_init(void){//TODO:create a thread for sec to receive info from pri 
	
	int retn = 0;
	pthread_t tid;

	// 创建有名管道
    mkfifo(DPCP_FIFO, 0666);


	retn = pthread_create(&tid, NULL,
			thread_dpcp_monit, NULL);
	if (0 != retn) {
		printf("### %s:%d thread create failed.\n",
				__FUNCTION__, __LINE__);
		return -1;
	}
#if 1
	char thread_name[IFNAMSIZ];
	snprintf(thread_name, IFNAMSIZ, "dpcp_monit");

	retn = pthread_setname_np(tid, thread_name);
	if (retn) {
		printf("### Thread [%s] set name failed %d, %d - %s\n",
				thread_name, retn, errno, strerror(errno));
	}
#endif

}

void main(void){
    dpdk_sec_wait_pri_init();
}