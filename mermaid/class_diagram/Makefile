# Makefile for UML Relationships Demo

# 编译器设置
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2

# 目标文件
TARGET = uml_demo
SOURCES = main.cpp uml_classes.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = uml_classes.h

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "编译完成！可执行文件: $(TARGET)"

# 编译源文件
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 运行程序
run: $(TARGET)
	@echo "运行UML关系演示程序..."
	@echo "========================"
	./$(TARGET)

# 清理编译文件
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "清理完成"

# 重新编译
rebuild: clean all

# 显示帮助信息
help:
	@echo "可用的make目标:"
	@echo "  all      - 编译程序 (默认)"
	@echo "  run      - 编译并运行程序"
	@echo "  clean    - 清理编译文件"
	@echo "  rebuild  - 重新编译"
	@echo "  help     - 显示此帮助信息"

# 声明伪目标
.PHONY: all run clean rebuild help