
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
	cv::Mat img = cv::imread("6.png");
	cv::Mat img2 = img.clone();
	cv::Mat invMatrix;
	cv::Mat crop = projection(img, invMatrix);

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
	//cv::imshow("projection", crop);
	//cv::imshow("testCanny", testCanny);
	
	//################ MASK #################
	cv::Mat X = testCanny;

	int xL = 0;
	int xR = 0;

	calculateHistogram(X, &xL, &xR);

	std::cout << xL << "," << xR << std::endl;

	std::vector<double> p1 = detectLine(X, xL, 0.1 * X.cols, 0.1 * X.rows);  // p[2]*x^2 + p[1]*x + p[0]
	std::vector<double> p2 = detectLine(X, xR, 0.1 * X.cols, 0.1 * X.rows);

	std::cout << p1[0] << "," << p1[1] << "," << p1[2] << std::endl;
	std::cout << p2[0] << "," << p2[1] << "," << p2[2] << std::endl;

	std::vector<cv::Point> leftLane, rightLane;
	std::vector<cv::Point> laneArea;

	polyEval(X.rows, leftLane, rightLane, laneArea, p1, p2);

	cv::Mat X_color;
	cv::cvtColor(X, X_color, cv::COLOR_GRAY2BGR);

	cv::Mat lines(X.rows, X.cols, CV_8UC3, cv::Scalar(0));
	cv::fillPoly(lines, laneArea, cv::Scalar(0, 200, 0));
	cv::polylines(lines, leftLane, 0, cv::Scalar(0, 255, 255), 4);
	cv::polylines(lines, rightLane, 0, cv::Scalar(0, 255, 255), 4);

	// proyeccion inversa

	cv::Mat comeback = invProjection(lines, invMatrix, 1);

	//############### SHOW ##################
	//cv::imshow("Lines", lines);

	cv::addWeighted(X_color, 0.4, lines, 0.6, 0, X_color);
	//cv::imshow("Add", X_color);
	//cv::imshow("comeback", comeback);
	//cv::imshow("input", img2);

	addMask(img2, 1, comeback, 0.3);
	cv::imshow("final", comeback);
	cv::imwrite("final_detection.png", comeback);

	cv::waitKey(0);
	return 0;

 }

