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
#include <string>

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
    if (this->pesos.size() != entrada.size() ){
        std::cerr << "Tamaños no coinciden. " << pesos.size() << " : " << entrada.size();
	return 0;
    }

    float sumatoria = 0;
    for(int i = 0 ; i < entrada.size() ; ++i){
	    sumatoria+= entrada[i]*this->pesos[i];	
    }
    this->output=1 / ( 1 + ( exp(-sumatoria) ));
    return this->output;// sinoidal
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

    std::vector<Perceptron> neuronas;

    for (int i = 0; i < e_capa[0]; ++i){
        std::vector<float> pesos;
        neuronas.push_back( Perceptron( pesos , tasa_aprendizaje ) );
    }

    capas.push_back( Capa_red( neuronas ) );

    // Siguientes capas

    for (int i = 1; i < e_capa.size() ; ++i){
        
        neuronas.clear();
        for (int j = 0; j < e_capa[i]; ++j){
            std::vector<float> pesos;

            for (int p = 0; p < e_capa[i-1]+1 ; ++p){
                float valor = (rand() % 5 + 1) / 10.0;
                valor = ( (rand() % 10 + 1) > 5 ? -valor : valor); //Valor entre 0.5 y -0.5
                pesos.push_back( valor );
            }

            neuronas.push_back( Perceptron( pesos , tasa_aprendizaje ) );
        }

        capas.push_back( Capa_red( neuronas) );
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
	for (int i = 1 ; i < capas.size() ; ++i ){

        siguiente_entrada.insert(siguiente_entrada.begin(),1.0); // Esto es el x0 que es 1 siempre
		siguiente_entrada = capas[i].procesar_capa(siguiente_entrada);
	}

	return siguiente_entrada;
}




void printvector(std::vector<float> in){
    std::string out = "";
    for (int i = 0; i < in.size(); ++i)
    {
        std::cout <<"-"<<in[i]<<"-";
    }
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
    float error_inicial;
    float error_final;

    do{
        // Itero para cada ejemplo de entrenamiento.                        
        error_total = 0;
        for (int ejemplo = 0; ejemplo < ejemplos.size() ; ++ejemplo){
            float error; 
            float valor_esperado = ejemplos[ejemplo].valor_esperado[0]; // Nuestro valor esperado solo tiene uno.

            // Seteando las neuronas iniciales
            for ( int i = 0 ; i < ejemplos[ejemplo].entrada.size() ; ++i ){
                capas[0].neuronas[i].output = ejemplos[ejemplo].entrada[i];
            }

            std::vector<float> res = procesar_red( ejemplos[ejemplo].entrada );

            /*
            probar_red();
            std::cin.get();*/


            // Propagar el error hacia atras a travez de la red.
            
            // Calcular el error de las neuronas "output".

            int final_ = capas.size() - 1;
            for (int neurona = 0 ; neurona < capas[final_].neuronas.size(); ++neurona){ //Aqui es capa.size() - 1 porque son las finales siempre
                error = capas[final_].neuronas[neurona].output * ( 1 - capas[final_].neuronas[neurona].output ) * ( valor_esperado - capas[final_].neuronas[neurona].output );
                capas[final_].neuronas[neurona].error = error;
            }

            // Calculo el error de todas las neuronas escondidas (hidden units)
            // Me voy moviendo de alante para atras.
            // Recordar que la capa input no es modificada. No es usada en nuestra implementacion.
           for ( int capa = capas.size() - 2 ; capa > 0  ; --capa){
               for ( int neurona = 0; neurona < capas[capa].neuronas.size(); ++neurona){

                    // Calculando la sumatoria
                    float sumatoria = 0.0;
                    for ( int i = 0 ; i < capas[final_].neuronas.size() ; i++ ){
                        sumatoria+= capas[final_].neuronas[i].pesos[neurona+1]*capas[final_].neuronas[i].error;
                    }

                    error = capas[capa].neuronas[neurona].output * ( 1 - capas[capa].neuronas[neurona].output ) * sumatoria;
                    capas[capa].neuronas[neurona].error = error;
               }
           }

           // Actualizando pesos de cada capa
           for (int capa = 1; capa < capas.size() ; ++capa){
                
                // Se actualizan los pesos de cada neurona
                for (int neurona = 0; neurona < capas[capa].neuronas.size() ; ++neurona){

                    // Actualizo cada peso
                    for( int p = 0 ; p < capas[capa].neuronas[neurona].pesos.size() ; p++ ){

                        float delta;

                        if ( p == 0 ){
                            delta = capas[capa].neuronas[neurona].tasa_aprendizaje * capas[capa].neuronas[neurona].error; // SIempre x0 es 1
                        }
                        else{
                            delta = capas[capa].neuronas[neurona].tasa_aprendizaje * capas[capa].neuronas[neurona].error * capas[capa-1].neuronas[p-1].output;
                        }

                        capas[capa].neuronas[neurona].pesos[p]+=delta;
                    }


                }

           }

           //error_total = 0;
           for(  int ultimas = 0 ; ultimas < capas[final_].neuronas.size() ; ultimas++ ){
                int step_o = capas[final_].neuronas[ultimas].output > 0.5 ? 1:-1;

                if ( step_o != ejemplos[ejemplo].valor_esperado[ultimas] ){
                    error_total++;
                }

                //int err = (ejemplos[ejemplo].valor_esperado[ultimas] - step_o)/2;
                //error_total+= pow(err,2);
                //std::cout << ejemplos[ejemplo].valor_esperado[ultimas] << "|" << capas[final_].neuronas[ultimas].output << std::endl;
           }

           /*for (int capa = 1; capa < capas.size(); ++capa){
               for (int neurona = 0 ; neurona < capas[capa].neuronas.size(); ++neurona){
                   error_total += (valor_esperado - capas[capa].neuronas[neurona].output)* (valor_esperado - capas[capa].neuronas[neurona].output);
               }
           }

           error_total = error_total/2;
           if (i == 0){
               error_inicial = error_total;
           }*/
            
        }
        i++;
        std::cout << "error : " << error_total << std::endl;
        float porcentaje = ( (float) i / (float) iteraciones) * 100.0 ;
        //std::cout << "porcentaje: " << porcentaje << std::endl;

        //std::cin.get();

    } while (i < iteraciones && error_total >= 0.1 );
    //std::cout << "Error Inicial: " << error_inicial << std::endl;
    std::cout << "Error Total: " << error_total << std::endl;
    std::cout << "Iteraciones dadas: " << i << std::endl;
    std::cin.get();
}	

void Red_neuronal::probar_red( ){

	std::cout << "Red de " << capas.size() << " capas\n";

	for ( int i = 0 ; i < capas.size() ; ++i ){
		std::cout << "Capa #" << i << " tiene " << capas[i].neuronas.size() << " neuronas\n";

		for ( int j = 0 ; j < capas[i].neuronas.size() ; j++ ){
			for ( int k = 0 ; k < capas[i].neuronas[j].pesos.size() ; k++ ){
				std::cout << " y esa neurona # "<< j << " tiene peso = " << capas[i].neuronas[j].pesos[k];
			}
            std::cout << " y su output es: " << capas[i].neuronas[j].output << std::endl;
		}

	}

}


