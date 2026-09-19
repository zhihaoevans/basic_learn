CC = gcc
CFLAGS = -g -Wall

# Sanitizer 标志
ASAN_FLAGS = -fsanitize=address
TSAN_FLAGS = -fsanitize=thread
UBSAN_FLAGS = -fsanitize=undefined
LSAN_FLAGS = -fsanitize=leak # 通常包含在 ASan 中，但也可以单独使用

# 目标文件
TARGETS = asan_oob asan_uaf lsan_leak tsan_race ubsan_overflow

all: $(TARGETS)

# AddressSanitizer 示例
asan_oob: asan_oob.c
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $< -o $@

asan_uaf: asan_uaf.c
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $< -o $@

# LeakSanitizer 示例 (使用 ASan 标志通常也包含 LSan)
lsan_leak: lsan_leak.c
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $< -o $@

# ThreadSanitizer 示例
tsan_race: tsan_race.c
	$(CC) $(CFLAGS) $(TSAN_FLAGS) $< -o $@ -pthread

# UndefinedBehaviorSanitizer 示例
ubsan_overflow: ubsan_overflow.c
	$(CC) $(CFLAGS) $(UBSAN_FLAGS) $< -o $@

clean:
	rm -f $(TARGETS)
	rm -rf *.dSYM

.PHONY: all clean
