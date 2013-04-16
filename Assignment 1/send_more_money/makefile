UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: send-more-money
clean: 
	rm -rf out

send-more-money:
	mkdir out
	clang++ -framework gecode -o out/send-more-money send-more-money.cpp	

run:
	out/send-more-money

else
	# write your linux makefile here
all: send-more-money                                                            
clean: 
	rm -rf out
	rm -f lib
	 @echo ~~~Clean done~~~
send-more-money:
	ln -s /usr/local/lib lib
	mkdir out
	g++ send-more-money.cpp -o out/sendMoreMoney -L sendMoreMoney.o -lgecodesearch -lgecodeint -lgecodekernel -lgecodesupport -lgecodegist
	@echo ~~~g++ ready~~~
run:
	out/sendMoreMoney
endif
