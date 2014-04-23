all: pruebas

pruebas: state.o nodes.o heuristic.o pruebas.o
	
	g++ -g -o pruebas state.o nodes.o heuristic.o pruebas.o

15puzzle: state.o nodes.o heuristic.o 15puzzle.o 

	g++ -g -o 15puzzle state.o nodes.o heuristic.o 15puzzle.o

nodes.o: state.hh nodes.hh nodes.cc

	g++ -g -c nodes.cc

state.o: state.hh state.cc

	g++ -std=c++11 -g -c state.cc 
	
heuristic.o: nodes.hh heuristic.hh heuristic.cc

	g++ -g -c heuristic.cc

15puzzle.o: heuristic.hh 15puzzle.cc

	g++ -g -c 15puzzle.cc
	
pruebas.o: heuristic.hh pruebas.cc

	g++ -g -c pruebas.cc

clean:

	rm *.o *.h.gch *.exe
