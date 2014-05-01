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
#include <vector>

int dist_manhattan(State16*);

//std::list<Node*> ida_star(Node,int (*h)(State16*));

bool ida_star1(Node*,int (*h)(State16*));

bool compare_node_state16 (const Node* , const Node* );

State16* crear_estado_patron( int_fast64_t , char);

bool isClosed( State16* );

void calcularPDB();

void bfs_pdb(State16* , std::string );

void loadPDB();

void loadPattern( std::string , int );

void my_split(std::string&, char, std::vector<std::string>&);

State16* patternMask( State16* , int );

int pdbHeuristic( State16* );

int_fast64_t orMask( int );

bool a_star(Node* ,int (*h)(State16*));