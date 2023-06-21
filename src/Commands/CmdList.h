#pragma once
#include "_Command.h"

class CCmdList : public ICommand
{
public:
    CCmdList(){}

    virtual const char* Name()
    {
        return "list";
    }
    virtual const char* Hint() // вернуть короткое описание команды
    {
        return "Отобразить список объектов или свойства объекта";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "использование:\n"
                   "list               - вывести список установленных объектов\n"
                   "list <имя объекта> - вывести свойства указанного объекта\n";
        return ICommand::Help(pContext, vParameters); // стандартное сообщение об отсутсвии описания для переданного набора параметров
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

