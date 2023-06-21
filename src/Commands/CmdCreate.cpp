#include "../stdafx.h"
#include "CmdCreate.h"
#include <iostream>
#include <assert.h>
#include "../Context.h"
using namespace std;

// слова указанные в этом списке нельзя использовать как имена объектов. Они зарезервированы для использования как
// дополнительные параметры команд
const char* g_vsReservedWords[] = { "all" };

std::string CCmdCreate::Help(CContext* pContext, const vector<stringEx>& vParameters)
{
    if (!vParameters.size())
    {
        string res = "Использование:\n    create <тип объекта> <имя объекта без пробелов>\nПоддерживаемые типы объектов:\n";
        const map<string, CBaseObject*>* pvObjSamples = &pContext->m_ObjFactory.Objects();
        for (map<string, CBaseObject*>::const_iterator p = pvObjSamples->begin(); p != pvObjSamples->end(); ++p)
        {
            res += "   ";
            res += p->second->Type();
            res += " - ";
            res += p->second->Hint();
            res += '\n';
        }
        return res;
    }
    return ICommand::Help(pContext, vParameters);
}

bool CCmdCreate::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0)
    {
        pContext->m_Console << "Не указан тип создаваемого объекта" << endl;
        return false;
    }
    if (vParameters.size() == 1)
    {
        pContext->m_Console << "Не указано имя создаваемого объекта" << endl;
        return false;
    }
    if (vParameters.size() != 2)
    {
        pContext->m_Console << "Указано слишком много параметров для этой команды" << endl;
        return false;
    }
    CBaseObject* pObj = pContext->m_ActiveModel.FindObject(vParameters[1].c_str());
    if (pObj)
    {
        pContext->m_Console << "Объект с таким именем уже существует" << endl;
        return false;
    }
    for (size_t i = 0; i < countof(g_vsReservedWords); i++)
    {
        if (vParameters[1] == g_vsReservedWords[i])
        {
            pContext->m_Console << "Указанное имя не может быть присвоено объекту, это слово зарезервировано" << endl;
            return false;
        }
    }
    pObj = pContext->m_ObjFactory.CreateObject(vParameters[0].c_str());
    if (!pObj)
    {
        pContext->m_Console << "Указан неизвестный тип объекта" << endl;
        return false;
    }
    pObj->m_Name = vParameters[1];
    if (!pObj->InputParams(pContext->m_Console))
    {
        pContext->m_Console.ClearErrorFlag();
        delete pObj;
        return false;
    }
    if (!pContext->m_ActiveModel.AddObject(pObj))
    {
        assert(false); // только что проверяли что такое имя не используется
        delete pObj;
        pContext->m_Console << "Объект с таким именем уже существует" << endl;
        return false;
    }
    pContext->m_Console << "Новый объект " << vParameters[1].c_str() << " создан" << endl;
    return true;
}
