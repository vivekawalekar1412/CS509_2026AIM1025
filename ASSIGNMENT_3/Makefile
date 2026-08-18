CC = gcc
CFLAGS = -O3 -Wall -Iinclude -I../ASSIGNMENT_1/include

SRCS = ../ASSIGNMENT_1/src/csr.c src/kruskal.c src/prim.c src/driver_a3.c
TARGET = driver.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) src/*.o *.o