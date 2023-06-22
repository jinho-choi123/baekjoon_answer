CC = g++

CFLAGS = -g -Wall

TARGET = main

all: $(TARGET)

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 

test: test1 test2

test1: main input.txt
	cat input1.txt | ./main
	@echo ""

clean:
	$(RM) $(TARGET) $(TARGET).o

.PHONY: all run
