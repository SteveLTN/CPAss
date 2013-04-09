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
endif