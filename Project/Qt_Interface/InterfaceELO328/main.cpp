#include "mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QIcon>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("F1 Trainning");
    w.setFixedSize(720, 480);
    w.setWindowIcon(QIcon("../InterfaceELO328/icon.jpg"));

    w.show();
    return a.exec();
}
