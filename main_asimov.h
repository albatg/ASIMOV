/**
 *@file main_asimov.h
 *@version 1.0
 *@date 22/02/2024
 *@author Grupo ASIMOV
 *@title Librería para proyecto interdisciplinar de modelización del proceso de la glucólisis en una célula
*
*/

#ifndef MAIN_ASIMOV_H
#define MAIN_ASIMOV_H

#include <QMainWindow>
#include "asimov_library.h"
#include <help_dialog.h>
#include <QProcess>

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
    /**
     * @brief Abre un cuadro de diálogo para que el usuario seleccione un archivo y carga su contenido en el área de texto.
     * @details Utiliza un objeto rawInput para gestionar la carga del archivo.
     */
    void on_actionAbrir_triggered();

    /**
     * @brief Abre un cuadro de diálogo para que el usuario seleccione la ubicación y el nombre del archivo para guardar
     *        el contenido del área de texto en ese archivo.
     * @details Utiliza un cuadro de diálogo para la selección de la ubicación y nombre del archivo además de
     *          un objeto QFile para escribir en el archivo seleccionado.
     */
    void on_actionGuardar_triggered();

    /**
     * @brief Procesa el contenido del área de texto en busca de secciones clave (HEAD, DESCRIPTION)
     *        y muestra la información correspondiente en un QLabel.
     * @details Itera sobre una lista de palabras clave, busca las secciones en el contenido del área de texto
     *          y muestra la información en un QLabel.
     */

    void getParagraph();

    void clearAll();

    std::vector<std::string> split(const std::string& s, char delimiter);

    /**
     * @brief elimina los espacios, retornos de carro,saltos de línea y tabulaciones al principio y final de una cadena
     */
    std::string trim(const std::string& str);

    /**
     * @brief elimina los espaciosde dentro de una cadena (nos interesa para los formalismos)
     */
    std::string trimStringSpaces(const std::string& str);

    bool isDelimiter(char c);

    void processKeyword(std::string &keyword,std::string info);

    void on_actionNuevo_2_triggered();

    void on_helpButton_clicked();

    void runScript(std::string ecuacion, std::string Xo, float t_ini, float t_fin, int ciclos);

    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void on_calculate_button_clicked();

    void updateSource();

private:
    Ui::main_asimov *ui;
    HelpDialog *helpDialog;
    TRawInput rawInput;
    std::string head_file;
};
#endif // MAIN_ASIMOV_H
