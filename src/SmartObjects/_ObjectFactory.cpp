#include "../stdafx.h"
#include "_ObjectFactory.h"
#include "LampObject.h"
#include "DoorObject.h"
#include "RoomObject.h"
#include "../Utils/StringEx.h"
#include <assert.h>
using namespace std;

CObjectFactory::CObjectFactory()
                : m_Objects()
{
    RegObjectType(new CRoomObject("", 0, 0, 0, 0));
    RegObjectType(new CLampObject("", 0, 0, false));
    RegObjectType(new CDoorObject("", 0, 0, enmDirection::down, false));
}

void CObjectFactory::RegObjectType(CBaseObject* pObj)
{
    stringEx str(pObj->Type());
    str.strlwr(); // добавляем в бинарное дерево с ключом записанным в нижнем регистре
                  // при поиске тоже переданную строку приводим к нижнему регистру
                  // таким образом фабрика будет работать со названиями типов объектов независимо от регистра
    assert(m_Objects.count(str) == 0); // проверяем, что нет уже зарегистрированного типа объектов с тем же именем и, если находим,
                                       // то пытаемся привлеч внимание программиста
    m_Objects[str] = pObj;
}

CObjectFactory::~CObjectFactory()
{
    for (map<string, CBaseObject*>::iterator p = m_Objects.begin(); p != m_Objects.end(); ++p)
        delete p->second;
    m_Objects.clear();
}

CBaseObject* CObjectFactory::CreateObject(const char* psTypeName)
{
    stringEx str(psTypeName);
    str.strlwr();
    map<string, CBaseObject*>::const_iterator pIter = m_Objects.find(str);
    if (pIter == m_Objects.end()) // нет такого типа объектов
        return NULL;
    return pIter->second->Clone();
}
