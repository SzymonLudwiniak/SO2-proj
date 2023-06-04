BIN=./bin
SRC=./src
INCLUDE=./include
LIB = ./lib

TARGET=trains
FLAGS=-Wall -Wextra -g -std=c++20
LINKED = -lncurses
GXX = g++


all: clear build run

#for now, there is no subdir makefiles, will fix later
build: 
	$(GXX) $(FLAGS) $(SRC)/*.cpp $(SRC)/gui/*.cpp -o $(BIN)/$(TARGET) $(LINKED)

run: $(BIN)/$(TARGET)
	$(BIN)/$(TARGET)

clear:
	rm -rf $(BIN)/*

debug: $(BIN)/$(TARGET)
	gdb $(BIN)/$(TARGET)

memtest: $(BIN)/$(TARGET)
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 $(BIN)/$(TARGET)