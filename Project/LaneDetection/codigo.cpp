#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
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
    cv::Mat imgblur;
    cv::Mat imgray;
    int s = 25;
    double sigma = 3.0;

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
       // cv::GaussianBlur(imgray, imgblur, cv::Size(s, s), sigma, sigma);
       // cv::imshow("Result", imgblur);

        cv::waitKey(0);
    }



    else {
        cout << "Modo Video" << endl;
        cv::VideoCapture vid("lewis.mp4");
        //cv::VideoCapture vid;
        vid.open("lewis.mp4");

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

       
    




/* ------------------------------------------------------ */



/*--------------------------------------------------------------*/

void processImage(cv::Mat& dst, cv::Mat& src) {

    cv::Mat canny,canny2;
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    /*cv::Canny(img, canny, 250, 10);
    imshow("Canny", 255 - canny);*/

    cv::Canny(dst, canny2, 200, 10);
    imshow("Cannygray", 255 - canny2);



    //cv::Mat* roi;
   
}
/*void correccionGamma(cv::Mat& img) {

    int channels = img.channels();
    int step = img.step;
    uchar* data = img.data;

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            uchar& pixel = data[i * step + j * channels];
            if (gamma_mode == G_MODE::M1) {
                pixel = table[pixel];
            }
            else {
                pixel = (uchar)255 * pow((double)pixel / 255, g_gamma);
            }
        }
    }

}*/


/* Funcion que imprime el menu de ayuda */

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
