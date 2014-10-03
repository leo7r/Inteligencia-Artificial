/*
 * =====================================================================================
 *
 *       Filename:  perceptron.cc
 *
 *    Description:  Implementacion del perceptron.
 *
 *        Version:  1.0
 *        Created:  1/10/2014
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include "perceptron.h"
#include <iostream>
#include <stdlib.h>

/** 
 * Funcion de entrenamiento de perceptron.
 * @param ejemplos Los ejemplos de entrenamiento (La experiencia).
 * @param iteraciones Numero de iteraciones maximas a considerar.
 */
void Perceptron::entrenar(std::vector<Ejemplo> ejemplos , int iteraciones){
	
    float limite = 0.01;
    int it = 0;
    float error_total = 0.1;
	
    while ( error_total > limite && it < iteraciones ){
		
        error_total = 0;
		
	for (int i = 0 ; i < ejemplos.size() ; ++i){
			
	    float error = (ejemplos[i].valor_esperado - procesar(ejemplos[i].entrada));
			
	    for (int j=0 ; j < this->pesos.size() ; ++j ){
	        float delta = tasa_aprendizaje*error*ejemplos[i].entrada[j];
		this->pesos[j]+=delta;
		std::cout << "Peso " << j << " = " << pesos[j] << "E: " << error << " | ";
	    }
	    std::cout << std::endl;

	    error_total+=abs(error);
	}
	it++;

	std::cout << "Error total: " << error_total << " | Iters: " << it << std::endl;
    }

}
/**
 * Funcion que procesa una entrada y retorna el valor dado. 
 * @param entrada La entrada a procesar
 * @return int Retorna 1 si la sumatoria de la entrada por los pesos es mayor que 0 o -1 en caso contrario
 */
int Perceptron::procesar(std::vector<int> entrada){
    if (this->pesos.size() != entrada.size()){
        std::cerr << "Tamaños no coinciden.";
	return 0;
    }

    float sumatoria = 0.0;
        for(int i = 0 ; i < entrada.size() ; ++i){
	    sumatoria+= entrada[i]*this->pesos[i];	
    }

    return sumatoria > 0 ? 1:-1;
}


/** 
 * Este seria el delta
 */
void Perceptron::gradient_descent(std::vector<Ejemplo> ejemplos, int iteraciones){
	
    float limite = 0.01;
    int it = 0;
    float error_total = 0.1;
	
    while ( error_total > limite && it < iteraciones ){
		
        error_total = 0;
		
	for (int i = 0 ; i < ejemplos.size() ; ++i){
			
	    float error = (ejemplos[i].valor_esperado - procesar(ejemplos[i].entrada));
			
	    for (int j=0 ; j < this->pesos.size() ; ++j ){
	        peso[j] = peso[j] + tasa_aprendizaje*error*ejemplos[i].entrada[j];
		std::cout << "Peso " << j << " = " << pesos[j] << "E: " << error << " | ";
	    }
	    std::cout << std::endl;

	    error_total+=abs(error);
	}
	it++;

	std::cout << "Error total: " << error_total << " | Iters: " << it << std::endl;
    }


}
