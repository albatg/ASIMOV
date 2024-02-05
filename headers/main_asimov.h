<<<<<<< HEAD
#ifndef MAIN_ASIMOV_H
#define MAIN_ASIMOV_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class main_asimov;
}
QT_END_NAMESPACE

class main_asimov : public QMainWindow
{
    Q_OBJECT

public:
    main_asimov(QWidget *parent = nullptr);
    ~main_asimov();

private slots:
    void on_actionAbrir_triggered();

    void on_pushButton_clicked();

    void on_buttomMetanode_clicked();

    void on_parameter_button_clicked();

private:
    Ui::main_asimov *ui;
};
#endif // MAIN_ASIMOV_H
=======
#ifndef MAIN_ASIMOV_H
#define MAIN_ASIMOV_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class main_asimov;
}
QT_END_NAMESPACE

class main_asimov : public QMainWindow
{
    Q_OBJECT

public:
    main_asimov(QWidget *parent = nullptr);
    ~main_asimov();

private slots:
    void on_actionAbrir_triggered();

    void on_pushButton_clicked();

    void on_buttomMetanode_clicked();

    void on_parameter_button_clicked();

private:
    Ui::main_asimov *ui;
};
#endif // MAIN_ASIMOV_H
>>>>>>> f8cdf54a662b80227b6b5cc66f79e72ded2c3cd0
