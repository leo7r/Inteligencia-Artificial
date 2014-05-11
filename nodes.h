/*
 * =====================================================================================
 *
 *       Filename:  nodes.h
 *
 *    Description:  Header de los nodos para el 15-Puzzle.
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
   action* a;
   int cost;
} node;

typedef struct{
    node* node;
    struct node_box *next;
} node_box;

typedef struct{
    node_box* first_elem;
    node_box* last_elem;
    node_box* current_elem;
} node_list;

node make_root_node(state*); /* Crea la raiz del arbol de busqueda */

node make_node(node*,action*,state*); /* Construye un nodo que representa al estado s que se genera a partir de n con la accion s */

node_list extract_solution(node); /* Retorna el camino de la raiz a n */

node_list succ(state); /* Retorna una lista de nodos. */

/* Funciones de la lista */

void empty_list(node_list*);

void push_back(node_list*,node*);

void push_front(node_list*,node*);

int is_empty(node_list*);

node* next(node_list*);
