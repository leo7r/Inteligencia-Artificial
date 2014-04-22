/*
 * =====================================================================================
 *
 *       Filename:  state.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 12:11:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "state.hh"
#include <stdio.h>

void print_action( action a ){
	
	switch( a ){
	
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

State16::State16():current_state(-1),zero_index(' '){
}

State16::State16(int_fast64_t c,char z):current_state(c),zero_index(z){
}

State16::~State16(){}


bool State16::is_goal(){
    return current_state == 0x0123456789abcdef;
}


void State16::print_state(){
    
    int_fast64_t * object = &current_state; // pendiente aca
	
    size_t size = sizeof current_state;
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


char State16::find_zero_index(){

    int_fast64_t * object = &current_state; //pendiente aca
	
    size_t size = sizeof current_state;
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

State16* State16::a_derecha(){
	
	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 14 - zero_index );
	temp = (((temp & mask) << 4) | temp) & ~mask;
	
	return new State16(temp,zero_index+1);
}

State16* State16::a_izquierda(){
	
	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 16 - zero_index );
	temp = (((temp & mask) >> 4) | temp) & ~mask;
	
	return new State16(temp,zero_index-1);
}

State16* State16::a_arriba(){

	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 19 - zero_index );
	temp = (((temp & mask) >> 16) | temp) & ~mask;
	
	return new State16(temp,zero_index-4);
}

State16* State16::a_abajo(){

	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 11 - zero_index );
	temp = (((temp & mask) << 16) | temp) & ~mask;
	
	return new State16(temp,zero_index+4);
}
