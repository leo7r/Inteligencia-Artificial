/*
 * =====================================================================================
 *
 *       Filename:  heuristic.h
 *
 *    Description:  header de las heuristicas.
 *
 *        Version:  1.0
 *        Created:  07/05/14 18:52:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include "nodes.hh"
#include <stdio.h>

int dist_manhattan(State16*);

//std::list<Node*> ida_star(Node,int (*h)(State16*));

bool ida_star1(Node*,int (*h)(State16*));

bool a_star(Node* root,int (*h)(State16*));

bool compare_node_state16 (const Node* , const Node* );


