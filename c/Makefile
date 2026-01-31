# Makefile for building C examples under c/
# Compiles all .c files (excluding c/std/) into c/bin with filenames preserving path

CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -std=c11
BIN_DIR := bin

# Find .c sources, exclude std/ directory
SRCS := $(shell find . -name '*.c' -not -path './std/*')

.PHONY: all clean
all: $(BIN_DIR) $(SRCS)
	@echo "Building C examples..."
	@for src in $(SRCS); do \
		out="$(BIN_DIR)/$$(echo $$src | sed 's|^\./||' | sed 's|/|_|g' | sed 's|.c$$||')"; \
		$(CC) $(CFLAGS) "$$src" -o "$$out" || exit 1; \
		echo "built $$out"; \
	done

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)
