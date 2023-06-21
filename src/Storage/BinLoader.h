#pragma once
#include "_Loader.h"
#include <fstream>
using namespace std;

class CBinLoader : public ILoader
{
private:
    ifstream m_File;
public:
    CBinLoader(const char* sFileName);

    virtual operator bool();
    virtual bool Load(OUT string& str);
    virtual bool Load(OUT int& value);
    virtual bool Load(OUT bool& value);
};
