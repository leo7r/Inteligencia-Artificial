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
#include <math.h>
#include <stdlib.h>
#define TASA_APRENDIZAJE 0.01
#define ITERACIONES_MAX 100

/** 
 * Compara dos vectores.
 * @return bool
 */
bool comparar(std::vector<float> vector1 , std::vector<float> vector2){
    if (vector1.size() != vector2.size()) return false;
    for ( int i = 0; i < vector1.size(); ++i){
        if (vector1[i] != (vector2[i] > 0.5 ? 1 : 0) ) return false;
    }
    return true;
}

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
        tamano_capas.push_back(3);
        tamano_capas.push_back(i);
        tamano_capas.push_back(1);

        Red_neuronal red( tamano_capas , TASA_APRENDIZAJE ,5.0, 4.0);
        //red.probar_red();
        //std::cin.get();
        std::vector<Ejemplo_red> ejemplos;

        /* pesos ficticios
        std::vector<float> p1;
        std::vector<float> p2;
        std::vector<float> p3;
        p1.push_back(0.1);
        p1.push_back(0.8);
        p2.push_back(0.4);
        p2.push_back(0.6);
        p3.push_back(0.3);
        p3.push_back(0.9);

        red.capas[1].neuronas[0].pesos = p1;
        red.capas[1].neuronas[1].pesos = p2;
        red.capas[2].neuronas[0].pesos = p3;
        */

        std::cout << "Entrenando con " << i << " neuronas escondidas" <<  std::endl;
        while ( getline (file,line) ){

            std::vector<std::string> tok = split( line , ' ' );

            std::vector<float> entradas;
            //entradas.push_back( 1.0 );
            float valor1 = atof( tok[0].c_str() ) / 20.0;
            float valor2 = atof( tok[1].c_str() ) / 20.0;
            valor1 = (valor1 < 0 ? 0 : valor1);
            valor2 = (valor2 < 0 ? 0 : valor2);
            entradas.push_back(1.0);
            entradas.push_back( valor1 );
            entradas.push_back( valor2 );

            float valor3 = atof(tok[2].c_str()) ;
            std::vector<float> salidas;
            float salida = valor3;//(valor3 < 0 ? 0 : valor3);
            salidas.push_back( salida  );

            ejemplos.push_back( Ejemplo_red( entradas , salidas ) );

            //std::cout << x1 << " | " << x2 << " | " << t << std::endl;
        }

        //red.probar_red();
        red.entrenar_backpropagation( ejemplos , ITERACIONES_MAX );
        file.close();

        /*std::ofstream myfile;
        myfile.open ("circulo.txt", std::ios::out | std::ios::app );
        for ( int i = 0 ; i < 100 ; ++i ){
            for ( int j = 0 ; j < 100 ; ++j ){
                float x = i/100.0;
                float y = j/100.0;

                std::vector<float> entradas;
                entradas.push_back(1.0);
                entradas.push_back(x);
                entradas.push_back(y);

                std::vector<float> salida_red = red.procesar_red(entradas);   
                myfile << (salida_red[0] > 0.5 ? 1:0) << "\n";
            }
        }

        myfile.close();
*/
        //return -1;

        if (argc > 2){
            file_procesamiento.open(argv[2]);

            if (file_procesamiento.is_open()){

                float error_total = 0;
                int numero_total = 0;
                int correctas = 0;

                std::ofstream myfile;
                myfile.open ("prueba_estupida_de_bern.txt", std::ios::out | std::ios::app );

                while ( getline (file_procesamiento,line) ){
                    numero_total++;
                    std::vector<std::string> tok = split( line , ' ' );
                    std::vector<float> entradas;
                    float valor1 = atof( tok[0].c_str() ) / 20.0;
                    float valor2 = atof( tok[1].c_str() ) / 20.0;
                    entradas.push_back(1.0);
                    valor1 = (valor1 < 0 ? 0 : valor1);
                    valor2 = (valor2 < 0 ? 0 : valor2);
                    entradas.push_back( valor1 );
                    entradas.push_back( valor2 );

                    std::vector<float> salidas;
                    float salida = atof( tok[2].c_str() );

                    salida = (salida < 0 ? 0 : salida);
                    salidas.push_back(  salida  );

                    //ejemplos.push_back( Ejemplo_red( entradas , salidas ) );
                    
                    std::vector<float> salida_red = red.procesar_red(entradas);
                    std::cout << "Salida Red: ";
                    imprimir_salida(salida_red);

                    std::cout << " Salida Archivo: ";
                    imprimir_salida(salidas);
                    std::cout << std::endl;

                    if (comparar(salidas,salida_red)){
                        correctas++;
                    }
                    else{
                        myfile << valor1*20.0 << " " << valor2*20.0 << " " << "1" << "\n";
                    }
                    
                }
                std::cout << "Resultado: " << correctas << "/" << numero_total << std::endl; 
                //std::cin.get();
                file_procesamiento.close();
                myfile.close();
            }
        }

   //}
    return 0;
}
