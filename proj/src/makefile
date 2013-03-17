#!/bin/bash

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = compiler

all: ${BIN}
	
compiler: ${OBJ}
	g++ $^ -o $@
	
%.o: %.cpp
	g++ -c $< -o $@
	
.PHONY: clean
	
clean:
	rm -f ${OBJ}