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

#include "nodes.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Implementacion de nodos */
node::node( node* p , action a , state* st ):parent(p),node_state(st),action(a){
	cost = 1 + p->cost;
}

node::node( state* st ):node_state(st){
	parent = NULL;
	action = ROOT;
	cost = 0;
}

node::~node(){}

node_list* node::extract_solution(){

	node_list* result = new node_list();
    node* tmp = this;
    
    do{
		result.push_front(temp);
        tmp = (node*) tmp->parent;
    }  while(tmp != NULL);
	
    return result;
}

node_list* node::succ(){
	
	node_list* lista = new node_list();
	
	switch( node_state->zero_index ){
	
	case 0:
		lista.push_front( new node(this, DERECHA , node_state.a_derecha()) );
		lista.push_front( new node(this, ABAJO , node_state.a_abajo()) );
		lista.push_front( new node(this, IZQUIERDA , node_state.a_izquierda()) );
		lista.push_front( new node(this, ARRIBA , node_state.a_arriba()) );
	    break;
		
	case 1:
	case 2:
		lista.push_front( new node(this, DERECHA , node_state.a_derecha()) );
		lista.push_front( new node(this, ABAJO , node_state.a_abajo()) );
		lista.push_front( new node(this, IZQUIERDA , node_state.a_izquierda()) );
	    break;
		
	case 3:
		lista.push_front( new node(this, ABAJO , node_state.a_abajo()) );
		lista.push_front( new node(this, IZQUIERDA , node_state.a_izquierda()) );
	    break;
		
	case 4:
	case 8:
		lista.push_front( new node(this, DERECHA , node_state.a_derecha()) );
		lista.push_front( new node(this, ABAJO , node_state.a_abajo()) );
		lista.push_front( new node(this, ARRIBA , node_state.a_arriba()) );
	    break;
		
	case 5:
	case 6:
	case 9:
	case 10:
		lista.push_front( new node(this, DERECHA , node_state.a_derecha()) );
		lista.push_front( new node(this, ABAJO , node_state.a_abajo()) );
		lista.push_front( new node(this, IZQUIERDA , node_state.a_izquierda()) );
		lista.push_front( new node(this, ARRIBA , node_state.a_arriba()) );
	    break;
		
	case 7:
	case 11:
		lista.push_front( new node(this, ABAJO , node_state.a_abajo()) );
		lista.push_front( new node(this, IZQUIERDA , node_state.a_izquierda()) );
		lista.push_front( new node(this, ARRIBA , node_state.a_arriba()) );
	    break;
		
	case 12:
		lista.push_front( new node(this, DERECHA , node_state.a_derecha()) );
		lista.push_front( new node(this, ARRIBA , node_state.a_arriba()) );
	    break;
		
	case 13:
	case 14:
		lista.push_front( new node(this, DERECHA , node_state.a_derecha()) );
		lista.push_front( new node(this, IZQUIERDA , node_state.a_izquierda()) );
		lista.push_front( new node(this, ARRIBA , node_state.a_arriba()) );
	    break;
		
	case 15:
		lista.push_front( new node(this, IZQUIERDA , node_state.a_izquierda()) );
		lista.push_front( new node(this, ARRIBA , node_state.a_arriba()) );
	    break;
	}
	
	return lista;
}

/* Implementacion de node_box */

node_box::node_box( node* n , node_box* next_ ):node(n),next(next_){}

node_box::~node_box(){
	delete(n);
	delete(next);
}

/* Implementacion de node_list */

node_list:node_list(){}

/**
 * Nos dice si una lista de nodos es vacia o no.
 */
int is_empty(node_list* list){
    return (list->first_elem == NULL);
}

/**
 * Inicializa una lista de nodos en vacio. 
 */
node_list* empty_list(){
	node_list* list = (node_list*) malloc(sizeof(node_list));
    list->first_elem = NULL;
    list->last_elem = NULL;
    list->current_elem = NULL;
	return list;
}

/**
 * Coloca el elemento elem al final de la cola. 
 */
