#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;

enum class P_MODE { IMAGE, VIDEO } proc_mode;
enum class G_MODE { M1, M2 } gamma_mode;

cv::Mat img;
double g_gamma;
int x, y, w, h, r, g, b;

int argv_manager(int argc, char* argv[]);   // Gestiona los argumentos a las variables
int help();     // Imprime el menu de ayuda en caso de error en los argumentos

void processImage(cv::Mat& dst, cv::Mat& src);
void correccionGamma(cv::Mat& img);

bool flag_f = false;
bool flag_c = false;
uchar table[256];
void table_creator();

/* ------------------------------------------------------ */

int main(int argc, char* argv[]) {


    if (argv_manager(argc, argv) == 1) {
        return help();
    }

    if (proc_mode == P_MODE::IMAGE) {

        cout << "Modo Imagen" << endl;
        if (img.empty()) {
            cerr << "Error reading image " << endl;
            return 1;
        }

        cv::Mat result;
        processImage(result, img);

        cout << "Valor gamma = " << g_gamma << endl;
        cv::imshow("Input Image", img);
        cv::imshow("Result", result);

        cv::waitKey(0);
    }

    else {
        cout << "Modo Video" << endl;

        cv::VideoCapture vid;
        vid.open(0);

        if (!vid.isOpened()) {
            cerr << "Error opening input." << endl;
            return 1;
        }

        while (1) {
            vid >> img;

            cv::Mat result;
            processImage(result, img);

            cv::imshow("Video", img);
            cv::imshow("Modified video", result);
            if (cv::waitKey(10) != -1)
                break;
        }
        vid.release();
    }

    return 0;
}


/*--------------------------------------------------------------*/

void processImage(cv::Mat& dst, cv::Mat& src) {

    cv::Mat mod_img;
    cv::cvtColor(src, mod_img, cv::COLOR_BGR2YCrCb);
    cv::Mat* roi;

    //aqui seleccionamos una subseccion
    if (flag_f) {
        roi = new cv::Mat(mod_img, cv::Rect(x, y, w, h));
    }
    else {
        roi = new cv::Mat(mod_img, cv::Rect(0, 0, mod_img.size().width, mod_img.size().height));
    }

    if (gamma_mode == G_MODE::M1) {
        table_creator();
    }

    // implementa correccion gamma segun parametro m1 o m2
    correccionGamma(*roi);
    cv::cvtColor(mod_img, dst, cv::COLOR_YCrCb2BGR);

    //dibujo de rectangulo
    if (flag_c) {
        cv::rectangle(dst, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(b, g, r), 2);
    }
    // rectangulo debe ser negro
    else {
        cv::rectangle(dst, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 0, 0), 2);
    }
}


void correccionGamma(cv::Mat& img) {

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

}

void table_creator() {
    for (int i = 0; i <= 255; i++) {
        table[i] = (uchar) 255 * pow((double)i / 255, g_gamma);
    }
}

int argv_manager(int argc, char* argv[]) {

    /* Minimo de argumentos requeridos */
    if (argc < 4) {
        return 1;
    }

    /* Hace un loop por el resto de los argumentos */
    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-m1") == 0) {
            gamma_mode = G_MODE::M1;
            continue;
        }
        if (strcmp(argv[i], "-m2") == 0) {
            gamma_mode = G_MODE::M2;
            continue;
        }
        if (strcmp(argv[i], "-i") == 0) {
            proc_mode = P_MODE::IMAGE;
            if (argc >= 5) {
                img = cv::imread(argv[i + 1], 1);
                g_gamma = std::stod(argv[i + 2]);
            }
            i += 2;
            assert(g_gamma >= 0);
            continue;
        }
        if (strcmp(argv[i], "-v") == 0) {
            proc_mode = P_MODE::VIDEO;
            if (argc >= 4) {
                g_gamma = std::stod(argv[i + 1]);
            }
            i++;
            assert(g_gamma >= 0);
            continue;
        }
        if (strcmp(argv[i], "-f") == 0) {
            flag_f = true;
            if ((proc_mode == P_MODE::VIDEO && argc >= 9) || (proc_mode == P_MODE::IMAGE && argc >= 10)) {
                x = atoi(argv[i + 1]);
                y = atoi(argv[i + 2]);
                w = atoi(argv[i + 3]);
                h = atoi(argv[i + 4]);
                i += 4;
                continue;
            }
        }
        if (strcmp(argv[i], "-c") == 0) {
            flag_c = true;
            if ((proc_mode == P_MODE::VIDEO && argc == 13) || (proc_mode == P_MODE::IMAGE && argc == 14)) {
                r = atoi(argv[i + 1]);
                g = atoi(argv[i + 2]);
                b = atoi(argv[i + 3]);
                i += 3;
                continue;
            }
        }
        return 1;
    }
}


/* Funcion que imprime el menu de ayuda */
int help() {
    cerr << "Usage: ./GAMMA [-m1 | m2] -i image gamma [-f x y w h] [-c r g b]" << endl;
    cerr << "\t-m1: \tUsar tabla precalculada" << endl;
    cerr << "\t-m2: \tUsar calculo directo" << endl;
    cerr << "\t-i: \tModo imagen" << endl;
    cerr << "\t-v: \tModo video" << endl;
    cerr << "\timage: \tRuta de imagen a procesar" << endl;
    cerr << "\tgamma: \tNivel de correccion gamma, debe ser > 0" << endl;
    cerr << "\t-f: \t(Opcional) Se define el rectangulo con posicion (x,y) y dimensiones (w,h) al cual" << endl;
    cerr << "\t\t\t   se le aplica la correcion gamma. El resto se considera como borde." << endl;
    cerr << "\t-c: \t(Opcional) Color (r,g,b) del borde. Si no se define se utiliza negro." << endl;
    return 1;
}
