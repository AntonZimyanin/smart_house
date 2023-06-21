#include "../stdafx.h"
#include "CmdExit.h"
#include "../Context.h"

bool CCmdExit::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() > 0)
    {
        pContext->m_Console << "Неподдерживаемый параметр команды" << endl;
        return false;
    }
    pContext->Exit();
    return true;
}