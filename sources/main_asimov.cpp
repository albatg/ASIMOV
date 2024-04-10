/**
 *@file main_asimov.cpp
 *@version 1.0
 *@date 22/02/2024
 *@author Grupo ASIMOV
 *@title Implementación de funciones usadas por la UI
*/

#include "main_asimov.h"
#include "ui_main_asimov.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>



//pushButton_2
main_asimov::main_asimov(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_asimov)
{
    ui->setupUi(this);
    setWindowTitle("ASIMOV");

    ui->title_label->setText("");

    ui->menubar->setCornerWidget(ui->helpButton);


}

main_asimov::~main_asimov()
{
    delete ui;
}

void main_asimov::on_actionAbrir_triggered()
{
     // Solicita al usuario que seleccione un archivo
    QString fname = QFileDialog::getOpenFileName(this, "Título del Menú", "./", "All (*.*)");

    if (fname.isEmpty()) {
        // El usuario canceló la selección del archivo
        return;
    }
    // Establece la fuente de datos con la ruta del archivo seleccionado
    rawInput.setSource(fname);

    // Intenta cargar el contenido del archivo
    bool loaded = rawInput.loadFromFile();

    // Verifica si la carga tuvo éxito
    if (!loaded) {
        QMessageBox::warning(this, "Error", "No se pudo cargar correctamente el archivo.");
        return;
    }

      // Accede al contenido cargado y lo muestra en el widget de texto
    QString rawData = rawInput.getSource();

    ui->textBody->clear();
    ui->textBody->setText(rawData);
}


void main_asimov::on_actionGuardar_triggered(){
    // Obtén el texto del QTextEdit
    QString textToSave = ui->textBody->toPlainText();

    // Asigna el texto al TRawInput
    rawInput.setSource(textToSave);

    rawInput.setToFile();
}


void main_asimov::on_pushButton_clicked()
{
    //Recupera contenido en el área de texto textBody
    QString fileContent = ui->textBody->toPlainText();

    // Lista de palabras clave
    QStringList keywords = {"HEAD", "DESCRIPTION"};

    // Texto para el label
    QString labelText;

    // Itera sobre la lista de palabras clave buscando cuáles coinciden
    foreach (const QString &keyword, keywords) {
        //Busca la posición de la palabra clave dentro del contenido del archivo
        int keywordIndex = fileContent.indexOf(keyword);
        //Si ha encontrado la palabra (diferente ded -1, que es lo que devoldería si no encuentra nada)
        if (keywordIndex != -1) {
            /* Aquí usammos la función mid para obtenre una subcadena que comience justo después de la
             * palabra clave.
             * keywordIndex es la posición donde comienza y le sumamos su longitud
             */
            QString sectionAfterKeyword = fileContent.mid(keywordIndex + keyword.length());

            // Buscar el índice de la próxima línea después de la palabra clave
            int nextLineIndex = sectionAfterKeyword.indexOf('\n');
            //Si lo encontramos
            if (nextLineIndex != -1) {
                // Coge la subcadena y corta a partir del salto de línea
                QString sectionText = sectionAfterKeyword.left(nextLineIndex).trimmed();

                // Agrega el texto al label solo si es después de "HEAD" o "DESCRIPTION"
                if (keyword == "HEAD" || keyword == "DESCRIPTION") {
                    labelText += sectionText + "\n\n";
                }
            }
        }
    }

    // Mostrar el texto en el label
    ui->title_label->setText(labelText.trimmed().toUpper());
    ui->title_label->setAlignment(Qt::AlignCenter);
}


/*
 *  Botón para extraer de los datos la info de los METANODOS
 *  y mostrarla por la ventana de salida
 */
