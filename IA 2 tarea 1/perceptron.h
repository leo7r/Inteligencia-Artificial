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

/** 
 * Clase que representa un ejemplo para poder entrenar al Perceptron
 */
class Ejemplo {
    public:
        std::vector<int> entrada; /* Entrada del ejemplo */
	int valor_esperado; /* Valor esperado */

        /**
         * Constructor de ejemplo.
         * Recordar verificar la consistencia del tamaño de los pesos.
         */
	Ejemplo(std::vector<int> entrada, int valor_esperado):entrada(entrada),valor_esperado(valor_esperado){} 

	~Ejemplo(){}

};

/**
 * Clase del Perceptron
 */
class Perceptron {
    public:
    	std::vector<float> pesos;   /* Este peso incluye w0 */
    	float tasa_aprendizaje;

        Perceptron(std::vector<float> pesos):pesos(pesos),tasa_aprendizaje(0.1){}

        ~Perceptron(){}

        void entrenar(std::vector<Ejemplo> ejemplos , int iteraciones);
        void gradient_descent(std::vector<Ejemplo> ejemplos, int iteraciones);
        int procesar(std::vector<int> entrada);
};
