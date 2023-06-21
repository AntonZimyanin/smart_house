#pragma once
#include "_BaseObject.h"
#include "_IOpenCloseObject.h"

enum class enmDirection
{
    up = 0, 
    left = 1,
    down = 2,
    right = 3
};

class CDoorObject : public CBaseObject, public IOpenCloseObject
{
private:
    int m_X;
    int m_Y;
    enmDirection m_Dir;
    bool m_isOpen;
public:
    CDoorObject(const char* psName, int x, int y, enmDirection dir, bool isOpen);
    ~CDoorObject();

    virtual CBaseObject* Clone()
    {
        return new CDoorObject(m_Name.c_str(), m_X, m_Y, m_Dir, m_isOpen);
    }
    virtual bool InputParams(CConsoleManip& console);
    virtual bool Draw(CConsoleManip& console) const;
    virtual bool Store(IStorer* pStorer) const;
    virtual bool Load(ILoader* pLoader);
    virtual void Open();
    virtual void Close();

    virtual const char* Hint() const
    {
        return "Дверь";
    }
    virtual const char* Type() const
    {
        return "Door";
    }
    virtual void PrintProperties(CConsoleManip& console) const;
};

