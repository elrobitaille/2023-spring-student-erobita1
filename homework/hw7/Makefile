# Homework 7 Makefile

CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

# Builds all executables
all: DataLoopTest TDataLoopTest

# Build the executable DataLoopTest
DataLoopTest: DataLoopTest.o DataLoop.o
	$(CC) $(CFLAGS) -o DataLoopTest DataLoopTest.o DataLoop.o

# Build the object file DataLoopTest.o
DataLoopTest.o: DataLoopTest.cpp DataLoop.h
	$(CC) $(CFLAGS) -c DataLoopTest.cpp

# Build the object file DataLoop.o
DataLoop.o: DataLoop.cpp DataLoop.h
	$(CC) $(CFLAGS) -c DataLoop.cpp

# Build the executable TDataLoopTest
TDataLoopTest: TDataLoopTest.o
	$(CC) $(CFLAGS) -o TDataLoopTest TDataLoopTest.o

# Build the object file TDataLoopTest.o
TDataLoopTest.o: TDataLoopTest.cpp TDataLoop.h
	$(CC) $(CFLAGS) -c TDataLoopTest.cpp

# Executes both DataLoopTest and TDataLoopTest tests
test: DataLoopTest TDataLoopTest
	./DataLoopTest
	./TDataLoopTest

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o DataLoopTest TDataLoopTest