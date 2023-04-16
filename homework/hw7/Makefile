# Homework 7 Makefile

CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

all: DataLoopTest TDataLoopTest

DataLoopTest: DataLoopTest.o DataLoop.o
	$(CC) $(CFLAGS) -o DataLoopTest DataLoopTest.o DataLoop.o

DataLoopTest.o: DataLoopTest.cpp DataLoop.h
	$(CC) $(CFLAGS) -c DataLoopTest.cpp

DataLoop.o: DataLoop.cpp DataLoop.h
	$(CC) $(CFLAGS) -c DataLoop.cpp

TDataLoopTest: TDataLoopTest.o
	$(CC) $(CFLAGS) -o TDataLoopTest TDataLoopTest.o

TDataLoopTest.o: TDataLoopTest.cpp TDataLoop.h
	$(CC) $(CFLAGS) -c TDataLoopTest.cpp

test: DataLoopTest TDataLoopTest
	./DataLoopTest
	./TDataLoopTest

clean:
	rm -f *.o DataLoopTest TDataLoopTest