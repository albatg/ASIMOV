/**
 *@file asimov_library.cpp
 *@version 1.0
 *@date 22/02/2024
 *@author Grupo ASIMOV
 *@title Implementación de librería ASIMOV
*
*/

#ifndef ASIVMOV_LIBRARY_H
#define ASIVMOV_LIBRARY_H

#include "asimov_library.h"
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <fstream>

#endif // ASIVMOV_LIBRARY_H




// Constructor de la clase
TRawInput::TRawInput(std::string* v_source)
{
    // La variable que indica si el documento está cargado se pone a false como precaución
    m_loaded = false;
    // En caso de que v_source sea nulo, se asigna un nuevo objeto QString a m_source
    if (v_source == nullptr){
        m_source = new(std::string);
    } else{
        // Si v_source no es nulo, se asigna v_source a m_source y m_loaded pasa a ser true para indicar que se ha cargado un documento
        m_source = v_source;
        m_loaded = true;
    };
};

// Destructor de la clase
TRawInput::~TRawInput()
{
   // Liberamos la memoria asociada al objeto m_source
    delete m_source;
   // Asignamos el puntero a nullptr para evitar posibles problemas
    m_source = nullptr;
};

std::string TRawInput::getSource() {
    // En caso de que m_source no sea nullptr, devolvemos el contenido de m_source
    if (m_source != nullptr) {
        return *m_source;
    } else {
        // Caso donde m_source es nullptr, devolvemos un objeto QString vacío
        return std::string(); // Otra opción podría ser lanzar una excepción/devolver un valor predeterminado
    }
}

void TRawInput::setSource(const std::string& v_source)
{
    // Asignamos una nueva fuente de datos
    *m_source = v_source; // Copiamos el contenido del QString proporcionado

}

// Devuelve si hay una fuente cargada

bool TRawInput::getLoaded() {
    return m_loaded;
}

// Operación de carga desde archivo

bool TRawInput::loadFromFile() {
    // Verificamos si m_source está configurado y no vacío
    if (m_source == nullptr || m_source->empty()) {
        qDebug() << "Error: m_source no configurada o vacía";
        return false;
    }

    // Intentamos abrir el archivo en modo de solo lectura y texto
    std::ifstream file(*m_source);
    if (!file.is_open()) {
        qDebug() << "Error: no se pudo abrir el archivo" << *m_source;
        return false;
    }

    // Asignamos el contenido del archivo a m_source
    *m_source = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    // Marcamos m_loaded como true e indicamos que la carga desde el archivo fue exitosa
    m_loaded = true;

    // Cerramos el archivo después de leerlo
    file.close();

    return true;
}



void TRawInput::setToFile() {
    // QFileDialog para solicitar al usuario que seleccione o especifique un archivo para guardar
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Guardar archivo"), "", tr("Archivos de texto (*.txt);;Todos los archivos (*)"));

    if (fileName.isEmpty()) {
        // Por si el usuario cancela la operación
        return;
    }

    // Comprueba que m_source está inicializado y que contenga datos
    if (m_source == nullptr || m_source->empty()) {
        // Si m_source está vacío, muestra un mensaje de advertencia y no guarda el archivo
        QMessageBox::warning(nullptr, tr("Advertencia"), tr("El archivo está vacío"));
        return;
    }

    // Crea un objeto std::ofstream para escribir en el archivo
    std::ofstream file(fileName.toStdString());
    if (!file.is_open()) {
        // Si no se puede abrir el archivo, muestra un mensaje de error
        QMessageBox::critical(nullptr, tr("Error"), tr("No se pudo abrir el archivo para escritura"));
        return;
    }

    // Escribe el contenido de m_source en el archivo
    file << *m_source;

    // Cierra el archivo después de escribir
    file.close();

    // Muestra un mensaje de éxito indicando que el archivo se ha guardado correctamente
    QMessageBox::information(nullptr, tr("Éxito"), tr("Archivo guardado exitosamente"));
}



// Llamamos a clean para limpiar la memoria y creamos un objeto nuevo donde guardar la fuente
void TRawInput::newRawInput(){
    clean();
    m_source = new std::string();

}

