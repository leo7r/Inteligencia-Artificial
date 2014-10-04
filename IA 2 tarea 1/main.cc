/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  Tarea 1 AND OR.
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

int main(){

	std::vector<float> pesos;
	pesos.push_back(0.1); // w0
	pesos.push_back(0.1); // w1
	pesos.push_back(0.1); // w2

	std::vector<int> e1,e2,e3,e4;
	e1.push_back(1);
	e1.push_back(0);
	e1.push_back(0);

	e2.push_back(1);
	e2.push_back(1);
	e2.push_back(0);

	e3.push_back(1);
	e3.push_back(0);
	e3.push_back(1);

	e4.push_back(1);
	e4.push_back(1);
	e4.push_back(1);

	Ejemplo and1( e1 , -1 );
	Ejemplo and2( e2 , -1 );
	Ejemplo and3( e3 , -1 );
	Ejemplo and4( e4 , 1 );

	std::vector<Ejemplo> ejemplos;
	ejemplos.push_back( and1 );
	ejemplos.push_back( and2 );
	ejemplos.push_back( and3 );
	ejemplos.push_back( and4 );

	Perceptron p( pesos );
	p.tasa_aprendizaje = 0.1;	
	p.entrenar( ejemplos , 10 );

	// Prueba
	std::cout << p.procesar( e1 ) << std::endl;
	std::cout << p.procesar( e2 ) << std::endl;
	std::cout << p.procesar( e3 ) << std::endl;
	std::cout << p.procesar( e4 ) << std::endl;

	return 0;
}
