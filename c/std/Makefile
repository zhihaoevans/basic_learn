# Makefile for C Standard Library Demonstrations
# C标准库演示程序的Makefile

# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
MATHFLAGS = -lm

# 目标文件列表
TARGETS = stdio_demo stdlib_demo string_demo math_demo time_demo ctype_demo assert_demo limits_demo stddef_demo stdint_demo stdbool_demo errno_demo signal_demo setjmp_demo stdarg_demo locale_demo

# 源文件列表
SOURCES = stdio_demo.c stdlib_demo.c string_demo.c math_demo.c time_demo.c ctype_demo.c assert_demo.c limits_demo.c stddef_demo.c stdint_demo.c stdbool_demo.c errno_demo.c signal_demo.c setjmp_demo.c stdarg_demo.c locale_demo.c

# 默认目标：编译所有程序
all: $(TARGETS)

# 编译stdio演示程序
stdio_demo: stdio_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译stdlib演示程序
stdlib_demo: stdlib_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译string演示程序
string_demo: string_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译math演示程序（需要链接数学库）
math_demo: math_demo.c
	$(CC) $(CFLAGS) -o $@ $< $(MATHFLAGS)

# 编译time演示程序
time_demo: time_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译ctype演示程序
ctype_demo: ctype_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译assert演示程序（调试版本）
assert_demo: assert_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译assert演示程序（发布版本，禁用断言）
assert_demo_release: assert_demo.c
	$(CC) $(CFLAGS) -DNDEBUG -o $@ $<

# 编译limits演示程序
limits_demo: limits_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译stddef演示程序
stddef_demo: stddef_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译stdint演示程序
stdint_demo: stdint_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译stdbool演示程序
stdbool_demo: stdbool_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译errno演示程序
errno_demo: errno_demo.c
	$(CC) $(CFLAGS) -o $@ $< $(MATHFLAGS)

# 编译signal演示程序
signal_demo: signal_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 编译setjmp演示程序
setjmp_demo: setjmp_demo.c
	$(CC) $(CFLAGS) -o $@ $< $(MATHFLAGS)

# 编译stdarg演示程序
stdarg_demo: stdarg_demo.c
	$(CC) $(CFLAGS) -o $@ $< $(MATHFLAGS)

# 编译locale演示程序
locale_demo: locale_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# 运行所有演示程序
run: all
	@echo "=== 运行所有C标准库演示程序 ==="
	@echo
	@echo "1. stdio.h 演示:"
	@./stdio_demo
	@echo
	@echo "2. stdlib.h 演示:"
	@./stdlib_demo
	@echo
	@echo "3. string.h 演示:"
	@./string_demo
	@echo
	@echo "4. math.h 演示:"
	@./math_demo
	@echo
	@echo "5. time.h 演示:"
	@./time_demo
	@echo
	@echo "6. ctype.h 演示:"
	@./ctype_demo
	@echo
	@echo "7. assert.h 演示:"
	@./assert_demo
	@echo
	@echo "8. limits.h 演示:"
	@./limits_demo
	@echo
	@echo "9. stddef.h 演示:"
	@./stddef_demo
	@echo
	@echo "10. stdint.h 演示:"
	@./stdint_demo
	@echo
	@echo "11. stdbool.h 演示:"
	@./stdbool_demo
	@echo
	@echo "12. errno.h 演示:"
	@./errno_demo
	@echo
	@echo "13. signal.h 演示:"
	@./signal_demo
	@echo
	@echo "14. setjmp.h 演示:"
	@./setjmp_demo
	@echo
	@echo "15. stdarg.h 演示:"
	@./stdarg_demo
	@echo
	@echo "16. locale.h 演示:"
	@./locale_demo

# 运行单个演示程序
run-stdio: stdio_demo
	./stdio_demo

run-stdlib: stdlib_demo
	./stdlib_demo

run-string: string_demo
	./string_demo

run-math: math_demo
	./math_demo

