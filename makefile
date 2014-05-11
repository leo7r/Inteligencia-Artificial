all: pruebas

pruebas: nodes.o state.o pruebas.o

	gcc -g -o pruebas state.o nodes.o pruebas.o

nodes.o: state.h nodes.h nodes.c

	gcc -g -c nodes.c

state.o: state.h state.c

	gcc -g -c state.c 

pruebas.o: state.h nodes.h pruebas.c

	gcc -g -c pruebas.c

clean:

	rm *.o *.h.gch
