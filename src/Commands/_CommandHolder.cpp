#include "../stdafx.h"
#include "string.h"
#include "_CommandHolder.h"
#include "CmdHelp.h"
#include "CmdDemo.h"
#include "CmdList.h"
#include "CmdCreate.h"
#include "CmdDelete.h"
#include "CmdSwitchOn.h"
#include "CmdSwitchOff.h"
#include "CmdOpen.h"
#include "CmdClose.h"
#include "CmdVolume.h"
#include "CmdMusic.h"
#include "CmdMusicPosition.h"
#include "CmdStore.h"
#include "CmdLoad.h"
#include "CmdExit.h"
#include <assert.h>

CCommandHolder::CCommandHolder()
               : m_Commands()
{
    RegCommand(new CCmdHelp());
    RegCommand(new CCmdDemo());
    RegCommand(new CCmdList());
    RegCommand(new CCmdCreate());
    RegCommand(new CCmdDelete());
    RegCommand(new CCmdSwitchOn());
    RegCommand(new CCmdSwitchOff());
    RegCommand(new CCmdOpen());
    RegCommand(new CCmdClose());
    RegCommand(new CCmdVolume());
    RegCommand(new CCmdMusic());
    RegCommand(new CCmdMusicPosition());
    RegCommand(new CCmdStore());
    RegCommand(new CCmdLoad());
    RegCommand(new CCmdExit());
}

void CCommandHolder::RegCommand(ICommand* pCmd)
{
    stringEx name(pCmd->Name());
    name.strlwr();
    assert(m_Commands.count(name) == 0); // проверяем, что нет уже зарегистрированной команды с тем же именем и, если находим,
                                         // то пытаемся привлеч внимание программиста
    m_Commands[name] = pCmd;
}

CCommandHolder::~CCommandHolder()
{
    for (map<string, ICommand*>::iterator iter = m_Commands.begin(); iter != m_Commands.end(); ++iter)
        delete iter->second;
    m_Commands.clear();
}

ICommand* CCommandHolder::FindCommand(const char* pName)
{
    stringEx name(pName);
    name.strlwr();
    map<string, ICommand*>::const_iterator iter = m_Commands.find(name);
    if (iter == m_Commands.end())
        return nullptr;
    return iter->second;
}
