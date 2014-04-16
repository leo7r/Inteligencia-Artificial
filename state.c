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
	st.current_state = 0x0b48765c3219deaf; // Esto debe ser un generador de estados iniciales validos ( quiza lector de archivos ).
	st.zero_index = find_zero_index(st);
	return st;
} 

/* Chequea si estado es goal */
int is_goal( state st ){
	return st.current_state == 0x0123456789abcdef;
}

/*succ(state);*/ /* Retorna una lista de pares de <estado sucesivo, accione> (falta el tipo lista y par). */

void print_state(state* st ){
	
	long long int * object = &st->current_state;
	
	size_t size = sizeof st->current_state;
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

action new_action(enum posible_actions na, int c){
	action act;
    act.current_action = na;
    act.cost = c;
	
	return act;
}

char find_zero_index(state st){
	
	long long int * object = &st.current_state;
	
	size_t size = sizeof st.current_state;
	int i = (int) size-1;
	char count = 0;
		
	for( i ; i >= 0; i--){
		
		int first = (int) (((const unsigned char *) object)[i] & 0xf0) >> 4;
		
		if ( first == 0 ){
			return count;
		}
		else{
			count++;
			int second = (int) ((const unsigned char *) object)[i] & 0xf;
			
			if ( second == 0 ){
				return count;
			}
		}
		count++;
	}
  
}

state a_derecha( state* s ){
	
	int_fast64_t temp = s->current_state;
	
	int_fast64_t mask = 15ULL << 4 * ( 14 - s->zero_index );
	temp = (((temp & mask) << 4) | temp) & ~mask;
	
	state ret;
	ret.current_state = temp;
	ret.zero_index = s->zero_index+1;
	
	return ret;
}

state a_izquierda( state* s ){
	
	int_fast64_t temp = s->current_state;
	
	int_fast64_t mask = 15ULL << 4 * ( 16 - s->zero_index );
	temp = (((temp & mask) >> 4) | temp) & ~mask;
	
	state ret;
	ret.current_state = temp;
	ret.zero_index = s->zero_index-1;
	
	return ret;
}

state a_arriba( state* s ){

	int_fast64_t temp = s->current_state;
	
	int_fast64_t mask = 15ULL << 4 * ( 19 - s->zero_index );
	temp = (((temp & mask) >> 16) | temp) & ~mask;
	
	state ret;
	ret.current_state = temp;
	ret.zero_index = s->zero_index-4;
	
	return ret;
}

state a_abajo( state* s ){

	int_fast64_t temp = s->current_state;
	
	int_fast64_t mask = 15ULL << 4 * ( 11 - s->zero_index );
	temp = (((temp & mask) << 16) | temp) & ~mask;
	
	state ret;
	ret.current_state = temp;
	ret.zero_index = s->zero_index+4;
	
	return ret;
}