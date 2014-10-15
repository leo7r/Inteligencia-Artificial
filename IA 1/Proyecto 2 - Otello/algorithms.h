/*
 * =====================================================================================
 *
 *       Filename:  algorithm.h
 *
 *    Description:  Headers para los algoritmos a programar.
 *
 *        Version:  1.0
 *        Created:  15/05/14 16:00:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, 
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include "othello_cut.h"
/**
 * Otra implementacion de minimax. Esta si funciona.
 */
int minimax(state_t n, bool jugador);

/**
 * Algoritmo negamax sin depth
 */
int negamax(state_t n, bool jugador);

/**
 * Alphabeta sin el depth
 */
int alphabeta(state_t n, int alpha, int beta, bool jugador);

/**
 * Implementacion de algoritmo negamax con cortes determinados.
 */
int negamax_pruning(state_t n, int alpha, int beta, bool jugador);


/**
 * Implementacion de algoritmo de scout.
 */
int scout(state_t,  bool);
bool menorQue (int a, int b);
bool mayorQue (int a, int b);

/**
 * Negascout
 */
int nega_scout(state_t state, int depth, int alpha, int beta, bool jugador);
