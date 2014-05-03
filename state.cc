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
	
	/* pruebas
	std::cout << "Mask: ";
	State16* mstate = new State16(mask,0);
	mstate->print_state();
	std::cout << "\ntemp & mask: ";
	State16* fruf = new State16( (((((temp & mask) >> 16) & mask2) | temp) & ~mask)   ,0);
	fruf->print_state();
	State16* mstate2 = new State16( mask2 ,0);
	mstate2->print_state();
	*/
	
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
State24::State24(){}

State24::State24(char* arr, char zi): current_state(arr), zero_index(zi), closed(false){}
/**
 * Constructor para la clase State24
 */
State24::~State24(){}

bool State24::is_goal(){
    long long int r1 = 0x00443214c74254b6;
    long long int r2 = 0xb635cf84653a56d7;
    long long int* p1 =  (long long int*) &current_state[0];
    long long int* p2 =  (long long int*) &current_state[7];
    return ((*p1 == r1) && (*p2 == r2));
}
