#include "heuristic.hh"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ctype.h>

int main(){

        char array[15] = {0,68, 50,20, -57,66,84,-74,53,-49,-124,101,58,86,-41};
        //signed char array[15] = {-34,-34, -34,-34, -34,-34,-34,-83,-34,-34,-34,-34,-34,-34,-34};
        State24* ini = new State24(array,0);
        bool e = ini->is_goal();
        std::cout << e;
    
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
	loadPDB();
	State16* ini = crear_estado(0x7f82d63cb41a950e,14);
	//loadPDB();
/*  	State16* ini = crear_estado(0x1325a9f68edbc470,0);
	
	pdbHeuristic(ini);
	ini = crear_estado(0x7f82d63cb41a95e0,14);
	pdbHeuristic(ini);
	
	/*
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

	//std::cout << pdbHeuristic(ini);
	
	
	return 0;*/

}
