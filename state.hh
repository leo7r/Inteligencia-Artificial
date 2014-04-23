/*
 * =====================================================================================
 *
 *       Filename:  state.hh
 *
 *    Description: Headers para los estados
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
#include <unordered_map>

typedef enum {
	ARRIBA,
	DERECHA,
	ABAJO,
	IZQUIERDA,
	ROOT
} action;

 
void print_action(action);

class State{
    virtual bool is_goal() = 0;
    virtual void print_state() = 0;
    virtual char find_zero_index() = 0;
    virtual State* a_derecha() = 0;
    virtual State* a_izquierda() = 0;
    virtual State* a_arriba() = 0;
    virtual State* a_abajo() = 0;
};

class State16{
public:
    int_fast64_t current_state;
    char zero_index;
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

static std::unordered_map<int_fast64_t,State16*> stateMap;

/*class hash_table16{
public:
    static hash_table16* get_hash_table16();
    ~hash_table16();
private:
    hash_table();

}*/

State16* crear_estado(int_fast64_t , char);

