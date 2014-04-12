#include "state.h"
#include <stdio.h>

int main(){
	
	state fru = init();
	print_state(fru);
	
	state goal;
	goal.current_state = 0x0123456789abcdef;
	
	printf("init state is goal? %s\n" , is_goal(goal) ? "true" : "false" );

	action act;
	act.current_action = ARRIBA;
	
	print_action(act);
}

