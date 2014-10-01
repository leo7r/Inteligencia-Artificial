/*
 * =====================================================================================
 *
 *       Filename:  perceptron.h
 *
 *    Description:  Header del perceptron.
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

#include <stdint.h>
#include <iostream>
#include <vector>

class Ejemplo {
	public:
		std::vector<int> entrada;
		int valor_esperado;
		Ejemplo(std::vector<int> entrada, int valor_esperado):entrada(entrada),valor_esperado(valor_esperado){} //ojo recordar verificar consistencia en tamaños de vectores de entradas y pesos
		~Ejemplo(){}


};

class Perceptron {
    public:
    	std::vector<float> pesos;	// incluye w0
    	float tasa_aprendizaje;
    	//std::function<int(std::vector<int>,std::vector<float>)> funcion;

    	//Perceptron( std::vector<int> entradas , std::vector<float> pesos , std::function<int(std::vector<int>,std::vector<float>)> funcion );
    	Perceptron(std::vector<float> pesos):pesos(pesos){}
		~Perceptron(){}
		void entrenar(std::vector<Ejemplo> ejemplos , int iteraciones);
		int procesar(std::vector<int> entrada);
};
