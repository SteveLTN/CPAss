UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)

all: send-more-money
clean: 
	rm -rf out

send-more-money:
	mkdir out
	clang++ -framework gecode -o out/send-more-money send-more-money.cpp	

else
	# write your linux makefile here
endif