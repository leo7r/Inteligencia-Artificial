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
int miniMax(state_t , int, bool);

/**
 * Algoritmo MaxMin
 */
int maxMin(state_t, int, bool);
/**
 * Algoritmo negamax
 */
int negamax(state_t n, int depth, bool jugador);
