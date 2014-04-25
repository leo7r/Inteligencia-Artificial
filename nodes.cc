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
Node::Node( Node* p , action acc , State16* st ):parent(p),node_state(st),a(acc){
	cost = 1 + p->cost;
}

Node::Node( State16* st ):node_state(st){
	parent = 0;
	a = ROOT;
	cost = 0;
}

Node::~Node(){
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

std::list<Node*> Node::succ(){
	

	std::list<Node*> lista;
	switch( a ) {
		
		case DERECHA:
			switch( node_state->zero_index ){
			case 0:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				break;
				
			case 1:
			case 2:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				break;
				
			case 3:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				break;
				
			case 4:
			case 8:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 5:
			case 6:
			case 9:
			case 10:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 7:
			case 11:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 12:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 13:
			case 14:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 15:
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
			}
			break;
		case IZQUIERDA:
			switch( node_state->zero_index ){
			// 
			case 0:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				break;
				
			case 1:
			case 2:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 3:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 4:
			case 8:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 5:
			case 6:
			case 9:
			case 10:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 7:
			case 11:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 12:
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 13:
			case 14:
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 15:
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
			}
			break;
		case ARRIBA:
			switch( node_state->zero_index ){
			// 
			case 0:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				break;
				
			case 1:
			case 2:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 3:
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 4:
			case 8:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 5:
			case 6:
			case 9:
			case 10:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 7:
			case 11:
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 12:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 13:
			case 14:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 15:
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
			}
			break;
		case ABAJO:
			switch( node_state->zero_index ){
			// 
			case 0:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				break;
				
			case 1:
			case 2:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 3:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 4:
			case 8:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				break;
				
			case 5:
			case 6:
			case 9:
			case 10:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 7:
			case 11:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 12:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				break;
				
			case 13:
			case 14:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 15:
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
			}
			break;
		case ROOT:
			switch( node_state->zero_index ){
			// 
			case 0:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				break;
				
			case 1:
			case 2:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 3:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				break;
				
			case 4:
			case 8:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 5:
			case 6:
			case 9:
			case 10:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 7:
			case 11:
				lista.push_front( new Node(this, ABAJO , crear_estadop(node_state->a_abajop())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 12:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 13:
			case 14:
				lista.push_front( new Node(this, DERECHA , crear_estadop(node_state->a_derechap())) );
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
				
			case 15:
				lista.push_front( new Node(this, IZQUIERDA , crear_estadop(node_state->a_izquierdap())) );
				lista.push_front( new Node(this, ARRIBA , crear_estadop(node_state->a_arribap())) );
				break;
			}
			break;
	}
	/*
	switch( node_state->zero_index ){
	case 0:
		lista.push_front( new Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front( new Node(this, ABAJO , node_state->a_abajo()) );
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
	}*/
	
	return lista;
}

std::list<Node> Node::succN(){
	
	std::list<Node> lista;
	
	switch( node_state->zero_index ){
	
	case 0:
		lista.push_front( Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front(Node(this, ABAJO , node_state->a_abajo()) );
	    break;
		
	case 1:
	case 2:
		lista.push_front(  Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front(  Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front(  Node(this, IZQUIERDA , node_state->a_izquierda()) );
	    break;
		
	case 3:
		lista.push_front(  Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front(  Node(this, IZQUIERDA , node_state->a_izquierda()) );
	    break;
		
	case 4:
	case 8:
		lista.push_front(  Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front(  Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front(  Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 5:
	case 6:
	case 9:
	case 10:
		lista.push_front(  Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front(  Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front(  Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front(  Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 7:
	case 11:
		lista.push_front(  Node(this, ABAJO , node_state->a_abajo()) );
		lista.push_front(  Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front(  Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 12:
		lista.push_front(  Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front(  Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 13:
	case 14:
		lista.push_front(  Node(this, DERECHA , node_state->a_derecha()) );
		lista.push_front(  Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front(  Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
		
	case 15:
		lista.push_front(  Node(this, IZQUIERDA , node_state->a_izquierda()) );
		lista.push_front(  Node(this, ARRIBA , node_state->a_arriba()) );
	    break;
	}
	
	return lista;
}
