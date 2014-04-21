#include "windows.h"
#include <stdio.h>
#include "heuristic.h"

int main(){
    state* fru = init();
	printf("%d\n",dist_manhattan(fru));
    //print_state(fru);
	
	
    //printf("init state is goal? %s\n" , is_goal(goal) ? "true" : "false" );
    
    //print_action(act);
	
	//int pos = find_zero_index(fru);
	//printf("%d", fru.zero_index);
	
	
}

