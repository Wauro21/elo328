#ifndef RACINGLINE_H
#define RACINGLINE_H

/*
 * Proyecto ELO328 - 2020.S2 - G1
 * Modulo de Proyeccion de Pista
 * Autor: Diego Badillo - 16/12/2020
 */

#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>



std::vector<cv::Point> getDistances(cv::Mat X, std::vector<double> percentage, std::vector<double> p1left, std::vector<double> p2right, int n=10);
/*
 * Obtiene distancias transversales de la mascara para n subdivisiones
 * en el caso de que uno de los bordes se salga de la imagen, retorna -1. Se debe considerar cuando se implemente la funcion
 * relacionada a la telemetría
 */

#endif /* RACINGLINE_H */