void main_asimov::on_buttomMetanode_clicked()
{
    // Variables
    QString texto = ui->textBody->document()->toPlainText();
    QString keyM = "METANODE";

    QString info_metanodo;
    QStringList elementosM;
    QString nd = "nd";
    QString name, id, valor_ini_str, valor_max_str, valor_min_str, precision_str;
    double valor_ini, valor_max, valor_min, precision;

    int num_metanodos = texto.count(keyM);
    QVector<TModelMetabolite> metanodos;

    if (num_metanodos==0) // No hay metanodos en el texto seleccionado
    {
        ui->selectData->append("No se encontraron metanodos");
    }
    else // Sí hay metanodos
    {
        for (int i=1; i<num_metanodos; i++)
        {
            // Por cada metanodo encontrado, recogemos sus datos usando section
            info_metanodo = texto.section(keyM, i, i);
            //Separamos por tabulaciones
            elementosM = info_metanodo.split("\t");
            //Eliminamos otros elementos tales como saltos de linea y otros
            for (QString& elementoM : elementosM) {
                elementoM = elementoM.simplified();
            }
            //Eliminamos cadenas en blanco
            elementosM.removeAll("");

            //Escogemos los que nos interesan
            for (int j = 0; j < elementosM.size(); j += 6) {
                name = elementosM.value(j, "");
                id = elementosM.value(j+1, "");
                valor_ini_str = elementosM.value(j+2, "");
                valor_max_str = elementosM.value(j+3, "");
                valor_min_str = elementosM.value(j+4, "");
                precision_str = elementosM.value(j+5, "");

                // falta comprobar que el id es único para cada metanodo!!!

                // si algún dato numérico es nd, ponemos su valor por defecto
                if (valor_ini_str == nd)
                    valor_ini = 0;
                else
                    valor_ini = valor_ini_str.toDouble();

                if (valor_max_str == nd)
                    valor_max = INT_MAX;
                else
                    valor_max = valor_max_str.toDouble();

                if (valor_min_str == nd)
                    valor_min = 0;
                else
                    valor_min = valor_min_str.toDouble();

                if (precision_str == nd)
                    precision = 0.0000001;
                else
                    precision = precision_str.toDouble();

                // Creamos el metanodo y lo añadimos a la lista de metanodos
                TModelMetabolite metanodo = TModelMetabolite(name, id, valor_ini, valor_max, valor_min, valor_ini, precision, false);
                metanodos.push_back( metanodo );
            }
        }

        // Una vez recogida la info de todos los metanodos, mostramos los datos por pantalla
        for (int i=0; i<metanodos.size(); i++){
            ui->selectData->append("METANODO " + QString::number(i+1));
            ui->selectData->append("nombre: " + metanodos[i].getName());
            ui->selectData->append("id: " + metanodos[i].getId());
            ui->selectData->append("valor inicial: " + QString::number(metanodos[i].getInitValue()));
            ui->selectData->append("valor maximo: " + QString::number(metanodos[i].getTopValue()));
            ui->selectData->append("valor minimo: " + QString::number(metanodos[i].getBottomValue()));
            ui->selectData->append("precision: " + QString::number(metanodos[i].getPrecision()));
            ui->selectData->append("tag: " + QString::number(metanodos[i].getTag()) + "\n");
        }
    }
}
/*
void main_asimov::on_parameter_button_clicked()
{
    QString texto = ui->textBody->toPlainText();
    QString keyP = "PARAMETER";
    int num_parameters = texto.count(keyP);

    QString param_out;
    QString info_param;
    std::vector<TModelParameter> lista;
    QVector<TModelParameter> parameters;

    if (num_parameters==0) // No hay parametros en el texto seleccionado
    {
        ui->selectData->append("No se encontraron parametros");
    }
    else //En caso de que sí haya parámetros
    {
        for (int i=1; i<=num_parameters; i++)
        {
            // Por cada parametro encontrado, recogemos sus datos usando section
            info_param = texto.section(keyP, i, i);
             qDebug() << info_param;
            //Separamos por tabulaciones
            QStringList elementos = info_param.split("\t");
            //Eliminamos otros elementos tales como saltos de linea y otros
            for (QString& elemento : elementos) {
                elemento = elemento.simplified();
            }
            //Eliminamos cadenas en blanco
            elementos.removeAll("");


            for (const QString& elem : elementos) {
                qDebug() << elem;
            }
            //Escogemos los que nos interesan
            for (int j = 0; j < elementos.size(); j += 6) {
                QString description = elementos.value(j + 1, "");
                QString id = elementos.value(j + 3, "");
                QString value = elementos.value(j + 4, "");
                QString precision = elementos.value(j + 5, "");

                // Creamos el parametro y lo añadimos a la lista de parametros
                TModelParameter param = TModelParameter(id, description, value.toDouble(), precision.toDouble(), false);
                parameters.push_back(param);
            }
        }

        // Una vez recogida la información, mostramos los datos por pantalla
        for (int i=0; i<num_parameters; i++){
            ui->selectData->append("PARAMETRO " + QString::number(i+1));
            ui->selectData->append("index: " + QString::number(parameters[i].getIndex()));
            ui->selectData->append("id: " + parameters[i].getId());
            ui->selectData->append("description: " + parameters[i].getDescription());
            ui->selectData->append("value: " + QString::number(parameters[i].getValue()));
            ui->selectData->append("precision: " + QString::number(parameters[i].getPrecision()));
            ui->selectData->append("tag: " + QString::number(parameters[i].getTag()) + "\n");
        }
    }
}
*/


