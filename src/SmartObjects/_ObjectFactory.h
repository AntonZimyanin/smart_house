#pragma once
#include "_BaseObject.h"
using namespace std;

class CObjectFactory
{
private:
    map<string, CBaseObject*> m_Objects;
    void RegObjectType(CBaseObject* pObj);
public:
    CObjectFactory();
    virtual ~CObjectFactory();

    CBaseObject* CreateObject(const char* psTypeName);

    // другие объекты могут доступиться к списку доступных объектов но не могут его изменять
    const map<string, CBaseObject*>& Objects() const { return m_Objects; }
};

