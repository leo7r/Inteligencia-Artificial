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
 * Algoritmo MinMax
 */
int miniMax(state_t , int, bool jugador);

/**
 * Algoritmo MaxMin
 */
int maxMin(state_t, int, bool jugador);

/**
 * Algoritmo MinMax
 */
int miniMax(state_t n, bool jugador);

/**
 * Algoritmo MaxMin
 */
int maxMin(state_t,  bool jugador);
/**
 * Otra implementacion de minimax. Esta si funciona.
 */
int minimax(state_t n, bool jugador);

/**
 * Algoritmo negamax
 */
int negamax(state_t n, int depth, bool jugador);
/**
 * Algoritmo negamax sin depth
 */
int negamax(state_t n, bool jugador);

/**
 * Implementacion de algoritmo alphabeta.
 * alpha es el menor valor posible.
 * beta es el mayor valor posible.
 */
int alphabeta(state_t n, int depth, int alpha, int beta, bool jugador);
/**
 * Alphabeta sin el depth
 */
int alphabeta(state_t n, int alpha, int beta, bool jugador);

/**
 * Implementacion de algoritmo negamax con cortes determinados.
 */
int negamax_pruning(state_t n, int depth, int alpha, int beta, bool jugador);

/**
 * Implementacion de algoritmo negamax con cortes determinados.
 */
int negamax_pruning(state_t n, int alpha, int beta, bool jugador);


/**
 * Implementacion de algoritmo de scout.
 */
int scout(state_t, int depth , bool );
int scout(state_t,  bool);
bool menor (int a, int b);
bool mayor (int a, int b);

/**
 * Negascout
 */
int nega_scout(state_t state, int depth, int alpha, int beta, bool jugador);

int nega_scout(state_t state, int alpha, int beta, bool jugador);