void main_asimov::processKeyword(QString &keyword,QString info){
   // QVector<TModelParameter> parameters;
    QStringList elementos = info.split("\t");

    //Eliminamos otros elementos tales como saltos de linea y otros
    for (QString& elemento : elementos) {
        elemento = elemento.simplified();
    }
    //Eliminamos cadenas en blanco
    elementos.removeAll("");

  // qDebug() << keyword << "\n";
    if(keyword == "PARAMETER"){

        for (const QString &elemento : elementos) {
            qDebug() << elemento;
        }

        QString description = elementos.value(2, "");
        QString id = elementos.value(4, "");
        QString value = elementos.value(5, "");
        QString precision = elementos.value(6, "");

        // Creamos el parametro y lo añadimos a la lista de parametros
        TModelParameter param = TModelParameter(id, description, value.toDouble(), precision.toDouble(), false);
        parameters.push_back(param);

    }else if(keyword == "METANODE"){

        QString nd = "nd";
        QString name = elementos.value(2, "");
        QString id = elementos.value(3, "");
        QString valor_ini_str = elementos.value(4, "");
        QString valor_max_str = elementos.value(5, "");
        QString valor_min_str = elementos.value(6, "");
        QString precision_str = elementos.value(7, "");

        double valor_ini, valor_max, valor_min, precision;

        // falta comprobar que el id es único para cada metanodo!!!

        // si algún dato numérico es nd, ponemos su valor por defecto
        if (valor_ini_str == nd)
            valor_ini = 0;
        else
            valor_ini = valor_ini_str.toDouble();

        if (valor_max_str == nd)
            valor_max = INT_MAX;
        else
            valor_max = valor_max_str.toDouble();

        if (valor_min_str == nd)
            valor_min = 0;
        else
            valor_min = valor_min_str.toDouble();

        if (precision_str == nd)
            precision = 0.0000001;
        else
            precision = precision_str.toDouble();

        // Creamos el metanodo y lo añadimos a la lista de metanodos
        TModelMetabolite metanodo = TModelMetabolite(name, id, valor_ini, valor_max, valor_min, valor_ini, precision, false);
        metanodos.push_back( metanodo );
    }
}


void main_asimov::on_parameter_button_clicked(){
    QString texto = ui->textBody->toPlainText();
    QStringList keywords = {"HEAD", "DESCRIPTION", "REMARKS", "METANODE", "PARAMETER", "FORMALISM", "PROCESS", "EQUATION", "..."};

    int current_index = 0;
    QString keyword;

    while (current_index != -1) {
        int next_index = -1;
        for (const QString &kw : keywords) {
            int index = texto.indexOf(kw, current_index + 1); //current_index + 1 para que no haga bucle infinito y se atasque en la misma palabra
            // Si index != 1 es que encontró la palabra en el texto
            //  (next_index == -1 || index < next_index) para encontrar las palabras en orden en el que aparecen en el texto
            if (index != -1 && (next_index == -1 || index < next_index)) {
                next_index = index;
                //keyword = kw;
            }
        }
        //Sacamos la sección de la palabra que buscamos
        QString info_param = (next_index != -1) ? texto.mid(current_index, next_index - current_index) : texto.mid(current_index);
        info_param = info_param.trimmed();

        // Asignación de keyword después de info_param
        if (next_index != -1) {
            QStringList lines = info_param.split("\n", Qt::SkipEmptyParts);
            if (!lines.isEmpty()) {
                QString firstLine = lines.first().simplified();
                int spaceIndex = firstLine.indexOf(" ");
                if (spaceIndex != -1) {
                    keyword = firstLine.left(spaceIndex);
                } else {
                    keyword = firstLine;
                }
            }
        } else {
            keyword = info_param;
        }
       /* qDebug() << "Keyword: " << keyword;
        qDebug() << "Info_param: " << info_param;*/

        processKeyword(keyword,info_param);

        current_index = next_index;
    }

    //Esto no iría aquí, es de prueba
/*
    for (int i=0; i<parameters.size(); i++){
        ui->selectData->append("PARAMETRO " + QString::number(i+1));
        ui->selectData->append("index: " + QString::number(parameters[i].getIndex()));
        ui->selectData->append("id: " + parameters[i].getId());
        ui->selectData->append("description: " + parameters[i].getDescription());
        ui->selectData->append("value: " + QString::number(parameters[i].getValue()));
        ui->selectData->append("precision: " + QString::number(parameters[i].getPrecision()));
        ui->selectData->append("tag: " + QString::number(parameters[i].getTag()) + "\n");
    }*/

    for (int i=0; i<metanodos.size(); i++){
        ui->selectData->append("METANODO " + QString::number(i+1));
        ui->selectData->append("nombre: " + metanodos[i].getName());
        ui->selectData->append("id: " + metanodos[i].getId());
        ui->selectData->append("valor inicial: " + QString::number(metanodos[i].getInitValue()));
        ui->selectData->append("valor maximo: " + QString::number(metanodos[i].getTopValue()));
        ui->selectData->append("valor minimo: " + QString::number(metanodos[i].getBottomValue()));
        ui->selectData->append("precision: " + QString::number(metanodos[i].getPrecision()));
        ui->selectData->append("tag: " + QString::number(metanodos[i].getTag()) + "\n");
    }
}
void main_asimov::on_actionNuevo_2_triggered()
{
    // Llamamos para iniciar nuevo documento
    rawInput.newRawInput();

    // Limpiamos el contenido actual
    ui->title_label->clear();
    ui->textBody->clear();
    ui->selectData->clear();
}


void main_asimov::on_helpButton_clicked()
{
    helpDialog = new HelpDialog(this);
    helpDialog->show();
}

