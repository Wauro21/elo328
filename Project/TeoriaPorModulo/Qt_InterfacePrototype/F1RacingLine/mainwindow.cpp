#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include "mainProcessing.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Load default track icon */
    QPixmap imagen;
    imagen.load("../F1RacingLine/GUI_IMG/icon_track0.jpg");
    ui->trackViewer->setPixmap(imagen);
}


void MainWindow::on_videoButton_clicked()
{
    filename = QFileDialog::getOpenFileName(
                this, tr("Open File"), "../F1RacingLine/Dataset/img",
                tr("Images (*.png *.jpeg *.jpg *.bmp)"));
    ui->videoPath->setText(filename);
}

void MainWindow::on_csvButton_clicked()
{
    filenameUDP = QFileDialog::getOpenFileName(
                this, tr("Open File"), "../F1RacingLine/Dataset/csv",
                tr("Comma Separted Values (*.csv)"));
    ui->csvPath->setText(filenameUDP);
}

void MainWindow::on_runButton_clicked()
{
    std::string inputIMG = filename.toStdString();
    cv::Mat img = cv::imread(inputIMG.c_str());
    cv::Mat out;
    if(img.empty()){
        std::cerr << "Error opening image" << std::endl;
    }
    else{
        //cv::imshow("Input Image", img);
        mainProcessing(img, out);
        cv::imshow("Result", out);
        cv::waitKey(0);
    }
}

void MainWindow::on_trackSelection_currentIndexChanged(int index)
{
    QString file = "../F1RacingLine/GUI_IMG/icon_track";
    file += QString::number(index) + ".jpg";

    QPixmap trackIcon;
    trackIcon.load(file);
    ui->trackViewer->setPixmap(trackIcon);
}

void MainWindow::on_actionAbout_this_project_triggered()
{
    QMessageBox about;
    about.setWindowTitle("About This Project");
    about.setText("Proyecto ELO328 - 2020.S2\n"
                  "Sistema de Reconocimiento de Pista de F1\n\n"
                  "Autores: \tMauricio Aravena\n"
                  "\tDiego Badillo\n"
                  "\tSteev Gonzalez\n"
                  "\tSebastian Neira\n"
                  "\tFelipe Villenas");
    about.exec();
}

MainWindow::~MainWindow(){ delete ui; }
void MainWindow::on_exitButton_clicked(){ this->close(); }
void MainWindow::on_videoPath_textChanged(const QString &arg1){ filename = arg1; }
void MainWindow::on_csvPath_textChanged(const QString &arg1){ filenameUDP = arg1; }
