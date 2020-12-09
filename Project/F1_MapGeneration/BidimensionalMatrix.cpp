#include "BidimensionalMatrix.h"

//Constructor defecto
BidimensionalMatrix::BidimensionalMatrix(){
	this->size = 0;
	this->X = new std::vector<float>;
	this->Y = new std::vector<float>;
}

// Con vector de vectores
BidimensionalMatrix::BidimensionalMatrix(readVector input){
	this->X = new std::vector<float>;
	this->Y = new std::vector<float>;
	vec2mat(input);

}


// Setters
void BidimensionalMatrix::setX(std::vector<float> xValues){
	this->X = new std::vector<float>(xValues);
}

void BidimensionalMatrix::setY(std::vector<float> yValues){
	this->Y = new std::vector<float>(yValues);
}

void BidimensionalMatrix::addX(float value){
	this->X->push_back(value);
}

void BidimensionalMatrix::addY(float value){
	this->Y->push_back(value);
}

//Getters
std::vector<float> BidimensionalMatrix::getX(){
	return *(this->X);
}

std::vector<float> BidimensionalMatrix::getY(){
	return *(this->Y);
}

int BidimensionalMatrix::getSize(){
	return this->size;
}

// vector of vector to Matrix
void BidimensionalMatrix::vec2mat(readVector input){
	this->size = 2*input.size();
	for(unsigned int i = 0; i < input.size() ; i++){
		this->X->push_back(input.at(i).at(0));
		this->Y->push_back(input.at(i).at(1));
	}
	std::cout << "Matriz de " << this->size << " elementos, " << "2x" << input.size() << std::endl;
}

//Destructor
BidimensionalMatrix::~BidimensionalMatrix(){
	(this->X)->clear();
	(this->Y)->clear();
	this->X = NULL;
	this->Y = NULL;
}