// Si la memoria está ocupada, la limpiamos y establecemos que la fuente ya no está cargada
void TRawInput::clean(){
    if (m_source != nullptr) {
        m_source-> clear();
        m_loaded = false;
    } 
}

//MENSAJES DE ERROR
std::vector<std::string> ErrorHandler::errorMessages;

void ErrorHandler::showError(const std::string& errorMessage) {
    errorMessages.push_back(errorMessage);
}

 void ErrorHandler::displayErrors() {
    if (!errorMessages.empty()) {
        QString errorText = "Se encontraron los siguientes errores:\n";
        for (const auto& errorMessage : errorMessages) {
            errorText += " - " + errorMessage + "\n";
        }

        QMessageBox::critical(nullptr, "Errores", errorText);

        errorMessages.clear(); // Limpiar los mensajes de error después de mostrarlos.
    }
}


//METANODOS

std::vector<TModelMetabolite> TModelMetabolite::s_metabolites;

TModelMetabolite::TModelMetabolite(short int index, std::string name, std::string id, double initValue, double topValue,
                                   double bottomValue, double value, double precision, bool tag)
    : m_name(name), m_id(id), m_index(index), m_initValue(initValue), m_topValue(topValue), m_bottomValue(bottomValue),
    m_value(value), m_precision(precision), m_tag(tag)
{
    if (check())
        s_metabolites.push_back(*this);
    else{
        ErrorHandler::showError("Error al obtener el metabolito" + std::to_string(index));
    }
}

TModelMetabolite::TModelMetabolite()
{
    m_index = -1;
    m_name = "";
    m_id = "";
    m_initValue = -1;
    m_topValue = -1;
    m_bottomValue = -1;
    m_value = -1;
    m_precision = -1;
    m_tag = false;
}

bool TModelMetabolite::check()
{
    bool ok = true;

    // El índice del metabolito debe corresponder con la posición que le toca en el vector s_metabolites
    if ( m_index > (s_metabolites.size() + 1.0) )
        ok = false;

    // El valor inicial del metabolito no debe salirse de su rango especificado
    if ( m_initValue < m_bottomValue  &&  m_initValue > m_topValue)
        ok = false;
    return ok;
}
std::string TModelMetabolite::getName()
{
    return m_name;
}

std::string TModelMetabolite::getId()
{
    return m_id;
}

double TModelMetabolite::getInitValue()
{
    return m_initValue;
}

double TModelMetabolite::getTopValue()
{
    return m_topValue;
}

double TModelMetabolite::getBottomValue()
{
    return m_bottomValue;
}

double TModelMetabolite::getValue()
{
    return m_value;
}

double TModelMetabolite::getPrecision()
{
    return m_precision;
}

bool TModelMetabolite::getTag()
{
    return m_tag;
}

void TModelMetabolite::setValue(double v_value)
{
    m_value = v_value;
}

void TModelMetabolite::setTag(bool v_tag)
{
    m_tag = v_tag;
}

double TModelMetabolite::range()
{
    return (getTopValue() - getBottomValue());
}

void TModelMetabolite::clear() {
    s_metabolites.clear();
}


//PARAMETROS
std::vector<TModelParameter> TModelParameter::s_params;

TModelParameter::TModelParameter(short int index, std::string ID, std::string description, double value,double precision, bool tag)
    :m_index(index++),m_id(ID), m_description(description), m_value(value), m_precision(precision), m_tag(tag)
{

    if (check())
        s_params.push_back(*this);
    else
        ErrorHandler::showError("Error al obtener el parámetro" + std::to_string(index));

}
TModelParameter::TModelParameter()
{
    m_index = -1;
    m_id = "";
    m_description = "";
    m_value = -1;
    m_precision = -1;
    m_tag = false;
}

bool TModelParameter::check()
{
    bool ok = true;

    // El índice del parámetro debe corresponder con la posición que le toca en el vector s_params
    if ( m_index != (s_params.size() + 1.0) )
        ok = false;

    return ok;
}
short int TModelParameter::getIndex(){
    return m_index;
}

