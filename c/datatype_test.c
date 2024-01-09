#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char* argv[])

{
    unsigned char i;
    unsigned int j;
    char m;
    int n;

    i = -1;
    j = -1;
    m = -1;
    n = -1;

    if(i > 0){
        printf("unsigned char -1 > 0\n");
    }else{
        printf("unsigned char -1 < 0\n");
    }
    if(j > 0){
        printf("unsigned int -1 > 0\n");
    }else{
        printf("unsigned int -1 < 0\n");
    }
    if(m > 0){
        printf("char -1 > 0\n");
    }else{
        printf("char -1 < 0\n");
    }
    if(n > 0){
        printf("int -1 > 0\n");
    }else{
        printf("int -1 < 0\n");
    }
 
    if((char)i > 0){
        printf("(char)unsigned char -1 > 0\n");
    }else{
        printf("(char)unsigned char -1 < 0\n");
    }
    
    if((int)j > 0){
        printf("(int)unsigned int -1 > 0\n");
    }else{
        printf("(int)unsigned int -1 < 0\n");
    }

    if((unsigned char)m > 0){
        printf("(unsigned char)char -1 > 0\n");
    }else{
        printf("(unsigned char)char -1 < 0\n");
    }


    if((unsigned int)n > 0){
        printf("(unsigned int)int -1 > 0\n");
    }else{
        printf("(unsigned int)int -1 < 0\n");
    }

    printf("=============================================\n");

    if(i == -1){
        printf("unsigned char -1 = -1\n");
    }else{
        printf("unsigned char -1 != -1\n");
    }
    if(j == -1){
        printf("unsigned int -1 = -1\n");
    }else{
        printf("unsigned int -1 != -1\n");
    }
    if(m == -1){
        printf("char -1 = -1\n");
    }else{
        printf("char -1 != -1\n");
    }
    if(n == -1){
        printf("int -1 = -1\n");
    }else{
        printf("int -1 != -1\n");
    }
 
 
    if((char)i == -1){
        printf("(char)unsigned char -1 = -1\n");
    }else{
        printf("(char)unsigned char -1 != -1\n");
    }
    
    if((int)j == -1){
        printf("(int)unsigned int -1 = -1\n");
    }else{
        printf("(int)unsigned int -1 != -1\n");
    }

    if((unsigned char)m == -1){
        printf("(unsigned char)char -1 = -1\n");
    }else{
        printf("(unsigned char)char -1 != -1\n");
    }


    if((unsigned int)n == -1){
        printf("(unsigned int)int -1 = -1\n");
    }else{
        printf("(unsigned int)int -1 != -1\n");
    }


    return 0;
}
