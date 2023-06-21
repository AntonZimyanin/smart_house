#pragma once
#include "_Command.h"

class CCmdDemo : public ICommand
{
public:
    CCmdDemo(){}

    virtual const char* Name()
    {
        return "demo";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Заменить схему объектов на демонстрационную";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "demo\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

