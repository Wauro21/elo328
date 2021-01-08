#include <vector>
#include <iostream>
#include "frameProcessing.cpp"


void mainProcessing(cv::Mat& src, cv::Mat& dst, std::string csvFile)
{
    //Lectura puntos telemetria
    bool selCSV[] = {true, false, true, true, false, true};
    readVector readUDP = readFile(csvFile, csvSkip, nColsCSV, selCSV); // lee posición y orientación del auto

    dst = frameProcessing(src, readUDP[0]);
    return;
}

