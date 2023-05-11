/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-10-05 13:48:09
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-10-05 13:48:09
 * @FilePath: /learn/linux/b.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
extern int global_init_a;
int global_init_c = 10;

void swap(int *a, int *b){
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
    global_init_a = 5;
}