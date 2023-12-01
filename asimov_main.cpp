#include "asimov_main.h"
#include "./ui_asimov_main.h"

// ------------------------------------------------


asimov_Main::asimov_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::asimov_Main)
{
    ui->setupUi(this);
}

QString s2;
TRawInput entrada(&s2);

asimov_Main::~asimov_Main()
{
    delete ui;
}

void asimov_Main::on_pushButton_clicked()
{
    s2.append("A un panal de rica miel\n");
    s2.append("diez mil moscas acudieron y,\n");
    s2.append("por golosas, murieron,\n");
    s2.append("presas de patas en él\n");
    ui->textEdit->append(s2);
    ui->textEdit->append(s2);
    ui->textEdit->append("-----------------");
    s2 = ui->textEdit->document()->toPlainText();
    ui->textEdit->append(s2);

}


void asimov_Main::on_actionAbrir_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this, "Título del Menú ", "./", "All (*.*)");
    QFile file(fname);

    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream ReadFile(&file);
    ui->textEdit->setText(ReadFile.readAll());


}

