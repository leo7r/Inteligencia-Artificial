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
node make_node(node* parent,action* a,state* s){
    node new_node;
    new_node.parent = (struct node*) parent;
    new_node.node_state = s; 
    new_node.a = a;
    new_node.cost = 0; // Incompleto
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
        push_back(&result,&n);
        tmp = tmp->parent;
    }  while(tmp != NULL);
    return result;
}
/**
 * Retorna una lista de nodos. 
 */
node_list succ(state s){}
