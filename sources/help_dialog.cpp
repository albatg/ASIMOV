#include "help_dialog.h"
#include "ui_help_dialog.h"
#include <QMessageBox>

HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HelpDialog)
{
    cont = 1;

    ui->setupUi(this);
    setWindowTitle("ASIMOV AYUDA");

    ui->help_title->setText("PALABRAS CLAVE");
    ui->help_title->setStyleSheet("color: black");
    ui->previous_button->hide();
    ui->warning_label->setText("");

    setFixedSize(500, 450);

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
    cont++;
    if(cont == cont_max){
        ui->next_button->hide();
        ui->help_title->setText("EJEMPLO");
        ui->warning_label->setStyleSheet("color: black");
        ui->warning_label->setText("ADVERTENCIA: En caso de que los índices no sean correlativos y/o el mismo metanodo/aparámetro tenga dos índices diferentes, se mostrará un mensaje de error");

        setFixedSize(1000,500);

        std::string filePath = "../ASIMOV/prueba_asimov.txt";
        setInfo(filePath);
    }
    ui->previous_button->show();
}


void HelpDialog::on_previous_button_clicked()
{
    cont--;
    if(cont == 1){
        ui->help_title->setText("PALABRAS CLAVE");
        ui->help_title->setStyleSheet("color: black");
        ui->previous_button->hide();
        ui->warning_label->setText("");

        setFixedSize(500, 450);

        std::string filePath = "../ASIMOV/palabras_clave.txt";
        setInfo(filePath);
    }
    ui->next_button->show();
}

