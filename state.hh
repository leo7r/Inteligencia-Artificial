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

	public:
		char zero_index;
		bool closed;                  /* Nos dice si esta cerrado o no. */
		
		State();
		State(char zi);

		virtual bool is_goal() = 0;
		virtual void print_state() = 0;
		virtual char find_zero_index() = 0;
		virtual State* a_derecha() = 0;
		virtual State* a_izquierda() = 0;
		virtual State* a_arriba() = 0;
		virtual State* a_abajo() = 0;
		virtual bool is_posible( action ) = 0;
		virtual bool equals( State* st ) = 0;
};

class State16: public State{
public:
    int_fast64_t current_state;
    State16(); 
    State16(int_fast64_t,char);
    ~State16();
    bool is_goal();
	char* toCharArray();
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
	bool equals( State* st );
};

/**
 * Clase de State25.
 */
class State25: public State{
public:
    char* current_state;
    State25(); 
    State25(char*,char);
    ~State25();
    bool is_goal();
    void print_state();
    char find_zero_index();
    State25* a_derecha();
    State25* a_izquierda();
    State25* a_arriba();
    State25* a_abajo();
    bool is_posible( action );
	bool equals( State* st );
};

static std::unordered_map<int_fast64_t,State16*> stateMap;

State16* crear_estado(int_fast64_t , char);

State16* crear_estadop(std::pair<int_fast64_t,char>);
