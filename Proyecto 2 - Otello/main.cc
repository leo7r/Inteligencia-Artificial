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

void print_help(){
    cout << "Usage: ./othello -a { algorithm } -d {depth}\n";
    cout << "Algorithms: minimax, negamax, alphabeta, negamaxp \n";
}

int main(int argc, const char **argv) {
    state_t state;
    string *algorithm = 0;
    int depth = 0;

    /* Windows es una mierda. */
    for (int i = 0; i < argc ; i++){
        if (argv[i] == string("-a") && (i + 1 < argc)){
            algorithm = new string(argv[i+1]);
        } else if (argv[i] == string("-d") && (i + 1 < argc)){
            depth = atoi(argv[i+1]);
        }
    }

    if (algorithm == 0 || depth <= 0){
        print_help();
        return 0;
    }

    int result;
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
            cout << "Result: ";
            cout << result;
            cout << endl;
    cout << state;
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof(state) * 8 << endl;
	
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

