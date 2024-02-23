#include <stdio.h>
#include <signal.h>
// 全局计数器变量
int Cnt = 0;
// SIGALRM信号处理函数
void CbSigAlrm(int signo)
{
    // 输出定时提示信息
    printf("   seconds: %d", ++Cnt);
    printf("\r");
    // 重新启动定时器，实现1秒定时
    alarm(1);
}
void main()
{
    // 安装SIGALRM信号
    if (signal(SIGALRM, CbSigAlrm) == SIG_ERR)
    {
        perror("signal");
        return;
    }
    // 关闭标准输出的行缓存模式
    setbuf(stdout, NULL);
    // 启动定时器
    alarm(1);
    // 进程进入无限循环，只能手动终止
    while (1)
    {
        // 暂停，等待信号
        pause();
    }
}