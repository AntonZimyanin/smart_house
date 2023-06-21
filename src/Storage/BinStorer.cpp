#include "../stdafx.h"
#include "BinStorer.h"
#include <string.h>

CBinStorer::CBinStorer(const char* sFileName)
    : m_File(sFileName, ios_base::binary)
{
}

CBinStorer::operator bool()
{
    return m_File.good();
}


bool CBinStorer::Store(int value)
{
    m_File.write(reinterpret_cast<const char*>(&value), sizeof(value));
    return m_File.good();
}

bool CBinStorer::Store(const char* psStr)
{
    int len = psStr ? strlen(psStr) : 0;
    if (!Store(len))
        return false;
    if (len)
        m_File.write(psStr, len);
    return m_File.good();
}

bool CBinStorer::Store(bool value)
{
    m_File.write(reinterpret_cast<const char*>(&value), sizeof(value));
    return m_File.good();
}