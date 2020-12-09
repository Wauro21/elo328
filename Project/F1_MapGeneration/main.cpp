#include "mapGeneration.h"
#include "BidimensionalMatrix.h"
#include <iostream>
#include <vector>


int main(){
	bool test[] = {true,true};
	BidimensionalMatrix retorno(readFile("test.csv", 2, 2,test));
	plotSilverstone(false, false, "test");
	return 0;

}
