#pragma once
#include "_BaseObject.h"
#include "_ISwitchOnOffObject.h"

class CLampObject : public CBaseObject, public ISwitchOnOffObject
{
private:
    int m_X;
    int m_Y;
    bool m_isOn;
public:
    CLampObject(const char* psName, int x, int y, bool isOn);
    ~CLampObject();

    virtual CBaseObject* Clone()
    {
        return new CLampObject(m_Name.c_str(), m_X, m_Y, m_isOn);
    }
    virtual bool InputParams(CConsoleManip& console);
    virtual bool Draw(CConsoleManip& console) const;
    virtual bool Store(IStorer* pStorer) const;
    virtual bool Load(ILoader* pLoader);
    virtual void SwitchOn();
    virtual void SwitchOff();

    virtual const char* Hint() const
    {
        return "Светильник";
    }
    virtual const char* Type() const
    {
        return "Lamp";
    }
    virtual void PrintProperties(CConsoleManip& console) const;
};

