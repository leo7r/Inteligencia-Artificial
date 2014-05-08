/*
 * =====================================================================================
 *
 *       Filename:  heuristic.c
 *
 *    Description:  Implementacion de las heuristicas.
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
#include <limits>
#include <iostream>
#include <utility>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <queue>
#include <stdint.h>
#include <stdlib.h>
#include <map>
#include <stdexcept>
#include "heuristic.hh"

/**
 * Procedimiento que libera el espacio de un nodo.
 */
void liberar25(Node* suc){
    State25* tmp = (State25*) suc->node_state;
    free( tmp->current_state);
    delete tmp;
    delete suc;
}

/**
 * Procedimiento que libera el espacio de un nodo.
 */
void liberar(Node* suc){
    delete suc->node_state;
    delete suc;
}

int temporal = 0;

int manhattan[16][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4, 4, 3, 4, 5},
	{2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3, 5, 4, 3, 4},
	{3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2, 6, 5, 4, 3},
	{1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5},
	{2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4},
	{3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3},
	{4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2},
	{2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4},
	{3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3},
	{4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2},
	{5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1},
	{3, 4, 5, 6, 2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3},
	{4, 3, 4, 5, 3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2},
	{5, 4, 3, 4, 4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1},
	{6, 5, 4, 3, 5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0}

}; /* Matriz para el calculo de las distancias manhattan */


int manhattan25[25][25] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5, 4, 3, 4, 5, 6, 5, 4, 5, 6, 7},
	{2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5, 4, 3, 4, 5, 6, 5, 4, 5, 6},
	{3, 2, 1, 0, 1, 4, 3, 2, 1, 2, 5, 4, 3, 2, 3, 6, 5, 4, 3, 4, 7, 6, 5, 4, 5},
	{4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2, 7, 6, 5, 4, 3, 8, 7, 6, 5, 4},
	{1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 3, 4, 5, 6, 7},
	{2, 1, 2, 3, 4, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5, 4, 3, 4, 5, 6},
	{3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5, 4, 3, 4, 5},
	{4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 4, 3, 2, 1, 2, 5, 4, 3, 2, 3, 6, 5, 4, 3, 4},
	{5, 4, 3, 2, 1, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2, 7, 6, 5, 4, 3},
	{2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 2, 3, 4, 5, 6},
	{3, 2, 3, 4, 5, 2, 1, 2, 3, 4, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5},
	{4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4},
	{5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 4, 3, 2, 1, 2, 5, 4, 3, 2, 3},
	{6, 5, 4, 3, 2, 5, 4, 3, 2, 1, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2},
	{3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 1, 2, 3, 4, 5},
	{4, 3, 4, 5, 6, 3, 2, 3, 4, 5, 2, 1, 2, 3, 4, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4},
	{5, 4, 3, 4, 5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3},
	{6, 5, 4, 3, 4, 5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 4, 3, 2, 1, 2},
	{7, 6, 5, 4, 3, 6, 5, 4, 3, 2, 5, 4, 3, 2, 1, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1},
	{4, 5, 6, 7, 8, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4},
	{5, 4, 5, 6, 7, 4, 3, 4, 5, 6, 3, 2, 3, 4, 5, 2, 1, 2, 3, 4, 1, 0, 1, 2, 3},
	{6, 5, 4, 5, 6, 5, 4, 3, 4, 5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2},
	{7, 6, 5, 4, 5, 6, 5, 4, 3, 4, 5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1},
	{8, 7, 6, 5, 4, 7, 6, 5, 4, 3, 6, 5, 4, 3, 2, 5, 4, 3, 2, 1, 4, 3, 2, 1, 0}
};

 /**
  * Implementacion para la heuristica de distancia manhattan.
  */
int dist_manhattan(State16* st){

    int_fast64_t * object = &st->current_state;
	
	size_t size = sizeof st->current_state;
	int i = 0;
	int distancia = 0;
  
	for( i ; i < size; ++i){
		char first_index = (((const unsigned char *) object)[size-1-i] & 0xf0) >> 4;
		char second_index = ((const unsigned char *) object)[size-1-i] & 0xf;
		
		distancia+=manhattan[first_index][i*2]+manhattan[second_index][i*2+1];
	}
	
	return distancia;
}

