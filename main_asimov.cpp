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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile(":/Diffnes.qss");

    if (styleSheetFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        a.setStyleSheet(styleSheet);
    } else {

        qDebug() << "Error al abrir la hoja de estilos.";
    }
    main_asimov w;
    w.show();
    return a.exec();
}

//pushButton_2
main_asimov::main_asimov(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_asimov)
{
    ui->setupUi(this);
    setWindowTitle("ASIMOV");

    // Conecta la señal textChanged() del QTextEdit a la ranura updateSource()
    connect(ui->textBody, &QTextEdit::textChanged, this, &main_asimov::updateSource);

    ui->title_label->setText("");
    ui->t_ini_label->setStyleSheet("color: black");
    ui->t_fin_label->setStyleSheet("color: black");
    ui->cycles_label->setStyleSheet("color: black");

    ui->menubar->setCornerWidget(ui->helpButton);
}

main_asimov::~main_asimov()
{
    delete ui;
}

void main_asimov::clearAll(){
    TModelMetabolite::clear();
    TModelParameter::clear();
    TFormalism::clear();
    TProcess::clear();
    TEquation::clear();
}

void main_asimov::on_actionAbrir_triggered() {

    clearAll();
    // Solicita al usuario que seleccione un archivo
    QString qFileName = QFileDialog::getOpenFileName(this, "Título del Menú", "./", "All (*.*)");

    // Convierte el nombre de archivo de QString a std::string
    std::string fileName = qFileName.toStdString();

    if (fileName.empty()) {
        // El usuario canceló la selección del archivo
        return;
    }

    if(!rawInput.getSource().empty())
        rawInput.newRawInput();
    else{
        // Establece la fuente de datos con la ruta del archivo seleccionado

        rawInput.setSource(fileName);
        // Intenta cargar el contenido del archivo

        bool loaded = rawInput.loadFromFile();

        // Verifica si la carga tuvo éxito
        if (!loaded) {
            QMessageBox::warning(this, "Error", "No se pudo cargar correctamente el archivo.");
            return;
        }

        // Accede al contenido cargado
        std::string rawData = rawInput.getSource();

        // Muestra el contenido cargado en el widget de texto
        ui->textBody->clear();
        //ui->selectData->clear();
        ui->textBody->setText(QString::fromStdString(rawData));

    }

}



void main_asimov::on_actionGuardar_triggered() {
    // Obtiene el texto del QTextEdit
    QString qTextToSave = ui->textBody->toPlainText();

    // Convierte el texto de QString a std::string
    std::string textToSave = qTextToSave.toStdString();

    // Asigna el texto al TRawInput
    rawInput.setSource(textToSave);

    // Guarda el contenido en un archivo
    rawInput.setToFile();
}


