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
//#include <stdio.h>

/* Implementacion de nodos */
Node::Node( Node* p , action acc , State16* st ):parent(p),node_state(st),a(acc){
	cost = 1 + p->cost;
}

Node::Node( State16* st ):node_state(st){
	parent = NULL;
	a = ROOT;
	cost = 0;
}

Node::~Node(){}

std::list<Node*> Node::extract_solution(){

	std::list<Node*> result;
    Node* tmp = this;
    
    do{
		result.push_front(tmp);
        tmp = (Node*) tmp->parent;
    }  while(tmp != NULL);
	
    return result;
}

std::list<Node*> Node::succ(){
	
	std::list<Node*> lista;
	
	switch( node_state->zero_index ){
	
	case 0:
		lista.push_front( new Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front( new Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front( new Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front( new Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 1:
	case 2:
		lista.push_front( new Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front( new Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front( new Node(this, IZQUIERDA , node_state->a_izquierda()) );
	    break;
		
	case 3:
		lista.push_front( new Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front( new Node(this, IZQUIERDA , node_state->a_izquierda()) );
	    break;
		
	case 4:
	case 8:
		lista.push_front( new Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front( new Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front( new Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 5:
	case 6:
	case 9:
	case 10:
		lista.push_front( new Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front( new Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front( new Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front( new Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 7:
	case 11:
		lista.push_front( new Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front( new Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front( new Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 12:
		lista.push_front( new Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front( new Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 13:
	case 14:
		lista.push_front( new Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front( new Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front( new Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 15:
		lista.push_front( new Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front( new Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
	}
	
	return lista;
}
