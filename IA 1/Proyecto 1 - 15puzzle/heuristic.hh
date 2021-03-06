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

extern int expanded_nodes;

int dist_manhattan(State16*);

int dist_manhattan24(State25*);

//std::list<Node*> ida_star(Node,int (*h)(State16*));

std::pair<int,Node*> search(Node*, int, int,int (*h)(State16*) );

bool ida_star1(Node*,int (*h)(State16*));

std::pair<int,Node*> search(Node*, int, int,int (*h)(State25*) );

bool ida_star1(Node*,int (*h)(State25*));

bool compare_node_state16 (const Node* , const Node* );

State16* crear_estado_patron( int_fast64_t , char);

bool isClosed( State16* );

void calcularPDB();

void bfs_pdb(State16* , std::string );

void writeBinFile( std::ofstream* , int_fast64_t , int );

void loadPDB();

void loadPattern( std::string , int );

void my_split(std::string&, char, std::vector<std::string>&);

int_fast64_t patternMask( State16* , int );

int pdbHeuristic( State16* );

int_fast64_t orMask( int );

bool a_star(Node* ,int (*h)(State16*));

bool fexists(const char *);

//funciones para el 25 puzzle

State25* crear_estado_patron(char *  , char );

bool isClosed( State25* );

void calcularPDB25();

void writeBinFile( std::ofstream* , const char* , int );

void bfs_pdb(State25*  , std::string  );

void liberar25(Node* suc);

void loadPDB25();

int pdbHeuristic24(State25* st);
