#pragma once
#include "_Command.h"

class CCmdHelp : public ICommand
{
public:
    CCmdHelp(){}

    virtual const char* Name()
    {
        return "help";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Отобразить список доступных команд или описание указанной команды";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "help                    - отобразить список доступных команд\n"
                   "help <название команды> - отобразить описание команды\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

