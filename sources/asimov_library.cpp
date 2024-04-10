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


// Constructor de la clase
TRawInput::TRawInput(QString* v_source)
{
    // La variable que indica si el documento está cargado se pone a false como precaución
    m_loaded = false;
    // En caso de que v_source sea nulo, se asigna un nuevo objeto QString a m_source
    if (v_source == nullptr){
        m_source = new(QString);
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

QString TRawInput::getSource() {
    // En caso de que m_source no sea nullptr, devolvemos el contenido de m_source
    if (m_source != nullptr) {
        return *m_source;
    } else {
        // Caso donde m_source es nullptr, devolvemos un objeto QString vacío
        return QString(); // Otra opción podría ser lanzar una excepción/devolver un valor predeterminado
    }
}

void TRawInput::setSource(QString& v_source)
{
    // Asignamos una nueva fuente de datos
    *m_source = v_source; // Copiamos el contenido del QString proporcionado

    qDebug()<<"source: " << *m_source;
}

// Devuelve si hay una fuente cargada

bool TRawInput::getLoaded() {
    return m_loaded;
}

// Operación de carga desde archivo

bool TRawInput::loadFromFile()
{
    // Verificamos si m_source está configurado y no vacío
    if (m_source == nullptr || m_source->isEmpty()) {
        qDebug() << "Error: m_source no configurada o vacía";
        return false;
    }
    // Intentamos abrir el archivo en modo de solo lectura y texto
    QFile file(*m_source);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: no se pudo abrir el archivo" << *m_source;
        return false;
    }

    // Leemos el contenido del archivo y lo almacenamos en m_source
    QTextStream in(&file);
    *m_source = in.readAll(); // Lee todo el contenido del archivo y lo almacena en m_source

    // Marcamos m_loaded como true e indicamos que la carga desde el archivo fue exitosa
    m_loaded = true;

    return true;
}

void TRawInput::setToFile()
{
    // QFileDialog para solicitar al usuario que seleccione o especifique un archivo para guardar
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Guardar archivo"), "", tr("Archivos de texto (*.txt);;Todos los archivos (*)"));

    if (fileName.isEmpty()) {
        // Por si el usuario cancela la operación
        return;
    }

    // Comprueba que m_source está inicializado y que contenga datos
    if (m_source == nullptr || m_source->isEmpty()) {
        // Si m_source está vacío, muestra un mensaje de advertencia y no guarda el archivo
        QMessageBox::warning(nullptr, tr("Advertencia"), tr("El archivo está vacío"));
        return;
    }

    // Crea un objeto QFile con el nombre del archivo especificado
    QFile file(fileName);

    // Crea un QTextStream para escribir en el archivo
    QTextStream out(&file);
    out << *m_source;

    // Cierra el archivo después de escribir
    file.close();

    // Muestra un mensaje de éxito indicando que el archivo se ha guardado correctamente
    QMessageBox::information(nullptr, tr("Éxito"), tr("Archivo guardado exitosamente"));
}


// Llamamos a clean para limpiar la memoria y creamos un objeto nuevo donde guardar la fuente
void TRawInput::newRawInput(){
    clean();
    m_source = new QString();

}

// Si la memoria está ocupada, la limpiamos y establecemos que la fuente ya no está cargada
void TRawInput::clean(){
    if (m_source != nullptr) {
        m_source-> clear();
        m_loaded = false;
    } 
}


//METANODOS
TModelMetabolite::TModelMetabolite(QString name, QString id, double initValue, double topValue,
                                   double bottomValue, double value, double precision, bool tag)
    : m_name(name), m_id(id), m_initValue(initValue), m_topValue(topValue), m_bottomValue(bottomValue),
    m_value(value), m_precision(precision), m_tag(tag)
{}

QString TModelMetabolite::getName()
{
    return m_name;
}

QString TModelMetabolite::getId()
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

TModelParameter::TModelParameter(QString ID, QString description, double value,double precision, bool tag)
    :m_index(s_counter++),m_id(ID), m_description(description), m_value(value), m_precision(precision), m_tag(tag)
{
}

short int TModelParameter::getIndex(){
    return m_index;
}

QString TModelParameter::getId(){
    return m_id;
}
void TModelParameter::setid(QString v_id){
    m_id = v_id;
}
QString TModelParameter::getDescription(){
    return m_description;
}
void TModelParameter::setDescription(QString v_description){
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
