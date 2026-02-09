#include <stdio.h>

int main(void)
{
        int i = 0;
        int sum = 0;

        for (i = 1; i <= 200; i++)
        {
            sum += i;
        }

        printf("%d\n", sum);
        return 0;
}
