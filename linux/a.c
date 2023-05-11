/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-10-05 13:46:45
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-10-05 13:46:46
 * @FilePath: /learn/linux/a.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
int global_init_a=3;
int global_noinit_b;

void swap(int *a, int *b);

int main(){
    static int static_a = 3;
    static int static_b;
    int b = 4;
    swap(&static_a, &b);
    return 0;
}