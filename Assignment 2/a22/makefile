UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: a22
clean: 
	rm -rf out

a22:
	mkdir -p out
	clang++ -framework gecode -o out/a22 a22.cpp

run:
	out/a22
	
else
	# write your linux makefile here
endif