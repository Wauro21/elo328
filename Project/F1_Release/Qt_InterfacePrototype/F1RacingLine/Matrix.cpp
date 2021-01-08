#include "Matrix.h"

//Constructor defecto
Matrix::Matrix(){
	this->size = 0;
	this->X = new std::vector<float>;
	this->Y = new std::vector<float>;
}

// Con vector de vectores
Matrix::Matrix(readVector input){
	this->X = new std::vector<float>;
	this->Y = new std::vector<float>;
	vec2mat(input);

}


// Setters
void Matrix::setX(std::vector<float> xValues){
	this->X = new std::vector<float>(xValues);
}

void Matrix::setY(std::vector<float> yValues){
	this->Y = new std::vector<float>(yValues);
}

void Matrix::addX(float value){
	this->X->push_back(value);
	this->size = this->X->size();
}

void Matrix::addY(float value){
	this->Y->push_back(value);
	this->size = this->Y->size();
}

void Matrix::setSize(int size){
	this->size = size;
}
//Getters
std::vector<float> Matrix::getX(){
	return *(this->X);
}

std::vector<float> Matrix::getY(){
	return *(this->Y);
}

std::vector<float>* Matrix::getpX(){
	return (this->X);
}

std::vector<float>* Matrix::getpY(){
	return (this->Y);
}
int Matrix::getSize(){
	return this->size;
}

// vector of vector to Matrix
void Matrix::vec2mat(readVector input){
	this->size = input.size();
	for(unsigned int i = 0; i < input.size() ; i++){
		this->X->push_back(input.at(i).at(0));
		this->Y->push_back(input.at(i).at(1));
	}
	//std::cout << "Matriz de " << this->size << " elementos, " << "2x" << input.size() << std::endl;
}

//Destructor
Matrix::~Matrix(){
	(this->X)->clear();
	(this->Y)->clear();
	this->X = NULL;
	this->Y = NULL;
}