int dist_manhattan24(State25* st){
	
	int h = 0;
	
	for ( int i = 0 ; i < 25 ; ++i ){
		char c = st->current_state[i];
		h+= manhattan25[c][i];
	}
	
	return h;
}

/* Base de datos de patrones 15 puzzle*/

static std::map<std::pair<int_fast64_t,char>,State16*> hashPattern; /*  */
static std::unordered_map<int_fast64_t,int> firstPattern;           /*  */
static std::unordered_map<int_fast64_t,int> secondPattern;          /*  */
static std::unordered_map<int_fast64_t,int> thirdPattern;           /*  */

State16* first_pattern;
State16* second_pattern;
State16* third_pattern;

/* Base de datos de patrones 24 puzzle*/

static std::map<std::pair<std::string,char>,State25*> hashPattern25; 		/*  */
static std::unordered_map<std::string,int> firstPattern25;           /*  */
static std::unordered_map<std::string,int> secondPattern25;          /*  */
static std::unordered_map<std::string,int> thirdPattern25; 
static std::unordered_map<std::string,int> fourthPattern25;          /*  */

State25* first_pattern25;
State25* second_pattern25;
State25* third_pattern25;
State25* fourth_pattern25;



/**
 * Crea y retorna un estado del patron. 
 */
State16* crear_estado_patron(int_fast64_t st , char zero_index){
		
	std::pair<int_fast64_t,char> par(st,zero_index);
	
	std::map<std::pair<int_fast64_t,char>,State16*>::const_iterator isState = hashPattern.find(par);
	
	if ( isState == hashPattern.end() ){
		State16* state = new State16(st,zero_index);
		std::pair<int_fast64_t,char> par(st,zero_index);
		hashPattern[par] = state;
		return state;
	}
	else{
		State16* ret = isState->second;
		ret->zero_index = zero_index;
		return ret;
	}
}
/**
 * Funcion que nos dice si un State16 se encuentra
 * en la tabla de hash de patrones hashPattern.
 */
bool isClosed( State16* st ){
	
	std::pair<int_fast64_t,char> par(st->current_state,st->zero_index);
	std::map<std::pair<int_fast64_t,char>,State16*>::const_iterator isState = hashPattern.find(par);
	
	
	return isState != hashPattern.end();
}
/**
 * Crea los diversos pedazos para la
 * base de datos de patrones.
 */
void calcularPDB(){
	
	first_pattern  = 	crear_estado_patron(0x0123006700000000,0);
	second_pattern  = 	crear_estado_patron(0x000045008900c000,0);
	third_pattern  = 	crear_estado_patron(0x0000000000ab0def,0);
	
	bfs_pdb(first_pattern,"patron1.txt");
	bfs_pdb(second_pattern,"patron2.txt");
	bfs_pdb(third_pattern,"patron3.txt");
}
/**
 * Escribe un archivo binario con los estados y costos.
 */
void writeBinFile( std::ofstream* file , int_fast64_t st , int h ){
	
	int_fast64_t * ptr = &st;
	int * ptr_i = &h;
	
	if ( file->is_open() ){
		file->write((const char*)ptr,(sizeof st));
		file->write((const char*) ptr_i , sizeof h );
	}
}
/**
 * BFS para la base de datos de patrones.
 */
