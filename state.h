/*
 * =====================================================================================
 *
 *       Filename:  state.h
 *
 *    Description:  Headers de los estados.
 *
 *        Version:  1.0
 *        Created:  07/05/14 18:52:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */

typedef struct{

} action; /* action probablemente sea un enum  */

typedef struct{
    /* Atributos de estado.  */    
    long long current_state;
} state; /* Este seria el estado para el 15-puzzle  */

state init(); /* Crea estado inicial  */

int is_goal(state); /* Chequea si estado es goal */

/*  succ(state); */ /* Retorna una lista de pares de <estado sucesivo, accione> (falta el tipo lista y par). */


