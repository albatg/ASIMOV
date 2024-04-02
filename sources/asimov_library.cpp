#include "asimov_library.h"
#include <QString>
#include <QFile>
#include <QRegularExpression>

// RAWINPUT
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

QString TRawInput::getSource()
{
    // En caso de que m_source no sea nullptr, devolvemos el contenido de m_source
    if (m_source != nullptr) {
        return *m_source;
    } else {
        // Caso donde m_source es nullptr, devolvemos un objeto QString vacío
        return QString(); // Otra opción podría ser lanzar una excepción/devolver un valor predeterminado
    }
}

void TRawInput::setSource(QString* v_source)
{
    // Liberamos el objeto anterior
    delete m_source;

    // Asignamos una nueva fuente de datos
    m_source = new QString(*v_source); // Copiamos el contenido del QString proporcionado
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


//METANODOS
std::vector<TModelMetabolite> TModelMetabolite::s_metabolites;

TModelMetabolite::TModelMetabolite(short int index, QString name, QString id, double initValue, double topValue,
                                   double bottomValue, double value, double precision, bool tag)
    : m_name(name), m_id(id), m_index(index), m_initValue(initValue), m_topValue(topValue), m_bottomValue(bottomValue),
     m_value(value), m_precision(precision), m_tag(tag)
{
    if (check())
        s_metabolites.push_back(*this);
    //else

}

bool TModelMetabolite::check()
{
    bool ok = true;

    // Comprobar que la numeración del identificador es correlativa
    // ... (hacer aquí las comprobaciones)

    return ok;
}

QString TModelMetabolite::getName()
{
    return m_name;
}

QString TModelMetabolite::getId()
{
    return m_id;
}

short int TModelMetabolite::getIndex()
{
    return m_index;
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
std::vector<TModelParameter> TModelParameter::s_params;

TModelParameter::TModelParameter(short int index, QString ID, QString description, double value,double precision, bool tag)
    :m_index(index), m_id(ID), m_description(description), m_value(value), m_precision(precision), m_tag(tag)
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

QString TModelParameter::getId(){
    return m_id;
}

QString TModelParameter::getDescription(){
    return m_description;
}

double TModelParameter::getValue(){
    return m_value;
}

double TModelParameter::getPrecision(){
    return m_precision;
}

bool TModelParameter::getTag(){
    return m_tag;
}

void TModelParameter::setTag(bool v_tag){
    m_tag = v_tag;
}

void TModelParameter::setValue(double v_value){
    m_value = v_value;
}


// FORMALISMOS
std::vector<TFormalism> TFormalism::s_formalisms;

TFormalism::TFormalism(QString id, QString name, QString formalism, std::vector<QString> variables)
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
    QString formalism_copy = m_formalism; // Trabajamos con una copia del formalismo

    // Comprobamos que todas las variables que se proporcionan están en el formalismo
    for (unsigned int i=0; i<m_variables.size(); i++)
    {
        if (formalism_copy.contains(m_variables[i]))
            formalism_copy.remove(m_variables[i]);
        else
            ok = false;
    }

    // Comprobamos que no hay más variables en el formalismo de las que se proporcionan
    // Si eliminamos los operadores y espacios en blanco, debe quedar un QString vacío
    formalism_copy.remove("[+-*/()]");
    QString formalism_empty = formalism_copy.simplified();
    if (!formalism_empty.isEmpty())
        ok = false;

    // Comprobar que la numeración del identificador es correlativa
    // ...

    return ok;
}

QString TFormalism::getId()
{
    return m_id;
}

QString TFormalism::getName()
{
    return m_name;
}

QString TFormalism::getFormalism()
{
    return m_formalism;
}

QString TFormalism::getVariables()
{
    QString lista_var;

    for (unsigned int i=0; i<m_variables.size(); i++)
    {
        lista_var.append(m_variables[i] + ',');
    }
    lista_var.removeLast();

    return lista_var;
}


// PROCESOS
std::vector<TProcess> TProcess::s_processes;

TProcess::TProcess(QString id, QString name, QString description, QString idForm, std::vector<QString> substances)
    :m_id(id), m_name(name), m_description(description), m_idForm(idForm), m_substances(substances)
{
    if (check())
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

    if (objForm.m_variables.size() != m_substances.size())
        ok = false;

    // Comprobamos que todos metabolitos y parámetros que indica el proceso existen:
    // Creamos un QString de identificadores de metabolitos y parámetros, y buscamos en él
    QString id_meta_params;

    for (unsigned int i=0; i<TModelMetabolite::s_metabolites.size(); i++)
    {
        id_meta_params.append(TModelMetabolite::s_metabolites[i].getId());
    }

    for (unsigned int j=0; j<TModelParameter::s_params.size(); j++)
    {
        id_meta_params.append(TModelParameter::s_params[j].getId());
    }

    for (unsigned int k=0; k<m_substances.size(); k++)
    {
        if (!id_meta_params.contains(m_substances[k]))
            ok = false;
    }

    return ok;
}

TFormalism TProcess::getFormalism(QString m_idForm)
{
    QString id_copy = m_idForm; // m_idForm es de la forma "F1"
    id_copy.remove('F');        // obtenemos "1"

    return TFormalism::s_formalisms[ id_copy.toInt() - 1 ];
}

QString TProcess::getProcess()
{
    // El proceso comienza siendo igual que el formalismo asociado
    TFormalism objForm = getFormalism(m_idForm);
    QString process = objForm.m_formalism;

    // Reemplazamos el valor de las variables del formalismo
    // por las del proceso específicas, respetando el orden
    for (unsigned int i=0; i<m_substances.size(); i++)
    {
        process.replace(objForm.m_variables[i], m_substances[i]);
    }

    return process;
}
