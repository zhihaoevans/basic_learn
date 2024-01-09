#include"myfifo.h"
#include<ctype.h>

int main(){
    int pri_fifo_fd , sec_fifo_fd;
    struct data_to_pass_st my_data;
    int times_to_send;

    pri_fifo_fd = open(S2P_FIFO_NAME , O_WRONLY);
    if(pri_fifo_fd == -1){
        fprintf(stderr , "Sorry , no server!\n");
        exit(EXIT_FAILURE);
    }


    mkfifo(P2S_FIFO_NAME , 0777);

    //这部分有5次循环，在每次循环中，客户将数据发送给服务器，然后打开客户FIFO（只读，阻塞模式）b并读回数据。在程序的最后，关闭服务器FIFO并将客户端的FIFO文件从系统中删除
    for(times_to_send = 0 ; times_to_send < 5 ; times_to_send++){

        sprintf(my_data.some_data , "Hello from %d\t" , my_data.client_pid);
        printf("%d sent %s" , my_data.client_pid , my_data.some_data);
        write(pri_fifo_fd , &my_data , sizeof(my_data));
        sec_fifo_fd  = open(P2S_FIFO_NAME , O_RDONLY);
        if(sec_fifo_fd != -1){
            if(read(sec_fifo_fd , &my_data , sizeof(my_data))  > 0){
                printf("received: %s\n" , my_data.some_data);
            }
            close(sec_fifo_fd);
        }
    }

close(pri_fifo_fd);
unlink(P2S_FIFO_NAME);
exit(EXIT_SUCCESS);

}
