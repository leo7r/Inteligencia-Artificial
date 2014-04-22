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

std::list<Node*> ida_start(Node,int (*h)());

