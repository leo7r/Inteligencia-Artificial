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
#include <string.h>

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

void imprimirAyuda(){
    std::cout << "15puzzle [opciones]\n";
    std::cout << "opciones: \n";
    std::cout << "-a { a* | ida* }              Algoritmo a utilizar\n";
    std::cout << "-h { manhattan | pdatabase }  Heuristica deseada\n";
    std::cout << "-f {archivo}                  Archivo con instancias a resolver\n";
}

int main(int argc, char *argv[]){
    std::string* f_name = 0;
    std::string* algoritmo = 0;
    std::string* heuristica = 0;
    int n,i;
    bool solution;

    for ( i = 0 ; i != argc ; i++){
        if (argv[i] == std::string("-a") && (i +1 < argc)){
           algoritmo = new std::string(argv[i+1]); 
        } else if (argv[i] == std::string("-h") && (i + 1 < argc)) {
           heuristica = new std::string(argv[i+1]); 
        } else if (argv[i] == std::string("-f") && (i + 1 < argc)){
           f_name = new std::string(argv[i+1]); 
        }
    }    
    
    if (algoritmo == 0 || f_name == 0 || heuristica == 0){
        imprimirAyuda();
        return 1;
    }

    std::fstream fs (f_name->data(), std::fstream::in);

    if (!fs){
        std::cout << "Fallo en abrir el archivo.";
        return 1;
    }

    char zero_index;
    int array[16];
    i = 0;

    if (*heuristica == "pdatabase"){
        std::cout << "Cargando base de datos de patrones: \n";
        //calcularPDB();	
        loadPDB();
    }
	
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

            if (*heuristica == "pdatabase"){
                if (*algoritmo == "a*"){
                    solution = a_star(n,pdbHeuristic);
                } else{
	            solution = ida_star1(n,pdbHeuristic);
                }
	    } else {
                if (*algoritmo == "a*"){
                    solution = a_star(n,dist_manhattan);
                } else {
	            solution = ida_star1(n,dist_manhattan);
                }
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
