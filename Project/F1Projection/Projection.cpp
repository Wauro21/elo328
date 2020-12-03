
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>
using namespace std;
using namespace cv;

//Dimensiones imagen

// iz	-inferior 0
// der-inferior 5660
// iz	-superior 2550
// der-superior 2946

#define ATTEMPTS 1

cv::Mat projection(cv::Mat in, int save);
cv::Mat kMeans(cv::Mat in, int n);
cv::Mat gammaCorrection(cv::Mat in, double g_gamma);

int main(int argc, char const* argv[])
{
	//Temporal, lectura archivo estatico
	cv::Mat img = cv::imread("test_3.png");
	cv::Mat crop = projection(img, 1);


	vector<cv::Mat> bgr_planes;
	cv::split(crop, bgr_planes);
	cv::Mat segmented = bgr_planes[0];


	for (int i = 0; i < segmented.rows; i++) {
		for (int j = 0; j < segmented.cols; j++) {
			if (segmented.at<uchar>(i, j) < 40) {
				segmented.at<uchar>(i, j) = 240;
			}
		}
	}

	cv::cvtColor(segmented, segmented, cv::COLOR_GRAY2BGR);
	//cv::Mat gamma = gammaCorrection(segmented, 0.5);
	segmented = kMeans(segmented, 3);
	//cv::threshold(segmented, segmented, 100, 255, 0);

	//cv::imshow("input", img);
	cv::imshow("projection", crop);
	//cv::imshow("gamma", gamma);
	cv::imshow("segmented", segmented);

	cv::waitKey(0);

	return 0;
}

cv::Mat projection(cv::Mat in, int save)
{
	int height = in.rows;
	int width = in.cols;

	float hRoi = floor(0.24 * height);
	float wRoi = 1.01 * width;
	float infL = wRoi / 2 - 0.046 * width;
	float infR = wRoi / 2 + 0.046 * width;
	float datasrc[8] = { 0, hRoi, wRoi, hRoi, 0, 0, wRoi, 0 };
	float datadst[8] = { infL, hRoi, infR, hRoi, 0, 0, wRoi, 0 };
	cv::Mat src = cv::Mat(4, 2, CV_32F, datasrc);
	cv::Mat dst = cv::Mat(4, 2, CV_32F, datadst);
	cv::Mat transformation = getPerspectiveTransform(src, dst);
	cv::Mat out(in, cv::Rect(0, 0.37 * height, width, 0.24 * height));
	cv::warpPerspective(out, out, transformation, cv::Size(wRoi, hRoi));
	cv::resize(out, out, cv::Size(out.cols / 2, out.rows * 2.5));
	if (save)
		cv::imwrite("projection.png", out);
	return out;
}

cv::Mat kMeans(cv::Mat in, int n)
{
	cv::Mat samples(in.rows * in.cols, in.channels(), CV_32F);
	for (int i = 0; i < in.rows; i++) {
		for (int j = 0; j < in.cols; j++) {
			for (int k = 0; k < in.channels(); k++) {
				samples.at<float>(i + j * in.rows, k) = in.at<Vec3b>(i, j)[k];
			}
		}
	}
	cv::Mat labels;
	cv::Mat centers;
	cv::kmeans(samples, n, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 3, 5.), ATTEMPTS, KMEANS_PP_CENTERS, centers);

	Mat newImg(in.size(), in.type());
	for (int i = 0; i < in.rows; i++) {
		for (int j = 0; j < in.cols; j++) {
			int cluster_idx = labels.at<int>(i + j * in.rows, 0);
			for (int k = 0; k < in.channels(); k++) {
				newImg.at<Vec3b>(i, j)[k] = centers.at<float>(cluster_idx, k);
			}
		}
	}
	return newImg;
}

cv::Mat gammaCorrection(cv::Mat in, double g_gamma)
{
	cv::Mat img;
	cv::cvtColor(in, img, cv::COLOR_BGR2YCrCb);
	uchar table[256];
	for (int i = 0; i <= 255; i++) {
		table[i] = (uchar)255 * pow((double)i / 255, g_gamma);
	}
	int channels = img.channels();
	int step = img.step;
	uchar* data = img.data;

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			uchar& pixel = data[i * step + j * channels];
				pixel = table[pixel];
		}
	}
	cv::cvtColor(img, img, cv::COLOR_YCrCb2BGR);
	return img;
}
