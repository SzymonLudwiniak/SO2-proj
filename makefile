BIN=./bin
SRC=./src
INCLUDE=./include
LIB = ./lib

TARGET=trains
FLAGS=-Wall -Wextra -g -std=c++20
LINKED = -lncurses
GXX = g++


all: clear build run


build: 
	$(GXX) $(FLAGS) $(SRC)/* -o $(BIN)/$(TARGET) $(LINKED)

run: $(BIN)/$(TARGET)
	$(BIN)/$(TARGET)

clear:
	rm -rf $(BIN)/*
