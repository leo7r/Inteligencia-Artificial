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

	    error_total+= (error >= 0 ? error : -error);
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

		    error_total+= (error >= 0 ? error : -error);
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
 * Constructor "automatico" de nuestra red neuronal
 * @param numero_entrada Numero de entradas que va a tener la neurona. Esto es el numero de pesos que voy a inicializar.
 * @param e_capa Indica una especificacion de las capa. Con este vector de capas nos indica el numero de capas y cuantos perceptrones posee.
 * @param tasa_aprendizaje Es la tasa del aprendizaje 
 */
Red_neuronal::Red_neuronal(std::vector<int> e_capa, float tasa_aprendizaje){

    int numero_neurona;
    
    for (int i = 0; i < e_capa.size(); ++i){

    	//std::cout << "Pasando por capa " << i << std::endl;

        numero_neurona = e_capa[i];
        std::vector<Perceptron> neuronas;
        // En este for inicializo las neuronas
        for (int j = 0; j < numero_neurona; ++j){
         	//std::cout << "Pasando por neurona " << j << std::endl;
            
            std::vector<float> pesos;
            pesos.push_back(1.0); //wo siempre es 1

            if ( i != 0 ){
            	// demas capas
            	for (int k = 0 ; k < e_capa[i-1]; ++k){
	                // Genero un numero entre 1 y 10 y lo divido entre 1000 para que sea pequeño
	                pesos.push_back(( (rand() % 10) + 1) / (float) 77.0 );
	                //pesos.push_back( 0.1 );
	            }
            }

            
            Perceptron* neurona_tmp = new Perceptron(pesos,tasa_aprendizaje);
            neuronas.push_back(*neurona_tmp); 
        }
        Capa_red* capa_tmp = new Capa_red(neuronas);
        capas.push_back(*capa_tmp);
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
    float error_total = 101;

    //repeat
    while(curr_iter < iteraciones && error_total >= 100 ){
		
        std::vector<float> a_j;
        error_total = 0;
        //std::cout << "Iteracion " << curr_iter << std::endl;

        //for each e in examples do
        for(int e = 0 ; e < ejemplos.size() ; ++e ){

        	//std::cout << "Ejemplo " << e << std::endl;

	        //for each node j in the input layer do a_j <-- x_j[e]
			a_j = ejemplos[e].entrada;
			std::vector<float> in;
			//for L = 2 to M do
			for (int i = 1 ; i < capas.size() ; ++i ){

			    //in_i <-- sumatoria (W[j][i]*a[j])
			    in.clear();
			    float sum = 0;
			    for (int k = 0 ; k < capas[i].neuronas.size() ; ++k ){
			        for (int p = 0; p < capas[i].neuronas[k].pesos.size(); ++p){
			        float peso1 = capas[i].neuronas[k].pesos[p];
				    sum+= peso1 * a_j[p];
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

			    //int valor_real = a_j[i] > 0.5 ? 1 : -1;

			    float error = ejemplos[e].valor_esperado[i] - a_j[i];
			    float resultado = sino_p * ( error );

			    //std::cout << "O = " << valor_real << " | Esperado = " << ejemplos[e].valor_esperado[i] << std::endl;

			    error_total += (error >= 0 ? error : -error);

			    delta.push_back(resultado);
			}

			// for L= M - 1 to 1 do
			for (int i = capas.size()-2 ; i >= 0 ; --i){

			    //for each node j in layer L do
			    std::vector<float> delta_aux;
			    for (int j = 0; j < capas[i].neuronas.size(); ++j){
			        //ALERTA!!!###################
					float sino = 1 / ( 1 + ( exp(-in[i]) ));// sinoidal
			    	float sino_p = sino * (1 - sino);
			    	
					//ALERTA!!!###################

			        //for each node i in layer L + 1 do
			        for (int p = 0; p < capas[i+1].neuronas.size(); ++p){
				
			            //W[p][i] <-- W[p][i] + alfa * a_j * delta[i]
					    for (int k = 1; k < capas[i+1].neuronas[p].pesos.size(); ++k){
					    	//std::cout << "Peso antiguo " << k << " en neurona " << p << "de la capa " << i+1 << " es: " << capas[i+1].neuronas[p].pesos[k] << std::endl;
					        capas[i+1].neuronas[p].pesos[k]+= capas[i+1].neuronas[p].tasa_aprendizaje * a_j[j] * delta[p] ;
					    	//std::cout << "Peso " << k << " en neurona " << p << "de la capa " << i+1 << " es: " << capas[i+1].neuronas[p].pesos[k] << std::endl;
					    }

			        }

			        //std::cin.get();

			    }

			    delta = delta_aux;
					
			}
        }

        std::cout << "Error total: " << error_total << std::endl;
        curr_iter++;
    }
}	

void Red_neuronal::probar_red( ){

	std::cout << "Red de " << capas.size() << " capas\n";

	for ( int i = 0 ; i < capas.size() ; ++i ){
		std::cout << "Capa #" << i << " tiene " << capas[i].neuronas.size() << " neuronas\n";

		for ( int j = 0 ; j < capas[i].neuronas.size() ; j++ ){
			for ( int k = 0 ; k < capas[i].neuronas[j].pesos.size() ; k++ ){
				std::cout << "Y esa neurona tiene peso = " << capas[i].neuronas[j].pesos[k] << std::endl;
			}
		}

	}

}