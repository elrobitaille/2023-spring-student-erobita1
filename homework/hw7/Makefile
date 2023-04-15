# Homework 7 Makefile

CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

all: DataLoopTest

DataLoopTest: DataLoopTest.o DataLoop.o
	$(CC) $(CFLAGS) -o DataLoopTest DataLoopTest.o DataLoop.o

DataLoopTest.o: DataLoopTest.cpp DataLoop.h
	$(CC) $(CFLAGS) -c DataLoopTest.cpp

DataLoop.o: DataLoop.cpp DataLoop.h
	$(CC) $(CFLAGS) -c DataLoop.cpp

test: DataLoopTest
	./DataLoopTest

clean:
	rm -f *.o DataLoopTest 