std::string TModelParameter::getId(){
    return m_id;
}

void TModelParameter::setid(std::string v_id){
    m_id = v_id;
}

std::string TModelParameter::getDescription(){
    return m_description;
}

void TModelParameter::setDescription(std::string v_description){
    m_description = v_description;
}

double TModelParameter::getValue(){
    return m_value;
}

void TModelParameter::setValue(double v_value){
    m_value = v_value;
}

double TModelParameter::getPrecision(){
    return m_precision;
}

void TModelParameter::setPrecision(double v_precision){
    m_precision = v_precision;
}

bool TModelParameter::getTag(){
    return m_tag;
}

void TModelParameter::setTag(bool v_tag){
    m_tag = v_tag;
}

void TModelParameter::clear() {
    s_params.clear();
}

// FORMALISMOS
std::vector<TFormalism> TFormalism::s_formalisms;

TFormalism::TFormalism(std::string id, std::string name, std::string formalism, std::vector<std::string> variables)
    :m_id(id), m_name(name), m_formalism(formalism), m_variables(variables)
{

    if (check())
        s_formalisms.push_back(*this);
    else
        ErrorHandler::showError("Error al obtener el formalismo" + id);
}

TFormalism::TFormalism()
{
    m_id = "F";
    m_name = "";
    m_formalism = "";
    m_variables = {};
}

bool TFormalism::check()
{
    bool ok = true;

    std::string id_copy = m_id;
    std::string formalism_copy = m_formalism; // Trabajamos con una copia del formalismo

    size_t found = id_copy.find('F'); // Busca la posición de 'F' en id_copy
    if (found != std::string::npos) { // Verifica si se encontró 'F'
        id_copy.erase(found, 1); // Borra el carácter 'F'

        // Creamos una copia del vector de variables para no modificar el original
        std::vector<std::string> variables_copy = m_variables;

        for (const auto& variable : variables_copy)
        {
            // Buscamos la variable en formalism_copy y la eliminamos si se encuentra
            size_t pos = formalism_copy.find(variable);
            while (pos != std::string::npos)
            {
                formalism_copy.erase(pos, variable.length());
                pos = formalism_copy.find(variable, pos); // Buscamos la siguiente ocurrencia de la variable
            }
        }

        // Eliminamos los dígitos de formalism_copy
        formalism_copy.erase(std::remove_if(formalism_copy.begin(), formalism_copy.end(), [](char c) { return std::isdigit(c); }), formalism_copy.end());

        // Comprobamos que no hay más variables en el formalismo de las que se proporcionan
        // Si eliminamos los operadores y espacios en blanco, debe quedar un std::string vacío
        formalism_copy.erase(std::remove_if(formalism_copy.begin(), formalism_copy.end(), [](char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '[' || c == ']'; }), formalism_copy.end());
        formalism_copy.erase(std::remove_if(formalism_copy.begin(), formalism_copy.end(), [](char c) { return std::isspace(c); }), formalism_copy.end());

        if (!formalism_copy.empty())
            //preguntar a Elena
            ok = false; //false;

    }
    return ok;
}



std::string TFormalism::getId()
{
    return m_id;
}

std::string TFormalism::getName()
{
    return m_name;
}

std::string TFormalism::getFormalism()
{
    return m_formalism;
}

std::vector<TFormalism> TFormalism::getFormalisms(){
    return s_formalisms;
}

std::vector<std::string>& TFormalism::getVariables()
{
    return m_variables;
}

void TFormalism::clear() {
    s_formalisms.clear();
}


// PROCESOS
std::vector<TProcess> TProcess::s_processes;

TProcess::TProcess(std::string id, std::string name, std::string description, std::string idForm, std::vector<std::string> substances)
    :m_id(id), m_name(name), m_description(description), m_idForm(idForm), m_substances(substances)
{
    if (check())
        s_processes.push_back(*this);
    else
        ErrorHandler::showError("Error al obtener el proceso" + m_id);
}

TProcess::TProcess()
{
    m_id = "P";
    m_name = "";
    m_description = "";
    m_idForm = "";
    m_substances = {};
}

