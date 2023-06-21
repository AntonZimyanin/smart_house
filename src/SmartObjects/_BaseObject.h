#pragma once

#include <string>
#include "../Storage/_Loader.h"
#include "../Storage/_Storer.h"
#include "../Utils/ConsoleManip.h"
using namespace std;

class CContext;
class CConsoleManip;

// Абстрактный базовый класс для всех элементов "умного" дома: датчиков и самой комнаты.

class CBaseObject
{
public:
    string m_Name;

    CBaseObject(const char* psName)
        : m_Name(psName)
    {}
    virtual ~CBaseObject()
    {}
    virtual CBaseObject* Clone() = 0;
    virtual bool InputParams(CConsoleManip& console) = 0;
    virtual bool Draw(CConsoleManip& console) const = 0;
    virtual bool Store(IStorer* pStorer) const
    {
        return pStorer->Store(Type()) &&
               pStorer->Store(m_Name.c_str());
    }
    virtual bool Load(ILoader* pLoader)
    {
        return pLoader->Load(OUT m_Name);
    }
    virtual const char* Hint() const = 0;
    virtual const char* Type() const = 0;
    virtual void PrintProperties(CConsoleManip& console) const
    {
        console << Type() << "   " << m_Name.c_str() << endl;
    }
};

