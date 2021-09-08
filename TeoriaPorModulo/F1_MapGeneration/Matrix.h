#ifndef MATRIX_H
#define MATRIX_H
#include "mapGeneration.h"
#include <vector>
#include <iostream>
typedef std::vector<std::vector<float>> readVector;
class Matrix{
	public:
		//Constructor
		Matrix();
		Matrix(readVector input);
		//Setters
		void setX(std::vector<float> xValues);
		void setY(std::vector<float> yValues);
		void addX(float);
		void addY(float);
		void setSize(int);
		// Getters
		std::vector<float>  getX();
		std::vector<float>  getY();
		std::vector<float>* getpX();
		std::vector<float>* getpY();
		int getSize();

		// Vector of vector to Matrix
		void vec2mat(readVector input);

		//Destructor
		~Matrix();

	private:
		std::vector<float>* X;
		std::vector<float>* Y;
		int size;
};


#endif
