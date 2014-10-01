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
#include <stdlib.h>

void Perceptron::entrenar(std::vector<Ejemplo> ejemplos , int iteraciones){
	
	float limite = 0.01;
	int it = 0;
	float error_total = 0;
	
	while ( error_total > limite || it < iteraciones ){
		
		
		for (int i = 0 ; i < ejemplos.size() ; ++i){
			
			float error = (ejemplos[i].valor_esperado - procesar(ejemplos[i].entrada));
			
			for (int j=0 ; j < this->pesos.size() ; ++j ){
				float delta = this->tasa_aprendizaje*error*ejemplos[i].entrada[j];
				this->pesos[j]+=delta;			
			}

			error_total+=abs(error);
		}
		it++;
	}

}
int Perceptron::procesar(std::vector<int> entrada){
	if (this->pesos.size() != entrada.size()){
		std::cout << "ERROR MOTHERFUCKER";
		return 0;
	}

	int sumatoria = 0;
	for(int i = 0 ; i < entrada.size() ; ++i){
		sumatoria+= entrada[i]*this->pesos[i];	
	}

	return (sumatoria > 0 ? 1:-1);
}