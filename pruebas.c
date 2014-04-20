#include "nodes.h"
#include "windows.h"
#include <stdio.h>

int main(){
    state* fru = init();
    //print_state(fru);
	
	
    //printf("init state is goal? %s\n" , is_goal(goal) ? "true" : "false" );
    
    //print_action(act);
	
	//int pos = find_zero_index(fru);
	//printf("%d", fru.zero_index);
	
	print_state(fru);
	node_list* lista = succ(make_root_node(fru));
	node_box* ptr = lista->first_elem;
	
	while ( ptr != NULL ){
		print_state(ptr->node->node_state);
		//Sleep(1000);
		ptr = ptr->next;
	}
	
}

