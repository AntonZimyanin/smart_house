#pragma once
#include "_BaseObject.h"

class CRoomObject : public CBaseObject
{
private:
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;
public:
    CRoomObject(const char* psName, int x, int y, int width, int height);
    ~CRoomObject()
    {}
    virtual CBaseObject* Clone()
    {
        return new CRoomObject(m_Name.c_str(), m_X, m_Y, m_Width, m_Height);
    }
    virtual bool InputParams(CConsoleManip& console);
    virtual bool Draw(CConsoleManip& console) const;
    virtual bool Store(IStorer* pStorer) const;
    virtual bool Load(ILoader* pLoader);

    virtual const char* Hint() const
    {
        return "Комната";
    }
    virtual const char* Type() const
    {
        return "Room";
    }
    int X() const { return m_X; }
    int Y() const { return m_Y; }
    int Width() const { return m_Width; }
    int Height() const { return m_Height; }
    virtual void PrintProperties(CConsoleManip& console) const;
};

