
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>

#include "segFunctions.h"
#include "LaneDetection.h"

int main() 
{
	cv::Mat img = cv::imread("4.png");
	cv::Mat img2 = img.clone();
	cv::Mat invMatrix;
	cv::Mat crop = projection(img, invMatrix);

	cv::Mat X = getEdges(crop);
	cv::imwrite("edges_segmentation.png", X);

	//############### SHOW ##################
	//cv::imshow("projection", crop);
	//cv::imshow("edges_segmentation", X);
	
	//################ MASK #################
	cv::Mat lines = getMask(X);

	// proyeccion inversa
	cv::Mat retrieval = invProjection(lines, invMatrix, 1);

	//############### SHOW ##################
	//cv::imshow("Lines", lines);

	/*
	// obtiene suma ponderada entre los bordes segmentados y la mascara
	cv::Mat X_color;
	cv::cvtColor(X, X_color, cv::COLOR_GRAY2BGR);
	cv::addWeighted(X_color, 0.4, lines, 0.6, 0, X_color);
	cv::imshow("Add", X_color);
	*/

	//cv::imshow("input", img2);

	// se agrega mascara a imagen de entrada
	addMask(img2, 1, retrieval, 0.3);
	cv::imshow("final", retrieval);
	cv::imwrite("final_detection.png", retrieval);

	cv::waitKey(0);
	return 0;

 }

