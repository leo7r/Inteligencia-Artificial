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

#include <stdint.h>
 
enum posible_actions {
	ARRIBA,
	DERECHA,
	ABAJO,
	IZQUIERDA
};
 
typedef struct{
	enum posible_actions current_action;
	int cost;
} action; 

typedef struct{
    /* Atributos de estado.  */
    int_fast64_t current_state;
} state; /* Este seria el estado para el 15-puzzle  */

state init(); /* Crea estado inicial  */

int is_goal(state); /* Chequea si estado es goal */

/* Imprime una representacion de un estado */
void print_state(state);

/* Imprime la representacion de una accion */
void print_action(action);

action new_action(action*,enum posible_actions, int);
