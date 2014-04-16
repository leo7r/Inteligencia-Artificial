#include "nodes.h"
#include <stdio.h>

int main(){
    state fru = init();
    //print_state(fru);
	
    state goal,one,two,three;
    goal.current_state = 0x0123456789abcdef;
    one.current_state = 0x0000000000000001;
    two.current_state = 0x0000000000000002;
    three.current_state= 0x0000000000000003;
	
    //printf("init state is goal? %s\n" , is_goal(goal) ? "true" : "false" );
    
    //print_action(act);

   /* Probando la lista */ 
    node_list nuevo; 
    empty_list(&nuevo);
    int a = is_empty(&nuevo);
    node node1 = make_root_node(&one);
	
	//int pos = find_zero_index(fru);
	//printf("%d", fru.zero_index);
	
	print_state(&fru);
	//node_list lista = succ(make_root_node(&fru));
	
	node ini_node = make_root_node(&fru);
	state pt = a_derecha(&fru);
	node pt_n = make_node(&ini_node, new_action(DERECHA,1) , &pt);
	print_state(pt_n.node_state);
	
	//node_box* ptr = lista.first_elem;
	//print_state(ptr->node->node_state);
	
	/*
	while ( ptr != NULL ){
		print_state(ptr->node->node_state);
		ptr = ptr->next;
	}*/
	
}

