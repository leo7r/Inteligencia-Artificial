/*
 * =====================================================================================
 *
 *       Filename:  heuristic.c
 *
 *    Description:  Implementacion de las heuristicas.
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
#include <limits>
#include <utility>
#include <list>
#include <stdint.h>
#include "heuristic.hh"

int manhattan[16][16] = {  

	{0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6} ,   /* 0 */
	{1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4, 4, 3, 4, 5} ,   /* 1 */
	{2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3, 5, 4, 3, 4} ,   /* 2 */
	{3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2, 6, 5, 4, 3} ,   /* 3 */
	{1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5} ,   /* 4 */
	{2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4} ,   /* 5 */
	{3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 4} ,   /* 6 */
	{4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2} ,   /* 7 */
	{2, 3, 4, 5, 1, 1, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4} ,   /* 8 */
	{3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3} ,   /* 9 */
	{4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2} ,   /* 10 */
	{5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1} ,   /* 11 */
	{3, 4, 5, 6, 2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3} ,   /* 12 */
	{4, 3, 4, 5, 3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2} ,   /* 13 */
	{5, 4, 3, 4, 4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1} ,   /* 14 */
	{6, 5, 4, 3, 5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0} ,   /* 15 */
};
 
int dist_manhattan(State16* st){

        int_fast64_t * object = &st->current_state;
	
	size_t size = sizeof st->current_state;
	int i = 0;
	int distancia = 0;
  
	for( i ; i < size; ++i){
		char first_index = (((const unsigned char *) object)[size-1-i] & 0xf0) >> 4;
		char second_index = ((const unsigned char *) object)[size-1-i] & 0xf;
		
		distancia+=manhattan[first_index][i*2]+manhattan[second_index][i*2+1];
	}
	
	return distancia;
}

std::pair<std::list<Node*>,int> bounded_dfs(Node n,int g ,int bound,int (*h)(State16*)){
    std::list<Node*> vacio;
    if (g + h(n.node_state) > bound) return std::make_pair(vacio,g+h(n.node_state)); 
    if (n.node_state->is_goal()){
        std::list<Node*> result = n.extract_solution();
        return std::make_pair(result,n.cost);
    }
    int new_bound = std::numeric_limits<int>::max();
    std::list<Node*> suc = n.succ();
    std::pair<std::list<Node*>, int> result;
    std::list<Node*>::iterator it;
    for ( it = suc.begin() ; it != suc.end(); ++it){
        result = bounded_dfs(Node(&n,(*it)->a,(*it)->node_state),g,bound,h);
        if (!result.first.empty()) return result;
        new_bound = new_bound < result.second ? new_bound : result.second;
    }
    return std::make_pair(0,new_bound);
}

std::list<Node*> ida_start(Node root,int (*h)(State16*)){
   int bound = h(root.node_state); 
   std::pair < std::list<Node*>, int> par;
   while (bound != std::numeric_limits<int>::max()){
       par = bounded_dfs(root, 0, bound,h);
       if (!par.first.empty()) return par.first; 
       bound = par.second;
   }
}