std::vector<std::string> main_asimov::split(const std::string& s, char delimiter) {
    //Vector para almacenar subcadenas
    /*std::vector<std::string> tokens;

    //Lee datos de una cadena como si fueran datos de un flujo de entrada estándar
    std::istringstream iss(s);

    // Variable para almacenar cada subcadena mientras se divide la cadena
    std::string token;

    //Lee la cadena de entrada y la divide usando el delimitador
    while (std::getline(iss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    //Devuelve el vector de subcadenas
    return tokens;*/

    std::vector<std::string> tokens;
    std::string currentToken;

    bool prevSpace = false;

    for (char c : s) {
        if (c == delimiter) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            if (prevSpace && !tokens.empty()) {

                tokens.push_back("");
            }
            prevSpace = true;
        } else if (c == ' ') {

            if (prevSpace && !currentToken.empty() && currentToken.back() != ' ') {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            prevSpace = true;
        } else {
            currentToken += c;
            prevSpace = false;
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;

    return tokens;
}
/*
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;

    while (getline(iss, token, delimiter)) {
        // Si el token no está vacío, agregarlo al vector de tokens
        if (!token.empty()) {
            // Dividir el token usando espacios consecutivos como delimitadores adicionales
            std::istringstream tokenStream(token);
            std::string word;
            while (getline(tokenStream, word, ' ')) {
                // Si la palabra no está vacía, agregarla al vector de tokens
                if (!word.empty()) {
                    tokens.push_back(word);
                }
            }
        }
    }

    return tokens;*/



std::string main_asimov::trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");

    if (first == std::string::npos || last == std::string::npos)
        return "";
    else
        return str.substr(first, last - first + 1);
}

std::string main_asimov::trimStringSpaces(const std::string& str){
    std::string result;
    for (char c : str) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    return result;
}

bool main_asimov::isDelimiter(char c) {

    return (c == '(' || c == ')' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/');
}

void main_asimov::processKeyword(std::string &keyword,std::string info){
    std::vector<std::string> elementos = split(info,'\t');
    //elementos = split(info,' '); // info.split("\t");

    //Eliminamos otros elementos tales como saltos de linea y otros
    for (std::string& elemento : elementos) {
        elemento.erase(std::remove(elemento.begin(), elemento.end(), '\n'), elemento.end());

    }
    // Eliminamos cadenas en blanco
    elementos.erase(std::remove(elementos.begin(), elementos.end(), ""), elementos.end());


    if(keyword == "HEAD"){
        elementos.erase(std::remove_if(elementos.begin(), elementos.end(), [](const std::string& str) {
                      return str.empty() || std::all_of(str.begin(), str.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); });
                  }), elementos.end());

        QString texto;
        for (const auto& str : elementos) {
            texto.append(QString::fromStdString(str));
        }
        ui->title_label->setText(texto);
        ui->title_label->setStyleSheet("color: black");


    }else if(keyword == "PARAMETER"){
        int index = (elementos.size() > 0) ? std::stoi(elementos.at(0)) : 0;
        std::string description, id, value, precision;

        if (index == ((elementos.size() > 2) ? std::stoi(elementos.at(2)) : 0)) {
            description = (elementos.size() > 1) ? elementos.at(1) : "";
            id = (elementos.size() > 3) ? elementos.at(3) : "";
            value = (elementos.size() > 4) ? elementos.at(4) : "";
            precision = (elementos.size() > 5) ? elementos.at(5) : "";

        }

        // Creamos una objeto de TModelParameter que se almacenará en su array interno
        TModelParameter param = TModelParameter(index,id, description, std::stod(value), std::stod(precision), false);

    }else if(keyword == "METANODE"){
        double valor_ini, valor_max, valor_min, precision;

        int index = (elementos.size() > 0) ? std::stoi(elementos.at(0)) : 0;

        if (index == std::stoi(elementos.at(2))){
            std::string nd = "nd";
            std::string name = (elementos.size() > 1) ? elementos.at(1) : "";
            std::string id = (elementos.size() > 3) ? elementos.at(3) : "";
            std::string valor_ini_str = (elementos.size() > 4) ? elementos.at(4) : "";
            std::string valor_max_str = (elementos.size() > 5) ? elementos.at(5) : "";
            std::string valor_min_str = (elementos.size() > 6) ? elementos.at(6) : "";
            std::string precision_str = (elementos.size() > 7) ? elementos.at(7) : "";

            // Si algún dato numérico es "nd", asignamos su valor por defecto
            if (valor_ini_str == nd)
                valor_ini = 0.0;
            else
                valor_ini = std::stod(valor_ini_str);

            if (valor_max_str == nd)
                valor_max = std::numeric_limits<double>::max();
            else
                valor_max = std::stod(valor_max_str);

            if (valor_min_str == nd)
                valor_min = 0.0;
            else
                valor_min = std::stod(valor_min_str);

            if (precision_str == nd)
                precision = 0.0000001;
            else
                precision = std::stod(precision_str);

            // Creamos el metanodo
            TModelMetabolite metanodo = TModelMetabolite(index, name, id, valor_ini, valor_max, valor_min, valor_ini, precision, false);
        }
    }else if(keyword == "FORMALISM"){
        std::string m_id = (elementos.size() > 0) ? elementos.at(0) : "";
        std::string m_name = (elementos.size() > 1) ? elementos.at(1) : "";

        std::string formula_completa = (elementos.size() > 2) ? elementos.at(2) : "";
        std::vector<std::string> par = split(formula_completa, '=');
        std::string m_formalism = (!par.empty()) ? par.back() : "";


        std::vector<std::string> variables = split(par.front(), ',');
        if (!variables.empty())
        {
            variables.front().erase(std::remove(variables.front().begin(), variables.front().end(), '('), variables.front().end());
            variables.back().erase(std::remove(variables.back().begin(), variables.back().end(), ')'), variables.back().end());
        }
        std::vector<std::string> m_variables;
        for (std::string& var : variables)
        {
            var = trim(var);
            m_variables.push_back(var);

        }
        m_formalism = trimStringSpaces(m_formalism);

        // Creamos el objeto formalismo y lo añadimos a la lista de formalismos
        TFormalism form = TFormalism(m_id, m_name, m_formalism, m_variables);

    }else if(keyword == "PROCESS"){

        std::string m_id = (elementos.size() > 0) ? elementos.at(0) : "";
        std::string m_description = (elementos.size() > 1) ? elementos.at(1) : "";
        std::string m_name = (elementos.size() > 3) ?elementos.at(3) : "";
        std::string m_idForm = (elementos.size() > 4) ? elementos.at(4) : "";
        std::string substances = (elementos.size() > 5) ?elementos.at(5) : "";


        if (!substances.empty() && substances.front() == '(' && substances.back() == ')') {
            substances.erase(substances.begin()); // Elimina el paréntesis inicial
            substances.erase(substances.end() - 1); // Elimina el paréntesis final


        }
        std::vector<std::string> subs = split(substances, ',');

        std::vector<std::string> m_substances;
        for (std::string& s : subs) {
            s = trim(s);
            m_substances.push_back(s);
        }


        // Creamos el objeto proceso y lo añadimos a la lista de procesos
        TProcess process = TProcess(m_id, m_name, m_description, m_idForm, m_substances);

    }else if(keyword == "EQUATION"){

        int index = (elementos.size() > 0) ? std::stoi(elementos.at(0)) : 0;

        std::string eq = (elementos.size() > 1) ? elementos.at(1) : "";
        std::string expression = (elementos.size() > 2) ? elementos.at(2) : "";

        expression = trim(expression);
        std::string var;
        int pos_ini = eq.find('(');
        int pos_fin = eq.find(')');

        var = eq.substr(pos_ini + 1, (pos_fin - pos_ini) - 1);

        TEquation equation = TEquation(index, eq, var, expression );

    }
}
void main_asimov::getParagraph(){
    // Se obtiene el texto de entrada
    std::string texto = rawInput.getSource();
    // Definición de las palabras clave
    std::vector<std::string> keywords = {"HEAD", "DESCRIPTION", "REMARKS", "METANODE", "PARAMETER", "FORMALISM", "PROCESS", "EQUATION"};

    // Inicializamos el índice actual
    size_t current_index = 0;

    // Bucle hasta que no se encuentren más palabras clave
    // npos -> valor estático definido en la clase std::string (posición inválida o un valor no encontrado en una cadena).
    while (current_index != std::string::npos) {

        // Inicializamos el siguiente índice como no encontrado
        size_t next_index = std::string::npos;

        // Buscamos la siguiente palabra clave
        for (const std::string &kw : keywords) {
            size_t index = texto.find(kw, current_index + 1); // Empezamos la búsqueda después del índice actual
            // Verifica si la palabra clave actual es la primera encontrada o si se encuentra antes que la siguiente palabra clave en el texto
            if (index != std::string::npos && (next_index == std::string::npos || index < next_index)) {
                // Actualiza el siguiente índice con el valor del índice actual si se cumple la condición
                next_index = index;
            }
        }

        // Extraemos la información entre las palabras clave
        std::string info_param = (next_index != std::string::npos) ? texto.substr(current_index, next_index - current_index) : texto.substr(current_index);

        // Busca el primer carácter que no sea un espacio, una tabulación o un salto de línea desde el principio de info_param
        size_t trimmed_begin = info_param.find_first_not_of(" \t\n");
        // Busca el último carácter que no sea un espacio, una tabulación o un salto de línea desde el final de info_param
        size_t trimmed_end = info_param.find_last_not_of(" \t\n");

        // Se extrae la parte de la cadena entre estos índices para eliminar los espacios en blanco al principio y al final de la cadena.
        if (trimmed_begin != std::string::npos && trimmed_end != std::string::npos) {
            info_param = info_param.substr(trimmed_begin, trimmed_end - trimmed_begin + 1);
        } else {
            info_param = "";
        }

        // Buscamos la primera palabra clave dentro de la información
        std::string keyword;
        for (const std::string &kw : keywords) {
            size_t kw_index = info_param.find(kw);
            if (kw_index != std::string::npos) {
                keyword = kw;
                // Eliminar la palabra clave de info_param
                info_param.erase(kw_index, kw.length());
                break;
            }
        }

        // Procesar la palabra clave y la información
        processKeyword(keyword, info_param);


        // Actualizar el índice actual para la próxima iteración
        current_index = next_index;
    }

}
void main_asimov::on_calculate_button_clicked() {

    // Recogemos datos del archivo de entrada
    getParagraph();


    std::vector<TProcess> processes = TProcess::getProcesses();
    std::vector<TEquation> equations = TEquation::getEquations();
    std::vector<TModelMetabolite> meta = TModelMetabolite::getMetabolites();
    std::vector<TModelParameter> params = TModelParameter::getParams();
    std::vector<TEquation> eq = TEquation::getEquations();

    qDebug() << "eq size: " << eq.size();
    qDebug() << "params size: " << params.size();

    ErrorHandler::displayErrors();

    // Recogemos datos de la interfaz
    float t_ini = ui->t_ini_spinbox->value();
    float t_fin = ui->t_fin_spinbox->value();
    int cycles = ui->cycles_spinbox->value();

    // Argumento valores iniciales de los metabolitos

    std::vector<float> Xo;
    std::string XoString;

    /*for (size_t m = 0; m< meta.size(); m++)
        Xo.push_back(meta[m].getInitValue());*/

    for(int i = 0; i< eq.size(); i++){
        qDebug() << eq[i].getEquation();
        for(int j = 0; j < meta.size();j++){
            if(eq[i].getEquation().find(meta[j].getId()) != std::string::npos){
                qDebug() << "entra: " << meta[j].getInitValue();
                Xo.push_back(meta[j].getInitValue());
            }
        }
    }
    qDebug() << Xo.size();
    for (size_t i = 0; i < Xo.size(); ++i) {
        XoString += std::to_string(Xo[i]);
        if (i < Xo.size() - 1) {
            XoString += " ";
        }
    }

    // Argumento ecuaciones


    std::string ecuacion;
    std::string idMeta, idParam, sust;
    size_t pos = 0;
    size_t len = 0;
    std::string substr;



    // Colocamos los string de las m ecuaciones separadas por espacios
    for (size_t e = 0; e< eq.size(); e++){
        ecuacion.append(trimStringSpaces(eq[e].getEquationChanged()));
        ecuacion.append(" ");
    }

    qDebug() << "meta: " << meta.size();
    // Sustituimos metabolitos por x[]
    for (size_t m=0; m<meta.size(); m++){
        pos  = 0;
        sust = "x[" + std::to_string(m) + "]";
        idMeta = meta[m].getId();
        len = idMeta.length();

        pos = ecuacion.find(idMeta, pos);


        while( pos != std::string::npos && isDelimiter(ecuacion[pos + len]) ){
            ecuacion.replace(pos, len, sust);
            pos = ecuacion.find(idMeta, pos+len);
        }
    }

    // Sustituimos parámetros por su valor
   /* for (size_t m=0; m<params.size(); m++){
        pos  = 0;
        sust = "p[" + std::to_string(m) + "]";
        idParam = params[m].getId();
        len = idParam.length();

        pos = ecuacion.find(idParam, pos);


        while( pos != std::string::npos && isDelimiter(ecuacion[pos + len]) ){
            ecuacion.replace(pos, len, sust);
            pos = ecuacion.find(idParam, pos+len);
        }
    }*/

    for (size_t p=0; p< params.size(); p++){
        pos = 0;
        idParam = params[p].getId();
        len = idParam.length();
        pos = ecuacion.find(idParam, pos);

        while( pos != std::string::npos && isDelimiter(ecuacion[pos + len])){
            ecuacion.replace(pos, len, std::to_string(params[p].getValue()));
            pos = ecuacion.find(idParam, pos+len);
        }
    }
    runScript(ecuacion, XoString, t_ini, t_fin, cycles);
}


