#pragma once
#include "_Storer.h"
#include <fstream>
using namespace std;

class CTxtStorer : public IStorer
{
private:
    ofstream m_File;
public:
    CTxtStorer(const char* sFileName);

    virtual operator bool();
    virtual bool Store(int value);
    virtual bool Store(const char* psStr);
    virtual bool Store(bool value);
};



