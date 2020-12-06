#ifndef SEGFUNCTIONS_H
#define SEGFUNCTIONS_H

/*
 * Proyecto ELO328 - 2020.S2 - G1
 * Modulo de Deteccion de Pista
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

cv::Mat projection(cv::Mat in, int save);
// genera proyeccion geometrica en perspectiva "bird's eye"
cv::Mat kMeans(cv::Mat in, int n);
// segmenta imagen mediante algoritmo de k means (prueba)
cv::Mat gammaCorrection(cv::Mat in, double g_gamma);
// aplica correccion gamma (prueba)
void drawLine(cv::Mat& src, int width);
// elimina lineas del trapecio generado por la proyeccion
void opening(cv::Mat& src, cv::Mat& dst, int x, int y);
// apertura morfologica
void closing(cv::Mat& src, cv::Mat& dst, int x, int y);
// cierre morfologico
void hideWheels(cv::Mat& src);
// oculta ruedas

#endif /* SEGFUNCTIONS_H */