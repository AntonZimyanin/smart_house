#pragma once
#include "_Command.h"

class CCmdOpen : public ICommand
{
public:
    CCmdOpen(){}
    virtual const char* Name()
    {
        return "open";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Открыть дверь";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "open <имя двери> - открыть указанную дверь\n"
                   "open all         - открыть все двери\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

