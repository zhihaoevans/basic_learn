#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int sizeof_arr(char *arr){
    return sizeof(arr);
}

int main(int argc, char* argv[])

{
    int i = 2;
    printf("it is %d\n", (i == 2));
    printf("it is %d\n", (i = 3));
    printf("it is %d\n", strlen("hello"));


    return 0;
}