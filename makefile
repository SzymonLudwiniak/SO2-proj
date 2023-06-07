BIN=./bin
SRC=./src
INCLUDE=./include
LIB = ./lib

TARGET=trains
FLAGS=-Wall -Wextra -g -std=c++20 -pthread
LINKED = -lncurses
GXX = g++


all: clear build run


build: 
	$(GXX) $(FLAGS) $(SRC)/* -o $(BIN)/$(TARGET) $(LINKED)

run: $(BIN)/$(TARGET)
	$(BIN)/$(TARGET)

clear: $(BIN)/$(TARGET)
	rm -rf $(BIN)/*
