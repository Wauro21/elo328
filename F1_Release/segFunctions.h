#ifndef SEGFUNCTIONS_H
#define SEGFUNCTIONS_H

/*
 * Proyecto ELO328 - 2020.S2 - G1
 * Modulo de segmentación
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
 * @brief       : oculta líneas del trapecio generado al aplicar Canny a la proyección
 * @param src   : matriz a editar
 * @param width : ancho de las líneas
 */
void drawLine(cv::Mat& src, int width);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : apertura morfológica
 * @param src   : matriz fuente
 * @param dst   : matriz destino
 * @param x     : ancho elemento estructurante (elípse)
 * @param y     : altura elemento estructurante (elípse)
 */
void opening(cv::Mat& src, cv::Mat& dst, int x, int y);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : cierre morfológico
 * @param src   : matriz fuente
 * @param dst   : matriz destino
 * @param x     : ancho elemento estructurante (elípse)
 * @param y     : altura elemento estructurante (elípse)
 */
void closing(cv::Mat& src, cv::Mat& dst, int x, int y);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : oculta las ruedas en la proyección
 * @param src   : matriz fuente
 */
void hideWheels(cv::Mat& src);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : superpone la máscara a la imagen de entrada (1080p)
 * @param src   : matriz fuente (imagen de entrada)
 * @param alpha : ponderación de src
 * @param ROI   : máscara
 * @param beta  : ponderación de ROI
 */
void addMask(cv::Mat src, double alpha, cv::Mat& ROI, double beta);
/*---------------------------------------------------------------------------*/
/*
 * @brief       : segmentación de bordes mediante Canny y operaciones morfológicas
 * @param crop  : matriz fuente
 * @return      : matriz correspondiente a la segmentación de crop
 */
cv::Mat getEdges(cv::Mat crop);
/*---------------------------------------------------------------------------*/
#endif /* SEGFUNCTIONS_H */
