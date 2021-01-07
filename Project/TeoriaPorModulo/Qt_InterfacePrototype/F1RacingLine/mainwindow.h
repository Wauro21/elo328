#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include "loadwin.h"

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

private:
    Ui::MainWindow *ui;
    LoadWin *lwin;

};
#endif // MAINWINDOW_H
