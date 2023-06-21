#pragma once

#include "_Command.h"
using namespace std;

class CCommandHolder
{
private:
    map<string, ICommand*> m_Commands;
    void RegCommand(ICommand*);
public:
    CCommandHolder();
    virtual ~CCommandHolder();

    ICommand* FindCommand(const char* pName);

    friend class CCmdHelp;
};

