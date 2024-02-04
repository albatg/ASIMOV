#include "asimov_main.h"
#include "./ui_asimov_main.h"

// ------------------------------------------------

asimov_Main::asimov_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::asimov_Main)
{
    ui->setupUi(this);
}



asimov_Main::~asimov_Main()
{
    delete ui;
}

// ------------------------------------------------
/*
 *  Botón de prueba
 */
void asimov_Main::on_pushButton_clicked()
{
    QString s2;

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

// ------------------------------------------------
/*
 *  Opción del menú desplegable para ABRIR UN FICHERO
 *  de datos subiéndolo desde el ordenador
 */
void asimov_Main::on_actionAbrir_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this, "Título del Menú ", "./", "All (*.*)");
    QFile file(fname);

    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream ReadFile(&file);
    ui->textEdit->setText(ReadFile.readAll());
}

/*
 *  Botón para extraer de los datos la info de los METANODOS
 *  y mostrarla por la ventana de salida
 */
void asimov_Main::on_buttomMetanode_clicked()
{
    // Variables
    QString texto = ui->textEdit->document()->toPlainText();
    QString key = "METANODE";
    QString salida_metanodos;
    QString info_metanodo;
    QString nd = "nd";
    QString name, id, valor_ini_str, valor_max_str, valor_min_str, precision_str;
    double valor_ini, valor_max, valor_min, precision;
    int num_metanodos = texto.count(key);
    std::vector<TModelMetabolite> metanodos_recogidos;

    if (num_metanodos==0) // No hay metanodos en el texto seleccionado
    {
        ui->selectData->append("No se encontraron metanodos");
    }
    else // Sí hay metanodos
    {
        salida_metanodos.append("Metanodos encontrados:\n\n");

        for (int i=1; i<num_metanodos; i++)
        {
            // Por cada metanodo encontrado, recogemos sus datos
            info_metanodo = texto.section(key, i, i);
            salida_metanodos.append(info_metanodo);

            name          = info_metanodo.section("\t", 0, 0, QString::SectionSkipEmpty);
            id            = info_metanodo.section("\t", 1, 1, QString::SectionSkipEmpty);
            valor_ini_str = info_metanodo.section("\t", 2, 2, QString::SectionSkipEmpty);
            valor_max_str = info_metanodo.section("\t", 3, 3, QString::SectionSkipEmpty);
            valor_min_str = info_metanodo.section("\t", 4, 4, QString::SectionSkipEmpty);
            precision_str = info_metanodo.section("\t", 5, 5, QString::SectionSkipEmpty);

            // le quitamos el salto de línea que se guarda al final del nombre
            name.chop(1);

            // falta comprobar que el id es único para cada metanodo!!!!

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
                precision = 0.00001;
            else
                precision = precision_str.toDouble();

            // Creamos el metanodo y lo añadimos a la lista de metanodos
            TModelMetabolite metanodo = TModelMetabolite(name, id, valor_ini, valor_max, valor_min, valor_ini, precision, false);
            metanodos_recogidos.push_back( metanodo );

            // Mostramos la info detallada de cada metanodo por separado
            QString info_detallada = "- Nombre: ";
            info_detallada.append(metanodos_recogidos[i-1].getName());
            info_detallada.append(" - Id: ");
            info_detallada.append(metanodos_recogidos[i-1].getId());
            info_detallada.append(" - Valor inicial: ");
            info_detallada.append(std::to_string(metanodos_recogidos[i-1].getInitValue()));
            info_detallada.append(" - Valor max: ");
            info_detallada.append(std::to_string(metanodos_recogidos[i-1].getTopValue()));
            info_detallada.append(" - Valor min: ");
            info_detallada.append(std::to_string(metanodos_recogidos[i-1].getBottomValue()));
            info_detallada.append(" - Valor: ");
            info_detallada.append(std::to_string(metanodos_recogidos[i-1].getValue()));
            info_detallada.append(" - Precisión: ");
            info_detallada.append(std::to_string(metanodos_recogidos[i-1].getPrecision()));
            info_detallada.append(" - Etiqueta: ");
            info_detallada.append(std::to_string(metanodos_recogidos[i-1].getTag()));
            info_detallada.append("\n\n");
            salida_metanodos.append(info_detallada);
        }

        // Una vez recogida la info de todos los metanodos, mostramos los datos por pantalla
        ui->selectData->append(salida_metanodos);
    }
}

