#include "heuristic.hh"
#include <iostream>

int main(){
	
	State16* ini = new State16(0x0123456789abcdef,0);
	
	std::cout << dist_manhattan(ini);
	
	return 0;
}