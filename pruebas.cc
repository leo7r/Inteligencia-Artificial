#include "heuristic.hh"
#include <iostream>

int main(){
	
	State16* ini = crear_estado(0x59de63271c0a48bf,10); //new State16(0x59de63271c0a48bf,10);
	Node* node = new Node(ini);
	
	ini->print_state();
	
	std::list<Node*> succ =  node->succ();
	succ.sort(compare_node_state16);
	
	
	std::cout << "\nSucesores:\n";
	
    while (!succ.empty()){
        Node* tmp = succ.front();
		tmp->node_state->print_state();
		std::cout << '\n';
		std::cout << dist_manhattan(tmp->node_state);
        succ.pop_front();
    }
	
	return 0;
}