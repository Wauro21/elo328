#include "racingLine.h"

std::vector<cv::Point> getDistances(cv::Mat X, std::vector<double> percentage, std::vector<double> p1left, std::vector<double> p2right, int n)
{
	double dif = (double)X.rows / n; //para X de altura 647, 64.7 con n=10 969x647
	std::vector<double> returnVector;
	double distance;
	std::vector<cv::Point> returnV2;
	double raceLineY;


	for (int i = 0; i < n; i++) {
		double x = n*dif - i * dif;
		if (p2right[2] * x * x + p2right[1] * x + p2right[0] > 969
			|| p1left[2] * x * x + p1left[1] * x + p1left[0] < 0) {
			returnVector.push_back(-1);
			continue;
		}
		distance = p2right[2] * x * x + p2right[1] * x + p2right[0] - (p1left[2] * x * x + p1left[1] * x + p1left[0]);
		returnVector.push_back(distance);
		raceLineY = (p1left[2] * x * x + p1left[1] * x + p1left[0]) + percentage.at(i) * distance;
		returnV2.push_back(cv::Point(x,raceLineY));
	}
	return returnV2;
}

std::vector<double> racingPoly(std::vector<cv::Point> racingPoints)
{
	std::vector<double> polyValues;
	std::vector<double>* dataY = new std::vector<double>;
	std::vector<double>* dataX = new std::vector<double>;

	for (int i = 0; i < racingPoints.size(); i++) {
		dataY->push_back(racingPoints[i].x);
		dataX->push_back(racingPoints[i].y);
	}

	PolynomialRegression<double> polyfit;
	polyfit.fitIt(*dataY, *dataX, 2, polyValues); 

	return polyValues;
}

void drawRacingLine(cv::Mat& X, std::vector<double> polyValues, int widthRacingLine)
{
	std::vector<cv::Point> leftLane, rightLane;
	std::vector<cv::Point> laneArea;
	std::vector<double> polyValuesL(polyValues), polyValuesR(polyValues);


	polyValuesL[0] -= widthRacingLine;
	polyValuesR[0] += widthRacingLine;

	polyEval(X.rows, leftLane, rightLane, laneArea, polyValuesL, polyValuesR);
	cv::fillPoly(X, laneArea, cv::Scalar(0, 0, 255));
	cv::polylines(X, leftLane, 0, cv::Scalar(255, 255, 255), 4);
	cv::polylines(X, rightLane, 0, cv::Scalar(255, 255, 255), 4);
}