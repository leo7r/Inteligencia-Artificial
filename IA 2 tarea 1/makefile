all: main

main: perceptron.o  main.o

	clang++ -std=c++11 -g -o main perceptron.o main.o

perceptron.o: perceptron.cc perceptron.h

	clang++ -std=c++11 -g -c perceptron.cc

main.o: main.cc perceptron.h

	clang++ -std=c++11 -g -c main.cc

clean:

	rm *.o *.exe main
