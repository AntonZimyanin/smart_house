#pragma once
#include "_Command.h"


class CCmdSwitchOn : public ICommand
{
public:
    CCmdSwitchOn(){}

    virtual const char* Name()
    {
        return "on";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Включить светильник";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
				   "on <имя светильника> - включить выбранный светильник\n"
		           "on all               - включить все светильники\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

