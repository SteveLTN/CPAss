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
all: donald                                                            
clean: 
	rm -rf out
	rm -f lib
	 @echo ~~~Clean done~~~
donald:
	ln -s /usr/local/lib lib
	mkdir out
	g++ donald.cpp -o out/donald -L donald.o -lgecodesearch -lgecodeint -lgecodekernel -lgecodesupport -lgecodegist
	@echo ~~~g++ ready~~~
run:
	out/donald
endif
