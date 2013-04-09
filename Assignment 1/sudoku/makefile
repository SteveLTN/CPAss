UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: sudoku
clean: 
	rm -rf out

sudoku:
	mkdir -p out
	clang++ -framework gecode -o out/sudoku sudoku.cpp
	
else
	# write your linux makefile here
endif
