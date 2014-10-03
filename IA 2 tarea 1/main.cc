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
 *         Author:  Ruben Serradas, 
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

        // Aprendiendo AND
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
	p.entrenar( ejemplos , 10 );

	// Prueba

	std::cout << p.procesar( e1 ) << std::endl;
	std::cout << p.procesar( e2 ) << std::endl;
	std::cout << p.procesar( e3 ) << std::endl;
	std::cout << p.procesar( e4 ) << std::endl;

        // Aprendiendo OR 
        
        int valores_ini_e1[] = { 1, 0, 0 }; 
        int valores_ini_e2[] = { 1, 0, 1 };
        int valores_ini_e3[] = { 1, 1, 0 }; 
        int valores_ini_e4[] = { 1, 1, 1 }; 

        std::vector<int> e1_or (valores_ini_e1,valores_ini_e1 + sizeof(valores_ini_e1) / sizeof(int) ); //Esta manera es mas chevere
        std::vector<int> e2_or (valores_ini_e2,valores_ini_e2 + sizeof(valores_ini_e2) / sizeof(int) );
        std::vector<int> e3_or (valores_ini_e3,valores_ini_e3 + sizeof(valores_ini_e3) / sizeof(int) );
        std::vector<int> e4_or (valores_ini_e4,valores_ini_e4 + sizeof(valores_ini_e4) / sizeof(int) );

	Ejemplo or1( e1 , -1 );
	Ejemplo or2( e2 , 1 );
	Ejemplo or3( e3 , 1 );
	Ejemplo or4( e4 , 1 );

        Ejemplo a_ejemplos_or[] = { or1, or2, or3,or4 };

        std::vector<Ejemplo> ejemplos_or (a_ejemplos_or,a_ejemplos_or + sizeof(a_ejemplos_or) / sizeof(Ejemplo));
        Perceptron p_or (pesos);
        p.entrenar(ejemplos_or,10);

	std::cout << p.procesar( e1_or ) << std::endl;
	std::cout << p.procesar( e2_or ) << std::endl;
	std::cout << p.procesar( e3_or ) << std::endl;
	std::cout << p.procesar( e4_or ) << std::endl;

        //Aprendiendo XOR
        
	return 0;
}
