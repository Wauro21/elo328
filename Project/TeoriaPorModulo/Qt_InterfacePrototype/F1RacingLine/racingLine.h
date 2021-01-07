#ifndef RACINGLINE_H
#define RACINGLINE_H

/*
 * Proyecto ELO328 - 2020.S2 - G1
 * Modulo de línea de carreras
 * Autor: Diego Badillo - 16/12/2020
 */

#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>

#include "LaneDetection.h"
#include "polyfit.h"


/*---------------------------------------------------------------------------*/
/*
 * @brief       : obtiene la ubicación en pixeles de la línea de carreras una imagen con las dimensiones de X a partir de un vector de valores entre 0 y 1
 * @param X     : matriz fuente, de la cual se extraerán las dimensiones
 * @param percentage: vector de valores entre 0 y 1 (posición relativa de la línea de carreras entre el borde izquierdo y borde derecho para varias alturas)
 * @param p1left: vector que contiene parámetros de un polinomio de segundo orden, que representa el borde izquierdo de la pista
 * @param p2right: vector que contiene parámetros de un polinomio de segundo orden, que representa el borde derecho de la pista
 * @param n     : cantidad de puntos a generar para el vector de retorno
 * @return      : vector de retorno que contiene la ubicación en píxeles de la línea de carreras en n puntos
 */
std::vector<cv::Point> getDistances(cv::Mat X, std::vector<double> percentage, std::vector<double> p1left, std::vector<double> p2right, int n=10);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : obtiene una interpolación polinomial para el vector de entrada
 * @param racingPoints  : vector que contiene los puntos de la línea de carreras (en píxeles)
 * @return      : vector de parámetros que representan los parametros de un polinomio de orden 2
 */
std::vector<double> racingPoly(std::vector<cv::Point> racingPoints);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : grafica la línea de carreras en la imagen de entrada
 * @param X     : matriz de entrada
 * @param polyValues: parámetros del polinomio de segundo orden que representan la línea de carreras
 * @param widthRacingLine: ancho de la línea de carreras
 */
void drawRacingLine(cv::Mat& X, std::vector<double> polyValues, int widthRacingLine = 25);
/*---------------------------------------------------------------------------*/

#endif /* RACINGLINE_H */
