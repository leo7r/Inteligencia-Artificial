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

class node {
	public:
		node* parent;
		state* node_state;
		action* action;
		int cost;
		
		node( node* , action , state* );
		node( state* );
		~node();
		node_list* extract_solution();
		node_list* succ();
}

class node_box {
	public:
		node* node;
		node_box* next;
		
		node_box( node* , node_box* );
		~node_box();
}

class node_list {
	public:
		node_box* first_elem;
		node_box* last_elem;
		node_box* current_elem;
		
		node_list();
		~node_list();
		void push_back( node* );
		void push_front( node* );
		int is_empty();
		node* next();
}