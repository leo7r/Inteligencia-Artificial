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
#include <utility>
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
    bool closed;
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
    std::pair<int_fast64_t,char> a_derechap();
    std::pair<int_fast64_t,char> a_izquierdap();
    std::pair<int_fast64_t,char> a_arribap();
    std::pair<int_fast64_t,char> a_abajop();
	bool is_posible( action );
};

class State24{
    State24(); 
    ~State24();
};

static std::unordered_map<int_fast64_t,State16*> stateMap;

State16* crear_estado(int_fast64_t , char);

State16* crear_estadop(std::pair<int_fast64_t,char>);
