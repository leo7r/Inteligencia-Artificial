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

#include "state.hh"
#include <stdint.h>
#include <list>

class Node {
    public:
		Node* parent;
		State* node_state;
		action a;
		int cost;
	
		Node( Node* , action , State* );
		Node( State* );
		~Node();
		std::list<Node*> extract_solution();
		std::list<Node*> succ();
        void succ(std::list<Node*> *);
		bool is_posible(action);
};
