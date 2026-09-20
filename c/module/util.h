/*
 * util.h —— 模块的“接口”：头文件只放声明，不放定义。
 * include guard 防止被重复包含；外部代码只 include 本文件即可使用模块。
 */
#ifndef UTIL_H
#define UTIL_H

/* extern 变量声明：告诉编译器“这个变量在别处定义（util.c）”，此处不分配存储 */
extern int util_call_count;

/* 函数原型：模块对外提供的能力 */
int util_max(int a, int b);
long util_pow(int base, unsigned int exp);

#endif /* UTIL_H */
