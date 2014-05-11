/*
 * =====================================================================================
 *
 *       Filename:  state.c
 *
 *    Description:  Implementacion de los estados.
 *
 *        Version:  1.0
 *        Created:  07/05/14 18:52:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */

#include "state.h"
#include <stdio.h>
 
/* Crea estado inicial  */
state init( ){
	state st;
	st.current_state = 0xab987654321cdef0;
	return st;
} 

/* Chequea si estado es goal */
int is_goal( state st ){
	return st.current_state == 0x0123456789abcdef;
}

/*  succ(state); */ /* Retorna una lista de pares de <estado sucesivo, accione> (falta el tipo lista y par). */

void print_state(state st ){
	
	long long int * object = &st.current_state;
	
	size_t size = sizeof st.current_state;
	size_t i = size-1;
	
	int jump = 0;
	printf("\n");
  
	for( i ; i > 0; i--){
		jump++;
		printf("%01d\t", (((const unsigned char *) object)[i] & 0xf0) >> 4 );
		printf("%01d\t", ((const unsigned char *) object)[i] & 0xf);
		
		if ( jump == 2 ){
			printf("\n");
			jump = 0;
		}
	
	}
  
	printf("%01d\t", (((const unsigned char *) object)[0] & 0xf0) >> 4 );
	printf("%01d\t\n", ((const unsigned char *) object)[0] & 0xf);
}

void print_action( action a ){
	
	switch( a.current_action ){
	
	case ARRIBA:
		printf("Arriba");
		break;
	case DERECHA:
		printf("Derecha");
		break;
	case ABAJO:
		printf("Abajo");
		break;
	case IZQUIERDA:
		printf("Izquierda");
		break;
	}
}


action new_action(action* new,enum posible_actions na, int c){
    new->current_action = na;
    new->cost = c;
}
