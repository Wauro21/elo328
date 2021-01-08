#include "segFunctions.h"

void drawLine(cv::Mat& src, int width)
{
	cv::line(src, cv::Point(0.4577 * src.cols, src.rows),
		cv::Point(0, 0), cv::Scalar(0, 0, 0), width);
	cv::line(src, cv::Point(0.5464 * src.cols, src.rows),
		cv::Point(0.9856 * src.cols, 0), cv::Scalar(0, 0, 0), width);
}

void opening(cv::Mat& src, cv::Mat& dst, int x, int y)
{
	cv::erode(src, dst, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(x, y)));
	cv::dilate(dst, dst, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(x, y)));
}

void closing(cv::Mat& src, cv::Mat& dst, int x, int y)
{
	cv::dilate(src, dst, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(x, y)));
	cv::erode(dst, dst, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(x, y)));
}

void hideWheels(cv::Mat& src)
{
	cv::rectangle(
		src,
		cv::Point(0.47 * src.cols, 0.94 * src.rows),
		cv::Point(0.53 * src.cols, src.rows),
		cv::Scalar(0, 0, 0),
		-1
	);
}

void addMask(cv::Mat src, double alpha, cv::Mat& ROI, double beta)
{
	cv::copyMakeBorder(
		ROI, ROI,
		397, 425, 0, 0,
		cv::BORDER_CONSTANT,
		cv::Scalar(0, 0, 0)
	);
	//std::cout << src.rows << "," << src.cols << std::endl;
	//std::cout << ROI.rows << "," << ROI.cols << std::endl;

	cv::addWeighted(src, alpha, ROI, beta, 0, ROI);
}


cv::Mat getEdges(cv::Mat crop)
{
	//test: aplicar morfologia antes de segmentar para lograr uniformidad en el asfalto
	cv::Mat test;
	cv::Mat testCanny;
	opening(crop, test, 3, 7);
	cv::cvtColor(test, test, cv::COLOR_BGR2GRAY);

	cv::Canny(test, testCanny, 150, 40);
	drawLine(testCanny, 7);
	hideWheels(testCanny);
	cv::dilate(testCanny, testCanny, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	return testCanny;
}
