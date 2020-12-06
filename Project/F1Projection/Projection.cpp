
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>

#include "segFunctions.h"


int main() 
{
	//Temporal, lectura archivo estatico
	cv::Mat img = cv::imread("4.png");
	cv::Mat crop = projection(img, 0);
	cv::Mat dstEdge;
	cv::Canny(crop, dstEdge, 240, 10);
	//cv::dilate(crop, crop, getStructuringElement(cv::MORPH_ELLIPSE, Size(2, 20)));


	cv::Mat threshold;
	cv::cvtColor(crop, threshold, cv::COLOR_BGR2GRAY);

	
	cv::adaptiveThreshold(threshold, threshold, 255,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 21, -19);

	//eliminar lineas trapecio
	drawLine(threshold, 7);
	drawLine(dstEdge, 6);
	cv::dilate(dstEdge, dstEdge, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)));

	cv::Mat sum;
	cv::add(threshold, dstEdge, sum);

	cv::Mat morph;
	opening(sum, morph, 3, 3);
	closing(morph, morph, 5, 5);
	//opening(morph, morph, 3, 3);

	//test: aplicar morfologia antes de segmentar para lograr uniformidad en el asfalto
	cv::Mat test;
	cv::Mat testCanny;
	cv::Mat testThreshold;
	opening(crop, test, 2, 3);

	cv::cvtColor(test, test, cv::COLOR_BGR2GRAY);
	cv::Canny(test, testCanny, 160, 70);
	drawLine(testCanny, 6);
	cv::imwrite("testCanny.png", testCanny);


	//############### SHOW ##################
	//cv::imshow("detection", dstEdge);
	cv::imshow("projection", crop);
	//cv::imshow("threshold", threshold);
	//cv::imshow("sum", sum);
	//cv::imshow("morph", morph);
	cv::imshow("testCanny", testCanny);
	cv::imshow("test", test);


	cv::waitKey(0);
	
	return 0;
}

