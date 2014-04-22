/*
 * =====================================================================================
 *
 *       Filename:  ida_start.cc
 *
 *    Description:  Algoritmo de IDA*
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


void ida_start(Node root,int (*h)()){
   int bound = h(root); 
   int t;
   while(1){
         t = search(root,0,bound);   
         if (t == 0) return;
         if (t == MAX_INT) return;
         bound = t;
   }
}

int search(Node n,int g ,int bound){
    int f = g + n.cost;
    if (f > bound) return f; 
    if (n.node_state.is_goal() ) return f;
    int min = MAX_INT;
}
