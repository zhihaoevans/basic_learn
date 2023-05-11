/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-12-31 03:50:50
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-12-31 03:50:50
 * @FilePath: /learn/makefile/test.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <sys/stat.h>
#include <unistd.h>
main()
{
    struct stat buf;
    fstat("/etc/passwd", &buf);
    printf("/etc/passwd file size = %d \n", buf.st_size);
}