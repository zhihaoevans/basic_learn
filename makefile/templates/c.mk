# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -Wall -g

# 定义链接选项
LDFLAGS =

# 定义目标文件
TARGET = main

# 定义源文件
SOURCES = main.c

# 定义对象文件
OBJECTS = $(SOURCES:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# 编译源文件为对象文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)

# 防止make递归调用时重复包含Makefile
.PHONY: all clean