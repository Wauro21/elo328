#include "Projection.h"

cv::Mat projection(cv::Mat in, cv::Mat& invMatrix, int save)
{
	int height = in.rows;
	int width = in.cols;

	// Valores de ROI obtenidos empíricamente. Para formar el trapecio que servirá para generar la matrix inversa, se calibra usando una imagen que contenga una sección de la pista recta.
	float hRoi = floor(0.24 * height);
	float wRoi = 1.01 * width;
	float infL = wRoi / 2 - 0.046 * width;
	float infR = wRoi / 2 + 0.046 * width;
	float datasrc[8] = { 0, hRoi, wRoi, hRoi, 0, 0, wRoi, 0 };
	float datadst[8] = { infL, hRoi, infR, hRoi, 0, 0, wRoi, 0 };
	cv::Mat src = cv::Mat(4, 2, CV_32F, datasrc);
	cv::Mat dst = cv::Mat(4, 2, CV_32F, datadst);
	cv::Mat transformation = getPerspectiveTransform(src, dst);
	// la matriz inversa se almacena para su posterior uso al final del procesamiento (en main)
	invMatrix = cv::getPerspectiveTransform(dst, src);
	cv::Mat out(in, cv::Rect(0, 0.37 * height, width, 0.24 * height));
	cv::warpPerspective(out, out, transformation, cv::Size(wRoi, hRoi));
	cv::resize(out, out, cv::Size(out.cols / 2, out.rows * 2.5)); // valores empíricos
	if (save)
		cv::imwrite("projection.png", out);
	return out;
}

cv::Mat invProjection(cv::Mat in, cv::Mat invMatrix, int save)
{
	// la matriz inversa ingresada como parámetro en esta función, es calculada previamente en projection()
	cv::Mat out;
	//std::cout << in.rows << "," << in.cols << std::endl;
	cv::resize(in, out, cv::Size(in.cols * 1.9815, in.rows * 0.4));
	cv::warpPerspective(out, out, invMatrix, cv::Size(out.cols, out.rows));
	if (save)
		cv::imwrite("inv_projection.png", out);
	return out;
}

cv::Mat kMeans(cv::Mat in, int n)
{
	// esta función solo fue usada como una de las pruebas para generar segmentación de la pista. Esta función no es creación propia, solo fue referenciada.
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
