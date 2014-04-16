/*
 * =====================================================================================
 *
 *       Filename:  nodes.c
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

/**
 * Nos dice si una lista de nodos es vacia o no.
 */
int is_empty(node_list* list){
    return (list->first_elem == NULL);
}

/**
 * Inicializa una lista de nodos en vacio. 
 */
void empty_list(node_list* list){
    list->first_elem = NULL;
    list->last_elem = NULL;
    list->current_elem = NULL;
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
 * Coloca el elemento elem al frente de la cola. 
 */
void push_front(node_list* list, node* elem){
    node_box* new_elem = (node_box*) malloc(sizeof(node_box));
    if (new_elem == NULL){
        fprintf (stderr, "Problemas en la asignacion de memoria; %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    }
    new_elem->node = elem;
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
 */
node make_root_node(state* s){
    node new_node;
    new_node.parent = NULL;
    new_node.node_state = s; 
    new_node.a = NULL;
    new_node.cost = 0;
    return new_node;
}

/**
 * Construye un nodo que representa al estado s que se genera a partir de n con la accion s
 */
node make_node(node* parent,action a,state* s){
    node new_node;
    new_node.parent = (struct node*) parent;
    new_node.node_state = s; 
    new_node.a = &a;
    new_node.cost = a.cost + parent->cost; 
    return new_node;
}
/**
 * Retorna el camino de la raiz a n
 */
node_list extract_solution(node n){
    node_list result;
    node *tmp = &n;
    empty_list(&result);
    do{
        push_front(&result,&n);
        tmp = (node*) tmp->parent;
    }  while(tmp != NULL);
    return result;
}

/**
 * Retorna la lista de sucesores de un nodo. 
 */
node_list succ(node n){
	
	node_list lista;
	empty_list(&lista);
	state* pt = (state*) malloc(sizeof (state));
	node* pt_n = (node*) malloc(sizeof(node));
	
	state* pt1 = (state*) malloc(sizeof(state));
	node* pt_n1 = (node*) malloc(sizeof(node));

	switch( n.node_state->zero_index ){
	
	case 0:
	    *pt = a_derecha(n.node_state);
	    *pt_n = make_node(&n, new_action(DERECHA,1) , pt);
	    push_front(&lista, pt_n );
	    *pt1 = a_abajo(n.node_state);
	    *pt_n1 = make_node(&n, new_action(ABAJO,1) , pt1);
	    push_front(&lista, pt_n1);
	    break;
	}
	
	return lista;
}
