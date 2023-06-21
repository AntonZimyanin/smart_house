#pragma once
#include "_Command.h"
class CCmdSwitchOff : public ICommand
{
public:
    CCmdSwitchOff(){}

    virtual const char* Name()
    {
        return "off";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Выключить светильник";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
		           "off <имя светильника> - выключить выбранный светильник\n"
		           "off all               - выключить все светильники\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

