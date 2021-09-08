#ifndef MAPGENERATION_H
#define MAPGENERATION_H
//Imports
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "matplotlibcpp.h"
#include "Matrix.h"
//Definicion de datatype para conveniencia
typedef std::vector<std::vector<float>> readVector;
//DEFINES
#define SILVERPATH "silverstone/"

class Matrix;
// Leer archivos
readVector readFile(std::string nameFile, int nSkip, int nCols, bool* indexes);

// Print del vector resultante
void printVector(readVector toPrint);

// Plot silverstone
void plotSilverstone(bool center, bool racingLine, std::string saveName);

// Plot generico
void plotXZ(readVector input, std::string name, std::string style);

// rotacion
void rotation(Matrix& input, float xVal, float zVal);

// window
Matrix window(Matrix& input, float xVal, float zVal, float epsilon);

// Distances
std::vector<double> manyDistances(Matrix& leftBorder, Matrix& rightBorder, Matrix& racingLine, float x, float y, int n = 10);

double oneDistance(Matrix& leftBorder, Matrix& rightBorder, Matrix& racingLine, float x, float y);



#endif
