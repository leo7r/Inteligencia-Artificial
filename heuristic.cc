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
#include <iostream>
#include <utility>
#include <list>
#include <queue>
#include <stdint.h>
#include "heuristic.hh"

int temporal = 0;
int manhattan[16][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4, 4, 3, 4, 5},
	{2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3, 5, 4, 3, 4},
	{3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2, 6, 5, 4, 3},
	{1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5},
	{2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4},
	{3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3},
	{4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2},
	{2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4},
	{3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3},
	{4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2},
	{5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1},
	{3, 4, 5, 6, 2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3},
	{4, 3, 4, 5, 3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2},
	{5, 4, 3, 4, 4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1},
	{6, 5, 4, 3, 5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0}


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

/*std::pair<std::list<Node*>,int> bounded_dfs(Node n,int g ,int bound,int (*h)(State16*)){
    std::list<Node*>* vacio = new std::list<Node*>;
    if (g + h(n.node_state) > bound){ 
        std::pair<std::list<Node*>,int> result0;
        result0 = std::make_pair(*vacio,g+h(n.node_state));
        return result0;
    }
    if (n.node_state->is_goal()){
        std::list<Node*>* result = new std::list<Node*>;
        *result = n.extract_solution();
        std::pair<std::list<Node*>,int> result1;
        result1 =  std::make_pair(*result,n.cost);
        return result1;
    }
    int new_bound = std::numeric_limits<int>::max();
    std::list<Node*>* suc = new std::list<Node*>;
    *suc = n.succ();
    std::pair<std::list<Node*>, int> result;
    std::list<Node*>::iterator it;
    for ( it = suc->begin() ; it != suc->end(); ++it){
        result = bounded_dfs(Node(&n,(*it)->a,(*it)->node_state),g,bound,h);
        if (!result.first.empty()) return result;
        new_bound = new_bound < result.second ? new_bound : result.second;
    }
    std::pair<std::list<Node*>,int> result2;
    result2 = std::make_pair(0,new_bound);
    return result2;
}*/

/*std::list<Node*> ida_star(Node root,int (*h)(State16*)){
   int bound = h(root.node_state); 
   std::pair < std::list<Node*>, int> par;
   while (bound != std::numeric_limits<int>::max()){
       par = bounded_dfs(root, 0, bound,h);
       if (!par.first.empty()){
            return par.first; 
       }
       bound = par.second;
   }
}*/

int expanded_nodes;

std::pair<int,bool> search(Node* node, int g, int bound,int (*h)(State16*)){
    std::pair<int,bool> f;
    f.first = g + h(node->node_state);
    if (f.first > bound ) return f;
    if (node->node_state->is_goal()){
        f.second = true;
        return f;
    }
    std::pair<int,bool> min;
    min.first = std::numeric_limits<int>::max();
    temporal++;
	
	
    int num_succ = 0;
	
    std::list<Node*> succ =  node->succ();
    expanded_nodes++;
    while (!succ.empty()){
        		
	Node* tmp = succ.front();
			
	std::pair<int,bool> t = search(tmp,g + tmp->cost,bound,h); // La vaina no funcionaba porque no le estaban sumando tmp->cost a g
			
			
	if (t.second == true) return t;
	if (t.first < min.first) min.first = t.first;			
		
        succ.pop_front();
    }
	
	
    return min;
}

bool ida_star1(Node* root, int (*h)(State16*)){
	
	expanded_nodes = 0;

   int bound = h(root->node_state); 
   std::pair<int,bool> t;
   while(1){
       t = search(root,0,bound,h);
	   
       if (t.second == true) return true;
       if (t.first == std::numeric_limits<int>::max()) return false;
   }
}

bool compare_node_state16 (const Node* first, const Node* second)
{ 
    if (dist_manhattan(first->node_state)<=dist_manhattan(second->node_state)) return true;
    else return false;
}

class compare_node{
    bool reverse;
    int (*h)(State16*);
    int (*h2)(State24*); 
public:
    compare_node(bool revparam, int(*f)(State16*)): reverse(revparam),h(f),h2(0){
    }
    compare_node(bool revparam, int(*f)(State24*)): reverse(revparam),h2(f),h(0){
    }
    bool operator() (Node* n1, Node* n2){
        if (h2 == 0){
            if (reverse) return ((n1->cost + h(n1->node_state)) > (n2->cost + h(n2->node_state)));
            else return ((n1->cost + h(n1->node_state)) < (n2->cost + h(n2->node_state)));
        } else{
            if (reverse) return ((n1->cost) > (n2->cost));
            else return ((n1->cost) < (n2->cost));
        }
    }
};

static std::unordered_map<int_fast64_t,int> dist16;

bool a_star(Node* root,int (*h)(State16*)){
    std::priority_queue<Node*,std::vector<Node*>,compare_node> q (compare_node(false,h));  
    q.push(root);
    while (!q.empty()){
        Node* n = q.top();
        q.pop();
        if ((n->node_state->closed != false) || (dist16[n->node_state->current_state] > n->cost)) {
            n->node_state->closed = true;
            dist16[n->node_state->current_state] = n->cost;
            if (n->node_state->is_goal()) return true;
            
            std::list<Node*> succ =  n->succ();
            while (!succ.empty()){
                Node* tmp = succ.front();
                if (h(tmp->node_state) < std::numeric_limits<int>::max()) q.push(tmp);     
                succ.pop_front();
            }
        }
    }
    return false;
}
