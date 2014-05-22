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
int miniMax(state_t , int);

/**
 * Algoritmo MaxMin
 */
int maxMin(state_t, int);
/**
 * Algoritmo negamax
 */
int negamax(state_t n, int depth, bool jugador);

/**
 * Implementacion de algoritmo alphabeta.
 * alpha es el menor valor posible.
 * beta es el mayor valor posible.
 */
int alphabeta(state_t n, int depth, int alpha, int beta, bool jugador);

/**
 * Implementacion de algoritmo negamax con cortes determinados.
 */
int negamax_pruning(state_t n, int depth, int alpha, int beta, bool jugador);


/**
 * Implementacion de algoritmo de scout.
 */

