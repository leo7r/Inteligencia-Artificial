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
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <queue>
#include <stdint.h>
#include <stdlib.h>
#include <map>
#include "heuristic.hh"

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


};
 
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


/* Base de datos de patrones */

static std::map<std::pair<int_fast64_t,char>,State16*> hashPattern;
static std::unordered_map<int_fast64_t,int> firstPattern;
static std::unordered_map<int_fast64_t,int> secondPattern;
static std::unordered_map<int_fast64_t,int> thirdPattern;

State16* first_pattern;
State16* second_pattern;
State16* third_pattern;

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

bool isClosed( State16* st ){
	
	std::pair<int_fast64_t,char> par(st->current_state,st->zero_index);
	std::map<std::pair<int_fast64_t,char>,State16*>::const_iterator isState = hashPattern.find(par);
	
	
	return isState != hashPattern.end();
}

void calcularPDB(){
	
	first_pattern  = 	crear_estado_patron(0x0123006700000000,0);
	second_pattern  = 	crear_estado_patron(0x000045008900c000,0);
	third_pattern  = 	crear_estado_patron(0x0000000000ab0def,0);
	
	//bfs_pdb(first_pattern);
	//bfs_pdb(second_pattern);
	bfs_pdb(third_pattern);
}

void bfs_pdb(State16* st){

	std::list<Node*> open;
	Node* nodo = new Node( st );
	open.push_front(nodo);
	int num_nodos = 0;
	
	
	std::ofstream myfile;
	myfile.open ("patron3.txt");
	
	while ( !open.empty() ){
		Node* aux = open.front();
		
		for ( int act = ARRIBA ; act < ROOT ; act++ ){
				
			if ( aux->node_state->is_posible((action)act) ){
				
				State16* suc_state;
				
				switch( act ){
					
					case ARRIBA:
						suc_state = aux->node_state->a_arriba();
						break;
					case ABAJO:
						suc_state = aux->node_state->a_abajo();
						break;
					case IZQUIERDA:
						suc_state = aux->node_state->a_izquierda();
						break;
					case DERECHA:
						suc_state = aux->node_state->a_derecha();
						break;
				}
								
				if ( !isClosed(suc_state) ){
					State16* new_state = crear_estado_patron(suc_state->current_state,suc_state->zero_index);
					Node* node = new Node( aux , (action) act , new_state );
					
					if ( aux->node_state->current_state == new_state->current_state ){
						node->cost-=1;
					}
					else{
						myfile << new_state->current_state << ":" << node->cost << "\n";
						num_nodos++;
					}
					
					open.push_back(node);
					//std::cout << "Costo del nodo: " << node->cost << "\n";
				}
				
			}
		}

		open.pop_front();
	}
	
	std::cout << "Numero de nodos cerrados: " << num_nodos << "\n";
	hashPattern.clear();
	myfile.close();
}

void my_split(std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
	
}

void loadPDB(){
	loadPattern("patron1.txt",firstPattern);
	loadPattern("patron2.txt",secondPattern);
	loadPattern("patron3.txt",thirdPattern);
}

void loadPattern( std::string patron , std::unordered_map<int_fast64_t,int> hash ){
	
	std::ifstream myfile;
	myfile.open (patron);
	std::string line;
	
	if (myfile.is_open()){
			
		while ( std::getline(myfile,line) ){
			
			std::vector<std::string> v;
			my_split(line,':',v);
			
			int_fast64_t st = strtoll (v.front().c_str(), NULL, 10);
			int h = atoi(v.back().c_str());
			
			hash[st] = h;
			
		}
	myfile.close();
	}
		
}

