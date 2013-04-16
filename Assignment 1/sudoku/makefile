UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: sudoku
clean: 
	rm -rf out

sudoku:
	mkdir -p out
	clang++ -framework gecode -o out/sudoku sudoku.cpp
	
run:
	out/sudoku

gist:
	mkdir -p out
	clang++ -framework gecode -o out/sudoku-gist sudoku-gist.cpp
	
else
	# write your linux makefile here
all: sudoku                                                            
clean: 
	rm -rf out
	rm -f lib
	 @echo ~~~Clean done~~~
sudoku:
	ln -s /usr/local/lib lib
	mkdir out
	g++ sudoku.cpp -o out/sudoku -L sudoku.o -lgecodesearch -lgecodeint -lgecodekernel -lgecodesupport -lgecodegist -lgecodedriver -lgecodeminimodel
	@echo ~~~g++ ready~~~
run:
	out/sudoku
endif
