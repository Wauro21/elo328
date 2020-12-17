#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Load default track icon */
    QPixmap imagen;
    imagen.load("../InterfaceELO328/icon_track0.jpg");
    ui->trackViewer->setPixmap(imagen);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(
                this, tr("Open File"), "../InterfaceELO328",
                tr("Images (*.png *.jpeg *.jpg *.bmp)"));
    ui->lineEdit->setText(filename);
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString file = "../InterfaceELO328/icon_track";
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
                  "Autores: Mauricio Aravena\n"
                  "\tDiego Badillo\n"
                  "\tSteev Gonzalez\n"
                  "\tSebastian Neira\n"
                  "\tFelipe Villenas");
    about.exec();
}

void MainWindow::on_pushButton_2_clicked()
{


}

void MainWindow::on_pushButton_4_clicked()
{
    filenameUDP = QFileDialog::getOpenFileName(
                this, tr("Open File"), "../InterfaceELO328",
                tr("Comma Separted Values (*.csv)"));
    ui->lineEdit_2->setText(filenameUDP);
}
