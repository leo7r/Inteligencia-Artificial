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
  struct nodeList *next;
} nodeList;

node make_root_node(state); /* Crea la raiz del arbol de busqueda */

node make_node(node,action,state); /* Construye un nodo que representa al estado s que se genera a partir de n con la accion s */

void extract_solution(node); /* Retorna el camino de la raiz a n */

nodeList succ(state); /* Retorna una lista de nodos. */

