#include "../stdafx.h"
#include "TxtLoader.h"

CTxtLoader::CTxtLoader(const char* sFileName)
    : m_File(sFileName),
      m_prevValueIsInt(false)
{
}

CTxtLoader::operator bool()
{
    return m_File.good();
}


bool CTxtLoader::Load(OUT int& value)
{
    m_File >> value;
    m_prevValueIsInt = true;
    return m_File.good();
}

bool CTxtLoader::Load(OUT string& str)
{
    if (m_prevValueIsInt) // прошлое значение прочтено как число - в буфере остался символ конца строки который надо удалить
        getline(m_File, str);
    getline(m_File, str);
    m_prevValueIsInt = false;
    return m_File.good();
}

bool CTxtLoader::Load(OUT bool& value)
{
    string str;
    if (!Load(OUT str))
        return false;
    value = str == "true";
    return true;
}
