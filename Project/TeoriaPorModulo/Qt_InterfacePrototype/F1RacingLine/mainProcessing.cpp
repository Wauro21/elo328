
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>

#include "segFunctions.h"
#include "Projection.h"
#include "LaneDetection.h"
#include "racingLine.h"

void mainProcessing(cv::Mat& src, cv::Mat& dst)
{
    cv::Mat img2 = src.clone();
    cv::Mat invMatrix;
    cv::Mat proj = projection(src, invMatrix);

    /* Generacion de Mascara */
    std::vector<double> pLeft, pRight;
    cv::Mat lines = getMask(proj, pLeft, pRight);

    /* Proyeccion Inversa */
    cv::Mat retrieval = invProjection(lines, invMatrix, 1);

    /* Suma de Mascara a Imagen Original */
    addMask(img2, 1, retrieval, 0.3);

    dst = retrieval.clone();
    return;
 }

