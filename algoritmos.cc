/*
 * =====================================================================================
 *
 *       Filename:  algoritmos.cc
 *
 *    Description:  Implementacion de los algoritmos de busqueda
 *
 *        Version:  1.0
 *        Created:  21/04/14 14:30:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "nodes.hh"
#include <limits>
#include <utility>
#include <list>

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


