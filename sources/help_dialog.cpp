#include "help_dialog.h"
#include "ui_help_dialog.h"
#include <QMessageBox>

HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    setWindowTitle("ASIMOV AYUDA");
    ui->help_title->setText("PALABRAS CLAVE");
    ui->help_title->setStyleSheet("color: black");
    ui->previous_button->hide();
    resize(500, 450);


    std::string filePath = "../ASIMOV/palabras_clave.txt";
    setInfo(filePath);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::setInfo(std::string filePath){
    help_rawInput.setSource(filePath);
    bool loaded = help_rawInput.loadFromFile();

    // Verifica si la carga tuvo éxito
    if (!loaded) {
        QMessageBox::warning(this, "Error", "No se pudo cargar correctamente el archivo.");
        return;
    }

    // Accede al contenido cargado
    std::string rawData = help_rawInput.getSource();

    // Muestra el contenido cargado en el widget de texto
    ui->help_body->clear();
    ui->help_body->setText(QString::fromStdString(rawData));
}

void HelpDialog::on_next_button_clicked()
{
    ui->previous_button->show();
    ui->help_title->setText("EJEMPLO");

    resize(1000, 500);

    std::string filePath = "../ASIMOV/prueba_asimov.txt";
    setInfo(filePath);
}


void HelpDialog::on_previous_button_clicked()
{
    ui->help_title->setText("PALABRAS CLAVE");
    resize(500, 450);
    std::string filePath = "../ASIMOV/palabras_clave.txt";
    setInfo(filePath);
}

