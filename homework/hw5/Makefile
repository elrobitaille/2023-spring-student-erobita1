# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

# Compile all together
all: hw5 test

# Target to create the hw5 executable 
hw5: hw5.o language_model.o
	$(CC) $(CFLAGS) -o hw5 hw5.o language_model.o

# Compiles hw5.cpp into an object file
hw5.o: hw5.cpp language_model.h
	$(CC) $(CFLAGS) -c hw5.cpp

# Compiles language_model.cpp into an object file
language_model.o: language_model.cpp language_model.h
	$(CC) $(CFLAGS) -c language_model.cpp

# Target to create the test executable
model_tests: model_tests.o language_model.o
	$(CC) $(CFLAGS) -o model_tests model_tests.o language_model.o

# Compiles model_tests.cpp into an object file
model_tests.o: model_tests.cpp model_tests.h language_model.h
	$(CC) $(CFLAGS) -c model_tests.cpp

test: model_tests
	./model_tests

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o hw5	