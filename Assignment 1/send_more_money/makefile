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
endif