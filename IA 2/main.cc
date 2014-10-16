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
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>

/** 
 * Función que imprime un mensaje de ayuda.
 */
void help(){
    std::cout << "Clasificador de puntos en una circuferencia.\n";
    std::cout << "Para correr el programa coloque:\n" ;
    std::cout << "./puntos [archivo de datos entrenamiento]\n.";
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
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
        return -1;
    }
    
    /** 
     * Comienzo a parsear cada una de las
     * lineas para formar los ejemplos
     */

    std::vector<int> tamano_capas;
    tamano_capas.push_back(2);
    tamano_capas.push_back(3);
    tamano_capas.push_back(1);

    Red_neuronal red( tamano_capas , 0.01 );
    std::vector<Ejemplo_red> ejemplos;

    while ( getline (file,line) ){

        std::vector<std::string> tok = split( line , ' ' );

        std::vector<float> entradas;
        entradas.push_back( atof( tok[0].c_str() ) );
        entradas.push_back( atof( tok[1].c_str() ) );

        std::vector<float> salidas;
        salidas.push_back( atof( tok[2].c_str() ) );

        ejemplos.push_back( Ejemplo_red( entradas , salidas ) );

        //std::cout << x1 << " | " << x2 << " | " << t << std::endl;
    }

    //red.probar_red();
    red.entrenar_backpropagation( ejemplos , 1000 );

    return 0;
}
