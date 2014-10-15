/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  Main para el proyecto numero dos. Parte 2.
 *
 *        Version:  1.0
 *        Created:  14/10/14 21:55:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include "perceptron.h"

/** 
 * Función que imprime un mensaje de ayuda.
 */
void help(){
    std::cout << "Clasificador de puntos en una circuferencia.\n";
    std::cout << "Para correr el programa coloque:\n" ;
    std::cout << "./puntos [archivo de datos entrenamiento]\n.";
}

int main(int argc,char *argv[]){
    std::ifstream file;
    std::string line;

    if (argc < 2){
        help();
    } else {
       file.open(argv[1]); 
    }

    if (!file.is_open()){
        std::cerr << "Archivo no existe o no fue posible abrirlo.\n";
        exit(-1);
    }
    
    /** 
     * Comienzo a parsear cada una de las
     * lineas
     */
    while ( getline (file,line) ){
    } 
}
