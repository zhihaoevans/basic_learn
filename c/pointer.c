/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-12-18 13:12:24
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-12-18 14:18:52
 * @FilePath: /learn/c/pointer.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>

int main(void){
    int i;
    char *arra[3] = {"aa","bb","cc"};
    char *arrb[3] = {"dd","ff","gg"};
    int * * parr;
    parr = arra;
    for (i = 0; i < (sizeof(arra)/sizeof(arra[0])); i++){
        printf("parr[%d]%s\t", i ,parr[i]);
    }
    printf("\n");
    parr = arrb;
    for (i = 0; i < (sizeof(arrb)/sizeof(arrb[0])); i++){
        printf("parr[%d]%s\t", i ,parr[i]);
    }
}