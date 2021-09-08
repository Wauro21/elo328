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


//std::string nDataset = "2";
//std::string imgExt = ".jpg";
//std::string testDataPath = "TestDataset/";
//std::string defaultIMG = testDataPath + nDataset + imgExt;
//std::string defaultCSV = testDataPath + nDataset + ".csv";
std::string defaultIMG = "TestDataset/RacingLineTest/0wo.jpg";
std::string defaultCSV = "TestDataset/RacingLineTest/0.csv";
int main(int argc, char* argv[])
{
	//implementacion de prueba solo incluye imagenes por ahora
	cv::Mat img = (argc == 1) ? cv::imread(defaultIMG) : cv::imread(argv[1]);
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
	// ----------------------------------------------------------------------
	//Lectura puntos telemetria
	bool selCSV[] = {true, false, true, true, false, true};
	readVector readUDP = readFile(defaultCSV, csvSkip, nColsCSV, selCSV); // lee posición y orientación del auto
	//Carga lineas pista
	Matrix innerLimit(readFile(SILVERPATH + trackArray[1], trackSkip, nColsTrack, selCols));
	Matrix outerLimit(readFile(SILVERPATH + trackArray[2], trackSkip, nColsTrack, selCols));
	Matrix raceLine(readFile(SILVERPATH+trackArray[3], trackSkip, nColsTrack, selCols));

	//ventana
	Matrix wInnerLimit = window(innerLimit, readUDP[0][0], readUDP[0][1], windowRes);
	Matrix wOuterLimit = window(outerLimit, readUDP[0][0], readUDP[0][1], windowRes);
	Matrix wRaceLine = window(raceLine, readUDP[0][0], readUDP[0][1], windowRes);
	rotation(wInnerLimit, readUDP[0][2], readUDP[0][3]);
	rotation(wOuterLimit, readUDP[0][2], readUDP[0][3]);
	rotation(wRaceLine, readUDP[0][2], readUDP[0][3]);
	// Calculo distancia
	std::vector<double> percentage = manyDistances(wOuterLimit, wInnerLimit, wRaceLine);
	for (int i = 0; i < percentage.size(); i++){
		std::cout << percentage[i] << std::endl;
	}
	std::vector<cv::Point> racingPoints = getDistances(mask, percentage, pLeft, pRight);
	std::vector<double> racePoly = racingPoly(racingPoints);
	drawRacingLine(mask, racePoly);

	// proyeccion inversa
	cv::Mat retrieval = invProjection(mask, invMatrix, 1);



	//############### SHOW ##################
	cv::imwrite("mask.png", mask);
	cv::imshow("mask", mask);

	// se agrega mascara a imagen de entrada
	addMask(img2, 1, retrieval, 0.3);
	cv::imshow("final", retrieval);
	cv::imwrite("final_detection.png", retrieval);

	cv::waitKey(0);
}
