#pragma once
#include "_Command.h"

class CCmdStore : public ICommand
{
public:
    CCmdStore(){}

    virtual const char* Name()
    {
        return "store";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Сохранить расположение объектов в указанный файл";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "store txt <filename> - сохранить в текстовый файл\n"
                   "store bin <filename> - сохранить в бинарный файл\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};
