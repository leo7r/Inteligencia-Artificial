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
/**
 * Implementacion minMax
 * @param jugador: Nos dice el jugador del cual se calcula el minMax. Black es true y false es White.
 */
int minMax(state_t n, int depth, bool jugador){
    if ( n.terminal() || (depth == 0)) return n.value();
    int value = numeric_limits<int>::max();       
    list<int> succ = n.succ(jugador); // Si agarra mucha memoria. Hacerlo a mano.
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         value = min(value,maxMin(new_state,depth-1,jugador));
         succ.pop_front();
    }
    return value;
}

int maxMin(state_t n, int depth, bool jugador){
    if ( n.terminal() || (depth == 0)) return n.value();
    int value = numeric_limits<int>::max();       
    list<int> succ = n.succ(!jugador); // Si agarra mucha memoria. Hacerlo a mano.
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(!jugador,pos);
         value = max(value,minMax(new_state,depth-1,!jugador));
         succ.pop_front();
    }
    return value;
}