int_fast64_t orMask( int index ){
	
	switch( index ){
		
		case 0:
			return 0xf000000000000000;
		case 1:
			return 0x0f00000000000000;
		case 2:
			return 0x00f0000000000000;
		case 3:
			return 0x000f0000000000000;
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

State16* firstPatternMask( State16* st ){
	
	int_fast64_t * object = &st->current_state;
	
    size_t size = sizeof st->current_state;
    int i = (int) size-1;
	
	int_fast64_t mask = 0x0000000000000000;
	int_fast64_t * mask_ptr = &mask;
	  
    for( i ; i >= 0; i--){
	    //printf("%01d\t", (((const unsigned char *) object)[i] & 0xf0) >> 4 );
		int first_cell = (((const unsigned char *) object)[i] & 0xf0) >> 4;
		int second_cell = ((const unsigned char *) object)[i] & 0xf;
		
		if ( first_cell == 1 || first_cell == 2 || first_cell == 3 || first_cell == 6 || first_cell == 7 ){
			
			mask = mask | orMask(i);
		}
		
		if ( second_cell == 1 || second_cell == 2 || second_cell == 3 || second_cell == 6 || second_cell == 7 ){
			
			mask = mask | orMask(i+1);
		}
		
		
		//std::cout << first_cell << " " << second_cell << " ";
    }
	
	return new State16(mask,0);
}

/* Algoritmos */

int expanded_nodes;

std::pair<int,bool> search(Node* node, int g, int bound,int (*h)(State16*)){
    std::pair<int,bool> f;
    f.first = g + h(node->node_state);
	
	f.second = false;
	
    if (f.first > bound ){ 
		return f;
	};
    if (node->node_state->is_goal()){
        f.second = true;
        return f;
    }
    std::pair<int,bool> min;
    min.first = std::numeric_limits<int>::max();
	min.second = false;
    temporal++;
	
    //std::list<Node*> succ =  node->succ();	
    expanded_nodes++;
	
	for ( int act = ARRIBA ; act < ROOT ; act++ ){
				
		if ( node->is_posible((action)act) ){
			
			Node* suc;
			
			switch( act ){
				
				case ARRIBA:
					suc = new Node( node , (action) act , crear_estadop(node->node_state->a_arribap()) );
					break;
				case ABAJO:
					suc = new Node( node , (action) act , crear_estadop(node->node_state->a_abajop()) );
					break;
				case IZQUIERDA:
					suc = new Node( node , (action) act , crear_estadop(node->node_state->a_izquierdap()) );
					break;
				case DERECHA:
					suc = new Node( node , (action) act , crear_estadop(node->node_state->a_derechap()) );
					break;
			}
		
			std::pair<int,bool> t = search(suc,suc->cost ,bound,h);
				
			if (t.second == true){
				return t;
			}
			if (t.first < min.first){
				min.first = t.first;
			}
                        delete suc;
		}
	}
	
	/*
	for ( std::list<Node*>::iterator it=succ.begin(); it != succ.end() ; ++it){
        
		Node* tmp = *it;
		
		std::pair<int,bool> t = search(tmp,tmp->cost ,bound,h);
				
		if (t.second == true){
			return t;
		}
		if (t.first < min.first){
			min.first = t.first;
		}
    }
    */
	return min;
}

bool ida_star1(Node* root, int (*h)(State16*)){
	
	expanded_nodes = 0;

   int bound = h(root->node_state); 
   std::pair<int,bool> t;
   while(1){
   
	   std::cout << "Bound: " << bound << "\n";
       t = search(root,0,bound,h);
	   
       if (t.second == true){
		std::cout << "Numero de nodos expandidos: " << expanded_nodes;
		stateMap.clear();
		delete(root);
		return true;
	   }
       if (t.first == std::numeric_limits<int>::max()){
		stateMap.clear();
		delete(root);
		return false;
		}
	   
	   bound = t.first;
   }
}

bool compare_node_state16 (const Node* first, const Node* second)
{ 
    if (dist_manhattan(first->node_state)<dist_manhattan(second->node_state)) return true;
    else return false;
}

class compare_node{
    bool reverse;
    int (*h)(State16*);
    int (*h2)(State24*); 
public:
    compare_node(bool revparam, int(*f)(State16*)): reverse(revparam),h(f),h2(0){
    }
    compare_node(bool revparam, int(*f)(State24*)): reverse(revparam),h2(f),h(0){
    }
    bool operator() (Node* n1, Node* n2){
        if (h2 == 0){
            if (reverse) return ((n1->cost + h(n1->node_state)) > (n2->cost + h(n2->node_state)));
            else return ((n1->cost + h(n1->node_state)) < (n2->cost + h(n2->node_state)));
        } else{
            if (reverse) return ((n1->cost) > (n2->cost));
            else return ((n1->cost) < (n2->cost));
        }
    }
};

static std::unordered_map<int_fast64_t,int> dist16;

bool a_star(Node* root,int (*h)(State16*)){
    std::priority_queue<Node*,std::vector<Node*>,compare_node> q (compare_node(true,h));  
    q.push(root);
    while (!q.empty()){
        Node* n = q.top();
        q.pop();
        if ((n->node_state->closed == false) || (dist16[n->node_state->current_state] > n->cost)) {
            n->node_state->closed = true;
            dist16[n->node_state->current_state] = n->cost;
            if (n->node_state->is_goal()) return true;
            
            std::list<Node*> succ =  n->succ();
            while (!succ.empty()){
                Node* tmp = succ.front();
                if (h(tmp->node_state) < std::numeric_limits<int>::max()) q.push(tmp);     
                succ.pop_front();
            }
        }
    }
    return false;
}