void bfs_pdb(State16* st , std::string file ){

	std::list<Node*> open;
	Node* nodo = new Node( st );
	open.push_front(nodo);
	int num_nodos = 0;
	
	
	std::ofstream myfile;
	myfile.open (file, std::ios::out | std::ios::binary);
	
	while ( !open.empty() ){
		Node* aux = open.front();
		
		for ( int act = ARRIBA ; act < ROOT ; act++ ){
			if ( aux->node_state->is_posible((action)act) ){
				State16* suc_state;
				switch( act ){
					
					case ARRIBA:
						suc_state = (State16*) aux->node_state->a_arriba();
						break;
					case ABAJO:
						suc_state = (State16*) aux->node_state->a_abajo();
						break;
					case IZQUIERDA:
						suc_state = (State16*) aux->node_state->a_izquierda();
						break;
					case DERECHA:
						suc_state = (State16*) aux->node_state->a_derecha();
						break;
				}
								
				if ( !isClosed(suc_state) ){
				    State16* new_state = crear_estado_patron(suc_state->current_state,suc_state->zero_index);
                    delete suc_state;
				    Node* node = new Node( aux , (action) act , new_state );
					
				    if ( ((State16*)aux->node_state)->current_state == new_state->current_state ){
					node->cost-=1;
				    }
				    else{
						
				        try{
					    firstPattern.at(new_state->current_state);
							
					    if ( firstPattern[new_state->current_state] > node->cost ){
					        firstPattern[new_state->current_state] = node->cost;
					    }
							
					}
					catch(const std::out_of_range& oor ){
					    firstPattern[new_state->current_state] = node->cost;
					}
					num_nodos++;
				    }
					
				    open.push_back(node);
				}	
			}
		}
		open.pop_front();
        liberar(aux);
	}
	
	std::unordered_map<int_fast64_t,int>::const_iterator isState = firstPattern.begin();
		
	for ( auto it = firstPattern.begin(); it != firstPattern.end(); ++it ){
		writeBinFile( &myfile , it->first , it->second );
	}
	
	std::cout << "Numero de nodos cerrados: " << num_nodos <<  " | " << firstPattern.size() << "\n" ;
	hashPattern.clear();
	firstPattern.clear();
	myfile.close();
}
/**
 * Corta un string determinado y lo coloca en un vector.
 */
void my_split(std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
	
}
/**
 * Carga los archivos de la base de datos de patrones.
 */
void loadPDB(){
	loadPattern("patron1.txt",1);
	loadPattern("patron2.txt",2);
	loadPattern("patron3.txt",3);
}
/** 
 * Carga todos los patrones de la base de datos de patrones.
 */
void loadPattern( std::string patron , int num_patron ){
	
	std::ifstream file;
	file.open (patron, std::ios::in | std::ios::binary);
	
	
	int_fast64_t st;	
	int h;
	
	int_fast64_t * ptr2 = (int_fast64_t*) malloc(sizeof st);
	int * ptr2_i = (int*) malloc(sizeof h);
	
	int size = 524159;
	
	if ( file.is_open() ){
		for ( int i = 0 ; i < size ; ++i ){
			file.read((char*)ptr2,sizeof st);
			file.read((char*)ptr2_i,sizeof h);
			
			st = *ptr2;
			h = *ptr2_i;
			
			switch( num_patron ){
				case 1:
					firstPattern[st] = h;
					break;
				case 2:
					secondPattern[st] = h;
					break;
				case 3:
					thirdPattern[st] = h;
					break;
			}
		}
	}
	
	std::cout << "Cargado patron: " << num_patron << "\n";
	file.close();
}

/**
 * Retorna una mascara dependiendo
 * de la posicion dada en index.
 */
int_fast64_t orMask( int index ){
	
	switch( index ){
		
		case 0:
			return 0xf000000000000000;
		case 1:
			return 0x0f00000000000000;
		case 2:
			return 0x00f0000000000000;
		case 3:
			return 0x000f000000000000;
		case 4:
			return 0x0000f00000000000;
		case 5:
			return 0x00000f0000000000;
		case 6:
			return 0x000000f000000000;
		case 7:
			return 0x0000000f00000000;
		case 8:
			return 0x00000000f0000000;
		case 9:
			return 0x000000000f000000;
		case 10:
			return 0x0000000000f00000;
		case 11:
			return 0x00000000000f0000;
		case 12:
			return 0x000000000000f000;
		case 13:
			return 0x0000000000000f00;
		case 14:
			return 0x00000000000000f0;
		case 15:
			return 0x000000000000000f;
	}
	
}
/**
 * Retorna un patron dado un State16* y el num_patron.
 */
