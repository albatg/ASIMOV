#ifndef ASIMOV_MAIN_H
#define ASIMOV_MAIN_H

#include <QMainWindow>
#include "asimov_library.h"
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class asimov_Main;
}
QT_END_NAMESPACE

class asimov_Main : public QMainWindow
{
    Q_OBJECT

public:
    asimov_Main(QWidget *parent = nullptr);
    ~asimov_Main();

private slots:
    void on_pushButton_clicked();

    void on_actionAbrir_triggered();

private:
    Ui::asimov_Main *ui;
};
#endif // ASIMOV_MAIN_H
