# 定义编译器
CXX = g++

# 定义编译选项
CXXFLAGS = -Wall -Wextra -std=c++17

# 定义链接选项
LDFLAGS = 

# 定义要编译的源文件
SOURCES = main.cpp example.cpp utils.cpp

# 定义生成的目标文件
OBJECTS = $(SOURCES:.cpp=.o)

# 定义最终的可执行文件名
TARGET = my_program

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

# 编译源文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)

# 伪目标，避免与文件名冲突
.PHONY: all clean