#ifndef LOADWIN_H
#define LOADWIN_H

#include <QDialog>
#include <QProgressBar>

namespace Ui {
class LoadWin;
}

class LoadWin : public QDialog
{
    Q_OBJECT

public:
    explicit LoadWin(QWidget *parent = nullptr);
    ~LoadWin();
    QProgressBar *pBar;

private:
    Ui::LoadWin *ui;
};

#endif // LOADWIN_H
