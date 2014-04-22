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

int_fast64_t toInt64(int* array){
    
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
    while(!fs.eof()) {
        fs >> n;

    }
    return 0;

}
