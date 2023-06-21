#include "../stdafx.h"
#include "CmdSwitchOff.h"
#include <iostream>
#include "../Context.h"
#include "../SmartObjects/_ISwitchOnOffObject.h"
using namespace std;

bool CCmdSwitchOff::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0)
    {
        pContext->m_Console << "Не указано имя светильника" << endl;
        return false;
    }
    if (vParameters.size() > 1)
    {
        pContext->m_Console << "Неподдерживаемый параметр команды" << endl;
        return false;
    }
    CBaseObject* pObj = pContext->m_ActiveModel.FindObject(vParameters[0].c_str());
    if (pObj)
    {
        ISwitchOnOffObject* pLight = dynamic_cast<ISwitchOnOffObject*>(pObj);
        if (!pLight)
        {
            pContext->m_Console << "Указанный объект не поддерживает включение/отключение" << endl;
            return false;
        }
        pLight->SwitchOff();
        return true;
    }
    if (vParameters[0] == "all")
    {
        vector<ISwitchOnOffObject*> vpObjects;
        if (!pContext->m_ActiveModel.GetObjectsByType<ISwitchOnOffObject>(OUT vpObjects))
            pContext->m_Console << "Светильников не найдено" << endl;
        else
        {
            for (vector<ISwitchOnOffObject*>::iterator pIter = vpObjects.begin(); pIter != vpObjects.end(); ++pIter)
                (*pIter)->SwitchOff();
        }
        return true;
    }
    pContext->m_Console << "Указанный светильник не найден" << endl;
    return false;
}