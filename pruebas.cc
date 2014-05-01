#include "heuristic.hh"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ctype.h>

int main(){
	
	/*State16* ini = crear_estado(0x7f82d63cb04a951e,9); //new State16(0x59de63271c0a48bf,10);
	Node* node = new Node(ini);
	node->a = ARRIBA;
	
	ini->print_state();
	
	std::list<Node*> succ =  node->succ();
	succ.sort(compare_node_state16);
	
	
	std::cout << "\nSucesores:\n";
	
    while (!succ.empty()){
        Node* tmp = succ.front();
		tmp->node_state->print_state();
		std::cout << '\n';
		
		std::cout << "Accion: ";
		print_action(tmp->a);
		
		//std::cout << dist_manhattan(tmp->node_state);
        succ.pop_front();
    }*/
	
	//calcularPDB();
	//loadPDB();
	State16* ini = crear_estado(0x1325a9f68edbc470,0);
	
	//0x7f82d63cb04a951e
    Node *n = new Node(ini);
	ini->print_state();
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
		
	bool funciona = ida_star1(n,dist_manhattan);
		
	if ( funciona ){
		std::cout << "Funciono!";
	}
	else{
		std::cout << "No funciono :(";
	}	
		
	end = std::chrono::system_clock::now();
		
	std::chrono::duration<double> elapsed_seconds = end-start;
		
	std::cout << "Tiempo: " << elapsed_seconds.count() << "\n";
	
	/*
	State16* patron = patternMask(ini,1);
	patron->print_state();
	patron = patternMask(ini,2);
	patron->print_state();
	patron = patternMask(ini,3);
	patron->print_state();
	*/
	
	//std::cout << pdbHeuristic(ini);
	
	
	return 0;
}