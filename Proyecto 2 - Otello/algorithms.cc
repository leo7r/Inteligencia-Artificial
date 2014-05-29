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
int miniMax(state_t n, int depth, bool jugador){
    /*cout << "Depth: ";
    cout << depth;
    cout << endl;*/
    if ( n.terminal() || (depth == 0)) return n.value();
    int value = numeric_limits<int>::max();       
    list<int> succ = n.succ(jugador); // Maximizo el negro.

    if (succ.empty()) return n.value();
	
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         value = min(value,maxMin(new_state,depth-1, !jugador));
         succ.pop_front();
    }
    /*cout << "Value: ";
    cout << value;
    cout << endl;*/
    return value;
}

int maxMin(state_t n, int depth, bool jugador){
    if ( n.terminal()) return n.value();
    int value = numeric_limits<int>::min();       
    list<int> succ = n.succ(jugador); 

    if (succ.empty()) return n.value();
    	
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         value = max(value,miniMax(new_state,jugador));
         succ.pop_front();
    }
    
    return value;
}
/**
 * Implementacion miniMax sin el depth
 * Black es true y false es White.
 */
int miniMax(state_t n, bool jugador){
    if ( n.terminal()) return n.value();
    int value = numeric_limits<int>::max();       
    list<int> succ = n.succ(jugador); // Maximizo el negro.
	
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         value = min(value,maxMin(new_state, !jugador));
         succ.pop_front();
    }
    return value;
}

/**
 * Implementacion maxMin sin el depth
 * Black es true y false es White.
 *
 */
int maxMin(state_t n, bool jugador){
    if ( n.terminal() ) return n.value();
    int value = numeric_limits<int>::min();       
    list<int> succ = n.succ(jugador); // Si agarra mucha memoria. Hacerlo a mano.
	
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         value = max(value,miniMax(new_state,jugador));
         succ.pop_front();
    }
    
    return value;
}
/**
 * Implementacion de algoritmo negamax
 */
int negamax(state_t n, int depth, bool jugador){
	int signo = jugador? 1 : -1 ;
    if ( n.terminal() || (depth == 0)) return signo*n.value();
    int value = numeric_limits<int>::min();       
    list<int> succ = n.succ(jugador);
	
    for (list<int>::iterator it = succ.begin();
         it != succ.end();
         ++it
        ){
            state_t new_state = n.move(jugador,*it);
            value = max(value, -negamax(new_state,depth-1,!jugador));
         }
    return value;
}

/**
 * Implementacion de algoritmo negamax sin el depth.
 */
int negamax(state_t n, bool jugador){
    int signo = jugador? 1 : -1 ;
    if ( n.terminal()) return signo*n.value();
    int value = numeric_limits<int>::min();       
    list<int> succ = n.succ(jugador);
	
    for (list<int>::iterator it = succ.begin();
         it != succ.end();
         ++it
        ){
            state_t new_state = n.move(jugador,*it);
            value = max(value, -negamax(new_state,!jugador));
         }
    return value;
}

/**
 * Implementacion de algoritmo alphabeta.
 * alpha es el menor valor posible.
 * beta es el mayor valor posible.
 */
int alphabeta(state_t n, int depth, int alpha, int beta, bool jugador){
	int signo = jugador? 1 : -1 ;
    if ( n.terminal() || (depth == 0)) return signo*n.value();
    int pos; 
    if (jugador){
        list<int> succ = n.succ(jugador);
		
        while (!succ.empty()){
            pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            alpha = max(alpha, alphabeta(new_state,depth-1,alpha,beta,!jugador)); 
            if (alpha >= beta) break;
            succ.pop_front();
        }
        return alpha;
    } else{
        list<int> succ = n.succ(jugador);
		
        while (!succ.empty()){
            pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            beta = min(beta, alphabeta(new_state,depth-1,alpha,beta,!jugador)); 
            if (alpha >= beta) break;
            succ.pop_front();
        }
        return beta;
    }
}
/**
 * Alphabeta sin el depth.
 */
int alphabeta(state_t n, int alpha, int beta, bool jugador){
    if ( n.terminal() ) return n.value();
    int pos; 
    if (jugador){
        list<int> succ = n.succ(jugador);
		
        while (!succ.empty()){
            pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            alpha = max(alpha, alphabeta(new_state,alpha,beta,!jugador)); 
            if (alpha >= beta) break;
            succ.pop_front();
        }
        return alpha;
    } else{
        list<int> succ = n.succ(jugador);
		
        while (!succ.empty()){
            pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            beta = min(beta, alphabeta(new_state,alpha,beta,!jugador)); 
            if (alpha >= beta) break;
            succ.pop_front();
        }
        return beta;
    }
}


/**
 * Implementacion de algoritmo negamax con cortes determinados.
 */
int negamax_pruning(state_t n, int depth, int alpha, int beta, bool jugador){
    int signo = jugador? 1 : -1 ;
    if ( n.terminal() || (depth == 0)) return signo*n.value();
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
/**
 * Implementacion de algoritmo negamax con cortes determinados y sin depth.
 */
int negamax_pruning(state_t n, int alpha, int beta, bool jugador){
    int signo = jugador? 1 : -1 ;
    if ( n.terminal()) return signo*n.value();
    int m = alpha;
    list<int> succ = n.succ(jugador); // Si agarra mucha memoria. Hacerlo a mano.
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         int t = -negamax_pruning(new_state,-beta,-m,!jugador);
         succ.pop_front();
         m = max(t,m);
         if (m >= beta) return m;
    }
    return m;
}