int_fast64_t patternMask( State16* st , int num_patron ){
	
	int_fast64_t * object = &st->current_state;
	
    size_t size = sizeof st->current_state;
    int i = (int) size-1;
	
		
	int_fast64_t mask = 0x0000000000000000;
	int_fast64_t * mask_ptr = &mask;
	  
    for( i ; i >= 0; i--){
		int first_cell = (((const unsigned char *) object)[i] & 0xf0) >> 4;
		int second_cell = ((const unsigned char *) object)[i] & 0xf;
		
		bool comp1 = false;
		bool comp2 = false;
	
		switch( num_patron ){
			
			case 1:
				comp1 = first_cell == 1 || first_cell == 2 || first_cell == 3 || first_cell == 6 || first_cell == 7;
				comp2 = second_cell == 1 || second_cell == 2 || second_cell == 3 || second_cell == 6 || second_cell == 7;
				break;
			case 2:
				comp1 = first_cell == 4 || first_cell == 5 || first_cell == 8 || first_cell == 9 || first_cell == 12;
				comp2 = second_cell == 4 || second_cell == 5 || second_cell == 8 || second_cell == 9 || second_cell == 12;
				break;
			case 3:
				comp1 = first_cell == 10 || first_cell == 11 || first_cell == 13 || first_cell == 14 || first_cell == 15;
				comp2 = second_cell == 10 || second_cell == 11 || second_cell == 13 || second_cell == 14 || second_cell == 15;
				break;
			
		}
		
		if ( comp1 ){
			mask = mask | orMask((size - i -1)*2);
		}
		
		if ( comp2 ){
			
			mask = mask | orMask((size - i )*2-1);
			
		}
		
		
    }
	
	return mask;
}
/**
 * Heuristica de PDB.
 */
int pdbHeuristic( State16* st ){
	
	int h = 0;
	int fp,sp,tp;
	
	int_fast64_t firstMask = patternMask(st,1);
	int_fast64_t fP = firstMask & st->current_state;
	fp = firstPattern[fP];
	//h+= firstPattern[fP];
	
	firstMask = patternMask(st,2);
	fP = firstMask & st->current_state;
	//h+= secondPattern[fP];
	sp = secondPattern[fP];
	
	firstMask = patternMask(st,3);
	fP = firstMask & st->current_state;
	//h+= thirdPattern[fP];
	tp = thirdPattern[fP];
	
	
	//std::cout << "H = " << (fp+sp+tp) << " = " << fp << "+" << sp << "+" << tp << "\n";
	return fp+sp+tp;
}


/**
 * Funcions para Crear o Cargar PDB puzzle 25
 */
State25* crear_estado_patron(char * st , char zero_index){
		
	std::pair<std::string,char> par(std::string(st),zero_index);
	
	std::map<std::pair<std::string,char>,State25*>::const_iterator isState = hashPattern25.find(par);
	
	if ( isState == hashPattern25.end() ){
		State25* state = new State25(st,zero_index);
		std::pair<std::string,char> par(std::string(st),zero_index);
		hashPattern25[par] = state;
		return state;
	}
	else{
		State25* ret = isState->second;
		ret->zero_index = zero_index;
		return ret;
	}
}

bool isClosed( State25* st ){
	
	std::pair<std::string,char> par(std::string(st->current_state),st->zero_index);
	std::map<std::pair<std::string,char>,State25*>::const_iterator isState = hashPattern25.find(par);
	
	
	return isState != hashPattern25.end();
}

