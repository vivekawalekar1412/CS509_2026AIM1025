# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude -I../ASSIGNMENT_1/include

# Source Files (Linking CSR from Assignment 1)
SRCS = src/bellman_ford.c \
       src/floyd_warshall.c \
       src/driver_a2.c \
       ../ASSIGNMENT_1/src/csr.c

OBJS = $(SRCS:.c=.o)
TARGET = driver.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o ../ASSIGNMENT_1/src/*.o $(TARGET)

.PHONY: all clean