bool TProcess::check()
{
    bool ok = true;
    std::string id_copy = m_id;

    size_t found = id_copy.find('P'); // Busca la posición de 'P' en id_copy
    if (found != std::string::npos) { // Verifica si se encontró 'F'
        id_copy.erase(found, 1); // Borra el carácter 'P'
    }
    TFormalism objForm = getFormalism(m_idForm);

    if (objForm.m_id == "F")
        ok = false;

    if (objForm.getVariables().size() != getSubstances().size())
        ok = false;

    // Comprobamos que todos metabolitos y parámetros que indica el proceso existen:
    // Creamos un std::string de identificadores de metabolitos y parámetros, y buscamos en él
    std::string id_stored;

    for (unsigned int i = 0; i < TModelMetabolite::s_metabolites.size(); i++)
    {
        id_stored.append(TModelMetabolite::s_metabolites[i].getId());

    }

    for (unsigned int j = 0; j < TModelParameter::s_params.size(); j++)
    {
        id_stored.append(TModelParameter::s_params[j].getId());
    }

    for (unsigned int k = 0; k < m_substances.size(); k++)
    {
        if (id_stored.find(m_substances[k]) == std::string::npos)
            ok = false;

    }


    return ok;
}

TFormalism TProcess::getFormalism(std::string m_idForm)
{
    // Copiamos el ID del formalismo y eliminamos el prefijo "F"
    std::string id_copy = m_idForm;
    id_copy.erase(std::remove(id_copy.begin(), id_copy.end(), 'F'), id_copy.end());

    // Convertimos el ID a un entero y restamos 1 para obtener el índice en el vector de formalismos
    int index = std::stoi(id_copy) - 1;

    // Retornamos el formalismo correspondiente
    return TFormalism::s_formalisms[index];
}

std::string TProcess::getProcess()
{
    // El proceso comienza siendo igual que el formalismo asociado
    TFormalism objForm = getFormalism(m_idForm);


    std::string process = objForm.m_formalism;

    // Reemplazamos el valor de las variables del formalismo
    // por las del proceso específicas, respetando el orden
    for (unsigned int i = 0; i < objForm.m_variables.size(); i++)
    {
        std::string variable = objForm.m_variables[i];
        size_t pos = 0;
        // Buscar y reemplazar todas las ocurrencias de la variable en el proceso
        while ((pos = process.find(variable, pos)) != std::string::npos)
        {
            // Verificar que la variable esté delimitada por caracteres que no sean alfanuméricos
            if ((pos == 0 || !std::isalnum(process[pos - 1])) &&
                (pos + variable.size() == process.size() || !std::isalnum(process[pos + variable.size()])))
            {
                // Reemplazar la ocurrencia de la variable en el proceso
                process.replace(pos, variable.length(), m_substances[i]);

               // Mover la posición más allá de la sustitución
               pos += m_substances[i].length();
            }else{
                pos += 1;
            }

        }
    }

    return process;
}

std::string TProcess::getId()
{
    return m_id;
}

std::string TProcess::getName()
{
    return m_name;
}

std::string TProcess::getDescription()
{
    return m_description;
}

std::string TProcess::getIDForm()
{
    return m_idForm;
}

std::vector<std::string>& TProcess::getSubstances()
{
    return m_substances;
}

std::vector<TProcess> TProcess::getProcesses(){
    return s_processes;
}

void TProcess::clear() {
    s_processes.clear();
}


// ECUACIONES
std::vector<TEquation> TEquation::s_equations;

TEquation::TEquation(int index, std::string equation, std::string variable, std::string expression)
    :m_index(index), m_equation(equation), m_variable(variable), m_expression(expression)
{
    if (check())
        s_equations.push_back(*this);
    else
        ErrorHandler::showError("Error al obtener la ecuación" + std::to_string(index));

}

TEquation::TEquation()
{
    m_index = -1;
    m_equation = "";
    m_variable = "";
    m_expression = "";
}

int TEquation::getIndex(){
    return m_index;
}

std::string TEquation::getEquation(){
    return m_equation;
}

