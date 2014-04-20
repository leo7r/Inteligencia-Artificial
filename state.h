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

typedef enum { false, true } bool;
 
typedef enum {
	ARRIBA,
	DERECHA,
	ABAJO,
	IZQUIERDA,
	ROOT
} action;
 
/*
typedef struct{
	enum posible_actions current_action;
	int cost;
        bool closed;
} action; 
*/

typedef struct{
    /* Atributos de estado.  */
    int_fast64_t current_state;
    char zero_index;
} state; /* Este seria el estado para el 15-puzzle  */

state* init(); /* Crea estado inicial  */

state* make_state(int_fast64_t , char); /*aca se debera chequear si ya existe el estado en el hash*/

int is_goal(state*); /* Chequea si estado es goal */

/* Imprime una representacion de un estado */
void print_state(state*);

/* Imprime la representacion de una accion */
void print_action(action);

//action new_action(enum posible_actions, int);

char find_zero_index(state*);

state* a_derecha(state*);
state* a_izquierda(state*);
state* a_arriba(state*);
state* a_abajo(state*);
