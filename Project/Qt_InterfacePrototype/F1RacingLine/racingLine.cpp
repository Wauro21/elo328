#include "racingLine.h"

std::vector<double> getDistances(cv::Mat X, std::vector<double> p1left, std::vector<double> p2right, int n)
{
	double dif = (double)X.rows / n; //para X de altura 647, 64.7 con n=10
	std::vector<double> returnVector;
	double distance;

	for (int i = 0; i < n; i++) {
		double x = i * dif;
		distance = p2right[2] * x * x + p2right[1] * x + p2right[0] - (p1left[2] * x * x + p1left[1] * x + p1left[0]);
		returnVector.push_back(distance);
	}

	return returnVector;
}
