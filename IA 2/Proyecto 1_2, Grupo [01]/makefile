all: main

main: punto iris

	

punto: perceptron.o  main.o

	g++ -std=c++11 -g -o punto perceptron.o main.o
	
iris: perceptron.o iris.o

	g++ -std=c++11 -g -o iris perceptron.o iris.o

perceptron.o: perceptron.cc perceptron.h

	g++ -std=c++11 -g -c perceptron.cc

main.o: main.cc perceptron.h

	g++ -std=c++11 -g -c main.cc
	
iris.o: iris.cc perceptron.h

	g++ -std=c++11 -g -c iris.cc

clean:

	rm *.o *.exe punto iris
