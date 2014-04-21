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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Implementacion de nodos */
Node::Node( Node* p , action a , State16* st ):parent(p),node_state(st),action(a){
	cost = 1 + p->cost;
}

Node::Node( State16* st ):node_state(st){
	parent = NULL;
	action = ROOT;
	cost = 0;
}

Node::~Node(){}

Node_list* Node::extract_solution(){

	Node_list* result = new Node_list();
    Node* tmp = this;
    
    do{
		result.push_front(temp);
        tmp = (Node*) tmp->parent;
    }  while(tmp != NULL);
	
    return result;
}

Node_list* Node::succ(){
	
	Node_list* lista = new Node_list();
	
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
		lista.push_front( new Node(this, IZQUIERDA , Node_state->a_izquierda()) );
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

/* Implementacion de node_box */

Node_box::Node_box( Node* n , Node_box* next_ ):node(n),next(next_){}

Node_box::~Node_box(){
	delete(n);
	delete(next);
}

/* Implementacion de node_list */

Node_list::Node_list(){}

Node_list::~Node_list(){
	delete(first_elem);
	delete(last_elem);
	delete(current_elem);
}

void Node_list::push_back( Node* node ){
	
	Node_box* new_elem = new Node_box(node,NULL);
	
	if ( is_empty() ){
		first_elem = new_elem;
		current_elem = new_elem;
		last_elem = new_elem;
	}
	else{
		last_elem = new_elem;
	}
}

void Node_list::push_front( Node* node ){
	
	Node_box* new_elem = new Node_box(node,NULL);
	
	if ( is_empty() ){
		first_elem = new_elem;
		current_elem = new_elem;
		last_elem = new_elem;
	}
	else{
		new_elem->next = first_elem;
        first_elem = new_elem;
        current_elem = new_elem;
	}
}

bool Node_list::is_empty(){
	return first_elem == NULL;
}

Node* Node_list::next(){
	Node* result = (Node*) current_elem;
	current_elem = (Node_box*) current_elem->next;
	
	return result;
}
