#ifndef MAPGENERATION_H
#define MAPGENERATION_H
//Imports
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "matplotlibcpp.h"
#include "BidimensionalMatrix.h"
#define SILVERPATH "silverstone/"
//Definicion de datatype para conveniencia
typedef std::vector<std::vector<float>> readVector;
//DEFINES


// Leer archivos
readVector readFile(std::string nameFile, int nSkip, int nCols, bool* indexes);

// Print del vector resultante
void printVector(readVector toPrint);

// Plot silverstone
void plotSilverstone(bool center, bool racingLine, std::string saveName);

// Plot generico
void plotXZ(readVector input, std::string name, std::string style);
#endif
