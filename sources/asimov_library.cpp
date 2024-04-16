/**
 *@file asimov_library.cpp
 *@version 1.0
 *@date 22/02/2024
 *@author Grupo ASIMOV
 *@title Implementación de librería ASIMOV
*
*/

#include "asimov_library.h"
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <fstream>


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

void TRawInput::setSource(std::string& v_source)
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


//METANODOS

std::vector<TModelMetabolite> TModelMetabolite::s_metabolites;

TModelMetabolite::TModelMetabolite(short int index, std::string name, std::string id, double initValue, double topValue,
                                   double bottomValue, double value, double precision, bool tag)
    : m_name(name), m_id(id), m_index(index), m_initValue(initValue), m_topValue(topValue), m_bottomValue(bottomValue),
    m_value(value), m_precision(precision), m_tag(tag)
{
    if (check()){
        s_metabolites.push_back(*this);
    }
    //else

    }

bool TModelMetabolite::check()
{
    bool ok = true;

    // Comprobar que la numeración del identificador es correlativa
    // ... (hacer aquí las comprobaciones)

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

//PARAMETROS
short int TModelParameter::s_counter = 1;
std::vector<TModelParameter> TModelParameter::s_params;

TModelParameter::TModelParameter(std::string ID, std::string description, double value,double precision, bool tag)
    :m_index(s_counter++),m_id(ID), m_description(description), m_value(value), m_precision(precision), m_tag(tag)
{

    if (check())
        s_params.push_back(*this);
    //else
    // Mensaje de error?
}

bool TModelParameter::check()
{
    bool ok = true;

    // Comprobar que la numeración del identificador es correlativa
    // ...

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

// FORMALISMOS
std::vector<TFormalism> TFormalism::s_formalisms;

TFormalism::TFormalism(std::string id, std::string name, std::string formalism, std::vector<std::string> variables)
    :m_id(id), m_name(name), m_formalism(formalism), m_variables(variables)
{

    if (check())
        s_formalisms.push_back(*this);
    //else
    // Mostrar mensaje de error, por dónde? ("Error al obtener el formalismo" + QString::number(m_id))
}

bool TFormalism::check()
{
    bool ok = true;
    std::string formalism_copy = m_formalism; // Trabajamos con una copia del formalismo

    // Comprobamos que todas las variables que se proporcionan están en el formalismo
    for (unsigned int i = 0; i < m_variables.size(); i++)
    {
        size_t pos = formalism_copy.find(m_variables[i]);
        if (pos != std::string::npos)
            formalism_copy.erase(pos, m_variables[i].length());
        else
            ok = false;
    }

    // Comprobamos que no hay más variables en el formalismo de las que se proporcionan
    // Si eliminamos los operadores y espacios en blanco, debe quedar un std::string vacío
    formalism_copy.erase(std::remove_if(formalism_copy.begin(), formalism_copy.end(), [](char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'; }), formalism_copy.end());
    formalism_copy.erase(std::remove_if(formalism_copy.begin(), formalism_copy.end(), [](char c) { return std::isspace(c); }), formalism_copy.end());

    if (!formalism_copy.empty())
        //preguntar a Elena
        ok = true; //false;

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


// PROCESOS
std::vector<TProcess> TProcess::s_processes;

TProcess::TProcess(std::string id, std::string name, std::string description, std::string idForm, std::vector<std::string> substances)
    :m_id(id), m_name(name), m_description(description), m_idForm(idForm), m_substances(substances)
{
    //if (check())
    s_processes.push_back(*this);
    //else
    // Mostrar mensaje de error, por dónde? ("Error al obtener el proceso" + QString::number(m_id))
}

bool TProcess::check()
{
    bool ok = true;

    // Comprobar que la numeración del identificador es correlativa
    // ...

    // La longitud del vector de variables del formalismo asociado debe coincidir
    // con la longitud del vector de sustancias del proceso (implícitamente se
    // comprueba que el formalismo existe)
    TFormalism objForm = getFormalism(m_idForm);

    if (objForm.getVariables().size() != getSubstances().size())
        ok = false;

    // Comprobamos que todos metabolitos y parámetros que indica el proceso existen:
    // Creamos un std::string de identificadores de metabolitos y parámetros, y buscamos en él
    std::string id_meta_params;

    for (unsigned int i = 0; i < TModelMetabolite::s_metabolites.size(); i++)
    {
        id_meta_params.append(TModelMetabolite::s_metabolites[i].getId());
    }

    for (unsigned int j = 0; j < TModelParameter::s_params.size(); j++)
    {
        id_meta_params.append(TModelParameter::s_params[j].getId());
    }

    for (unsigned int k = 0; k < m_substances.size(); k++)
    {
        if (id_meta_params.find(m_substances[k]) == std::string::npos)
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
    for (unsigned int i = 0; i < m_substances.size(); i++)
    {
        size_t pos = process.find(objForm.m_variables[i]);
        if (pos != std::string::npos)
        {
            process.replace(pos, objForm.m_variables[i].size(), m_substances[i]);
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
