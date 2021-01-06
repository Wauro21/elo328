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
	cv::Mat img = cv::imread("1.png");
	cv::Mat crop = projection(img, 0);
	
	//test: aplicar morfologia antes de segmentar para lograr uniformidad en el asfalto
	cv::Mat test;
	cv::Mat testCanny;
	opening(crop, test, 5, 8);
	cv::cvtColor(test, test, cv::COLOR_BGR2GRAY);

	cv::Canny(test, testCanny, 150, 40);
	drawLine(testCanny, 7);
	hideWheels(testCanny);
	cv::dilate(testCanny, testCanny, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	cv::imwrite("testCanny.png", testCanny);

	//############### SHOW ##################
	cv::imshow("projection", crop);
	cv::imshow("testCanny", testCanny);
	//cv::imshow("test", test);

	cv::waitKey(0);
	
	return 0;
}

