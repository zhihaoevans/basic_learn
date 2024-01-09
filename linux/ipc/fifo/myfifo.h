//包含客户端和服务器程序都会用到的数据结构等。为了方便使用，
//也包含了必要的系统头文件

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>

#define S2P_FIFO_NAME "./s2p_fifo"
#define P2S_FIFO_NAME "./p2s_fifo"

#define BUFFER_SIZE 20

typedef enum{
    TYPE_REQUEST,
} msg_type_t;

struct data_to_pass_st{
    pid_t client_pid;
    msg_type_t msg_type;
    char some_data[BUFFER_SIZE + 1];
};