/**
 * Implementacion de test.
 * @param (*c)(int, int): Funcion de comparacion.
 */
bool test(state_t n, int depth, int value, bool (*c)(int, int), bool jugador){
    if ( n.terminal() || (depth == 0)) return c(n.value(),value);
    if (jugador){
    
        for( int pos = 0; pos < DIM; ++pos ) {
            if((jugador && n.is_black_move(pos)) || (!jugador && n.is_white_move(pos))) {
                state_t new_state = n.move(jugador,pos);
                if (test(new_state, depth -1 , value, c,!jugador)) return true; // Pendiente aca.
            }
        }

        return true;
    } else{
        for( int pos = 0; pos < DIM; ++pos ) {
            if((jugador && n.is_black_move(pos)) || (!jugador && n.is_white_move(pos))) {
                state_t new_state = n.move(jugador,pos);
                if (!test(new_state, depth -1 , value, c,!jugador)) return false; // Pendiente aca.
            }
        }
        return false;
    }
    return !jugador;
}

/**
 * Implementacion de test.
 * @param (*c)(int, int): Funcion de comparacion.
 */
bool test(state_t n, int value, bool (*c)(int, int), bool jugador){
    if ( n.terminal()) return c(n.value(),value);
    if (jugador){
        std::list<int> succ = n.succ(jugador);    
        while(!succ.empty()) {
            int pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            if (test(new_state, value, c,!jugador)) return true; // Pendiente aca.
            succ.pop_front();
        }
        return true;
    } else{
        std::list<int> succ = n.succ(jugador);    
        while(!succ.empty()) {
            int pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            if (!test(new_state, value, c,!jugador)) return false; // Pendiente aca.
            succ.pop_front();
        }
        return false;
    }
    return !jugador;
}

/**
 * Si Mahoma no va a la montaña, la montaña vendrá a Mahoma.
 */
inline bool mayorQue(int a, int b){
    return a > b;
}

inline bool menorQue(int a, int b){
    return a < b;
}

int scout(state_t n, int depth, bool jugador){
    if ( n.terminal() || (depth == 0)) return n.value();
    list<int> succ = n.succ(jugador); 
    if (succ.empty()) return n.value();
    int pos = succ.front();
    state_t new_state = n.move(jugador,pos);
    int v = scout(new_state,depth-1,!jugador);
    succ.pop_front();
    while (!succ.empty()){
        pos = succ.front();
        new_state = n.move(jugador,pos);
        if (jugador && test(new_state,depth-1,v, mayorQue,jugador)) v = scout(new_state,depth-1,!jugador);
        if (!jugador && test(new_state,depth-1,v,menorQue,jugador)) v = scout(new_state,depth-1,!jugador);
        succ.pop_front();
    }
    return v;
}
/**
 * Scout sin depth.
 */
int scout(state_t n, bool jugador){
    int signo = jugador? 1 : -1 ;
    if ( n.terminal()) return signo*n.value();
    list<int> succ = n.succ(jugador); 
    if (succ.empty()) return n.value();
    int pos = succ.front();
    state_t new_state = n.move(jugador,pos);
    int v = scout(new_state,!jugador);
    succ.pop_front();
    while (!succ.empty()){
        pos = succ.front();
        new_state = n.move(jugador,pos);
        if (jugador && test(new_state,v, mayorQue,jugador)) v = scout(new_state,!jugador);
        if (!jugador && test(new_state,v,menorQue,jugador)) v = scout(new_state,!jugador);
        succ.pop_front();
    }
    return v;
}

int nega_scout(state_t state, int depth, int alpha, int beta, bool jugador){
    int signo = jugador? 1 : -1 ;
	if ( state.terminal() || (depth == 0)) return (signo*state.value());
    int m = numeric_limits<int>::min();
    int n = beta;
	bool succ_vacia = true;

    for( int pos = 0; pos < DIM; ++pos ) {
        if((jugador && state.is_black_move(pos)) || (!jugador && state.is_white_move(pos))) {
			succ_vacia = false;
            state_t new_state = state.move(jugador,pos);
            int t = -nega_scout(new_state, depth-1, -n, -max(m,alpha), !jugador);
            if (t > m){
                if (n == beta || depth < 3 || t >= beta){
                 m = t;
                } else {
                    m = -nega_scout(new_state, depth - 1 , -beta, -t, !jugador);
                }
            }
            if (m >= beta) return m; // Este algoritmo es burda de raro.
            n = max(alpha,m) + 1;
        }
    }
	
	if ( succ_vacia ){
		return -nega_scout(state,depth-1,-beta,-alpha,!jugador);
	}
	
    return m;
}

int nega_scout(state_t state, int alpha, int beta, bool jugador){
    int signo = jugador? 1 : -1 ;
	if ( state.terminal()) return (signo*state.value());
    int m = numeric_limits<int>::min();
    int n = beta;
	bool succ_vacia = true;

    for( int pos = 0; pos < DIM; ++pos ) {
        if((jugador && state.is_black_move(pos)) || (!jugador && state.is_white_move(pos))) {
			succ_vacia = false;
            state_t new_state = state.move(jugador,pos);
            int t = -nega_scout(new_state, -n, -max(m,alpha), !jugador);
            if (t > m){
                if (n == beta || t >= beta){
                 m = t;
                } else {
                    m = -nega_scout(new_state, -beta, -t, !jugador);
                }
            }
            if (m >= beta) return m; // Este algoritmo es burda de raro.
            n = max(alpha,m) + 1;
        }
    }
	
	if ( succ_vacia ){
		return -nega_scout(state,-beta,-alpha,!jugador);
	}
	
    return m;
}
