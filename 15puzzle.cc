/*
 * =====================================================================================
 *
 *       Filename:  15puzzle.cc
 *
 *    Description:  Resolucion de 15 puzzle
 *
 *        Version:  1.0
 *        Created:  21/04/14 21:59:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "heuristic.hh"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <exception>
#include <chrono>
#include <ctime>

int_fast64_t toInt64(int* array){
   int_fast64_t tmp[16]; 
   int i = 0;
   while (i != 16){
        tmp[i]  = 0x000000000000000;
        tmp[i] = tmp[i] | array[i];
        tmp[i] = tmp[i] << (60-(i*4));
        i++;
    }
    i = 1;
    while (i != 16){
        tmp[0] = tmp[0] | tmp[i];
        i++;
    }
    return tmp[0];
}

int main(int argc, char *argv[]){
    std::string* f_name;
    if (argc == 1){
        f_name = new std::string();
        std::cout << "Escriba el nombre del archivo con las instancias del puzzle: ";
        std::cin >> *f_name;
    } else {
        f_name = new std::string(argv[1]);
    }
    std::fstream fs (f_name->data(), std::fstream::in); 
    if (!fs){
        std::cout << "Fallo en abrir el archivo.";
        return 1;
    }
    int n,i;
    char zero_index;
    int array[16];
    i = 0;
    while(!fs.eof()) {
        fs >> n;
        if (n == 0) zero_index = i;
        array[i] = n;
        i++;
        if (i == 16){
            int_fast64_t a =  toInt64(array);
            State16* s = new State16(a,zero_index);
            Node *n = new Node(s);
			
			std::chrono::time_point<std::chrono::system_clock> start, end;
			start = std::chrono::system_clock::now();
			
			bool funciona = ida_star1(n,dist_manhattan);
			
			if ( funciona ){
				std::cout << "Funciono!";
			}
			else{
				std::cout << "No funciono :(";
			}	
			
			end = std::chrono::system_clock::now();
			
			std::chrono::duration<double> elapsed_seconds = end-start;
			
			std::cout << "Tiempo: " << elapsed_seconds.count() << "\n";
			//std::cin.get();
            
            i = 0;
        }
    }
    return 0;
}
