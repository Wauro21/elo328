#ifndef PROJECTION_H
#define PROJECTION_H

/*
 * Proyecto ELO328 - 2020.S2 - G1
 * Modulo de proyeccion de pista
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

/*---------------------------------------------------------------------------*/
/*
 * @brief       : proyección a vista "bird's eye"  (vista superior)
 * @param in    : matriz fuente
 * @param invMatrix: matriz de proyección inversa (3x3) (se almacena para su uso posterior)
 * @param save  : 1 si se quiere guardar resultado como .png, 0 para no guardar
 * @return      : imagen proyectada
 */
cv::Mat projection(cv::Mat in, cv::Mat& invMatrix, int save = 0);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : proyección inversa (desde vista "bird's eye") a perspectiva del piloto
 * @param in    : matriz fuente
 * @param invMatrix: matriz de proyección inversa (3x3)
 * @param save  : 1 si se quiere guardar resultado como .png, 0 para no guardar
 * @return      : imagen proyectada
 */
cv::Mat invProjection(cv::Mat in, cv::Mat invMatrix, int save = 0);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : segmentación mediante k-means (función deprueba, no usada)
 * @param in    : matriz fuente
 * @param n     : número de clusters
 * @return      : imagen segmentada
 */
cv::Mat kMeans(cv::Mat in, int n);
/*---------------------------------------------------------------------------*/
#endif /* PROJECTION_H */
