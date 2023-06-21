#include "../stdafx.h"
#include "BinLoader.h"
#include <assert.h>

CBinLoader::CBinLoader(const char* sFileName)
    : m_File(sFileName, ios_base::binary)
{
}

CBinLoader::operator bool()
{
    return m_File.good();
}

bool CBinLoader::Load(OUT int& value)
{
    m_File.read(reinterpret_cast<char*>(&value), sizeof(value));
    return m_File.good();
}

bool CBinLoader::Load(OUT string& str)
{
    str = "";
    int len = 0;
    if (!Load(OUT len))
        return false;
    if (len > 1024)
    {
        assert(false); // файл повреждён - слишком большая строка
        return false;
    }
    if (len)
    {
        str.resize(len);
        m_File.read(&str[0], len);
    }
    return m_File.good();
}

bool CBinLoader::Load(OUT bool& value)
{
    m_File.read(reinterpret_cast<char*>(&value), sizeof(value));
    return m_File.good();
}