void calcularPDB25(){

	char array1[25] = {0,1,2,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
	char array2[25] = {0,0,0,0,0,5,6,0,0,0,10,11,0,0,0,15,16,0,0,0,0,0,0,0,0};
	char array3[25] = {0,0,0,0,0,0,0,0,8,9,0,0,0,13,14,0,0,0,0,19,0,0,0,0,24};
	char array4[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,18,0,20,21,22,23,0};
	
	first_pattern25   = crear_estado_patron(array1,0);
	second_pattern25  = crear_estado_patron(array2,0);
	third_pattern25   = crear_estado_patron(array3,0);
	fourth_pattern25  = crear_estado_patron(array4,0);
	
	
	bfs_pdb(first_pattern25,"patron1_25.txt");
	//bfs_pdb(second_pattern25,"patron2_25.txt");
	//bfs_pdb(third_pattern25,"patron3_25.txt");
	//bfs_pdb(fourth_pattern25,"patron4_25.txt");
}

void writeBinFile( std::ofstream* file , const char *st , int h ){
	
	int * ptr_i = &h;
	
	if ( file->is_open() ){
		file->write( st,(sizeof st));
		file->write((const char*) ptr_i , sizeof h );
	}
}

void bfs_pdb(State25* st , std::string file ){

	std::list<Node*> open;
	Node* nodo = new Node( st );
	open.push_front(nodo);
	int num_nodos = 0;
	
	std::ofstream myfile;
	myfile.open (file, std::ios::out | std::ios::binary);
	
	while ( !open.empty() ){
		Node* aux = open.front();
		
		for ( int act = ARRIBA ; act < ROOT ; act++ ){
			if ( aux->node_state->is_posible((action)act) ){
				State25* suc_state;
				switch( act ){
					case ARRIBA:
						suc_state = (State25*) aux->node_state->a_arriba();
						break;
					case ABAJO:
						suc_state = (State25*) aux->node_state->a_abajo();
						break;
					case IZQUIERDA:
						suc_state = (State25*) aux->node_state->a_izquierda();
						break;
					case DERECHA:
						suc_state = (State25*) aux->node_state->a_derecha();
						break;
				}
								
				if ( !isClosed(suc_state) ){
				    State25* new_state = crear_estado_patron(suc_state->current_state,suc_state->zero_index);
                                    delete suc_state;
				    Node* node = new Node( aux , (action) act , new_state );
					
				    if ( ((State25*)aux->node_state)->current_state == new_state->current_state ){
						node->cost-=1;
				    }
				    else{
				        //myfile << new_state->current_state << ":" << node->cost << "\n";
						
				        try{
					    firstPattern25.at(std::string(new_state->current_state));
                                            std::cout << "try\n";
							
					    if ( firstPattern25[std::string(new_state->current_state)] > node->cost ){
					        firstPattern25[std::string(new_state->current_state)] = node->cost;
					    }
							
					}
					catch(const std::out_of_range& oor ){
                                            std::cout << "catch\n";
					    firstPattern25[std::string(new_state->current_state)] = node->cost;
					}
					num_nodos++;
				    }
					
				    open.push_back(node);
				}	
			}
		}
		open.pop_front();
                liberar(aux);
	}
	
	std::unordered_map<std::string,int>::const_iterator isState = firstPattern25.begin();
		
	for ( auto it = firstPattern25.begin(); it != firstPattern25.end(); ++it ){
		writeBinFile( &myfile , it->first.data() , it->second );
		//myfile << it->first << ":" << it->second << "\n";
		//std::cin.get();
	}
	
	std::cout << "Numero de nodos cerrados: " << num_nodos <<  " | " << firstPattern25.size() << "\n" ;
	hashPattern25.clear();
	firstPattern25.clear();
	myfile.close();
}
/*
void loadPDB25(){
	loadPattern25("patron1_25.txt",1);
	loadPattern25("patron2_25.txt",2);
	loadPattern25("patron3_25.txt",3);
	loadPattern25("patron4_25.txt",4);
}

void loadPattern25( std::string patron , int num_patron ){
	
	std::ifstream file;
	file.open (patron, std::ios::in | std::ios::binary);
	
	
	char * st;	
	int h;
	
	char * ptr2 = (char*) malloc(sizeof st);
	int * ptr2_i = (int*) malloc(sizeof h);
	
	int size = 524159;
	
	if ( file.is_open() ){
		for ( int i = 0 ; i < size ; ++i ){
			file.read((char*)ptr2,sizeof st);
			file.read((char*)ptr2_i,sizeof h);
			
			st = *ptr2;
			h = *ptr2_i;
			
			switch( num_patron ){
				case 1:
					firstPattern25[st] = h;
					break;
				case 2:
					secondPattern25[st] = h;
					break;
				case 3:
					thirdPattern25[st] = h;
					break;
				case 4:
					fourthPattern25[st] = h;
					break;
			}
		}
	}
	
	std::cout << "Cargado patron: " << num_patron << "\n";
	file.close();
}
*/

/* Algoritmos */

/**
 * Algoritmo de busqueda recursiva.
 */
std::pair<int,Node*> search(Node* node, int g, int bound,int (*h)(State16*)){
    std::pair<int,Node*> f;
	
    f.first = g + h((State16*)node->node_state);
    f.second = NULL;
    
    if (f.first > bound ){
		//std::cout << "--- Estado se paso del bound : " << bound << " (" << g + h(node->node_state) << "):\n";
		//node->node_state->print_state();
		return f;
	};
    if (node->node_state->is_goal()){
        f.second = node;
        return f;
    }	
    std::pair<int,Node*> min;
    min.first = std::numeric_limits<int>::max();
	min.second = NULL;
    temporal++;
	
    expanded_nodes++;
	
	for ( int act = ARRIBA ; act < ROOT ; act++ ){
				
		if ( node->is_posible((action)act) ){
			
			Node* suc;
			
			switch( act ){
				
				case ARRIBA:
					suc = new Node( node , (action) act , node->node_state->a_arriba() );
					break;
				case ABAJO:
					suc = new Node( node , (action) act , node->node_state->a_abajo() );
					break;
				case IZQUIERDA:
					suc = new Node( node , (action) act , node->node_state->a_izquierda() );
					break;
				case DERECHA:
					suc = new Node( node , (action) act , node->node_state->a_derecha() );
					break;
			}
			
			std::pair<int,Node*> t = search(suc,suc->cost ,bound,h);
				
			if (t.second != NULL){
				return t;
			}
			if (t.first < min.first){
				min.first = t.first;
			}
			liberar(suc);
		}
	}
	
	return min;
}

int expanded_nodes;
/**
 * Implementacion de algoritmo de ida estrella.
 */
bool ida_star1(Node* root, int (*h)(State16*)){	
    expanded_nodes = 0;
    int bound = h((State16*)root->node_state); 
    std::pair<int,Node*> t;
    while(1){
   
        std::cout << "Bound:" << bound <<"\n";
        t = search(root,0,bound,h);
	   
        if (t.second != NULL){
			
			std::cout << "Numero de nodos expandidos: " << expanded_nodes;
                        std::cout << "\n";
			stateMap.clear();
			//delete(root);
			return true;
		}
        if (t.first == std::numeric_limits<int>::max()){
			stateMap.clear();
			//delete(root);
			return false;
        }
	bound = t.first;
   }
}



/**
 * Mismo algoritmo para 25-puzzle.
 */
std::pair<int,Node*> search(Node* node, int g, int bound,int (*h)(State25*)){
    std::pair<int,Node*> f;
	
    f.first = g + h((State25*)node->node_state);
    f.second = NULL;
    
    if (f.first > bound ){
		//std::cout << "--- Estado se paso del bound : " << bound << " (" << g + h(node->node_state) << "):\n";
		//node->node_state->print_state();
		return f;
	};
    if (node->node_state->is_goal()){
        f.second = node;
        return f;
    }	
    std::pair<int,Node*> min;
    min.first = std::numeric_limits<int>::max();
	min.second = NULL;
    temporal++;
	
	/*std::cout << "Expandiendo estado con h = " << h(node->node_state) << " | bound = " << bound << "\n";
	node->node_state->print_state();
	std::cin.get();
	*/
	
    expanded_nodes++;
	
	for ( int act = ARRIBA ; act < ROOT ; act++ ){
				
		if ( node->is_posible((action)act) ){
			
			Node* suc;
			
			switch( act ){
				
				case ARRIBA:
					suc = new Node( node , (action) act , node->node_state->a_arriba() );
					break;
				case ABAJO:
					suc = new Node( node , (action) act , node->node_state->a_abajo() );
					break;
				case IZQUIERDA:
					suc = new Node( node , (action) act , node->node_state->a_izquierda() );
					break;
				case DERECHA:
					suc = new Node( node , (action) act , node->node_state->a_derecha() );
					break;
			}
			
			std::pair<int,Node*> t = search(suc,suc->cost ,bound,h);
				
			if (t.second != NULL){
				return t;
			}
			if (t.first < min.first){
				min.first = t.first;
			}
			liberar25(suc);
		}
	}
	return min;
}

/**
 * Implementacion de algoritmo de ida estrella.
 */
bool ida_star1(Node* root, int (*h)(State25*)){	
    expanded_nodes = 0;
    int bound = h((State25*)root->node_state); 
    std::pair<int,Node*> t;
    while(1){
   
        std::cout << "Bound: " << bound << "\n";
        t = search(root,0,bound,h);
	   
        if (t.second != NULL){
			
			std::cout << "Numero de nodos expandidos: " << expanded_nodes;
			stateMap.clear();
			//delete(root);
			return true;
		}
        if (t.first == std::numeric_limits<int>::max()){
			stateMap.clear();
			//delete(root);
			return false;
        }
	bound = t.first;
   }
}
/**
 * Clase para comparar nodos.
 */
class compare_node{
    bool reverse;
    int (*h)(State16*);
    int (*h2)(State25*); 
public:
    compare_node(bool revparam, int(*f)(State16*)): reverse(revparam),h(f),h2(0){
    }
    compare_node(bool revparam, int(*f)(State25*)): reverse(revparam),h2(f),h(0){
    }
    bool operator() (Node* n1, Node* n2){
        if (h2 == 0){
            if (reverse) return ((n1->cost + h((State16*)n1->node_state)) > (n2->cost + h((State16*)n2->node_state)));
            else return ((n1->cost + h((State16*)n1->node_state)) < (n2->cost + h((State16*)n2->node_state)));
        } else{
            if (reverse) return ((n1->cost) > (n2->cost));
            else return ((n1->cost) < (n2->cost));
        }
    }
};

/**
 * Algoritmo A*.
 */
bool a_star(Node* root,int (*h)(State16*)){
    std::unordered_map<int_fast64_t,int> dist16;
    std::priority_queue<Node*,std::vector<Node*>,compare_node> q (compare_node(true,h));  
    std::list<Node*>* succ = new std::list<Node*>;
    q.push(root);
    while (!q.empty()){
        Node* n = q.top();
        q.pop();
        if ((n->node_state->closed == false) || (dist16[((State16*)n->node_state)->current_state] > n->cost)) {
            n->node_state->closed = true;
            dist16[((State16*)n->node_state)->current_state] = n->cost;
            if (n->node_state->is_goal()) return true;
            
			for ( int act = ARRIBA ; act < ROOT ; act++ ){
				
				if ( n->is_posible((action)act) ){
					
					Node* suc;
					
					switch( act ){
						
						case ARRIBA:
							suc = new Node( n , (action) act , n->node_state->a_arriba() );
							break;
						case ABAJO:
							suc = new Node( n , (action) act , n->node_state->a_abajo() );
							break;
						case IZQUIERDA:
							suc = new Node( n , (action) act , n->node_state->a_izquierda() );
							break;
						case DERECHA:
							suc = new Node( n , (action) act , n->node_state->a_derecha() );
							break;
					}
					
					if (h((State16*)suc->node_state) < std::numeric_limits<int>::max()){
						q.push(suc);     
					} else{
						liberar(suc);
					}
				}
			}
			
        }
        delete n;
    }
    return false;

}

bool fexists(const char *filename)
{
  std::ifstream ifile(filename);
  return ifile;
}
