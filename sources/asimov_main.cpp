#include "main_asimov.h"
#include "asimov_library.h"
#include "ui_main_asimov.h"
#include <QFileDialog>
#include <QMessageBox>


main_asimov::main_asimov(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_asimov)
{
    ui->setupUi(this);
    ui->title_label->setText("");
}

main_asimov::~main_asimov()
{
    delete ui;
}

void main_asimov::on_actionAbrir_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Título del Menú", "./", "All (*.*)");
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    QTextStream ReadFile(&file);
    QString fileContent = ReadFile.readAll();

    // Limpiar el contenido actual del QTextEdit
    ui->textBody->clear();

    ui->textBody->insertPlainText(fileContent);
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
            /* Aquí usammos la función mid para obtener una subcadena que comience justo después de la
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
    int index;

    int num_metanodos = texto.count(keyM);
    QVector<TModelMetabolite> metanodos;

    if (num_metanodos==0) // No hay metanodos en el texto seleccionado
    {
        ui->selectData->append("No se encontraron metanodos");
    }
    else // Sí hay metanodos
    {
        for (int i=1; i<=num_metanodos; i++)
        {
            // Por cada metanodo encontrado, recogemos sus datos usando section
            info_metanodo = texto.section(keyM, i, i);

            //Separamos por tabulaciones
            elementosM = info_metanodo.split("\t");

            //Eliminamos otros elementos tales como saltos de linea y otros
            for (QString& elementoM : elementosM) {
                elementoM = elementoM.simplified();
            }
            elementosM.removeAll("");

            // Comprobación del índice y recogida de datos
            index = elementosM.value(0, "").toInt();
            if ( index == elementosM.value(2, "").toInt() && index == i)
            {
                name = elementosM.value(1, "");
                id = elementosM.value(3, "");
                valor_ini_str = elementosM.value(4, "");
                valor_max_str = elementosM.value(5, "");
                valor_min_str = elementosM.value(6, "");
                precision_str = elementosM.value(7, "");
            }
            else
            {
                ui->selectData->append("Error al obtener el METANODO" + QString::number(i));
            }

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
            TModelMetabolite metanodo = TModelMetabolite(name, id, index, valor_ini, valor_max, valor_min, valor_ini, precision, false);
            metanodos.push_back( metanodo );
        }

        // Una vez recogida la info de todos los metanodos, mostramos los datos por pantalla
        for (int i=0; i<metanodos.size(); i++)
        {
            ui->selectData->append("METANODO " + QString::number(i+1));
            ui->selectData->append("nombre: " + metanodos[i].getName());
            ui->selectData->append("id: " + metanodos[i].getId());
            ui->selectData->append("index: " + QString::number(metanodos[i].getIndex()));
            ui->selectData->append("valor inicial: " + QString::number(metanodos[i].getInitValue()));
            ui->selectData->append("valor maximo: " + QString::number(metanodos[i].getTopValue()));
            ui->selectData->append("valor minimo: " + QString::number(metanodos[i].getBottomValue()));
            ui->selectData->append("precision: " + QString::number(metanodos[i].getPrecision()));
            ui->selectData->append("tag: " + QString::number(metanodos[i].getTag()) + "\n");
        }
    }
}


void main_asimov::on_parameter_button_clicked()
{
    QString texto = ui->textBody->toPlainText();
    QString keyP = "PARAMETER";
    int num_parameters = texto.count(keyP);

    QString description, id, value, precision;
    QString info_param;
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

            //Separamos por tabulaciones
            QStringList elementos = info_param.split("\t");

            //Eliminamos otros elementos tales como saltos de linea y otros
            for (QString& elemento : elementos) {
                elemento = elemento.simplified();
            }
            elementos.removeAll("");

            // Comprobación del índice y recogida de datos
            int index = elementos.value(0, "").toInt();
            if ( index == elementos.value(2, "").toInt() && index == i)
            {
                description = elementos.value(1, "");
                id = elementos.value(3, "");
                value = elementos.value(4, "");
                precision = elementos.value(5, "");
            }
            else
            {
                ui->selectData->append("Error al obtener el PARAMETRO" + QString::number(i));
            }

            // Creamos el parametro y lo añadimos a la lista de parametros
            TModelParameter param = TModelParameter(index, id, description, value.toDouble(), precision.toDouble(), false);
            parameters.push_back(param);
        }

        // Una vez recogida la informacion, mostramos los datos por pantalla
        for (int i=0; i<parameters.size(); i++){
            ui->selectData->append("PARAMETRO " + QString::number(i+1));
            ui->selectData->append("id: " + parameters[i].getId());
            ui->selectData->append("description: " + parameters[i].getDescription());
            ui->selectData->append("value: " + QString::number(parameters[i].getValue()));
            ui->selectData->append("precision: " + QString::number(parameters[i].getPrecision()));
            ui->selectData->append("tag: " + QString::number(parameters[i].getTag()) + "\n");
        }
    }
}