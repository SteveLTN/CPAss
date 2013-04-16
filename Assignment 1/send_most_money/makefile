UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: send-most-money
clean: 
	rm -rf out

send-most-money:
	mkdir -p out
	clang++ -framework gecode -o out/send-most-money send-most-money.cpp
	
run:
	out/send-most-money
	
else
	# write your linux makefile here
all: send-most-money                                                            
clean: 
	rm -rf out
	rm -f lib
	 @echo ~~~Clean done~~~
send-most-money:
	ln -s /usr/local/lib lib
	mkdir out
	g++ send-most-money.cpp -o out/sendMostMoney -L sendMostMoney.o -lgecodesearch -lgecodeint -lgecodekernel -lgecodesupport -lgecodegist
	@echo ~~~g++ ready~~~
run:
	out/sendMostMoney
endif
