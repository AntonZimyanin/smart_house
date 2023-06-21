#pragma once
#include "_Command.h"

class CCmdExit : public ICommand
{
public:
    CCmdExit(){}

    virtual const char* Name()
    {
        return "exit";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Завершение работы программы";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "exit\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

