#ifndef MAPGENERATION_H
#define MAPGENERATION_H
//Imports
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "matplotlibcpp.h"
// Leer archivos
std::vector<std::vector<float>> readFile(std::string nameFile, int nSkip, int nCols, bool* indexes);

// Print del vector resultante
void printVector(std::vector<std::vector<float>>toPrint);

#endif
