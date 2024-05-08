TARGET=host

CC=gcc
CFLAGS=-o $(TARGET) -lm

SRC=$(wildcard src/*.c)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC)
