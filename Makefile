CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -Iinclude -g
SRC=src/main.cc src/log.cc src/aligment.cc src/points.cc src/icp.cc
BIN=gpgpu-icp

.PHONY: all clean check

all:
	$(CC) $(CXXFLAGS) $(SRC) -o $(BIN)

check: clean all
	./$(BIN)

clean:
	$(RM) $(BIN)
