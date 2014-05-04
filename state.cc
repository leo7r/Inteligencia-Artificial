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
#include <utility>
#include <iostream>

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

State16::State16():current_state(-1),zero_index(' '), closed(false){
}

State16::State16(int_fast64_t c,char z):current_state(c),zero_index(z),closed(false){
}

//funcion para crear estado tomando en cuenta si existe o no
State16* crear_estado(int_fast64_t st , char zero_index ){
	
	std::unordered_map<int_fast64_t,State16*>::const_iterator isState = stateMap.find(st);
	
	if ( isState == stateMap.end() ){
		State16* state = new State16(st,zero_index);
		stateMap[st] = state;
		return state;
	}
	else{
		return isState->second;
	}
}

State16* crear_estadop(std::pair<int_fast64_t,char> s){

	std::unordered_map<int_fast64_t,State16*>::const_iterator isState = stateMap.find(s.first);
	
	if ( isState == stateMap.end() ){
		State16* state = new State16(s.first,s.second);
		stateMap[s.first] = state;
		return state;
	}
	else{
		return isState->second;
	}
}

State16::~State16(){
}

bool State16::is_goal(){
    return current_state == 0x0123456789abcdef;
}

bool State16::is_posible( action act ){
	
	switch( zero_index ){
		
		case 0:
			if ( act == DERECHA || act == ABAJO )
				return true;
			break;
		case 1:
		case 2:
			if ( act != ARRIBA )
				return true;
			break;
		case 3:
			if ( act == ABAJO || act == IZQUIERDA )
				return true;
			break;
		case 4:
		case 8:
			if ( act != IZQUIERDA )
				return true;
			break;
		case 5:
		case 6:
		case 9:
		case 10:
			return true;
			break;
		case 7:
		case 11:
			if ( act != DERECHA )
				return true;
			break;
		case 12:
			if ( act == ARRIBA || act == DERECHA )
				return true;
			break;
		case 13:
		case 14:
			if ( act != ABAJO )
				return true;
			break;
		case 15:
			if ( act == ARRIBA || act == IZQUIERDA )
				return true;
			break;
		
	}
	
	return false;
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

char* State16::toCharArray(){
    
	char* array = new char[8];
	
    int_fast64_t * object = &current_state; // pendiente aca
	
    size_t size = sizeof current_state;
    int i = (int) size-1;
	
	array = (char*) (this->current_state);
  
    /*for( i ; i >= 0; i--){
	    //printf("%01d\t", (((const unsigned char *) object)[i] & 0xf0) >> 4 );
	    //printf("%01d\t", ((const unsigned char *) object)[i] & 0xf);

		array[size-i] = (((const unsigned char *) object)[i] & 0xf0) >> 4;
		array[size-i+1] = (((const unsigned char *) object)[i] & 0xf);		
    }*/
	
	return array;
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
	
	int_fast64_t mask2 = ~(4095ULL << 4 * ( 16 - zero_index ));
	
	temp = ((((temp & mask) >> 16) & mask2) | temp) & ~mask;
	
	return new State16(temp,zero_index-4);
}

State16* State16::a_abajo(){

	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 11 - zero_index );
	temp = (((temp & mask) << 16) | temp) & ~mask;
	
	return new State16(temp,zero_index+4);
}

std::pair<int_fast64_t,char> State16::a_derechap(){
	
	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 14 - zero_index );
	temp = (((temp & mask) << 4) | temp) & ~mask;
	
        std::pair<int_fast64_t,char> result = std::make_pair(temp,zero_index+1);
	return result;
}

std::pair<int_fast64_t,char> State16::a_izquierdap(){
	
	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 16 - zero_index );
	temp = (((temp & mask) >> 4) | temp) & ~mask;
	
        std::pair<int_fast64_t,char> result = std::make_pair(temp,zero_index-1);
	return result;
}

std::pair<int_fast64_t,char> State16::a_arribap(){

	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 19 - zero_index );
	
	int_fast64_t mask2 = ~(4095ULL << 4 * ( 16 - zero_index ));
	
	temp = ((((temp & mask) >> 16) & mask2) | temp) & ~mask;
	
        std::pair<int_fast64_t,char> result = std::make_pair(temp,zero_index-4);
	return result;
}

std::pair<int_fast64_t,char> State16::a_abajop(){

	int_fast64_t temp = current_state;
	int_fast64_t mask = 15ULL << 4 * ( 11 - zero_index );
	temp = (((temp & mask) << 16) | temp) & ~mask;
	
        std::pair<int_fast64_t,char> result = std::make_pair(temp,zero_index+4);
	return result;
}
/**
 * Constructor para la clase State24
 */
State24::State24():closed(false){}

State24::State24(short int* array, char zi):current_state(array), zero_index(zi), closed(false){}
/**
 * Destructor para la clase State24
 */
State24::~State24(){}

bool State24::is_goal(){
    short int array[9] = {68,6410,12752,19094,25436, 31778, -27416, -21074, -16384};
    int i = 0;
    for (i ; i < 9; i++){
        if (current_state[i] != array[i]) return false;
    }
    return true;
}

void State24::print_state(){
    int i = 0;
    int jump = 0;
    printf("\n");
    for (i ; i< 8; i++){
        printf("%01d\t",(current_state[i] & 0xf800) >> 11); jump++;
        if (jump == 5) {jump = 0; printf("\n");}
        printf("%01d\t",(current_state[i] & 0x07c0) >> 6); jump++;
        if (jump == 5) {jump = 0; printf("\n");}
        printf("%01d\t",(current_state[i] & 0x003e) >> 1); jump++;
        if (jump == 5) {jump = 0; printf("\n");}

    }
    printf("%01d\t",(current_state[i] & 0xf800) >> 11); jump++;

}
