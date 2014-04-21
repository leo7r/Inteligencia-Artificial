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

class Node {
	public:
		Node* parent;
		State16* node_state;
		action action;
		int cost;
		
		Node( Node* , action , State16* );
		Node( State16* );
		~Node();
		Node_list* extract_solution();
		Node_list* succ();
}

class Node_box {
	public:
		Node* node;
		Node_box* next;
		
		Node_box( Node* , Node_box* );
		~Node_box();
}

class Node_list {
	public:
		Node_box* first_elem;
		Node_box* last_elem;
		Node_box* current_elem;
		
		Node_list();
		~Node_list();
		void push_back( Node* );
		void push_front( Node* );
		bool is_empty();
		Node* next();
}