run-time: time_demo
	./time_demo

run-ctype: ctype_demo
	./ctype_demo

run-assert: assert_demo
	./assert_demo

run-limits: limits_demo
	./limits_demo

run-stddef: stddef_demo
	./stddef_demo

run-stdint: stdint_demo
	./stdint_demo

run-stdbool: stdbool_demo
	./stdbool_demo

run-errno: errno_demo
	./errno_demo

run-signal: signal_demo
	./signal_demo

run-setjmp: setjmp_demo
	./setjmp_demo

run-stdarg: stdarg_demo
	./stdarg_demo

run-locale: locale_demo
	./locale_demo

# 测试编译（检查语法错误）
test: all
	@echo "所有程序编译成功！"

# 清理生成的文件
clean:
	rm -f $(TARGETS) assert_demo_release
	rm -f *.o
	rm -f core
	rm -rf *.dSYM

# 深度清理（包括备份文件）
distclean: clean
	rm -f *~
	rm -f *.bak
	rm -f .*.swp

# 安装（复制到系统目录，需要管理员权限）
install: all
	@echo "注意：这只是演示程序，通常不需要安装到系统目录"
	@echo "如果确实需要，请手动复制到合适的位置"

# 创建源代码压缩包
archive:
	tar -czf c_stdlib_demos.tar.gz $(SOURCES) Makefile README.md

# 显示帮助信息
help:
	@echo "可用的make目标："
	@echo "  all          - 编译所有演示程序"
	@echo "  clean        - 清理生成的文件"
	@echo "  distclean    - 深度清理"
	@echo "  run          - 运行所有演示程序"
	@echo "  run-<name>   - 运行指定的演示程序"
	@echo "  test         - 测试编译"
	@echo "  archive      - 创建源代码压缩包"
	@echo "  help         - 显示此帮助信息"
	@echo
	@echo "单个程序编译："
	@echo "  stdio_demo   - 编译stdio演示"
	@echo "  stdlib_demo  - 编译stdlib演示"
	@echo "  string_demo  - 编译string演示"
	@echo "  math_demo    - 编译math演示"
	@echo "  time_demo    - 编译time演示"
	@echo "  ctype_demo   - 编译ctype演示"
	@echo "  assert_demo  - 编译assert演示"
	@echo "  limits_demo  - 编译limits演示"
	@echo "  stddef_demo  - 编译stddef演示"
	@echo "  stdint_demo  - 编译stdint演示"
	@echo "  stdbool_demo - 编译stdbool演示"
	@echo "  errno_demo   - 编译errno演示"
	@echo "  signal_demo  - 编译signal演示"
	@echo "  setjmp_demo  - 编译setjmp演示"
	@echo "  stdarg_demo  - 编译stdarg演示"
	@echo "  locale_demo  - 编译locale演示"

# 声明伪目标
.PHONY: all clean distclean run test install archive help run-stdio run-stdlib run-string run-math run-time run-ctype run-assert run-limits run-stddef run-stdint run-stdbool run-errno run-signal run-setjmp run-stdarg run-locale

# 编译器特定的优化选项
debug: CFLAGS += -DDEBUG -O0
debug: all

release: CFLAGS += -DNDEBUG -O2
release: all

# 内存检查（需要valgrind）
memcheck: all
	@echo "使用valgrind检查内存泄漏..."
	@for target in $(TARGETS); do \
		echo "检查 $$target:"; \
		valgrind --leak-check=full --show-leak-kinds=all ./$$target; \
		echo; \
	done

# 代码风格检查（需要cppcheck）
stylecheck:
	@echo "检查代码风格..."
	@cppcheck --enable=all --std=c99 $(SOURCES)

# 显示编译信息
info:
	@echo "编译器: $(CC)"
	@echo "编译选项: $(CFLAGS)"
	@echo "数学库选项: $(MATHFLAGS)"
	@echo "目标文件: $(TARGETS)"
	@echo "源文件: $(SOURCES)"