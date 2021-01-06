
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>

#include "segFunctions.h"
#include "Projection.h"
#include "LaneDetection.h"
#include "racingLine.h"

int main(int argc, char* argv[])
{
	int mode = 0; // 0 image, 1 video

	if (!mode) {
		if(argc == 1)
			return -1;
		cv::Mat img = cv::imread(argv[1]);
		cv::Mat img2 = img.clone();
		cv::Mat invMatrix;
		cv::Mat crop = projection(img, invMatrix);
		cv::Mat X = getEdges(crop);
		//cv::imwrite("edges_segmentation.png", X);

		//############### SHOW ##################
		std::vector<double> pLeft, pRight;
		cv::Mat lines = getMask(crop, pLeft, pRight);
		std::vector<double> percentage;
		percentage.push_back(0.547338);
		percentage.push_back(0.581579);
		percentage.push_back(0.613516);
		percentage.push_back(0.647212);
		percentage.push_back(0.682559);
		percentage.push_back(0.718007);
		percentage.push_back(0.747749);
		percentage.push_back(0.78124);
		percentage.push_back(0.819643);
		percentage.push_back(0.843576);
		std::vector<cv::Point> racingPoints = getDistances(X, percentage, pLeft, pRight);

		for (int i = 0; i < 10; i++) {
			std::cout << "point: " << racingPoints[i] << std::endl;
			cv::circle(lines, cv::Point(racingPoints[i].y,racingPoints[i].x), 10, cv::Scalar(255,255,255), 10);
		}

		std::vector<double> racePoly = racingPoly(racingPoints);

		std::cout << "racePoly" << racePoly[0] << "," << racePoly[1] << "," << racePoly[2] << std::endl;

		drawRacingLine(lines, racePoly);

		// proyeccion inversa
		cv::Mat retrieval = invProjection(lines, invMatrix, 1);


		//############### SHOW ##################
		cv::imwrite("Lines.png", lines);
		cv::imshow("Lines", lines);

		/*
		// obtiene suma ponderada entre los bordes segmentados y la mascara
		cv::Mat X_color;
		cv::cvtColor(X, X_color, cv::COLOR_GRAY2BGR);
		cv::addWeighted(X_color, 0.4, lines, 0.6, 0, X_color);
		cv::imshow("Add", X_color);
		*/

		//cv::imshow("input", img2);
			// se agrega mascara a imagen de entrada
		addMask(img2, 1, retrieval, 0.3);
		cv::imshow("final", retrieval);
		cv::imwrite("final_detection.png", retrieval);

		cv::waitKey(0);
	}
	//############################ VIDEO #################################
	//IMPORTANTE: NO TRABAJAR CON MP4, NO USAR IMAGENES NEGRAS PARA LA FUNCION GETMASK
	else {
		cv::VideoCapture vid("video.mov");
		if (!vid.isOpened()) std::exit(-1);


		int ex = static_cast<int>(vid.get(cv::CAP_PROP_FOURCC));
		cv::Size S = cv::Size(	(int)vid.get(cv::CAP_PROP_FRAME_WIDTH),
								(int)vid.get(cv::CAP_PROP_FRAME_HEIGHT));
		double FPS = vid.get(cv::CAP_PROP_FPS);


		//cv::VideoWriter out;
		//out.open("out.mp4", ex, FPS, S, true);

		cv::VideoWriter out(
			"out.mov",
			cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
			FPS,
			S
			);

		if (!out.isOpened()) std::exit(-1);

		cv::Mat frame;

		while (1) {
			vid >> frame;				//read
			if (frame.empty()) break;


			cv::Mat img2 = frame.clone();
			cv::Mat invMatrix;

			cv::Mat crop = projection(frame, invMatrix);
			cv::Mat X = getEdges(crop);

			//################ MASK #################
			std::vector<double> pLeft, pRight;
			cv::Mat lines = getMask(X, pLeft, pRight);
			std::cout << "p1left: " << pLeft[0] << "," << pLeft[1] << "," << pLeft[2] << std::endl;
			std::cout << "p2right: " << pRight[0] << "," << pRight[1] << "," << pRight[2] << std::endl;


			// proyeccion inversa
			cv::Mat retrieval = invProjection(lines, invMatrix);

			// se agrega mascara a imagen de entrada
			addMask(img2, 1, retrieval, 0.3);

			out << retrieval;

			if (cv::waitKey(1000.0 / FPS) == 27) break; //ESC key
		}
	}

	return 0;
 }
