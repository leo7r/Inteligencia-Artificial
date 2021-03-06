/*
 * =====================================================================================
 *
 *       Filename:  iris.cc
 *
 *    Description: Principal para la parte dos del proyecto.
 *
 *        Version:  1.0
 *        Created:  18/10/14 15:05:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas 
 *   Organization:  USB
 *
 * =====================================================================================
 */

#include <fstream>
#include "perceptron.h"
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <iostream>
#define ITERACIONES_MAX 100000
#define TASA_APRENDIZAJE 0.05
#define RANDOM_MAX 4
#define DIVISOR 1.0
#define ERROR_MINIMO 0.0001

/**
 * Funcion que imprime una salida de vector
 * @param salida Vector de floats que se quiere imprimir.
 */
void imprimir_salida(std::vector<float> salida){
    for (int i = 0; i < salida.size(); ++i){
        std::cout << salida[i] << " "; 
    }
}

void imprimir_clasificacion(std::vector<float> salida){
    if (salida.size() != 3) {
        imprimir_salida(salida);
        return;
    }
    if (salida[0] == 1 && salida[1] == 0 && salida[2] == 0) std::cout << "Iris-setosa";
    else if (salida[0] == 0 && salida[1] == 1 && salida[2] == 0) std::cout << "Iris-versicolor";
    else if (salida[0] == 0 && salida[1] == 0 && salida[2] == 1) std::cout << "Iris-virginica";
    else imprimir_salida(salida);
}

/** 
 * Funciones delimitadoras.
 */
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
using namespace std;
/** 
 * Funcion que imprime un mensaje de ayuda.
 */
void print_help(){
    cout << "Clasificador de Iris Setosa." << endl;   
    cout << "Para correr el programa es necesario realizar:" << endl;
    cout << string("iris [-p] <numero de pregunta (1 o 2)> [-n]") << 
             string("<numero de neuronas en la capa intermedia> [-f] <archivo entrenamiento> [-c] <archivo de comparacion>")<< endl;
}

/** 
 * Funcion main del programa.
 */
