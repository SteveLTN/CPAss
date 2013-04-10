UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: n-queens
clean: 
	rm -rf out

n-queens:
	mkdir -p out
	clang++ -framework gecode -o out/n-queens queens.cpp

run: all
	out/n-queens

else
	# write your linux makefile here
endif