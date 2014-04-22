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

int main(){
    std::string* f_name = new std::string();
    std::cout << "Escriba el nombre del archivo con las instancias del puzzle: ";
    std::cin >> *f_name;
    std::cout << "\n" << *f_name;
    return 0;
}
