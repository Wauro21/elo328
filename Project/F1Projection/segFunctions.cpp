#include "segFunctions.h"


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
				samples.at<float>(i + j * in.rows, k) = in.at<cv::Vec3b>(i, j)[k];
			}
		}
	}
	cv::Mat labels;
	cv::Mat centers;
	cv::kmeans(samples, n, labels, cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 3, 5.), ATTEMPTS, cv::KMEANS_PP_CENTERS, centers);

	cv::Mat newImg(in.size(), in.type());
	for (int i = 0; i < in.rows; i++) {
		for (int j = 0; j < in.cols; j++) {
			int cluster_idx = labels.at<int>(i + j * in.rows, 0);
			for (int k = 0; k < in.channels(); k++) {
				newImg.at<cv::Vec3b>(i, j)[k] = centers.at<float>(cluster_idx, k);
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