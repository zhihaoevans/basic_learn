#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
    int i = 0;

    for (i = 0; i < 2; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            exit(1);
        }
        else if (pid == 0)
        {
            exit(0);
        }
    }
    printf("hello world\n");
    return 0;
}
