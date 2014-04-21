/*
 * =====================================================================================
 *
 *       Filename:  State.hh
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 11:41:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdint.h>

typedef enum {
	ARRIBA,
	DERECHA,
	ABAJO,
	IZQUIERDA,
	ROOT
} action;
 
void print_action(action);

class State16{
private:
    int_fast64_t current_state;
    char zero_index;
public:
    State16(); 
    State16(int_fast64_t,char);
    ~State16();
    bool is_goal();
    void print_state();
    char find_zero_index();
    State16* a_derecha();
    State16* a_izquierda();
    State16* a_arriba();
    State16* a_abajo();
};