int main(int argc, char* argv[]){
    int pregunta = -1;
    int neuronas = -1;
    string nombre_arch_datos ("");
    string nombre_arch_comp ("");
    ifstream file_datos;
    ifstream file_comp;
    string line;

    if (argc == 1){
        print_help();   
        exit (-1);
    }

    // Me voy moviendo por los argumentos.
    for ( int i = 1; i < argc ; ++i){
        string arg_tmp (argv[i]);
        if ((arg_tmp.compare(string("-p")) == 0) && (i + 1 < argc)){
            pregunta = atoi(argv[i + 1]);
        }
        if ((arg_tmp.compare(string("-n")) == 0) && (i + 1 < argc)){
            neuronas = atoi(argv[i + 1]);
        }
        if ((arg_tmp.compare(string("-f")) == 0) && (i + 1 < argc)){
            nombre_arch_datos = string(argv[i + 1]);
        }
        if ((arg_tmp.compare(string("-c")) == 0) && (i + 1 < argc)){
            nombre_arch_comp = string(argv[i + 1]);
        }
    }

    if (neuronas <= 0){
        exit;
    }

    if (nombre_arch_datos.compare(string("")) != 0){
        file_datos.open(nombre_arch_datos);
        if (!file_datos.is_open()){
            cerr << "Archivo no existe o no fue posible abrirlo.\n";
            return -1;
        }
    }else {
        cerr << "Archivo no existe o no fue posible abrirlo.\n";
        return -1;
    }

    if (nombre_arch_comp.compare(string("")) != 0){
        file_comp.open(nombre_arch_comp);
        if (!file_comp.is_open()){
            cerr << "Archivo no existe o no fue posible abrirlo.\n";
            return -1;
        }
    }else {
        cerr << "Archivo no existe o no fue posible abrirlo.\n";
        return -1;
    }
     

    vector<int> tamano_capas;
    

    if (pregunta == 1){
        tamano_capas.push_back(5);
        tamano_capas.push_back(neuronas);
        tamano_capas.push_back(1);
        cout << "Clasificador Binario Iris Setosa" << endl;
        cout << "Entrenando con " << neuronas << " neuronas " << endl;

        Red_neuronal red (tamano_capas , TASA_APRENDIZAJE, RANDOM_MAX, DIVISOR );
        vector<Ejemplo_red> ejemplos;
        //Obtengo todos los ejemplos.
        while ( getline (file_datos,line) ){
            
            vector<string> tok = split( line , ',' );

            if (tok.size() != 5){
                continue;
            }

            vector<float> entradas;
            vector<float> salidas;
            entradas.push_back( 1.0 );
            entradas.push_back( atof( tok[0].c_str() ) );
            entradas.push_back( atof( tok[1].c_str() ) );
            entradas.push_back( atof( tok[2].c_str() ) );
            entradas.push_back( atof( tok[3].c_str() ) );

            if (tok[4].compare(string("Iris-setosa")) == 0){
                salidas.push_back(1);
            }else{
                salidas.push_back(0);
            }
            ejemplos.push_back(Ejemplo_red( entradas, salidas));
        }
        file_datos.close();
        red.entrenar_backpropagation(ejemplos,ITERACIONES_MAX, ERROR_MINIMO);

        int correctas = 0;
        int lineas = 0;

        //Comienzo a probar.
        while( getline(file_comp, line)){
            vector<string> tok = split( line , ',' );

            if (tok.size() != 5){
                continue;
            }

            vector<float> entradas;
            vector<float> salidas;
            float valor0 = ( atof( tok[0].c_str() ));
            float valor1 = ( atof( tok[1].c_str() ) );
            float valor2 = ( atof( tok[2].c_str() ) );
            float valor3 = ( atof( tok[3].c_str() ) );
            entradas.push_back( 1.0 );
            entradas.push_back( valor0 );
            entradas.push_back( valor1 );
            entradas.push_back( valor2 );
            entradas.push_back( valor3 );

            if (tok[4].compare(string("Iris-setosa")) == 0){
                salidas.push_back(1);
            }else{
                salidas.push_back(0);
            }
/*
            for (int i = 0; i < entradas.size(); ++i)
            {
                std::cout << entradas[i] << " | ";
            }*/

            vector<float> salida_red = red.procesar_red(entradas); //red.procesar_red_redondeo(entradas);
            
            lineas++;
            if ( (salida_red[0] > 0.5 ? 1 : 0) == salidas[0] ){
                correctas++;
            }

            
            /*cout << "Salida Red:";
            imprimir_salida(salida_red);
            cout << " Salida Archivo: ";
            imprimir_salida(salidas);
            cout << endl;*/
        }

        std::cout << "Correctas = " << correctas << " / " << lineas << std::endl;
        

    }else if (pregunta == 2){
        tamano_capas.push_back(5);
        tamano_capas.push_back(neuronas);
        tamano_capas.push_back(3);
        cout << "Clasificador de Flores" << endl;
        cout << "Entrenando con " << neuronas << " neuronas " << endl;
        // Inicializando los vectores de salida relevantes mediante arreglos. 
        float array_setosa[] = { 1, 0 , 0};
        float array_versicolor[] = {0 , 1, 0};
        float array_virginica[] = {0 , 0, 1};
        vector<float> setosa (array_setosa, array_setosa + sizeof(array_setosa) / sizeof(float) );
        vector<float> versicolor (array_versicolor, array_versicolor + sizeof(array_versicolor) / sizeof(float) );
        vector<float> virginica (array_virginica, array_virginica + sizeof(array_virginica) / sizeof(float) );
        
        Red_neuronal red (tamano_capas , TASA_APRENDIZAJE, RANDOM_MAX, DIVISOR );
        vector<Ejemplo_red> ejemplos;
        //Obtengo todos los ejemplos.
        while ( getline (file_datos,line) ){
            
            vector<string> tok = split( line , ',' );

            if (tok.size() != 5){
                continue;
            }

            vector<float> entradas;
            vector<float> salidas;
            float valor0 = ( atof( tok[0].c_str() ));
            float valor1 = ( atof( tok[1].c_str() ) );
            float valor2 = ( atof( tok[2].c_str() ) );
            float valor3 = ( atof( tok[3].c_str() ) );
            entradas.push_back( 1.0 );
            entradas.push_back( valor0 );
            entradas.push_back( valor1 );
            entradas.push_back( valor2 );
            entradas.push_back( valor3 );

            // Voy a poner una salida dependiendo del nombre de la flor.
            if (tok[4].compare(string("Iris-setosa")) == 0){
                salidas = setosa;
            }else if (tok[4].compare(string("Iris-versicolor")) == 0){
                salidas = versicolor;
            } else if (tok[4].compare(string("Iris-virginica")) == 0){
                salidas = virginica;
            }
            ejemplos.push_back(Ejemplo_red( entradas, salidas));
        }
        file_datos.close();
        red.entrenar_backpropagation(ejemplos,ITERACIONES_MAX, ERROR_MINIMO);

        int buenas = 0;
        int total = 0;

        //Comienzo a probar.
        while( getline(file_comp, line)){
            vector<string> tok = split( line , ',' );

            if (tok.size() != 5){
                continue;
            }

            vector<float> entradas;
            vector<float> salidas;
            entradas.push_back( 1.0 );
            entradas.push_back( atof( tok[0].c_str() ) );
            entradas.push_back( atof( tok[1].c_str() ) );
            entradas.push_back( atof( tok[2].c_str() ) );
            entradas.push_back( atof( tok[3].c_str() ) );

            // Voy a poner una salida dependiendo del nombre de la flor.
            if (tok[4].compare(string("Iris-setosa")) == 0){
                salidas = setosa;
            }else if (tok[4].compare(string("Iris-versicolor")) == 0){
                salidas = versicolor;
            } else if (tok[4].compare(string("Iris-virginica")) == 0){
                salidas = virginica;
            }

            vector<float> salida_red = red.procesar_red_redondeo(entradas);

            total++;
            if ( salida_red[0] == salidas[0] && salida_red[1] == salidas[1] && salidas[2] == salida_red[2] ){
                buenas++;
            }

            /*cout << "Salida Red:";
            imprimir_clasificacion(salida_red);
            cout << " Salida Archivo: ";
            imprimir_salida(salidas);
            cout << " ";
            imprimir_clasificacion(salidas);
            cout << endl;*/
        }
    
        std::cout << "buenas: " << buenas << " | " << total << std::endl;

    }
}
