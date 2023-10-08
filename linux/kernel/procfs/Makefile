kernel_path := /usr/src/kernels/`uname -r`

all:
	make -C ${kernel_path} M=`pwd` modules 
#KCFLAGS=-DDEBUG if this, pr_debug just like printk

clean:
	make -C ${kernel_path} M=`pwd` clean

obj-m += proc_file.o