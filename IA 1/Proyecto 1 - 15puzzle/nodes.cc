/*
 * =====================================================================================
 *
 *       Filename:  nodes.cc
 *
 *    Description:  Implementacion de nodos.
 *
 *        Version:  1.0
 *        Created:  10/05/14 19:37:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */

#include "nodes.hh"
#include <stdint.h>
//#include <stdio.h>

/* Implementacion de nodos */
Node::Node( Node* p , action acc , State* st ):parent(p),node_state(st),a(acc){
	cost = 1 + p->cost;
}

Node::Node( State* st ):node_state(st){
	parent = 0;
	a = ROOT;
	cost = 0;
}

Node::~Node(){
    //delete node_state;
    //delete this;
}

std::list<Node*> Node::extract_solution(){

    std::list<Node*> result;
    Node* tmp = this;
    
    do{
	result.push_front(tmp);
        tmp = (Node*) tmp->parent;
    }  while(tmp != 0);
	
    return result;
}

bool Node::is_posible( action act ){
	
	switch( a ){
		
		case ARRIBA:
			switch( node_state->zero_index ){
				
				case 0:
					if ( act == DERECHA )
						return true;
					break;
				case 1:
				case 2:
					if ( act == DERECHA || act == IZQUIERDA )
						return true;
					break;
				case 3:
					if ( act == IZQUIERDA )
						return true;
					break;
				case 4:
				case 8:
					if ( act == DERECHA || act == ARRIBA )
						return true;
					break;
				case 5:
				case 6:
				case 9:
				case 10:
					if ( act != ABAJO )
						return true;
					break;
				case 7:
				case 11:
					if ( act == IZQUIERDA || act == ARRIBA )
						return true;
					break;				
			}
			break;
			
		case ABAJO:
			switch( node_state->zero_index ){
				case 4:
				case 8:
					if ( act == DERECHA || act == ABAJO )
						return true;
					break;
				case 5:
				case 6:
				case 9:
				case 10:
					if ( act != ARRIBA )
						return true;
					break;
				case 7:
				case 11:
					if ( act == IZQUIERDA || act == ABAJO )
						return true;
					break;
				case 12:
					if ( act == DERECHA )
						return true;
					break;
				case 13:
				case 14:
					if ( act == IZQUIERDA || act == DERECHA )
						return true;
					break;
				case 15:
					if ( act == IZQUIERDA )
						return true;
					break;
			}
			break;
		
		case IZQUIERDA:
			switch( node_state->zero_index ){
				
				case 0:
					if ( act == ABAJO )
						return true;
					break;
				
				case 1:
				case 2:
					if ( act == ABAJO || act == IZQUIERDA )
						return true;
					break;
				case 4:
				case 8:
					if ( act == ABAJO || act == ARRIBA )
						return true;
					break;
				case 5:
				case 6:
				case 9:
				case 10:
					if ( act != DERECHA )
						return true;
					break;
				case 12:
					if ( act == ARRIBA )
						return true;
					break;
				case 13:
				case 14:
					if ( act == IZQUIERDA || act == ARRIBA )
						return true;
					break;
					
			}
			break;
		
		case DERECHA:
			switch( node_state->zero_index ){
				
				case 1:
				case 2:
					if ( act == ABAJO || act == DERECHA )
						return true;
					break;
				case 3:
					if ( act == ABAJO )
						return true;
					break;
				case 5:
				case 6:
				case 9:
				case 10:
					if ( act != IZQUIERDA )
						return true;
					break;
				case 7:
				case 11:
					if ( act == ABAJO || act == ARRIBA )
						return true;
					break;
				case 13:
				case 14:
					if ( act == ARRIBA || act == DERECHA )
						return true;
					break;
				case 15:
					if ( act == ARRIBA )
						return true;
					break;
				
			}
			break;
		
		case ROOT:
			switch( node_state->zero_index ){
				
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
			break;
	}
	
	return false;
}
