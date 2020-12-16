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