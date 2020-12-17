#include "mapGeneration.h"
#include "Matrix.h"
#include <iostream>
#include <vector>


int main(){
	Matrix sInput;
	sInput.addX(1.0);
	sInput.addY(0.0);
	sInput.setSize(1);
	std::cout << sInput.getX().size() << std::endl;
	rotation(sInput, 0.0, -1.0);
	plotSilverstone(true, false, "test_16_12_rotated");

	return 0;

}
