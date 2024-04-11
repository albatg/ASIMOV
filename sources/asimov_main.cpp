#include "main_asimov.h"
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
    QString fname = QFileDialog::getOpenFileName(this, "Título del Menú", "./", "All (*.*)");

    if (fname.isEmpty()) {
        // El usuario canceló la selección del archivo
        return;
    }

    rawInput.setSource(&fname);

    bool loaded = rawInput.loadFromFile();

    if (!loaded) {
        QMessageBox::warning(this, "Error", "No se pudo cargar correctamente el archivo.");
        return;
    }

    // Accede a los datos
    QString rawData = rawInput.getSource();

    ui->textBody->clear();
    ui->textBody->setText(rawData);
}


void main_asimov::on_actionGuardar_triggered(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar archivo"), "", tr("Archivos de texto (*.txt);;Todos los archivos (*)"));

    if (fileName.isEmpty()) {
        // El usuario canceló la operación
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("No se pudo abrir el archivo para escribir"));
        return;
    }

    QTextStream out(&file);
    out << ui->textBody->toPlainText(); // Guardar el contenido del QTextEdit en el archivo

    file.close();
    QMessageBox::information(this, tr("Éxito"), tr("Archivo guardado exitosamente"));
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

            //Eliminamos otros elementos tales como saltos de línea y otros
            for (QString& elementoM : elementosM) {
                elementoM = elementoM.simplified();
            }
            elementosM.removeAll("");

            // Comprobación del índice (único y correlativo) y recogida de datos
            index = elementosM.value(0, "").toInt();
            if ( index == elementosM.value(2, "").toInt() && index == i )
            {
                name = elementosM.value(1, "");
                id = elementosM.value(3, "");
                valor_ini_str = elementosM.value(4, "");
                valor_max_str = elementosM.value(5, "");
                valor_min_str = elementosM.value(6, "");
                precision_str = elementosM.value(7, "");

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
                TModelMetabolite metanodo = TModelMetabolite(index, name, id, valor_ini, valor_max, valor_min, valor_ini, precision, false);
                metanodos.push_back( metanodo );
            }
            else
            {
                ui->selectData->append("Error al obtener el METANODO" + QString::number(i));
            }
        }

        // Una vez recogida la info de todos los metanodos, mostramos los datos por pantalla
        for (int i=0; i<metanodos.size(); i++)
        {
            ui->selectData->append("METANODO " + QString::number(i+1));
            ui->selectData->append("nombre: " + metanodos[i].getName());
            ui->selectData->append("id: " + metanodos[i].getId());
            ui->selectData->append("index: " + QString::number(i+1));
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

            // Comprobación del índice (único y correlativo) y recogida de datos
            int index = elementos.value(0, "").toInt();
            if ( index == elementos.value(2, "").toInt() && index == i)
            {
                description = elementos.value(1, "");
                id = elementos.value(3, "");
                value = elementos.value(4, "");
                precision = elementos.value(5, "");

                // Creamos el parametro y lo añadimos a la lista de parametros
                TModelParameter param = TModelParameter(index, id, description, value.toDouble(), precision.toDouble(), false);
                parameters.push_back(param);
            }
            else
            {
                ui->selectData->append("Error al obtener el PARAMETRO" + QString::number(i));
            }
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

void main_asimov::on_formalism_button_clicked()
{
    // Variables
    QString texto = ui->textBody->document()->toPlainText();
    QString keyF = "FORMALISM";
    QString info_formalism;
    QStringList elementosF;
    int num_formalisms = texto.count(keyF);
    QVector<TFormalism> formalisms;

    if (num_formalisms==0) // No hay formalismos en el texto seleccionado
    {
        ui->selectData->append("No se encontraron formalismos");
    }
    else // Sí hay formalismos
    {
        for (int i=1; i<=num_formalisms; i++)
        {
            // Por cada formalismo encontrado, recogemos sus datos usando section
            info_formalism = texto.section(keyF, i, i);

            // Separamos por tabulaciones
            elementosF = info_formalism.split("\t", Qt::SkipEmptyParts);

            //Eliminamos otros elementos tales como saltos de linea y otros
            for (QString& elemento : elementosF) {
                elemento = elemento.simplified();
            }
            elementosF.removeAll("");

            // Recogida de datos
            QString m_id = elementosF.value(0, "");
            QString m_name = elementosF.value(1, "");

            QString formula_completa = elementosF.value(2, "");
            QStringList par = formula_completa.split('=');
            QString m_formalism = par.back().simplified();

            QStringList variables = par.first().split(',');
            variables[0] = variables.first().remove('(');
            variables[variables.size()-1] = variables.back().remove(')');
            std::vector<QString> m_variables;
            for (QString& var : variables)
            {
                var = var.simplified();
                m_variables.push_back(var);
            }

            // Creamos el objeto formalismo y lo añadimos a la lista de formalismos
            TFormalism form = TFormalism(m_id, m_name, m_formalism, m_variables);
            formalisms.push_back( form );
        }

        // Una vez recogida la info de todos los formalismos, mostramos los datos por pantalla
        for (int i=0; i<formalisms.size(); i++)
        {
            ui->selectData->append("FORMALISMO " + QString::number(i+1));
            ui->selectData->append("id: " + formalisms[i].getId());
            ui->selectData->append("nombre: " + formalisms[i].getName());
            ui->selectData->append("formalismo: " + formalisms[i].getFormalism());

            QString var_mostrar;
            std::vector<QString> var = formalisms[i].getVariables();

            for (unsigned int i=0; i<var.size(); i++)
                var_mostrar.append(var[i] + ", ");

            var_mostrar.chop(2);

            ui->selectData->append("variables: " + var_mostrar + "\n");
        }
    }
}


void main_asimov::on_process_button_clicked()
{
    // Variables
    QString texto = ui->textBody->document()->toPlainText();
    QString keyP = "PROCESS";
    QString info_process;
    QStringList elementosP;
    int num_process = texto.count(keyP);
    QVector<TProcess> processes;

    if (num_process==0) // No hay procesos en el texto seleccionado
    {
        ui->selectData->append("No se encontraron procesos");
    }
    else // Sí hay procesos
    {
        for (int i=1; i<=num_process; i++)
        {
            // Por cada proceso encontrado, recogemos sus datos usando section
            info_process = texto.section(keyP, i, i);

            // Separamos por tabulaciones
            elementosP = info_process.split("\t", Qt::SkipEmptyParts);

            //Eliminamos saltos de linea y otros espacios en blanco
            for (QString& elemento : elementosP) {
                elemento = elemento.simplified();
            }
            elementosP.removeAll("");

            // Recogida de datos
            QString m_id = elementosP.value(0, "");
            QString m_description = elementosP.value(1, "");
            QString m_name = elementosP.value(2, "");
            QString m_idForm = elementosP.value(3, "");
            QString substances = elementosP.value(4, "");

            QStringList subs = substances.split(',');
            subs[0] = subs.first().remove('(');
            subs[subs.size()-1] = subs.back().remove(')');
            std::vector<QString> m_substances;
            for (QString& s : subs)
            {
                s = s.simplified();
                m_substances.push_back(s);
            }

            // Creamos el objeto proceso y lo añadimos a la lista de procesos
            TProcess process = TProcess(m_id, m_name, m_description, m_idForm, m_substances);
            processes.push_back( process );
        }

        // Una vez recogida la info de todos los procesos, mostramos los datos por pantalla
        for (int i=0; i<processes.size(); i++)
        {
            ui->selectData->append("PROCESO " + QString::number(i+1));
            ui->selectData->append("id: " + processes[i].getId());
            ui->selectData->append("descripción: " + processes[i].getDescription());
            ui->selectData->append("nombre corto: " + processes[i].getName());
            ui->selectData->append("formalismo: " + processes[i].getIDForm());

            QString subs_mostrar;
            std::vector<QString> subs = processes[i].getSubstances();

            for (unsigned int i=0; i<subs.size(); i++)
                subs_mostrar.append(subs[i] + ", ");

            subs_mostrar.chop(2);

            ui->selectData->append("sustancias: " + subs_mostrar + "\n");
        }
    }
}
