#include "../stdafx.h"
#include "TxtStorer.h"


CTxtStorer::CTxtStorer(const char* sFileName)
    : m_File(sFileName)
{
}

CTxtStorer::operator bool()
{
    return m_File.good();
}


bool CTxtStorer::Store(int value)
{
    m_File << value << endl;
    return m_File.good();
}

bool CTxtStorer::Store(const char* psStr)
{
    if (!psStr)
        m_File << endl;
    else
        m_File << psStr << endl;
    return m_File.good();
}

bool CTxtStorer::Store(bool value)
{
    m_File << (value ? "true" : "false") << endl;
    return m_File.good();
}