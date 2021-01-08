#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

#include "loadwin.h"
#include "segFunctions.h"
#include "Projection.h"
#include "LaneDetection.h"
#include "racingLine.h"
#include "mapGeneration.h"
#include "Matrix.h"
#include "polyfit.h"

// Defines
#define csvSkip 1 //las lineas que se salta en la lectura del .csv
#define nColsCSV 6 // Numero columnas archivo csv
#define trackSkip 2 // skip 2 mask in trackfiles
#define nColsTrack 6 // número de columnas de lectura en .TRACK
#define windowRes 60 // Resolucion corte periférico
#define MODO_IMG false
#define MODO_VID true


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString filename;
    QString filenameUDP;

signals:
    void updateBar(int);

private slots:
    void on_videoButton_clicked();
    void on_csvButton_clicked();
    void on_trackSelection_currentIndexChanged(int index);
    void on_actionAbout_this_project_triggered();
    void on_exitButton_clicked();
    void on_runButton_clicked();
    void on_videoPath_textChanged(const QString &arg1);
    void on_csvPath_textChanged(const QString &arg1);
    void on_runvideoButton_clicked();

    void on_runvideoButton_clicked();

private:
    Ui::MainWindow *ui;
    LoadWin *lwin;

	void mainProcessing(std::string, cv::Mat&, std::string, bool mode = false);
	cv::Mat frameProcessing(cv::Mat&, std::vector<float>);


};
#endif // MAINWINDOW_H
