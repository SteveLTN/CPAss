UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: n-queens
clean: 
	rm -rf out

n-queens:
	mkdir -p out
	clang++ -g -framework gecode -o out/n-queens queens.cpp

run: all
	out/n-queens

else
	# write your linux makefile here
all: n-queens                                                            
clean: 
	rm -rf out
	rm -f lib
	 @echo ~~~Clean done~~~
n-queens:
	ln -s /usr/local/lib lib
	mkdir out
	g++ queens.cpp -o out/n-queens -L n-queens.o -lgecodesearch -lgecodeint -lgecodekernel -lgecodesupport -lgecodegist -lgecodedriver 
	@echo ~~~g++ ready~~~
run:
	out/n-queens
endif
