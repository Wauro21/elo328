#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

#include "LaneDetection.h"

int main()
{
    cv::Mat X = cv::imread("proj7.png", cv::IMREAD_GRAYSCALE);
    cv::adaptiveThreshold(X, X, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 21, -11);
    cv::imshow("asd", X);

    int xL = 0;
    int xR = 0;

    calculateHistogram(X, &xL, &xR);

    std::cout << xL << "," << xR << std::endl;

    std::vector<double> p1 = detectLine(X, xL);  // p[2]*x^2 + p[1]*x + p[0]
    std::vector<double> p2 = detectLine(X, xR);

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

    cv::imshow("Lines", lines);

    cv::addWeighted(X_color, 0.4, lines, 0.6, 0, X_color);
    cv::imshow("Add", X_color);

    cv::waitKey(0);
    return 0;
}