std::string TEquation::getExpression(){
    return m_expression;
}

std::string TEquation::getVariable(){
    return m_variable;
}

std::vector<TEquation> TEquation::getEquations(){
    return s_equations;
}

bool TEquation::check(){
    bool ok = true;


    /*// El índice de la ecuación debe corresponder con la posición que le toca en el vector s_equations
    if ( m_index != (s_equations.size() + 1.0) ){

        ok = false;
    }*/
    // Los procesos especificados en la expresión deben existir
    std::string expression = getExpression();
    std::vector<std::string> processes = getSplittedExpression(expression);
    std::vector<std::string> subs;
    std::string idProcess;
    bool encontrada = false;

    for (const auto& process : processes) {
        idProcess = process;

        size_t pos;

        if((pos = idProcess.find(' +')) != std::string::npos) idProcess.erase(pos, 1);
        if((pos = idProcess.find(' -')) != std::string::npos) idProcess.erase(pos, 1);

        if (getProcess(idProcess).getId() == "P"){
            ok = false;
        }

        subs = getProcess(idProcess).getSubstances();

        //PREGUNTAR A ELENA
       /* for (unsigned int s=0; s< subs.size(); s++){
            qDebug()<< subs[s];
            if (subs[s] == getVariable())
                encontrada = true;
        }*/
    }

    // La variable de la ecuación debe ser un metabolito indicado en alguno de los procesos
   /* if (!encontrada)
        ok = false;*/

    return ok;
}

TProcess TEquation::getProcess(std::string m_IdProc){
    std::string id_copy = m_IdProc;

    int index = 0;
    size_t pos = id_copy.find_first_of("0123456789");
    if (pos != std::string::npos){
        // Extraer el número que sigue después de la posición encontrada
        std::string num_process = id_copy.substr(pos);
        index = std::stoi(num_process) - 1;
    }

    // Retornamos el formalismo correspondiente
    return TProcess::getProcesses().at(index);
}

std::vector<std::string> TEquation::getSplittedExpression(std::string expression) {
    std::vector<std::string> processes;
    size_t i = 0;

    while (i < expression.size()) {
        // Buscamos 'P' seguido de uno o más dígitos
        if (expression[i] == 'P' && i + 1 < expression.size() && std::isdigit(expression[i + 1])) {
            size_t start = i;
            // Avanza hasta encontrar el siguiente espacio o un operador
            while (i < expression.size() && (std::isdigit(expression[i + 1]) || expression[i + 1] == 'P')) {
                ++i;
            }
            processes.push_back(expression.substr(start, i - start + 1)); // Incluimos 'P' y el número
        }
        // Busca '-' o '+' seguido de 'P' y uno o más dígitos
        else if ((expression[i] == '-' || expression[i] == '+') && i + 2 < expression.size() && expression[i + 1] == 'P' && std::isdigit(expression[i + 2])) {
            size_t start = i;
            // Avanza hasta encontrar el siguiente espacio o un operador
            while (i + 1 < expression.size() && !std::isspace(expression[i + 2]) && expression[i + 2] != '-' && expression[i + 2] != '+') {
                ++i;
            }
            processes.push_back(expression.substr(start, i - start + 2)); // Incluimos el signo, 'P' y el número
            ++i; // Avanza al siguiente caracter después del número
        }

        ++i;
    }

    return processes;
}

std::string TEquation::getEquationChanged(){
    std::string expression = getExpression();
    std::vector<std::string> processes = getSplittedExpression(expression);

    std::string equationChanged;


    // Itera sobre cada proceso y obtener su formalismo
    for (const auto& process : processes) {
        // Obtiene el formalismo asociado al proceso
        std::string formalism = getProcess(process).getProcess();

        // Agrega el formalismo al resultado, manteniendo el signo del proceso
        if((process.front() == '+' || process.front() == '-'))
            equationChanged.append(1, process.front()).append("(").append(formalism).append(")").append(" ");
        else
            equationChanged.append(formalism).append(" ");
    }

    return equationChanged;
}

void TEquation::clear() {
    s_equations.clear();
}


