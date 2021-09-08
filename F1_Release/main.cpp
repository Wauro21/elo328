// Imports generales
#include <cmath>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>


// Imports .h
#include "segFunctions.h"
#include "Projection.h"
#include "LaneDetection.h"
#include "racingLine.h"

#include "mapGeneration.h"
#include "Matrix.h"
#include "polyfit.h"

// Defines
#define trackSkip 2 // skip 2 mask in trackfiles
#define nColsTrack 6 // número de columnas de lectura en .TRACK
#define csvSkip 1 //las lineas que se salta en la lectura del .csv
#define nColsCSV 6 // Numero columnas archivo csv
#define windowRes 60 // Resolucion corte periférico
#define MODO_IMG false
#define MODO_VID true

std::string inputIMG = "NewTelemetry/0.jpg";
std::string udpIMG = "NewTelemetry/0.csv";

std::string inputVID = "NewTelemetry/redbull.mp4";
std::string udpVID = "NewTelemetry/redbull3.txt";

void mainProcessing(std::string, cv::Mat&, std::string, bool mode = false);
cv::Mat frameProcessing(cv::Mat&, std::vector<float>);

int main(int argc, char** argv){

    bool mode = false;;
    if(argc > 1){
        mode = atoi(argv[1]);
    }
    // Modo Imagen
    if(!mode){
        cv::Mat src = cv::imread(inputIMG.c_str());
        cv::Mat out;
        mainProcessing(inputIMG, out, udpIMG, MODO_IMG);

        cv::resize(out, out, cv::Size(1280, 720));
        cv::imshow("Result", out);
        cv::waitKey(0);
    }
    // Modo Video
    else{
        cv::Mat out;
	    mainProcessing(inputVID, out, udpVID, MODO_VID);
    }

}

void mainProcessing(std::string inputFile, cv::Mat& dst, std::string csvFile, bool mode)
{
	//Lectura puntos telemetria
	bool selCSV[] = {true, false, true, true, false, true};
	readVector readUDP = readFile(csvFile, csvSkip, nColsCSV, selCSV); // lee posición y orientación del auto

	// Modo Imagen
	if(!mode){
		cv::Mat src = cv::imread(inputFile.c_str());
		dst = frameProcessing(src, readUDP[0]);
	}
	// Modo Video
	else{
		cv::VideoCapture videoFile(inputFile.c_str());
		double N_frames = (double)videoFile.get(cv::CAP_PROP_FRAME_COUNT);	// numero de frames del video
		double n_frame = 0.0;
        cv::Size S = cv::Size((int)videoFile.get(cv::CAP_PROP_FRAME_WIDTH),(int)videoFile.get(cv::CAP_PROP_FRAME_HEIGHT));
        double FPS = videoFile.get(cv::CAP_PROP_FPS);
		cv::VideoWriter TEST("out.mp4",cv::VideoWriter::fourcc('m', 'p', '4','v'),FPS,S);

        std::cout << "Numero Frames = " << N_frames << std::endl;
		while(true){
			cv::Mat frame;
			videoFile >> frame;
			if(frame.empty()){
				break;
			}

			cv::Mat out = frameProcessing(frame, readUDP[(int)n_frame]);
            TEST << out;
			n_frame++;
			int curr_value = (int)(n_frame*100/N_frames);

			cv::imshow("Video", out);
			char c=(char)cv::waitKey(25);
			if(c == 27){
				break;
			}
		}
		videoFile.release();
		cv::destroyAllWindows();
	}

	return;
}

cv::Mat frameProcessing(cv::Mat& img, std::vector<float> readUDP){

	cv::Mat img2 = img.clone(); // copia de imagen para superposición final de la línea de carreras
	cv::Mat invMatrix; //matriz de proyección inversa
	cv::Mat crop = projection(img, invMatrix); // ROI con proyección bidimensional
	cv::Mat X = getEdges(crop); // segmentación de la proyección a imagen binaria
	std::vector<double> pLeft, pRight;
	cv::Mat mask = getMask(crop, pLeft, pRight); // imagen con máscara de la pista
	//####################################################################

	// Mejorar este "diccionario--------------------------------------------
	std::string trackArray[] = {"silverstone_2020_centerline.track","silverstone_2020_innerlimit.track", "silverstone_2020_outerlimit.track","silverstone_2020_racingline.track"};
	bool selCols[] = {false, true, true, false, false, false};
	//Carga lineas pista
	Matrix innerLimit(readFile(SILVERPATH + trackArray[1], trackSkip, nColsTrack, selCols));
	Matrix outerLimit(readFile(SILVERPATH + trackArray[2], trackSkip, nColsTrack, selCols));
	Matrix raceLine(readFile(SILVERPATH+trackArray[3], trackSkip, nColsTrack, selCols));

	//ventana
	Matrix wInnerLimit = window(innerLimit, readUDP[0], readUDP[1], windowRes);
	Matrix wOuterLimit = window(outerLimit, readUDP[0], readUDP[1], windowRes);
	Matrix wRaceLine = window(raceLine, readUDP[0], readUDP[1], windowRes);
	rotation(wInnerLimit, readUDP[2], readUDP[3]);
	rotation(wOuterLimit, readUDP[2], readUDP[3]);
	rotation(wRaceLine, readUDP[2], readUDP[3]);
	// Calculo distancia
	std::vector<double> percentage = manyDistances(wOuterLimit, wInnerLimit, wRaceLine);
	std::vector<cv::Point> racingPoints = getDistances(mask, percentage, pLeft, pRight);
	std::vector<double> racePoly = racingPoly(racingPoints);
	drawRacingLine(mask, racePoly);

	// proyeccion inversa
	cv::Mat retrieval = invProjection(mask, invMatrix, 1);
	addMask(img2, 1, retrieval, 0.3);

	return retrieval;
}
