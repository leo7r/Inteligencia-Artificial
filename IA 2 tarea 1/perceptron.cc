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
#include <math.h>

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
		//std::cout << "Peso " << j << " = " << pesos[j] << "E: " << error << " | ";
	    }

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
 * Funcion que procesa una entrada y retorna el valor dado. 
 * @param entrada La entrada a procesar
 * @return int Retorna sumatoria 
 */
float Perceptron::procesar_adaline(std::vector<int> entrada){
    if (this->pesos.size() != entrada.size()){
        std::cerr << "Tamaños no coinciden.";
	return 0;
    }

    float sumatoria = 0.0;
        for(int i = 0 ; i < entrada.size() ; ++i){
	    sumatoria+= entrada[i]*this->pesos[i];	
    }

    return sumatoria;// > 0 ? 1:-1;
}

/**
 * Funcion que procesa una entrada y retorna el valor dado. 
 * @param entrada La entrada a procesar
 * @return float Retorna sumatoria
 */
float Perceptron::procesar_neurona(std::vector<float> entrada){
    if (this->pesos.size() != entrada.size()){
        std::cerr << "Tamaños no coinciden.";
	return 0;
    }

    float sumatoria = 0;
    for(int i = 0 ; i < entrada.size() ; ++i){
	    sumatoria+= entrada[i]*this->pesos[i];	
    }

    return 1 / ( 1 + ( exp(-sumatoria) ));// sinoidal
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
        std::vector<float> deltas;
        
        for ( int ne = 0 ; ne < pesos.size() ; ne++ ){
        	deltas.push_back(0.0);
        }
		
		for (int i = 0 ; i < ejemplos.size() ; ++i){
			
			float o = procesar_adaline(ejemplos[i].entrada);
			float error = ejemplos[i].valor_esperado-o;

			 for (int j=0 ; j < this->pesos.size() ; ++j ){
			 	deltas[j]+= (tasa_aprendizaje/(it+1))*error*ejemplos[i].entrada[j];
		    	//deltas[j]+= tasa_aprendizaje*error*ejemplos[i].entrada[j];
		    }

		    error_total+=abs(error);
		}

	    for ( int j=0 ; j < this->pesos.size() ; ++j ){
	    	pesos[j]+=deltas[j];
	    	//std::cout << "Error: " << error << "| Peso: " << pesos[j] << std::endl;
	    }

		it++;

		std::cout << "Error total: " << error_total << " | Iters: " << it << std::endl;
    }
}

/**
 * Funcion que procesa una entrada para capa de neuronas y retorna los valores procesados por cada una. 
 * @param entrada La entrada a procesar
 * @return resultado de procesar sobre cada una de las neuronas de la capa.
 */
std::vector<float> Capa_red::procesar_capa(std::vector<float> entrada){
	std::vector<float> salidas;
	for (int i = 0 ; i < neuronas.size() ; ++i ){
		salidas.push_back(neuronas[i].procesar_neurona(entrada));
	}
	return salidas;
}

/**
 * Funcion que procesa una entrada para la red neuronal y retorna los valores procesados. 
 * @param capa_entrada La entrada a procesar
 * @return resultado de procesar sobre toda la red neuronal .
 */
std::vector<float> Red_neuronal::procesar_red(std::vector<float> capa_entrada){

	std::vector<float> siguiente_entrada = capa_entrada;
	for (int i = 0 ; i < capas.size() ; ++i ){
		siguiente_entrada = capas[i].procesar_capa(siguiente_entrada);
	}

	return siguiente_entrada;
}

void Red_neuronal::entrenar_backpropagation(std::vector<Ejemplo_red> ejemplos , int iteraciones){
	int curr_iter = 0;
	//repeat
	while(curr_iter < iteraciones ){
		
		std::vector<float> a_j;


		//for each e in examples do
		for(int e = 0 ; e < ejemplos.size() ; ++e ){
			//for each node j in the input layer do a_j <-- x_j[e]
			a_j = ejemplos[e].entrada;
			std::vector<float> in;
			//for L = 2 to M do
			for (int i = 0 ; i < capas.size() ; ++i ){

				//in_i <-- sumatoria (W[j][i]*a[j])
				in.clear();
				float sum = 0;
				for (int k = 0 ; k < capas[i].neuronas.size() ; ++k ){
					for (int p = 0; p < capas[i].neuronas[k].pesos.size(); ++p){
						sum+= capas[i].neuronas[k].pesos[p] * a_j[p];
					}
					in.push_back(sum);
				}

				//a[i] <-- g(in_i)
				a_j.clear();
				for (int j = 0; j < in.size() ; ++j){
					float sino = 1 / ( 1 + ( exp(-in[j]) ));// sinoidal
					a_j.push_back(sino);
				}

			}

			// for each node i in the output layer do
			std::vector<float> delta;
			for (int i = 0; i < capas.back().neuronas.size(); ++i){

				float sino = 1 / ( 1 + ( exp(-in[i]) ));// sinoidal
				float sino_p = sino * (1 - sino);
				float resultado = sino_p * (ejemplos[e].valor_esperado[i] - a_j[i]);
				delta.push_back(resultado);
			}

			// for L= M - 1 to 1 do
			for (int i = capas.size()-1 ; i >= 0 ; --i){
				//for each node j in layer L do
				std::vector<float> delta_aux;
				for (int j = 0; j < capas[i].neuronas.size(); ++j){
					//ALERTA!!!###################
					for (int m = 0; m < in.size(); ++m){
						float sino = 1 / ( 1 + ( exp(-in[j]) ));// sinoidal
						float sino_p = sino * (1 - sino);
						float sumatoria = 0;
						// delta[j] <-- g'(in[j]) * sumatoria(W[j][i]*delta[i])
						for (int k = 0; k < capas[i].neuronas[j].pesos.size(); ++k){
							sumatoria+= capas[i].neuronas[j].pesos[k] * delta[k];
						}
						delta_aux.push_back(sumatoria * sino_p);
					}
					delta = delta_aux;
					//ALERTA!!!###################

					//for each node i in layer L + 1 do
					for (int p = 0; p < capas[i+1].neuronas.size(); ++p){
						//W[p][i] <-- W[p][i] + alfa * a_j * delta[i]
						for (int k = 0; k < capas[i+1].neuronas[p].pesos.size(); ++k){
							capas[i+1].neuronas[p].pesos[k]+= capas[i+1].neuronas[p].tasa_aprendizaje * a_j[j] * delta[p] ;
						}
					}

				}

				delta = delta_aux;

				
			}
		}

	}
}	