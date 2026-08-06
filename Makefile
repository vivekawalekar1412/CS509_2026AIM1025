CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude -mconsole

SRC = src/gemm.c src/csr.c
OBJ = $(SRC:.c=.o)

TARGET_DRIVER = driver.exe
TARGET_WRAPPER = wrapper.exe

all: $(TARGET_DRIVER) $(TARGET_WRAPPER)

$(TARGET_DRIVER): src/driver.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(TARGET_WRAPPER): src/wrapper.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q src\*.o $(TARGET_DRIVER) $(TARGET_WRAPPER) 2>NUL || rm -f src/*.o $(TARGET_DRIVER) $(TARGET_WRAPPER)

.PHONY: all clean