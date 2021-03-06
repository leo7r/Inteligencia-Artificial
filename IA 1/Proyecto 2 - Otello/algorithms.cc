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
 * Algoritmo de minimax sin el depth.
 */
int minimax(state_t n, bool jugador){
    if ( n.terminal()) return n.value();
    int pos; 
    int value;
    if (jugador){
        list<int> succ = n.succ(jugador);
        value = MIN_INT;       
		
        while (!succ.empty()){
            pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            value = max(value, minimax(new_state,!jugador)); 
            succ.pop_front();
        }
        return value;
    } else{
        list<int> succ = n.succ(jugador);
        value = MAX_INT;       
        
        while (!succ.empty()){
            pos = succ.front();
            state_t new_state = n.move(jugador,pos);
            value = min(value, minimax(new_state,!jugador)); 
            succ.pop_front();
        }
        return value;
    }
}

/**
 * Implementacion de algoritmo negamax sin el depth.
 */
int negamax(state_t n, bool jugador){
    int signo = jugador? 1 : -1 ;
    if ( n.terminal()) return signo*n.value();
    int value = MIN_INT;       
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
 * Implementacion de algoritmo negamax con cortes determinados y sin depth.
 */
int negamax_pruning(state_t n, int alpha, int beta, bool jugador){
    int signo = jugador? 1 : -1 ;
    if ( n.terminal()) return signo*n.value();
    int m = alpha;
    list<int> succ = n.succ(jugador); // Si agarra mucha memoria. Hacerlo a mano.
		
	if ( succ.empty() ){
		return -negamax_pruning(n, -beta , -alpha , !jugador );
	}
	
    while (!succ.empty()){
         int pos = succ.front();
         state_t new_state = n.move(jugador,pos);
         int value = -negamax_pruning(new_state,-beta,-alpha,!jugador);
         succ.pop_front();
         m = max(m,value);
         alpha = max(value,alpha);
         if (alpha >= beta) break;
    }
    return m;
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

/**
 * Implementacion de test.
 * @param (*c)(int, int): Funcion de comparacion.
 */
bool test(state_t n, int value, bool (*c)(int, int), bool jugador){
    if ( n.terminal()) return c(n.value(),value);
    if (jugador){
        std::list<int> succ = n.succ(jugador);  
		
		if ( c == mayorQue ){
			while(!succ.empty()) {
				int pos = succ.front();
				state_t new_state = n.move(jugador,pos);				
				if (test(new_state, value, c,!jugador)) return true; // Pendiente aca.
				succ.pop_front();
			}
			return false;
		}
		else{
			while(!succ.empty()) {
				int pos = succ.front();
				state_t new_state = n.move(jugador,pos);
				if (!test(new_state, value, c,!jugador)) return false; // Pendiente aca.
				succ.pop_front();
			}
			return true;
		}
		
        
    } else{
        std::list<int> succ = n.succ(jugador); 

		if ( c == mayorQue ){
			while(!succ.empty()) {
				int pos = succ.front();
				state_t new_state = n.move(jugador,pos);
				if (!test(new_state, value, c,!jugador)) return false; // Pendiente aca.
				succ.pop_front();
			}
			return true;
		}
		else{
			while(!succ.empty()) {
				int pos = succ.front();
				state_t new_state = n.move(jugador,pos);
				if (test(new_state, value, c,!jugador)) return true; // Pendiente aca.
				succ.pop_front();
			}
			return false;
		}
			
        
    }
    
}

/**
 * Scout sin depth.
 */
int scout(state_t n, bool jugador){
    
	if ( n.terminal()) return n.value();
    list<int> succ = n.succ(jugador); 
    if (succ.empty()) return scout(n, !jugador);
    int pos = succ.front();
    state_t new_state = n.move(jugador,pos);
    int v = scout(new_state,!jugador);
    succ.pop_front();
	
    while (!succ.empty()){
        pos = succ.front();
        new_state = n.move(jugador,pos);
        if (jugador && test(new_state,v, mayorQue,!jugador)) v = scout(new_state,!jugador);
        if (!jugador && test(new_state,v,menorQue,!jugador)) v = scout(new_state,!jugador);
        succ.pop_front();
    }
    return v;
}

/*
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
*/
int nega_scout(state_t state, int depth , int alpha, int beta, bool jugador){
    int signo = jugador? 1 : -1 ;
    if ( state.terminal()) return (signo*state.value());
    list<int> succ = state.succ(jugador);
	
	int best_m = -100;
	int best_n = beta;
	
	if ( succ.empty() ){
		return -nega_scout(state, depth -1, -beta, -alpha, !jugador);
	}
	
	while ( !succ.empty() ){
		int pos = succ.front();
		state_t new_state = state.move(jugador, pos);
		int score = -nega_scout(new_state,depth-1,-best_n,-max(alpha , best_m ),!jugador);
		
		if ( score > best_m ){
			if ( best_n == beta || depth < 3 || score >= beta ){
				best_m = score;
			}
			else{
				best_m = -nega_scout(new_state , depth-1, -beta , -score , !jugador);
			}
		}
		
		if ( best_m >= beta ) return best_m;
		
		best_n = max(alpha,best_m) + 1;
		succ.pop_front();
	}
	
	return best_m;
	
	/*
	
    int alpha_ = max(score,alpha);
    while (!succ.empty()){
        pos = succ.front();
        state_t new_state = state.move(jugador,pos);
        score = -nega_scout(new_state, -alpha_ -1, -alpha_, !jugador);
        if ( alpha_ < score && score < beta){
            score = nega_scout(new_state, -beta,-score, !jugador);
        }
        if (alpha_ >= beta) break;
        succ.pop_front();
    }
    return alpha_;*/
}
