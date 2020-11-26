#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


int main(int argc, char const *argv[]) {
	//Temporal, lectura archivo estatico
	cv::Mat input = cv::imread("1.jpeg");

	

	cv::imshow("entrada",input);
	cv::waitKey(0);

	return 0;
}
