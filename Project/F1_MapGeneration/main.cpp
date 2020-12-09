#include "mapGeneration.h"
#include <iostream>
#include <vector>
int main(){
	bool test[] = {true,false,true};
	std::vector<std::vector<float>> retorno = readFile("test2.csv", 2, 3,test);
	printVector(retorno);
	return 0;

}
