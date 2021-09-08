#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <cmath>
#include <chrono>

// Variables relacionadas a la toma de tiempo
auto start = std::chrono::high_resolution_clock::now();
auto stop = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
double sumFrame = 0.0f;
double avgFrame = 0.0f;
unsigned int nFrames = 0;

using namespace std;

enum class P_MODE { IMAGE, VIDEO } proc_mode;
cv::Mat img;

void processImage(cv::Mat& dst, cv::Mat& src);
int help() {
    cerr << "Usage: ./GAMMA -i image " << endl;
    cerr << "\t-i: \tModo imagen" << endl;
    cerr << "\t-v: \tModo video" << endl;
    cerr << "\timage: \tRuta de imagen a procesar" << endl;
    return 1;
}

int argv_manager(int argc, char* argv[]) {

    /* Minimo de argumentos requeridos */
    if (argc < 2) {
        return 1;
    }

    /* Hace un loop por los argumentos */
    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-i") == 0) {
            proc_mode = P_MODE::IMAGE;
            img = cv::imread(argv[i + 1], 1);
        }

        if (strcmp(argv[i], "-v") == 0) {
            proc_mode = P_MODE::VIDEO;
            i++;
            continue;
            return 1;
        }
    }
}

int main(int argc, char* argv[]) {
    cv::Mat imgray;
    if (argv_manager(argc, argv) == 1) {
        return help();
    }
    if (proc_mode == P_MODE::IMAGE) {

        cout << "Modo Imagen" << endl;
        if (img.empty()) {
            cerr << "Error reading image " << endl;
            return 1;
        }

        cv::Mat imgray;
        processImage(imgray, img);

        // duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Tiempo ejecucion del modo " << argv[1] << " :" << duration.count() << "[us]" << std::endl;
        cv::imshow("Input Image", img);

        cv::waitKey(0);
    }

    else {
        cout << "Modo Video" << endl;
        cv::VideoCapture vid("lewis2.mp4");
        //cv::VideoCapture vid;
        vid.open("lewis2.mp4");
        if (!vid.isOpened()) {
            cerr << "Error opening input." << endl;
            return 1;
        }
        while (1) {
            vid >> img;
            cv::Mat result;
            nFrames += 1;
            processImage(result, img);
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            sumFrame += (double)duration.count();
            avgFrame = (double)sumFrame / nFrames;
            std::cout << "Tiempo Promedio por frame del modo " << argv[1] << ":" << avgFrame << "[us]" << std::endl;
            cv::imshow("Video", img);
            cv::imshow("Modified video", result);
            if (cv::waitKey(1) != -1)
                break;
        }
        vid.release();
        return 0;
    }
}

void processImage(cv::Mat& dst, cv::Mat& src) {
    cv::Mat imgblur;
    int s = 3;
    double sigma = 1.3;
    cv::Mat canny;  //salidas de pruebas de canny
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);  //img to B&W
    cv::GaussianBlur(dst, imgblur, cv::Size(s, s), sigma, sigma); //Filter Gauss imgB&N to imgblur
    cv::Canny(imgblur, canny, 200, 10);
    cv::Mat canny2 = 255 - canny;
    imshow("Canny2", canny2);

    // Creacion de mascara
    cv::Mat backgr = cv::Mat::zeros(cv::Size(canny2.cols, canny2.rows), CV_8UC1);
    cv::Mat backgr2 = backgr.clone();
    int x = 0, y = canny2.rows*0.382, w = canny2.cols, h = canny2.rows*0.145; // y = 275 - h = 105
    cv::rectangle(backgr, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(255), -1);
    // Bitwise
    cv::Mat RDI;
    cv::bitwise_and(canny2, backgr, RDI);   // Extraccion de pista
    cv::bitwise_not(RDI, RDI);              // Invertir extraccion
    cv::bitwise_and(RDI, backgr, RDI);      // AND con el mismo background, fonde negro - pista blanca
    cv::imshow("Region de interes", RDI);


    
    //   Hough       Hough      Hough       Hough

    vector<cv::Vec2f> lines; // will hold the results of the detection
    cv::HoughLines(RDI, lines, 1, (CV_PI / 180), 200, 0, 0); // runs the actual detection
    // Draw the lines
    std::cout << "Num lineas " << lines.size() << std::endl; //determinar dimensiones 
    cv::Mat cdst = src.clone();
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1500 * (-b));
        pt1.y = cvRound(y0 + 1500 * (a));
        pt2.x = cvRound(x0 - 1500 * (-b));
        pt2.y = cvRound(y0 - 1500 * (a));
        cv::line(cdst, pt1, pt2, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    }
    cv::imshow("Transformada de Hough lineal", cdst);
    /*
    // Circular Hough

    cv::Mat cdst2 = src.clone();
    vector<cv::Vec3f> circles;
    cv::HoughCircles(RDI, circles, cv::HOUGH_GRADIENT, 1,
        RDI.rows / 16,    // change this value to detect circles with different distances to each other
        150, 20, 0, 0);  // change the last two parameters
                          // (min_radius & max_radius) to detect larger circles

    for (size_t i = 0; i < circles.size(); i++) {
        cv::Vec3i c = circles[i];
        cv::Point center = cv::Point(c[0], c[1]);
        // circle center
        circle(src, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
        // circle outline
        int radius = c[2];
        circle(src, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
    }
    cv::imshow("Transformada de Hough circular", cdst2);
    */
}

cv::Mat sobelGradient(cv::Mat src) {
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    /// Generate grad_x and grad_y
    cv::Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;

    /// Gradiente X
    cv::Sobel(src, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_x, abs_grad_x);

    /// Gradiente Y
    cv::Sobel(src, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    /// Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    double maxVal;
    cv::minMaxLoc(grad, NULL, &maxVal, NULL, NULL);
    double factor = 255 / maxVal;

    cv::Mat m8u;
    grad.convertTo(m8u, CV_8U, factor);
    return m8u;
}