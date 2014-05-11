#include "nodes.h"
#include <stdio.h>

int main(){
    state fru = init();
    print_state(fru);
	
    state goal,one,two,three;
    goal.current_state = 0x0123456789abcdef;
    one.current_state = 0x0000000000000001;
    two.current_state = 0x0000000000000002;
    three.current_state= 0x0000000000000003;
	
    printf("init state is goal? %s\n" , is_goal(goal) ? "true" : "false" );

    action act;
    act.current_action = ARRIBA;
    action act2;
    new_action(&act2,ABAJO,24);
    action act3;
    new_action(&act3,DERECHA,24);
    
    print_action(act);

   /* Probando la lista */ 
    node_list nuevo; 
    empty_list(&nuevo);
    int a = is_empty(&nuevo);
    node node1 = make_root_node(&one); 
    
}

