/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-12-18 13:01:02
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-12-18 13:05:59
 * @FilePath: /learn/macro/test.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
struct B{
    int a;
    int b;
};

#define	_TAILQ_HEAD(name, type, qual)					\
struct name {								\
	qual type *tqh_first;		/* first element */		\
	qual type *qual *tqh_last;	/* addr of last next element */	\
}
#define TAILQ_HEAD(name, type)	_TAILQ_HEAD(name, struct type,)

TAILQ_HEAD(A,B);
