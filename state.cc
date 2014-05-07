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
#include <stdlib.h>

State::State():zero_index(0),closed(false){}
State::State(char zi):zero_index(zi),closed(false){}

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

State16::State16():State(0),current_state(-1){
}

State16::State16(int_fast64_t c,char z):State(z),current_state(c){
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

bool State16::equals( State* st ){
	return current_state == ((State16*)st)->current_state;
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
 * Constructor para la clase State25
 */
State25::State25():State(0){}

State25::State25(char* array, char zi):State(zi),current_state(array){}
/**
 * Destructor para la clase State25
 */
State25::~State25(){}

char goal_array[25] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};

bool State25::is_goal(){
    int i = 0;
    for (i ; i != 25; i++){
        if (current_state[i] != goal_array[i]) return false;
    }
    return true;
}

void State25::print_state(){
    char i = 0;
    char jump = 0;
    printf("\n");
    for (i ; i != 25 ; i++) {
        printf("%d\t",current_state[i]); jump++;
        if (jump == 5){ printf("\n"); jump = 0; }
    }
    printf("\n");
}

char State25::find_zero_index(){
    char i = 0;
    for (i ; i != 25 ; i++){
        if (current_state[i] == 0) return i;
    }
    return -1;
}

char* clonar(char* array){
    char* nuevo = (char*) malloc (sizeof(char) * 25);
    int i = 0;
    for (i; i != 25 ; i++){
        nuevo[i] = array[i];
    }
    return nuevo;
}

bool State25::is_posible( action act ){
	
	switch( zero_index ){
		
		case 0:
			if ( act == DERECHA || act == ABAJO )
				return true;
			break;
		case 1:
		case 2:
		case 3:
			if ( act != ARRIBA )
				return true;
			break;
		case 4:
			if ( act == ABAJO || act == IZQUIERDA )
				return true;
			break;
		case 5:
		case 10:
		case 15:
			if ( act != IZQUIERDA )
				return true;
			break;
		case 6:
		case 7:
		case 8:
		case 11:
		case 12:
		case 13:
		case 16:
		case 17:
		case 18:
			return true;
			break;
		case 9:
		case 14:
		case 19:
			if ( act != DERECHA )
				return true;
			break;
		case 20:
			if ( act == ARRIBA || act == DERECHA )
				return true;
			break;
		case 21:
		case 22:
		case 23:
			if ( act != ABAJO )
				return true;
			break;
		case 24:
			if ( act == ARRIBA || act == IZQUIERDA )
				return true;
			break;
		
	}
	
	return false;
}

bool State25::equals( State* st ){

	char i = 0;
	char* estado = ((State25*) st)->current_state;
	
	for (i ; i < 25 ; ++i ){
		if ( estado[i] != current_state[i] ){
			return false;
		}
	}
	
	return true;
}

State25* State25::a_derecha(){

	char* nuevo = clonar(current_state);

	char swapAux = nuevo[zero_index+1];
	nuevo[zero_index+1]=0;
	nuevo[zero_index]=swapAux;
	
	return new State25(nuevo,zero_index+1);
}

State25* State25::a_izquierda(){
    char* nuevo = clonar(current_state);

	char swapAux = nuevo[zero_index-1];
	nuevo[zero_index-1]=0;
	nuevo[zero_index]=swapAux;
	
	return new State25(nuevo,zero_index-1);
}

State25* State25::a_abajo(){
    char* nuevo = clonar(current_state);

	char swapAux = nuevo[zero_index+5];
	nuevo[zero_index+5]=0;
	nuevo[zero_index]=swapAux;
	
	return new State25(nuevo,zero_index+5);
}

State25* State25::a_arriba(){
    char* nuevo = clonar(current_state);

	char swapAux = nuevo[zero_index-5];
	nuevo[zero_index-5]=0;
	nuevo[zero_index]=swapAux;
	
	return new State25(nuevo,zero_index-5);
}
