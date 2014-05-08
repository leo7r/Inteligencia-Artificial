#include "heuristic.hh"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>

std::string arrayConverter(char* array){
    std::string nuevo;
    for (int i = 0; i < 25 ; i++){
        nuevo += (array[i]+ 97);
    }
    return nuevo + '\0';
}

class compareState25 { // simple comparison function
	public:
		bool operator()(const std::pair<char *, char> x,const std::pair<char *, char> y) {
			
			for (int i = 0; i<25; i++){
				if(x.first[i]!=y.first[i]) return true;
			}
			return x.second != y.second;
		} 
};
static std::map<std::pair<std::string,char>,State25*> hashPattern25; /*  */


int main(){

	calcularPDB25();
/*
        char array[25] = {1,3,2,7,4,5,6,0,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}; 
        State25* ini = new State25( array,7);
		State25* ini2=ini->a_derecha();
		ini2->print_state();
		State25* ini3=ini->a_abajo();
		ini3->print_state();
		State25* ini4=ini->a_izquierda();
		ini4->print_state();
		State25* ini5=ini->a_arriba();
		ini5->print_state();
		*/
		
		//std::cout << dist_manhattan24(ini)<<"\n";
		
		char array1[25] = {1,0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}; 
        State25* ini = new State25( array1,1);
		
		//std::cout << dist_manhattan24(ini)<<"\n";
		
        char array2[25] = {1,'a',2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}; 
        State25* ini2 = new State25( array2,1);
		
        char array3[25] = {'a',1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}; 
        State25* ini3 = new State25( array3,0);
		
        char array4[25] = {'a',2,1,3,5,4,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}; 
        State25* ini4 = new State25( array4,0);
		
                std::cout << ini->current_state << "\n";
                std::cout << std::string(arrayConverter(ini->current_state)) << '\n';
                std::cout << std::string(arrayConverter(ini->current_state)).length() << '\n';
		std::pair<std::string, char> par1(std::string(arrayConverter(ini->current_state)),ini->zero_index);
		std::pair<std::string, char> par2(std::string(ini2->current_state),ini2->zero_index);
		std::pair<std::string, char> par3(std::string(ini4->current_state),ini4->zero_index);
		std::pair<std::string, char> par4(std::string(ini3->current_state),ini->zero_index+1);
		
		hashPattern25[par2]=ini2;
		hashPattern25[par1]=ini;
		hashPattern25[par4]=ini3; 
		hashPattern25[par3]=ini4;
		std::cout << hashPattern25.size() << "\n";
		//std::cout << hashPattern25.size()<< "\n";;
		/*  		
		std::map<std::pair<char*,char>,State25*>::const_iterator it;
		it = hashPattern25.find(par4);
		
		if ( it == hashPattern25.end() )
			std::cout << "No encontro";
		else{
			std::cout << "Encontro";
		}*/
		/*
		ini->a_izquierda()->print_state();

        State24* tmp = ini->a_derecha();
        tmp->print_state();
        printf("index: %d\n",tmp->zero_index);


        State24* tmp1 = tmp->a_derecha();
        tmp1->print_state();
        State24* tmp2 = tmp1->a_derecha();
        tmp2->print_state();
        State24* tmp3 = tmp2->a_derecha();
        tmp3->print_state();
        State24* tmp4 = tmp3->a_derecha();
        tmp4->print_state();
        tmp3->a_izquierda()->a_izquierda()->print_state();

        tmp1->a_abajo()->print_state();
		*/

	/*State16* ini = crear_estado(0x7f82d63cb04a951e,9); //new State16(0x59de63271c0a48bf,10);
	Node* node = new Node(ini);
	node->a = ARRIBA;
	
	ini->print_state();
	
	std::list<Node*> succ =  node->succ();
	succ.sort(compare_node_state16);
	
	
	std::cout << "\nSucesores:\n";
	
    while (!succ.empty()){
        Node* tmp = succ.front();
		tmp->node_state->print_state();
		std::cout << '\n';
		
		std::cout << "Accion: ";
		print_action(tmp->a);
		
		//std::cout << dist_manhattan(tmp->node_state);
        succ.pop_front();
    }*/
	
	//calcularPDB();
	//loadPDB();
	/*State16* ini = crear_estado(0x0f82d63cb41a95e7,14);
	
	ini->print_state();
	
	std::ofstream myfile;
	myfile.open ("example.txt", std::ios::out | std::ios::binary);
	
	//char* buffer = ini->toCharArray();
	
	int_fast64_t * ptr = &ini->current_state;
	
	int myInt = 12;
	int * ptr_i = &myInt;
	
	if ( myfile.is_open() ){
		myfile.write((const char*)ptr,(sizeof ini->current_state));
		myfile.write((const char*) ptr_i , sizeof myInt );
		myfile.close();
	}
	
	
	std::ifstream file;
	file.open ("example.txt", std::ios::in | std::ios::binary);
	//char buffer2[8];
	int_fast64_t * ptr2 = (int_fast64_t*) malloc(sizeof ini->current_state);
	int * ptr2_i = (int*) malloc(sizeof myInt);
	
	if ( file.is_open() ){
	
		file.read((char*)ptr2,sizeof ini->current_state);
		file.read((char*)ptr2_i,sizeof myInt);
		//std::cout << ":D\n";
		file.close();
	}
	
	int_fast64_t asd = *ptr2;
	int num = *ptr2_i;
	ini = new State16(asd,0);
	ini->print_state();
	std::cout << "Entero: " << num << "\n";
	
	*/
/*  	State16* ini = crear_estado(0x1325a9f68edbc470,0);
	
	pdbHeuristic(ini);
	ini = crear_estado(0x7f82d63cb41a95e0,14);
	pdbHeuristic(ini);
	
	//0x7f82d63cb04a951e
    Node *n = new Node(ini);
	ini->print_state();
	
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
		
	bool funciona = ida_star1(n,dist_manhattan);
		
	if ( funciona ){
		std::cout << "Funciono!";
	}
	else{
		std::cout << "No funciono :(";
	}	
		
	end = std::chrono::system_clock::now();
		
	std::chrono::duration<double> elapsed_seconds = end-start;
		
	std::cout << "Tiempo: " << elapsed_seconds.count() << "\n";

	//std::cout << pdbHeuristic(ini);
	
	
	return 0;*/

}
