UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: donald
clean: 
	rm -rf out

donald:
	mkdir -p out
	clang++ -framework gecode -o out/donald donald.cpp

run:
	out/donald
	
else
	# write your linux makefile here
endif