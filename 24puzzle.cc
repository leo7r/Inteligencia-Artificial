/*
 * =====================================================================================
 *
 *       Filename:  24puzzle.cc
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
#include <string.h>

void imprimirAyuda(){
    std::cout << "15puzzle [opciones]\n";
    std::cout << "opciones: \n";
    std::cout << "-h { manhattan | pdatabase }  Heuristica deseada\n";
    std::cout << "-f {archivo}                  Archivo con instancias a resolver\n";
}

int main(int argc, char *argv[]){
    std::string* f_name = 0;
    std::string* heuristica = 0;
    int n;
	int i;
    bool solution;

    for ( i = 0 ; i != argc ; i++){
        if (argv[i] == std::string("-h") && (i + 1 < argc)) {
           heuristica = new std::string(argv[i+1]); 
        } else if (argv[i] == std::string("-f") && (i + 1 < argc)){
           f_name = new std::string(argv[i+1]); 
        }
    }    
    
    if (f_name == 0 || heuristica == 0){
        imprimirAyuda();
        return 1;
    }

    std::fstream fs (f_name->data(), std::fstream::in);

    if (!fs){
        std::cout << "Fallo en abrir el archivo.";
        return 1;
    }

    char zero_index;
    char array[25];
    i = 0;

    if (*heuristica == "pdatabase"){
        std::cout << "Cargando base de datos de patrones: \n";
        calcularPDB25();	
        loadPDB24();
    }
	
    while(!fs.eof()) {
        fs >> n;
		
		//std::cout << "n: " << n << "\n";
		//std::cin.get();
		
        if (n == 0) zero_index = i;
        array[i] = n;
        i++;
        if (i == 25){
            State25* s = new State25(array,zero_index);
            Node *n = new Node(s);		
	    std::chrono::time_point<std::chrono::system_clock> start, end;
	    start = std::chrono::system_clock::now();

            if (*heuristica == "manhattan"){
                solution = ida_star1(n,dist_manhattan24);
            } else{
                ///solution = ida_star1(n,dist_manhattan24);
            }

	    if ( solution == true ){
	        std::cout << "Funciono\n";
	    } else{
	        std::cout << "No funciono\n";
	    }	
	    end = std::chrono::system_clock::now();
				
	    std::chrono::duration<double> elapsed_seconds = end-start;
				
	    std::cout << "Tiempo: " << elapsed_seconds.count() << "\n";

            delete n; 
            delete s;
            i = 0;
        }
    }
    return 0;
}
