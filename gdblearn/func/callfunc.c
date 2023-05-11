#include <stdio.h>

int global = 1;

int func(void) 
{
    return (++global);
}

int main(void)
{
    printf("%d\n", global);
    return 0;
}
