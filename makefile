all: pruebas

pruebas: nodes.o state.o pruebas.o heuristic.o

	gcc -g -o pruebas state.o nodes.o heuristic.o pruebas.o

nodes.o: state.h nodes.h nodes.c

	gcc -g -c nodes.c

state.o: state.h state.c

	gcc -g -c state.c 
	
heuristic.o: state.h heuristic.h heuristic.c

	gcc -g -c heuristic.c 

pruebas.o: state.h nodes.h pruebas.c

	gcc -g -c pruebas.c

clean:

	rm *.o *.h.gch
