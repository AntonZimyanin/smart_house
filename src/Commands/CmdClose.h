#pragma once
#include "_Command.h"

class CCmdClose : public ICommand
{
public:
    CCmdClose(){}

    virtual const char* Name()
    {
        return "close";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Закрыть дверь";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "close <имя двери> - закрыть указанную дверь\n"
                   "close all         - закрыть все двери\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

