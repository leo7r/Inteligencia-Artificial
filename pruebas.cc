#include "heuristic.hh"
#include <iostream>

int main(){
	
	State16* ini = new State16(0xd7820f3cb64a951d,4);
	Node* node = new Node(ini);
	
	ini->print_state();
	
	std::list<Node*> succ =  node->succ();
	std::cout << "\nSucesores:\n";
	
    while (!succ.empty()){
        Node* tmp = succ.front();
		tmp->node_state->print_state();
        succ.pop_front();
    }
	
	return 0;
}