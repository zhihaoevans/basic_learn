#include <stdio.h>

int main(void)
{
        int i = 0;
        char a[100];

        for (i = 0; i < sizeof(a); i++)
        {
                a[i] = i;
        }

        return 0;
}
