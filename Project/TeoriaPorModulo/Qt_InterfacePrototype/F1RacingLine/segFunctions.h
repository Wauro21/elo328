#ifndef SEGFUNCTIONS_H
#define SEGFUNCTIONS_H

/*
 * Proyecto ELO328 - 2020.S2 - G1
 * Modulo de Proyeccion de Pista
 * Autor: Diego Badillo - 06/12/2020
 */

#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>

#define ATTEMPTS 1

void drawLine(cv::Mat& src, int width);
// elimina lineas del trapecio generado por la proyeccion
void opening(cv::Mat& src, cv::Mat& dst, int x, int y);
// apertura morfologica
void closing(cv::Mat& src, cv::Mat& dst, int x, int y);
// cierre morfologico
void hideWheels(cv::Mat& src);
// oculta ruedas
void addMask(cv::Mat src, double alpha, cv::Mat& ROI, double beta);
// solo funciona para 1080p (por mientras)
cv::Mat getEdges(cv::Mat crop);
// obtiene bordes de la imagen

#endif /* SEGFUNCTIONS_H */