void main_asimov::on_actionNuevo_2_triggered()
{
    clearAll();

    // Llamamos para iniciar nuevo documento
    rawInput.newRawInput();

    // Limpiamos el contenido actual
    ui->title_label->clear();
    ui->textBody->clear();
    //ui->selectData->clear();
}

void main_asimov::updateSource() {
    // Actualiza m_source con el texto actual del QTextEdit
    rawInput.setSource(ui->textBody->toPlainText().toStdString());
}


void main_asimov::on_helpButton_clicked()
{
    helpDialog = new HelpDialog(this);
    helpDialog->show();
}
void main_asimov::runScript(std::string ecuacion, std::string Xo, float t_ini, float t_fin, int ciclos) {
    std::string scriptPath = "../ASIMOV/script.py";

    std::vector<std::string> arguments = {
        scriptPath,
        "--ecuacion", ecuacion,
        "--Xo", Xo,
        "--tini", std::to_string(t_ini),
        "--tfin", std::to_string(t_fin),
        "--ciclos", std::to_string(ciclos)
    };

    qDebug() << "Argumentos pasados al script de Python:";
    qDebug() << "--ecuacion" << ecuacion << "--Xo" << Xo << "--tini" << t_ini << "--tfin" << t_fin << "--ciclos" << ciclos;

    QProcess *process = new QProcess(this);
    connect(process, &QProcess::finished, this, &main_asimov::onProcessFinished);

    // Convertir el vector de argumentos a QStringList
    QStringList args;
    for (const auto& arg : arguments) {
        args << QString::fromStdString(arg);
    }

    // Inicia el proceso de Python con los argumentos
    qDebug() << "Iniciando proceso de Python...";
    process->start("python", args);
    if (!process->waitForStarted()) {
        qDebug() << "Error: No se pudo iniciar el proceso de Python.";
    }
}




void main_asimov::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (process) {
        qDebug() << "Proceso de Python finalizado con código de salida:" << exitCode;
        qDebug() << "Error estándar del proceso:" << process->readAllStandardError();
        qDebug() << "Salida estándar del proceso:" << process->readAllStandardOutput();
        process->deleteLater();  // Libera la memoria del proceso
    }
}


