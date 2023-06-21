#pragma once
#include "_Storer.h"
#include <fstream>
using namespace std;

class CBinStorer : public IStorer
{
private:
    ofstream m_File;
public:
    CBinStorer(const char* sFileName);

    virtual operator bool();
    virtual bool Store(int value);
    virtual bool Store(const char* psStr);
    virtual bool Store(bool value);
};

