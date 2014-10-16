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
/** 
 * Algoritmo de entrenamiento de backpropagation.
 *
 * Este esta basado principalmente en el algoritmo del Mitchell de Machine Learning.
 * Pagina 98 (110 en el pdf). 
 * Faltan pruebas.
 *
 * @param ejemplos Un vector que contiene los ejemplos para el entrenamiento con el valor esperado.
 * @param iteraciones Numero de iteraciones maximo.
 */
void Red_neuronal::entrenar_backpropagation(std::vector<Ejemplo_red> ejemplos , int iteraciones){
    int i = 0;
    float error_total;

    do{
        // Itero para cada ejemplo de entrenamiento.                        
        error_total = 0;
        for (int ejemplo = 0; ejemplo < ejemplos.size() ; ++ejemplo){
        

            std::vector<float> entradas = ejemplos[ejemplo].entrada;
            float valor_esperado = ejemplos[ejemplo].valor_esperado[0]; // El valor esperado puede ser solo uno. Cambiar esto.

            // Propagar el input hacia delante.
            // Empiezo por la capa numero 1 pues la capa 0 es solo 
            // representativa.
            for (int capa = 1; capa < capas.size(); ++capa){
                for (int neurona = 0; neurona < capas[capa].neuronas.size(); ++neurona){
                    for (int p = 0; p < capas[capa].neuronas[neurona].pesos.size(); ++p){

                        Perceptron neurona_tmp = capas[capa].neuronas[neurona];
                        float peso = capas[capa].neuronas[neurona].pesos[p];

                        neurona_tmp.output = peso * entradas[p]; // Guardo en cada neurona el valor de su output
                    }
                }
            }

            // Propagar el error hacia atras a travez de la red.
            
            // Calcular el error de las neuronas "output".
            int final_ = capas.size() - 1;
            for (int neurona = 0 ; neurona < capas[final_].neuronas.size(); ++neurona){ //Aqui es capa.size() - 1 porque son las finales siempre
                Perceptron neurona_tmp = capas[final_].neuronas[neurona];
                neurona_tmp.error = neurona_tmp.output * ( 1 - neurona_tmp.output) * (valor_esperado - neurona_tmp.output);
                error_total += neurona_tmp.error;
            }

            // Calculo el error de todas las neuronas escondidas (hidden units)
            // Me voy moviendo de alante para atras.
            // Recordar que la capa input no es modificada. No es usada en nuestra implementacion.
           for ( int capa = capas.size() - 2 ; capa >= 1  ; --capa){
               for ( int neurona = 0; neurona < capas[capa].neuronas.size(); ++neurona){
                    Perceptron neurona_tmp = capas[capa].neuronas[neurona];
                    float sumatoria = capas[capa + 1].sum_peso_output(neurona_tmp.pesos);         
                    neurona_tmp.error = neurona_tmp.output * (1 - neurona_tmp.output) * sumatoria;
                    error_total += neurona_tmp.error;
               }
           }

           // Actualizo el peso de las neuronas.
           std::vector<float> nuevo_peso;
           nuevo_peso.push_back(1.0); // w0 siempre es 1.

            for (int capa = 1; capa < capas.size(); ++capa){
                for (int neurona = 0; neurona < capas[capa].neuronas.size(); ++neurona){
                    for (int p = 1; p < capas[capa].neuronas[neurona].pesos.size(); ++p){ // El peso 0 no es necesario actualizarlo. Siempre es 1.

                        Perceptron neurona_tmp = capas[capa].neuronas[neurona];
                        float peso_viejo = capas[capa].neuronas[neurona].pesos[p];
                        float delta = neurona_tmp.tasa_aprendizaje * neurona_tmp.error * entradas[p];
                        nuevo_peso.push_back(peso_viejo + delta);
                    }
                }
            }
            
        }
        i++;
    } while (i < iteraciones && error_total >= 100 );
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
