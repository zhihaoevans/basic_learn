#include <sys/ptrace.h>
#include <stdio.h>

int main()                                                                      
{
        if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0 ) {
                printf("Gdb is debugging me, exit.\n");
                return 1;
        }
        printf("No debugger, continuing\n");
        return 0;
}
