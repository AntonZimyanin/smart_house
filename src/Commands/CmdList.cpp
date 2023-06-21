#include "../stdafx.h"
#include "CmdList.h"
#include <iostream>
#include "../Context.h"
using namespace std;

bool CCmdList::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 1)
    {
        CBaseObject* pObj = pContext->m_ActiveModel.FindObject(vParameters[0].c_str());
        if (!pObj)
        {
            pContext->m_Console << "Указанный объект не найден" << endl;
            return false;
        }
        pObj->PrintProperties(pContext->m_Console);
        return true;
    }
    if (vParameters.size() > 0)
    {
        pContext->m_Console << "Неподдерживаемый параметр команды" << endl;
        return false;
    }
    pContext->m_ActiveModel.PrintListOfObjects(pContext->m_Console);
    return true;
}