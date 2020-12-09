#ifndef BIDIMENSIONALMATRIX_H
#define BIDIMENSIONALMATRIX_H
#include "mapGeneration.h"
#include <vector>
#include <iostream>
typedef std::vector<std::vector<float>> readVector;
class BidimensionalMatrix{
	public:
		//Constructor
		BidimensionalMatrix();
		BidimensionalMatrix(readVector input);
		//Setters
		void setX(std::vector<float> xValues);
		void setY(std::vector<float> yValues);
		void addX(float);
		void addY(float);
		// Getters
		std::vector<float> getX();
		std::vector<float> getY();
		int getSize();

		// Vector of vector to Matrix
		void vec2mat(readVector input);

	private:
		std::vector<float>* X;
		std::vector<float>* Y;
		int size;
};


#endif
