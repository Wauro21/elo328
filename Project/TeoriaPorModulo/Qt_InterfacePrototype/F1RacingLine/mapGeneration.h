#ifndef MAPGENERATION_H
#define MAPGENERATION_H
//Imports
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
//#include "matplotlibcpp.h"
#include "Matrix.h"
//Definicion de datatype para conveniencia
typedef std::vector<std::vector<float>> readVector;
//DEFINES
#define SILVERPATH "../F1RacingLine/silverstone/"

class Matrix;
// Leer archivos
/*---------------------------------------------------------------------------*/
/*
 * @brief       : lee archivo .csv
 * @param nameFile  : nombre del archivo
 * @param nSkip : cantidad de líneas a saltarse al principio de la lectura
 * @param nCols : cantidad de columnas por línea
 * @param indexes   : columnas a considerar para la lectura
 * @return      : vector de vectores que contiene los valores leídos por columnas y líneas
 */
readVector readFile(std::string nameFile, int nSkip, int nCols, bool* indexes);

/*---------------------------------------------------------------------------*/
/*
 * @brief       : imprime un vector de vectores
 * @param toPrint  : vector de vectores a imprimir
 */
void printVector(readVector toPrint);
/*---------------------------------------------------------------------------*/
// Plot silverstone
//void plotSilverstone(bool center, bool racingLine, std::string saveName);

// Plot generico
//void plotXZ(readVector input, std::string name, std::string style);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : aplica una rotación para fijar el eje y en la dirección a la que apunta el auto
 * @param input : vector de valore (x,z) a ser rotados
 * @param xVal  : componente x del vector de orientación del auto en el mapa sin rotar
 * @param zVal  : componente z del vector de orientación del auto en el mapa sin rotar
 */
void rotation(Matrix& input, float xVal, float zVal);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : restringe a una ventana radial los puntos del mapa para que solo se encuentren en torno al automóvil
 * @param input : mapa de entrada
 * @param xVal  : posición en x en torno a la cual generar el círculo
 * @param zVal  : posición en z en torno a la cual generar el círculo
 * @param epsilon: radio de círculo para restringir los puntos
 * @return      : matriz correspondiente a la segmentación de crop
 */
Matrix Mwindow(Matrix& input, float xVal, float zVal, float epsilon);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : obtiene valores entre 0 y 1 que representan la proporción de la ubicación de la línea de carreras respecto al borde izquierdo y derecho. Un valor de 0.5 representa que la línea de carreras se encuentra exactamente al centro de la pista para una posición vertical determinada. Un 1 representa que la línea de carreras coincide con el borde derecho. Funciona en conjunto con oneDistance()
 * @param leftBorder    : borde izquierdo de la pista
 * @param rightBorder   : borde derecho de la pista
 * @param racingLine    : línea de carreras
 * @param n     : cantidad de puntos para el vector de retorno. Por defecto es 10
 * @return      : vector de valores entre 0 y 1
 */
std::vector<double> manyDistances(Matrix& leftBorder, Matrix& rightBorder, Matrix& racingLine, int n = 10);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : dado un punto y, obtiene para esa posición vertical la proporción a la que se encuentra la línea de carreras respecto al borde izquierdo y el borde derecho.
 * @param leftBorder    : borde izquierdo de la pista
 * @param rightBorder   : borde derecho de la pista
 * @param racingLine    : línea de carreras
 * @param y     : posición vertical para el cálculo de la distancia transversal (horizontal)
 * @return      : valor entre 0 y 1
 */
double oneDistance(Matrix& leftBorder, Matrix& rightBorder, Matrix& racingLine, float y);
/*---------------------------------------------------------------------------*/



#endif
