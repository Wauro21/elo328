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

/*---------------------------------------------------------------------------*/
/*
 * @brief       : calcula el histograma de la región inferior de la imagen (de 1 canal). El resultado será usado posteriormenta para la estimación de la ubicación de los bordes de la pista.
 * @param X  	: imagen binaria correspondientea la segmentación de una proyección de la pista
 * @param xL	: punto estimado del inicio del borde izquierdo de la pista
 * @param xR	: punto estimado del inicio del borde derecho de la pista
 */
void calculateHistogram(cv::Mat& X, int* xL, int* xR);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : aplicación del algoritmo "window slide detection" para la detección de los bordes de la pista a partir de una imagen segmentada.
 * @param X 	: imagen binaria correspondientea la segmentación de una proyección de la pista
 * @param x0	: punto de inicio para comenzar a ejecutar el algoritmo de las ventanas (este valor se obtiene previamente de calculateHistogram())
 * @param w		: ancho de las ventanas (por defecto, 100 píxeles)
 * @param h		: altura de las ventanas (por defecto, 50 píxeles)
 * @return      : vector que contiene los parámetros de un polinomio de segundo orden que representan una curva (borde de la pista)
 */
std::vector<double> detectLine(cv::Mat& X, int x0, int w = 100, int h = 50);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : evaluación de polinomios de segundo orden en una imagen
 * @param size_x: tamaño en píxeles en x para la evaluación del polinomio (en el caso particular de este proyecto, representará la altura de la imagen máscara)ç
 * @param L		: borde izquierdo evaluado
 * @param R		: borde derecho evaluado
 * @param area	: area de la pista
 * @param p1	: polinomio que representa el borde izquierdo
 * @param p2	: polinomio que representa el borde derecho
 */
void polyEval(
	int size_x,
	std::vector<cv::Point>& L,
	std::vector<cv::Point>& R,
	std::vector<cv::Point>& area,
	std::vector<double>& p1,
	std::vector<double>& p2);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : obtiene la máscara a partir de una imagen segmentada
 * @param X  	: imagen de entrada segmentada binaria
 * @param p1	: polinomio de orden 2 que representa el borde izquierdo
 * @param p2	: polinomio de orden 2 que representa el borde derecho
 * @return      : máscara de la pista
 */
cv::Mat getMask(cv::Mat X, std::vector<double>& p1, std::vector<double>& p2);
/*---------------------------------------------------------------------------*/


#endif /* LANEDETECTION_H */
