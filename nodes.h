/*
 * =====================================================================================
 *
 *       Filename:  nodes.h
 *
 *    Description:  Header de los nodos, lista de nodos y heap para el 15-Puzzle.
 *
 *        Version:  1.0
 *        Created:  07/05/14 18:42:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */

#include "state.h"

typedef struct{
   struct node* parent;
   state* node_state; 
   action a;
   int cost;
} node;

typedef struct{
    node* node;
    struct node_box* next;
} node_box;

typedef struct{
    node_box* first_elem;
    node_box* last_elem;
    node_box* current_elem;
} node_list;

/* Funciones de nodos */
node* make_root_node(state*); /* Crea la raiz del arbol de busqueda */

node* make_node(node*,action,state*); /* Construye un nodo que representa al estado s que se genera a partir de n con la accion s */

node_list* extract_solution(node*); /* Retorna el camino de la raiz a n */

node_list* succ(node*); /* Retorna la lista de nodos sucesores. */

/* Funciones de la lista */

node_list* empty_list(); /* Inicializa la lista en NULL */

void push_back(node_list*,node*); /* Pone el elemento al final */

void push_front(node_list*,node*); /* Pone un elemento al principio */

int is_empty(node_list*); /* Revisa si el primer elemento es vacio. */

node* next(node_list*); /* Mueve el apuntador a nodo actual una posicion y retorna el nodo al que estaba apuntando anteriormente, */
