#include "loadwin.h"
#include "ui_loadwin.h"

LoadWin::LoadWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadWin)
{
    this->setWindowTitle("Processing Video File");
    this->setFixedSize(400,200);
    ui->setupUi(this);
    pBar = ui->progressBar;
}

LoadWin::~LoadWin()
{
    delete ui;
}
