all: othello

othello: main.o 

	g++ -std=c++11 -g -o othello main.o

main.o: main.cc othello_cut.h

	g++ -std=c++11 -g -c main.cc

clean:

	rm *.o othello
