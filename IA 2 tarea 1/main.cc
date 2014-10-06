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

#define NUM_ITERS 1000
#define TASA_A 0.3

int main(){

	std::vector<float> pesos;
	pesos.push_back(0.1); // w0
	pesos.push_back(0.1); // w1
	pesos.push_back(0.1); // w2

	std::cout << "APRENDIENDO AND:\n";
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
	p.tasa_aprendizaje = TASA_A;
	p.gradient_descent( ejemplos , NUM_ITERS );

	// Prueba
	/*
	std::cout << p.procesar( e1 ) << std::endl;
	std::cout << p.procesar( e2 ) << std::endl;
	std::cout << p.procesar( e3 ) << std::endl;
	std::cout << p.procesar( e4 ) << std::endl;*/

    // Aprendiendo OR 

	std::cout << "APRENDIENDO OR:\n";
    
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
    p_or.tasa_aprendizaje = TASA_A;
    p_or.gradient_descent(ejemplos_or, NUM_ITERS );

	/*std::cout << p_or.procesar( e1_or ) << std::endl;
	std::cout << p_or.procesar( e2_or ) << std::endl;
	std::cout << p_or.procesar( e3_or ) << std::endl;
	std::cout << p_or.procesar( e4_or ) << std::endl;*/

    //Aprendiendo XOR

	//return 0;

	std::cout << "APRENDIENDO XOR:\n";

    int valores_ini_xor_e1[] = { 1, 0, 0 };
    int valores_ini_xor_e2[] = { 1, 0, 1 };
    int valores_ini_xor_e3[] = { 1, 1, 0 };
    int valores_ini_xor_e4[] = { 1, 1, 1 };

    std::vector<int> e1_xor (valores_ini_xor_e1,valores_ini_xor_e1 + sizeof(valores_ini_xor_e1) / sizeof(int) ); //Esta manera es mas chevere
    std::vector<int> e2_xor (valores_ini_xor_e2,valores_ini_xor_e2 + sizeof(valores_ini_xor_e2) / sizeof(int) );
    std::vector<int> e3_xor (valores_ini_xor_e3,valores_ini_xor_e3 + sizeof(valores_ini_xor_e3) / sizeof(int) );
    std::vector<int> e4_xor (valores_ini_xor_e4,valores_ini_xor_e4 + sizeof(valores_ini_xor_e4) / sizeof(int) );

	Ejemplo xor1( e1 , -1 );
	Ejemplo xor2( e2 , 1 );
	Ejemplo xor3( e3 , 1 );
	Ejemplo xor4( e4 , -1 );

    Ejemplo a_ejemplos_xor[] = { xor1, xor2, xor3,xor4 };

    std::vector<Ejemplo> ejemplos_xor (a_ejemplos_xor,a_ejemplos_xor + sizeof(a_ejemplos_xor) / sizeof(Ejemplo));
    Perceptron p_xor (pesos);
    p_xor.tasa_aprendizaje = TASA_A;
    p_xor.gradient_descent(ejemplos_xor, NUM_ITERS );
/*
	std::cout << p_xor.procesar( e1_xor ) << std::endl;
	std::cout << p_xor.procesar( e2_xor ) << std::endl;
	std::cout << p_xor.procesar( e3_xor ) << std::endl;
	std::cout << p_xor.procesar( e4_xor ) << std::endl;*/
        
	return 0;
}
