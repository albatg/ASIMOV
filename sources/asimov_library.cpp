#include "asimov_library.h"


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
