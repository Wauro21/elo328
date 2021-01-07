#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

#include "segFunctions.h"
#include "Projection.h"
#include "LaneDetection.h"
#include "racingLine.h"
#include "mapGeneration.h"
#include "Matrix.h"
#include "polyfit.h"

#include "mainwindow.h"

// Defines
#define trackSkip 2 // skip 2 mask in trackfiles
#define nColsTrack 6 // número de columnas de lectura en .TRACK
#define windowRes 60 // Resolucion corte periférico


cv::Mat MainWindow::frameProcessing(cv::Mat& img, std::vector<float> readUDP){

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
    for (int i = 0; i < percentage.size(); i++){
        std::cout << percentage[i] << std::endl;
    }
    std::vector<cv::Point> racingPoints = getDistances(mask, percentage, pLeft, pRight);
    std::vector<double> racePoly = racingPoly(racingPoints);
    drawRacingLine(mask, racePoly);

    // proyeccion inversa
    cv::Mat retrieval = invProjection(mask, invMatrix, 1);
    addMask(img2, 1, retrieval, 0.3);

    return retrieval;
}
