/*
 *  Copyright (C) 2012 Universidad Simon Bolivar
 * 
 *  Permission is hereby granted to distribute this software for
 *  non-commercial research purposes, provided that this copyright
 *  notice is included with any such distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 *  EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *  SOFTWARE IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
 *  ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *  
 *  Blai Bonet, bonet@ldc.usb.ve
 *
 *  Last revision: 11/08/2012
 *
 */

#include "algorithms.h" // won't work correctly until .h is fixed!
#include <limits>
#include <iostream>
#include <stdlib.h>

using namespace std;

int get_size(int* arr){
    int result = 0;
    for (int i = 0; arr[i] != -1 ; i++){
        result++;
    }
    return result;
}

void print_help(){
    cout << "\nUsage: ./othello -a { algorithm } -s {State #}\n";
    cout << "Algorithms: minimax, negamax, alphabeta, negamaxp, scout, nega_scout \n";
    cout << "State #: state in the Principal Variation between 0 and 33.\n";
}

int main(int argc, const char **argv) {
    state_t state;
    string *algorithm = 0;
    int depth = -1;

    for (int i = 0; i < argc ; i++){
        if (argv[i] == string("-a") && (i + 1 < argc)){
            algorithm = new string(argv[i+1]);
        } else if (argv[i] == string("-s") && (i + 1 < argc)){
            depth = atoi(argv[i+1]);// OJO aca se cambia de una el depth como 33-estadoRequerido
        }
    }

    if (algorithm == 0 || depth < 0 || depth > 33){
        print_help();
        return 0;
    }
    /**
     * Hay que guardar todos los estados en un vector.
     * El depth debe ser entre 0 .. 32
     * Calculamos desde el estado vector[depth] hasta el estado final. Con un depth = 33 - (estado requerido). 
     * Eso deberia darnos siempre -4 (o 4 y -4 si estamos con negamax).
     */
	 
    int size = get_size(PV);
    int result;
	
	
	
	//llenar arreglo con los 33 estados de la PV
	state_t PV_states[34]; //33 pasos de la VP + estado incial
	state_t aux_state;
	PV_states[0]=aux_state; //estado inicial (6)
	
	for( int i = 0; PV[i] != -1; ++i ){
		bool aux_player = i % 2 == 0; // black moves first!
		aux_state = aux_state.move(aux_player, PV[i]);
		PV_states[i+1] = aux_state;
	}
	//chequeando si se guardaron bien
	
	/*for(int i = 0; i<34; i++){
		cout << "estado" << i <<"\n";
		cout << PV_states[i];
		cout << "\n";
	}*/
	
	
	bool player = depth % 2 == 0; // black moves first! ojo aca not sure
	if (*algorithm == "minimax"){ //bueno
	    result = minimax(PV_states[depth],player);
	} else if(*algorithm == "negamax"){ // chevere
		result = negamax(PV_states[depth],player);
	} else if (*algorithm == "alphabeta"){ //chevere
		result = alphabeta(PV_states[depth],numeric_limits<int>::min(), numeric_limits<int>::max(), player); 
	} else if (*algorithm == "negamaxp"){
            if (player){
	        result = negamax_pruning(PV_states[depth], numeric_limits<int>::min(), numeric_limits<int>::max(), player);
            } else {
	        result = -negamax_pruning(PV_states[depth], numeric_limits<int>::min(), numeric_limits<int>::max(), player); 
            }
	} else if (*algorithm == "scout"){
		result = scout(PV_states[depth], player); // este esta malisimo
	} else if (*algorithm == "nega_scout") {
		result = nega_scout(PV_states[depth], numeric_limits<int>::min(), numeric_limits<int>::max(), player); 
	} else{
            return 0;
        }
	
	
	// end new
	
	
	/*
    cout << "Principal variation:" << endl;
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        cout << state;
        if (*algorithm == "minimax"){
            result = miniMax(state,depth);
        } else if(*algorithm == "negamax"){
            result = negamax(state,depth,player);
        } else if (*algorithm == "alphabeta"){
            result = alphabeta(state,depth,numeric_limits<int>::min(), numeric_limits<int>::max(), player);
        } else if (*algorithm == "negamaxp"){
            result = negamax_pruning(state, depth, numeric_limits<int>::min(), numeric_limits<int>::max(), player);
        } else if (*algorithm == "scout"){
            result = scout(state, depth, player);
        } else if (*algorithm == "nega_scout") {
            result = nega_scout(state, depth, numeric_limits<int>::min(), numeric_limits<int>::max(), player);
        }
        cout << "Result: ";
        cout << result;
        cout << endl;
        cout << (player ? "Black" : "White")
             << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
             << endl;
        state = state.move(player, pos);
        cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
    }
	*/

    //cout << PV_states[depth];
    cout << "Result: ";
    cout << result;
    cout << endl;
    cout << "Value of the game = " << PV_states[depth].value() << endl;
    cout << "#bits per state = " << sizeof(PV_states[depth]) * 8 << endl;
	
	/*
    if( argc > 1 ) {
        int n = atoi(argv[1]);
        cout << endl << "Apply " << n << " random movements at empty board:";
        state = state_t();
        for( int i = 0; i < n; ++i ) {
            bool player = i % 2 == 0; // black moves first
            int pos = state.get_random_move(player);
            state = state.move(player, pos);
            cout << " " << pos;
        }
        cout << endl << state;
    }
	*/
	
    return 0;
}

