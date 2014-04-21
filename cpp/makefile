all: pruebas

pruebas: state.o nodes.o heuristic.o pruebas.o 

	g++ -g -o pruebas state.o nodes.o heuristic.o pruebas.o

nodes.o: state.hh nodes.hh nodes.cc

	g++ -g -c nodes.cc

state.o: state.hh state.cc

	g++ -g -c state.cc 
	
heuristic.o: state.hh heuristic.hh heuristic.cc

	g++ -g -c heuristic.cc

pruebas.o: state.hh nodes.hh pruebas.cc

	g++ -g -c pruebas.cc

clean:

	rm *.o *.h.gch
