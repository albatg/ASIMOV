#include "help_dialog.h"
#include "ui_help_dialog.h"

HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    setWindowTitle("Help");

}

HelpDialog::~HelpDialog()
{
    delete ui;
}
