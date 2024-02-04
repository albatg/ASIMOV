#include "asimov_library.h"

// --------------------------------------------------------
//                     TRawInput
// --------------------------------------------------------

TRawInput::TRawInput(QString* v_source)
{
    m_loaded = false;
    if (v_source == nullptr){
        m_source = new(QString);
    } else
    {
        m_source = v_source;
        m_loaded = true;
    }
}

TRawInput::~TRawInput()
{
    delete m_source;
    m_source = nullptr;
}


// --------------------------------------------------------
//                     TModelMetabolite
// --------------------------------------------------------

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
