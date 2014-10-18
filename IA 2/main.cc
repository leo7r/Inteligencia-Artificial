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
#include <math.h>

/**
 * Funcion que imprime una salida de vector
 */
void imprimir_salida(std::vector<float> salida){
    for (int i = 0; i < salida.size(); ++i){
        std::cout << salida[i] << " "; 
    }
}



/** 
 * Función que imprime un mensaje de ayuda.
 */
void help(){
    std::cout << "Clasificador de puntos en una circuferencia.\n";
    std::cout << "Para correr el programa coloque:\n" ;
    std::cout << "./puntos [archivo de datos entrenamiento] [archivo datos de procesamiento] [neuronas capa 2] \n.";
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
    std::ifstream file_procesamiento;
    std::string line;
    
    /** 
     * Comienzo a parsear cada una de las
     * lineas para formar los ejemplos
     */
    //for ( int i = 2; i <= 10 ; i++){
    int i;
    if (argc > 3){
        i = atoi(argv[3]);
    }

        if (argc < 2){
            help();
            return -1;
        } else {
            file.open(argv[1]); 
        }

        if (!file.is_open()){
            std::cerr << "Archivo no existe o no fue posible abrirlo.\n";
            return -1;
        }

        std::vector<int> tamano_capas;
        tamano_capas.push_back(2);
        tamano_capas.push_back(i);
        tamano_capas.push_back(1);

        Red_neuronal red( tamano_capas , 0.05 );
        std::vector<Ejemplo_red> ejemplos;

        std::cout << "Entrenando con " << i << " neuronas escondidas" <<  std::endl;
        while ( getline (file,line) ){

            std::vector<std::string> tok = split( line , ' ' );

            std::vector<float> entradas;
            //entradas.push_back( 1.0 );
            entradas.push_back( atof( tok[0].c_str() ) );
            entradas.push_back( atof( tok[1].c_str() ) );

            std::vector<float> salidas;
            float salida = atof( tok[2].c_str() );

            salidas.push_back( salida == -1 ? 0:salida );

            ejemplos.push_back( Ejemplo_red( entradas , salidas ) );

            //std::cout << x1 << " | " << x2 << " | " << t << std::endl;
        }

        //red.probar_red();
        red.entrenar_backpropagation( ejemplos , 500 );

        file.close();

        if (argc > 2){
            file_procesamiento.open(argv[2]);

            if (file_procesamiento.is_open()){

                float error_total = 0;
                
                while ( getline (file_procesamiento,line) ){
                    std::vector<std::string> tok = split( line , ' ' );
                    std::vector<float> entradas;
                    entradas.push_back( atof( tok[0].c_str() ) );
                    entradas.push_back( atof( tok[1].c_str() ) );

                    std::vector<float> salidas;
                    float salida = atof( tok[2].c_str() );
                    salidas.push_back(  salida == -1 ? 0:salida  );

                    //ejemplos.push_back( Ejemplo_red( entradas , salidas ) );
                    
                    std::vector<float> salida_red = red.procesar_red(entradas);

                    for( int ultimas = 0 ; ultimas < salida_red.size() ; ultimas++ ){
                        int step_o = salida_red[ultimas] > 0.0 ? 1:0;

                        if ( step_o != salidas[ultimas] ){
                            error_total++;
                        }
                   }

                    /*std::cout << "Salida Red: ";
                    imprimir_salida(salida_red);

                    std::cout << " Salida Archivo: ";
                    imprimir_salida(salidas);
                    std::cout << std::endl;*/
                }

                std::cout << "El error del test es: " << error_total;

                std::cin.get();
                file_procesamiento.close();
            }
        }

   //}
    return 0;
}
