/*
 * =====================================================================================
 *
 *       Filename:  algorithm.cc
 *
 *    Description:  Implementacion de algoritmos.
 *
 *        Version:  1.0
 *        Created:  15/05/14 16:00:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, 
 *   Organization:  USB 
 *
 * =====================================================================================
 */
#include <limits>
#include <list>
#include <algorithm>
#include "algorithms.h"

using namespace std;

int minMax(state_t n, int depth){
    if ( n.terminal() || (depth == 0)) return n.value();
    int value = numeric_limits<int>::max();       
    list<int> succ = n.succ(true); // Si agarra mucha memoria. Hacerlo a mano.
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(true,pos);
         value = min(value,maxMin(new_state,depth-1));
         succ.pop_front();
    }
    return value;
}

int maxMin(state_t n, int depth){
    if ( n.terminal() || (depth == 0)) return n.value();
    int value = numeric_limits<int>::max();       
    list<int> succ = n.succ(false); // Si agarra mucha memoria. Hacerlo a mano.
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(false,pos);
         value = max(value,minMax(new_state,depth-1));
         succ.pop_front();
    }
    return value;
}
