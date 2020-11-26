#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
//Dimensiones imagen
#define SPONGEBOB_FACTOR 100




// iz	-inferior 0
// der-inferior 5660
// iz	-superior 2550
// der-superior 2946

int main(int argc, char const *argv[]) {

	//Temporal, lectura archivo estatico
	cv::Mat srcImg = cv::imread("1.jpeg");
	int height = srcImg.rows;
	int width  = srcImg.cols;
	int padding = round(0.98*width);


	float hRoi = floor(0.24*height);
	float wRoi = 2.96*width;
	float infIz = wRoi/2 - 0.1*width;
	float infDer= wRoi/2 + 0.1*width;
	float datasrc[8] = {0, hRoi, wRoi, hRoi, 0, 0, wRoi, 0};
	float datadst[8] = {infIz, hRoi, infDer, hRoi, 0, 0, wRoi, 0};
	cv::Mat src = cv::Mat(4,2,CV_32F, datasrc);
	cv::Mat dst = cv::Mat(4,2,CV_32F, datadst);
	std::cout << src << std::endl;
	std::cout << dst << std::endl;


	cv::Mat transformation = getPerspectiveTransform(src,dst);
	std::cout << transformation << std::endl;

	cv::Mat crop(srcImg, cv::Rect(0, 0.37*height, width, 0.24*height));
	cv::copyMakeBorder(crop, crop, 0, 0, padding, padding, cv::BORDER_CONSTANT, 0);


	cv::warpPerspective(crop, crop, transformation, cv::Size(wRoi, hRoi));
	cv::imshow("entrada",srcImg);
	cv::imshow("salida",crop);
	cv::waitKey(0);

	return 0;
}
