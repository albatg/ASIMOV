#include "asimov_library.h"
#include <QString>
/*
TRawInput::TRawInput(QString* v_source)
{
    m_loaded = false;
    if (v_source == nullptr){
        m_source = new(QString);
    } else
    {
        m_source = v_source;
        m_loaded = true;
    };
};

TRawInput::~TRawInput()
{
    delete m_source;
    m_source = nullptr;
};
*/

//METANODOS
TModelMetabolite::TModelMetabolite(QString name, QString id, short int index, double initValue, double topValue,
                                   double bottomValue, double value, double precision, bool tag)
    : m_name(name), m_id(id), m_index(index), m_initValue(initValue), m_topValue(topValue), m_bottomValue(bottomValue),
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
TModelParameter::TModelParameter(short int m_Index, QString m_ID, QString m_Description, double m_Value,double m_Precision, bool m_Tag)
    : m_index(m_Index), m_id(m_ID), m_description(m_Description), m_value(m_Value), m_precision(m_Precision), m_tag(m_Tag)
{}

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
