#include "LaneDetection.h"

void calculateHistogram(cv::Mat& X, int* xL, int* xR) {

	/* xL corresponde al punto inicial de la linea izquierda, y xR para la linea derecha */

	int rows = X.rows;
	int cols = X.cols;

	cv::Mat histo(1, cols, CV_32S, cv::Scalar(0));

	uchar* data = X.data;
	int step = X.step;
	int ch = X.channels();

	/* Calculo de histograma para la parte inferior de la imagen */
	for (int i = (int)(rows / 2); i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//if (X.at<uchar>(i,j) > 0) {
			if (data[i*step+j*ch] > 0) {
				histo.at<int>(j) += 1;
			}
		}
	}

	int mid = (int)(cols / 2);
	cv::Mat histoL(histo, cv::Rect(0, 0, mid, 1));
	cv::Mat histoR(histo, cv::Rect(mid, 0, mid, 1));

	/* El unico que se utiliza es 'max_index' */
	double min, max;
	cv::Point max_index;
	cv::Point min_index;

	cv::minMaxLoc(histoL, &min, &max, &min_index, &max_index);
	*xL = max_index.x;
	cv::minMaxLoc(histoR, &min, &max, &min_index, &max_index);
	*xR = max_index.x + mid;
}

std::vector<double> detectLine(cv::Mat& X, int x0, int w, int h) {

	int rows = X.rows;
	int cols = X.cols;

	int X0 = x0;

	int n_win = rows / h;

	int w_begin = 0;
	int w_end = 0;

	/* Vectores para ir guardando los datos */
	std::vector<double>* dataX = new std::vector<double>;
	std::vector<double>* dataY = new std::vector<double>;

	for (int k = 1; k <= n_win; k++) {

		/* Comienza recorriendo la imagen desde abajo */
		for (int i = rows - k * h; i < rows - (k - 1) * h; i++) {
			for (int j = (int)(X0 - w / 2); j < (int)(X0 + w / 2); j++) {
				if (X.at<uchar>(i, j) > 0) {
					dataX->push_back(j);	// row == y coordinate, col == x coordinate
					dataY->push_back(i);
				}
			}
		}

		if (k == 1) {
			w_begin = 0;
			w_end = 0;
		}
		else {
			w_begin = w_end;
		}

		if (!dataX->empty()) {
			double mean = 0.0;
			w_end = dataX->size();
			/* Calculo de promedio */
			for (int m = w_begin; m < w_end; m++) {
				mean += dataX->at(m);
			}
			mean /= ( (double)w_end - (double)w_begin );

			X0 = (int)mean;
		}

	}

	std::vector<double> poly_values;

	PolynomialRegression<double> polyfit;
	polyfit.fitIt(*dataY, *dataX, 2, poly_values);

	delete dataX;
	delete dataY;

	return poly_values;
}

void polyEval(int size_x, std::vector<cv::Point>& L, std::vector<cv::Point>& R, std::vector<cv::Point>& area, 
			std::vector<double>& p1, std::vector<double>& p2) {

	for (int x = 0; x < size_x; x++) {
		double yL = p1[2] * x * x + p1[1] * x + p1[0];
		double yR = p2[2] * x * x + p2[1] * x + p2[0];
		cv::Point pointL((int)yL, x);
		cv::Point pointR((int)yR, x);
		L.push_back(pointL);
		R.push_back(pointR);
		area.push_back(pointL);
		area.push_back(pointR);
	}

}