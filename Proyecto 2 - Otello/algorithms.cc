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
 * Implementacion miniMax
 * Black es true y false es White.
 */
int miniMax(state_t n, int depth){
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
    int value = numeric_limits<int>::min();       
    list<int> succ = n.succ(false); // Si agarra mucha memoria. Hacerlo a mano.
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(false,pos);
         value = max(value,miniMax(new_state,depth-1));
         succ.pop_front();
    }
    return value;
}
/**
 * Implementacion de algoritmo negamax
 */
int negamax(state_t n, int depth, bool jugador){
    short int signo = jugador ? 1 : -1;
    if ( n.terminal() || (depth == 0)) return (signo * n.value());
    int value = numeric_limits<int>::min();       
    list<int> succ = n.succ(jugador); // Si agarra mucha memoria. Hacerlo a mano.
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         value = max(value, -negamax(new_state,depth-1,!jugador));
         succ.pop_front();
    }
    return value;
}
/**
 * Implementacion de algoritmo alphabeta.
 * alpha es el menor valor posible.
 * beta es el mayor valor posible.
 */
int alphabeta(state_t n, int depth, int alpha, int beta, bool jugador){
    if ( n.terminal() || (depth == 0)) return n.value();
    int pos; 
    if (jugador){
        list<int> succ = n.succ(jugador); // Si agarra mucha memoria. Hacerlo a mano.
        while (!succ.empty()){
            pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            alpha = max(alpha, alphabeta(new_state,depth-1,alpha,beta,!jugador)); 
            if (alpha >= beta) break;
            succ.pop_front();
        }
        return alpha;
    } else{
        list<int> succ = n.succ(jugador); // Si agarra mucha memoria. Hacerlo a mano.
        while (!succ.empty()){
            pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            beta = min(alpha, alphabeta(new_state,depth-1,alpha,beta,!jugador)); 
            if (alpha <= beta) break;
            succ.pop_front();
        }
        return beta;
    }
}

/**
 * Implementacion de algoritmo negamax con cortes determinados.
 */
int negamax_pruning(state_t n, int depth, int alpha, int beta, bool jugador){
    short int signo = jugador ? 1 : -1;
    if ( n.terminal() || (depth == 0)) return (signo * n.value());
    int m = alpha;
    list<int> succ = n.succ(jugador); // Si agarra mucha memoria. Hacerlo a mano.
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         int t = -negamax_pruning(new_state,depth-1,-beta,-m,!jugador);
         succ.pop_front();
         if (t > m) m = t;
         if (m >= beta) return m;
    }
    return m;
}

//bool test(state_t n, int depth, int value,  )
