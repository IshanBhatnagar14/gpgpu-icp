CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -Iinclude -g
SRC=src/main.cc src/log.cc
BIN=gpgpu-icp

all:
	$(CC) $(CXXFLAGS) $(SRC) -o $(BIN)

clean:
	$(RM) $(BIN)
