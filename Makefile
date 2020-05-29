CXX		  := gcc
CXX_FLAGS := -Wall -Wextra -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= main
EXECUTABLE2	:= main.sat


all: $(BIN)/$(EXECUTABLE) $(BIN)/$(EXECUTABLE2)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE2): asm/*.c 
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $< -o $@ $(LIBRARIES)  $(SRC)/mySimpleComputer.c 

$(BIN)/$(EXECUTABLE): $(SRC)/*.c 
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
