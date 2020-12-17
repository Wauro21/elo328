
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

int main() 
{
	int mode = 0; // 0 image, 1 video

	if (!mode) {
		cv::Mat img = cv::imread("4.png");
		cv::Mat img2 = img.clone();
		cv::Mat invMatrix;
		cv::Mat crop = projection(img, invMatrix);

		cv::Mat X = getEdges(crop);
		//cv::imwrite("edges_segmentation.png", X);
		//############### SHOW ##################
		//cv::imshow("projection", crop);
		//cv::imshow("edges_segmentation", X);

		//################ MASK #################
		cv::Mat lines = getMask(X);
		
		// proyeccion inversa
		cv::Mat retrieval = invProjection(lines, invMatrix, 1);
		
		//############### SHOW ##################
		//cv::imshow("Lines", lines);

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
		
		/*cv::VideoWriter out(
			"out.mov", 
			cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
			FPS,
			S
			);
		
		if (!out.isOpened()) std::exit(-1);*/

		cv::Mat frame;

		while (1) {
			vid >> frame;				//read
			if (frame.empty()) break;	

			
			cv::Mat img2 = frame.clone();
			cv::Mat invMatrix;
			
			cv::Mat crop = projection(frame, invMatrix);
			cv::Mat X = getEdges(crop);
			
			//################ MASK #################
			cv::Mat lines = getMask(X);
			
			
			// proyeccion inversa
			cv::Mat retrieval = invProjection(lines, invMatrix);

			// se agrega mascara a imagen de entrada
			addMask(img2, 1, retrieval, 0.3);
			
			//out << retrieval;
			cv::imshow("Video", retrieval);
			if (cv::waitKey(1000.0 / FPS) == 27) break; //ESC key
		}		
	}

	return 0;
 }