void push_back(node_list* list, node* elem){
    node_box* new_elem = (node_box*) malloc(sizeof(node_box));
    if (new_elem == NULL){
        fprintf (stderr, "Problemas en la asignacion de memoria; %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    }
    new_elem->node = elem;
    new_elem->next = NULL;
    if (is_empty(list)){
        list->last_elem = new_elem;
        list->first_elem = new_elem;
        list->current_elem = new_elem;
    } else {
        list->last_elem = new_elem;
    }
}

/**
 * Coloca el elemento elem al frente de la cola. (HAY QUE DECIDIR DONDE HACER LOS MALLOCS, me parece que deberian estar en make_node)
 */
void push_front(node_list* list, node* elem){
    node_box* new_elem = (node_box*) malloc(sizeof(node_box));
    if (new_elem == NULL){
        fprintf (stderr, "Problemas en la asignacion de memoria; %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    }
	
    new_elem->node = elem;
    new_elem->next = NULL;
    if (is_empty(list)){
        list->last_elem = new_elem;
        list->first_elem = new_elem;
        list->current_elem = new_elem;
    } else{
        new_elem->next = (struct node_box*) list->first_elem;
        list->first_elem = new_elem;
        list->current_elem = new_elem;
    }
}
/**
 * Retorna el elemento actual de la lista y mueve el apuntador una posicion.
 */
node* next(node_list* list){
    node* result = (node*) list->current_elem;
    list->current_elem =(node_box*) list->current_elem->next;
    return result;
}

/**
 * Crea la raiz del arbol de busqueda 
 * La funcion crea un nuevo nodo y lo retorna. Tal vez es posible optimizar si se
 * asigna memoria dinamicamente y retorna el apuntador. Aunque no lo creo.
 * (ACA DEBERIA HABER UN MALLOC TAMBIEN Y DEVOLVER node*)
 */
node* make_root_node(state* s){

	node* root_node = (node*) malloc(sizeof(node));
    root_node->parent = NULL;
    root_node->node_state = s; 
    root_node->a = ROOT;
    root_node->cost = 0;
    return root_node;
}

/**
 * Construye un nodo que representa al estado s que se genera a partir de n con la accion s () 
 *(HAY QUE DECIDIR DONDE HACER LOS MALLOCS, me parece que deberian estar aca y devolver un node*)
 */
node* make_node(node* parent,action a,state* s){
	node* new_node = (node*) malloc(sizeof(node));
    new_node->parent = parent;
    new_node->node_state = s; 
    new_node->a = a;
    new_node->cost = 1 + parent->cost; 
    return new_node;
}
/**
 * Retorna el camino de la raiz a n
 */
node_list* extract_solution(node* n){
    node_list* result = empty_list();
    node* tmp = n;
    
    do{
        push_front(result,n);
        tmp = (node*) tmp->parent;
    }  while(tmp != NULL);
	
    return result;
}

/**
 * Retorna la lista de sucesores de un nodo. (retornar node_list* mejor ? ) 
 */
node_list* succ(node* n){
<<<<<<< HEAD
=======

>>>>>>> cbb63749d07771fdc0eac3c9843f2de3de059dbc
	
	node_list* lista = empty_list();

	switch( n->node_state->zero_index ){
	
	case 0:
	    push_front(lista, make_node(n, DERECHA , a_derecha(n->node_state)));
	    push_front(lista, make_node(n, ABAJO , a_abajo(n->node_state)));
	    break;
		
	case 1:
	case 2:
	    push_front(lista, make_node(n, DERECHA , a_derecha(n->node_state)));
	    push_front(lista, make_node(n, ABAJO , a_abajo(n->node_state)));
		push_front(lista, make_node(n, IZQUIERDA , a_izquierda(n->node_state)));
	    break;
		
	case 3:
	    push_front(lista, make_node(n, ABAJO , a_abajo(n->node_state)));
		push_front(lista, make_node(n, IZQUIERDA , a_izquierda(n->node_state)));
	    break;
		
	case 4:
	case 8:
	    push_front(lista, make_node(n, DERECHA , a_derecha(n->node_state)));
	    push_front(lista, make_node(n, ABAJO , a_abajo(n->node_state)));
	    push_front(lista, make_node(n, ARRIBA , a_arriba(n->node_state)));
	    break;
		
	case 5:
	case 6:
	case 9:
	case 10:
	    push_front(lista, make_node(n, DERECHA , a_derecha(n->node_state)));
	    push_front(lista, make_node(n, ABAJO , a_abajo(n->node_state)));
		push_front(lista, make_node(n, IZQUIERDA , a_izquierda(n->node_state)));
	    push_front(lista, make_node(n, ARRIBA , a_arriba(n->node_state)));
	    break;
		
	case 7:
	case 11:
	    push_front(lista, make_node(n, ABAJO , a_abajo(n->node_state)));
		push_front(lista, make_node(n, IZQUIERDA , a_izquierda(n->node_state)));
	    push_front(lista, make_node(n, ARRIBA , a_arriba(n->node_state)));
	    break;
		
	case 12:
	    push_front(lista, make_node(n, DERECHA , a_derecha(n->node_state)));
	    push_front(lista, make_node(n, ARRIBA , a_arriba(n->node_state)));
	    break;
		
	case 13:
	case 14:
	    push_front(lista, make_node(n, DERECHA , a_derecha(n->node_state)));
		push_front(lista, make_node(n, IZQUIERDA , a_izquierda(n->node_state)));
	    push_front(lista, make_node(n, ARRIBA , a_arriba(n->node_state)));
	    break;
		
	case 15:
		push_front(lista, make_node(n, IZQUIERDA , a_izquierda(n->node_state)));
	    push_front(lista, make_node(n, ARRIBA , a_arriba(n->node_state)));
	    break;
	}
	
	return lista;
}
