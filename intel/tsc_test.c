#include <stdio.h>

unsigned long long native_read_tsc(void)
{
    unsigned long val;
    asm volatile("rdtsc" : "=A"(val));
    return val;
}

int main()
{
    unsigned long val;
    unsigned long val2;

    val = native_read_tsc();
    sleep(1);
    val2 = native_read_tsc();

    printf("%lld \n ", (val2 - val) / 1000000);

    return (0);
}