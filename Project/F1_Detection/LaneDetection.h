#ifndef LANEDETECTION_H
#define LANEDETECTION_H

/* 
 * Proyecto ELO328 - 2020.S2 - G1
 * Modulo de Deteccion de Pista
 * Autor: Felipe Villenas - 05/12/2020
 */

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

#include "polyfit.h"

void calculateHistogram(cv::Mat& X, int* xL, int* xR);
/*
 * Funcion para calcular el histograma de la region inferior de la imagen (de 1 canal)
 */

std::vector<double> detectLine(cv::Mat& X, int x0, int w = 100, int h = 50);
/*
 * Retorna los coeficientes del polinomio de la linea respectiva con 'x0'
 */

void polyEval(
	int size_x, 
	std::vector<cv::Point>& L, 
	std::vector<cv::Point>& R, 
	std::vector<cv::Point>& area,
	std::vector<double>& p1,
	std::vector<double>& p2);
/*
 * Evalua el polinomio 'p', y genera los vectores 'L' (linea izq.), 'R' (linea der.), y el 'area' de la pista
 */

cv::Mat getMask(cv::Mat X);
/*
 * Obtiene mascara a partir de imagen con bordes segmentados
 */


#endif /* LANEDETECTION_H */