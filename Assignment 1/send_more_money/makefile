all: send-more-money
clean: 
	rm -rf out

out/send-more-money.o:
	mkdir out
	clang++ -O3 -c send-more-money.cpp -o out/send-more-money.o

send-more-money: out/send-more-money.o
	clang++ -framework gecode -o out/send-more-money send-more-money.cpp