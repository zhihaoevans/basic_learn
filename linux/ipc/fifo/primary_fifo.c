#include <stdio.h>
#include"myfifo.h"
#include<ctype.h>
#include<errno.h>


//在服务器程序中，我们创建并打开服务器管道.被设置为只读的阻塞模式
//在稍作袖子后，服务器开始读取客户端发来的数据，这些数据是采用data_to_pass_st结构

int main(void)
{

    int p2s_fifo_fd , s2p_fifo_fd;
    struct data_to_pass_st my_data;
    int read_res;
    char client_fifo[256];
    char* tmp_char_ptr;
    int n;

    if(-1 == mkfifo(P2S_FIFO_NAME , 0777)){
        fprintf(stderr , "Sorry , Can't make %s\n" , S2P_FIFO_NAME);
        exit(EXIT_FAILURE);
    }

    if(-1 == mkfifo(S2P_FIFO_NAME , 0777)){
        fprintf(stderr , "Sorry , Can't make %s\n" , P2S_FIFO_NAME);
        exit(EXIT_FAILURE);
    }

    s2p_fifo_fd  = open(S2P_FIFO_NAME , O_RDONLY);
    if(s2p_fifo_fd == -1)
    {
        fprintf( stderr, "open s2p fifo failure\n");
        exit(EXIT_FAILURE);
    }
    p2s_fifo_fd  = open(P2S_FIFO_NAME , O_WRONLY);
    if(p2s_fifo_fd == -1)
    {
        fprintf( stderr, "open p2s fifo failure\n");
        exit(EXIT_FAILURE);
    }



    sleep(10);

    while (1) {
        /* send message */
        n = 0;
        while (n == 0 || (n < 0 && errno == EINTR))
            n = write(p2s_fifo_fd, &my_data, sizeof(my_data));
        if (n < 0)
            rte_panic("cannot write on configuration pipe\n");

        /* wait ack */
        do {
            n = read(s2p_fifo_fd, &my_data, sizeof(my_data));
        } while (n < 0 && errno == EINTR);

        if (n <= 0)
            rte_panic("cannot read on configuration pipe\n");

        rc = 0;
    }

    do{
        read_res = read(sec_fifo_fd , &my_data , sizeof(my_data));
        if(read_res > 0){
            tmp_char_ptr = my_data.some_data;
            while(*tmp_char_ptr){
            //对从客户端读取到的数据进行处理，把some_data中的左右字符全部转化为大写，并且把CLIENT——FIFO——NAME 和client_pid结合到一起
                *tmp_char_ptr = toupper(*tmp_char_ptr);
                tmp_char_ptr++;
            }
            sprintf(client_fifo , P2S_FIFO_NAME , my_data.client_pid);

            //以只写的方式打开客户通道，把经过处理的数据发送出去。最后，关闭服务器管道文件的文件描述符，删除FIFO文件，退出程序

            sec_fifo_fd = open(client_fifo , O_WRONLY);
            if(sec_fifo_fd != -1){
                write(sec_fifo_fd , &my_data , sizeof(my_data));
                close(sec_fifo_fd);
            }

        }

    }while(1);


    close(pri_fifo_fd);
    unlink(S2P_FIFO_NAME);
    exit(EXIT_SUCCESS);

    //return 0;
}
