CC = cc
CFLAGS = -O2 -Wall -Wextra
TARGET = main

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) | grep -q 'Hello, C'

clean:
	rm -f $(TARGET)
