# 定义内核源码目录，通常是当前目录的上级目录
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

# 定义模块名
MODULE_NAME := my_module

# 定义模块的源文件
obj-m += $(MODULE_NAME).o

# 定义模块的编译器和编译选项
CC := gcc
CFLAGS := -Wall -Wextra -O2 -I$(KERNELDIR)/include

# 默认目标
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

# 清理目标
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

# 防止make递归调用时重复包含Makefile
.PHONY: all clean