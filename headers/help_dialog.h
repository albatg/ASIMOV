#ifndef HELP_DIALOG_H
#define HELP_DIALOG_H

#include <QDialog>
#include <asimov_library.h>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

private slots:
    void setInfo(std::string filePath);
    void on_next_button_clicked();

    void on_previous_button_clicked();

private:
    Ui::HelpDialog *ui;
    TRawInput help_rawInput;
    int cont;
    const int cont_max = 2;
};

#endif // HELP_DIALOG_H
