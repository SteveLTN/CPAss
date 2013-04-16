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
all: a22                                                            
clean: 
	rm -rf out
	rm -f lib
	 @echo ~~~Clean done~~~
a22:
	ln -s /usr/local/lib lib
	mkdir out
	g++ a22.cpp -o out/a22 -L a22.o -lgecodesearch -lgecodeint -lgecodekernel -lgecodesupport -lgecodegist -lgecodedriver -lgecodeminimodel
	@echo ~~~g++ ready~~~
run:
	out/a22
endif
