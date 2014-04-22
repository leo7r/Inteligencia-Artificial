all: 15puzzle

15puzzle: state.o nodes.o heuristic.o 15puzzle.o 

	g++ -g -o 15puzzle state.o nodes.o heuristic.o 15puzzle.o

nodes.o: state.hh nodes.hh nodes.cc

	g++ -g -c nodes.cc

state.o: state.hh state.cc

	g++ -g -c state.cc 
	
heuristic.o: nodes.hh heuristic.hh heuristic.cc

	g++ -g -c heuristic.cc

15puzzle.o: heuristic.hh 15puzzle.cc

	g++ -g -c 15puzzle.cc

clean:

	rm *.o *.h.gch *.exe
