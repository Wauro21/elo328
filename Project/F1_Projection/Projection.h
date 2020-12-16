#ifndef PROJECTION_H
#define PROJECTION_H

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

cv::Mat projection(cv::Mat in, int save);
// genera proyeccion geometrica en perspectiva "bird's eye"
cv::Mat kMeans(cv::Mat in, int n);
// segmenta imagen mediante algoritmo de k means (prueba)

#endif /* PROJECTION_H */