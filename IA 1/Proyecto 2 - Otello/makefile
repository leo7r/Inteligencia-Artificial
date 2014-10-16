all: othello

othello: algorithms.o main.o 

	g++ -std=c++11 -g -o othello main.o algorithms.o

main.o: main.cc algorithms.h

	g++ -std=c++11 -g -c main.cc

algorithms.o: othello_cut.h algorithms.h algorithms.cc

	g++ -std=c++11 -g -c algorithms.cc

clean:

	rm *.o *.exe othello
