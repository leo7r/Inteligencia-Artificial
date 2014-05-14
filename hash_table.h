/*
 * =====================================================================================
 *
 *       Filename:  hash_table.h
 *
 *    Description:  Tabla de hash.
 *
 *        Version:  1.0
 *        Created:  07/05/14 19:09:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <gmp.h> // Libreria para numeros GRANDES. https://gmplib.org/ 
#include "state.h"
#include <limits.h>
#include <stdint.h>
mpz_t factorial16;

typedef struct{

} hash_table16;

/**
 * Algoritmo para asociar un numero a una permutacion 
 * Revisar "Ranking and unranking permutations in linear time"
 */
mpz_t rank(int, int_fast64_t , int_fast64_t);

/**
 * Algoritmo para obtener una permutacion de un numero determinado 
 * Revisar "Ranking and unranking permutations in linear time"
 */
void unrank(int, mpz_t, int_fast64_t*);

state* get(hash_table16*,int_fast64_t); /* Obtengo un estado a partir de la permutacion */

int put(hash_table16*,state*);          /* Inserto un estado en la tabla */
